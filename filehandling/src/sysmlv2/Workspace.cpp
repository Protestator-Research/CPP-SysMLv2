//
// Multi-file workspace. See Workspace.h.
//
#include <sysmlv2/Workspace.h>

#include "resolution/Resolver.h"

#include <kerml/parser/KerMlErrorListener.h>
#include <kerml/parser/KerMLLexer.h>
#include <kerml/parser/KerMLParser.h>
#include <kerml/parser/KerMlListenerImplementation.h>

#include <sysmlv2/parser/SysMLv2ErrorListener.h>
#include <sysmlv2/parser/SysMLv2Error.h>
#include <sysmlv2/parser/SysMLv2ListenerImplementation.h>
#include <sysmlv2/parser/SysMLv2Lexer.h>
#include <sysmlv2/parser/SysMLv2Parser.h>

#include <kerml/kernel/packages/Package.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>

#include <antlr4-common.h>
#include <BailErrorStrategy.h>
#include <DefaultErrorStrategy.h>
#include <Exceptions.h>
#include <atn/ParserATNSimulator.h>
#include <atn/PredictionMode.h>
#include <tree/ParseTreeWalker.h>
#include <boost/uuid/uuid_generators.hpp>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace {
    /**
     * Two-stage parse (the standard ANTLR 4 pattern). Stage one runs the parser in SLL prediction mode with the
     * BailErrorStrategy and without error listeners: it is considerably faster than full LL prediction, and for every
     * input it accepts it yields the same parse tree as full LL. If it hits a syntax error, or an SLL conflict
     * that only full-context prediction can resolve, it throws a ParseCancellationException. Stage two then rewinds
     * the token stream, resets the parser and parses again in LL mode with the DefaultErrorStrategy and the given
     * error listener, so that syntax errors are reported and recovered from exactly as in a single LL pass. Lexer
     * errors are reported by the lexer's own listeners while the tokens are fetched, once, in either stage.
     */
    template <class ParserType, class StartContext>
    StartContext* parseTwoStage(ParserType& parser, antlr4::CommonTokenStream& tokens,
                                antlr4::ANTLRErrorListener& errorListener, StartContext* (ParserType::*startRule)()) {
        auto* simulator = parser.template getInterpreter<antlr4::atn::ParserATNSimulator>();
        parser.removeErrorListeners();
        parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());
        simulator->setPredictionMode(antlr4::atn::PredictionMode::SLL);
        try {
            return (parser.*startRule)();
        } catch (const antlr4::ParseCancellationException&) {
            tokens.seek(0);
            parser.reset();
            parser.setErrorHandler(std::make_shared<antlr4::DefaultErrorStrategy>());
            simulator->setPredictionMode(antlr4::atn::PredictionMode::LL);
            parser.addErrorListener(&errorListener);
            return (parser.*startRule)();
        }
    }

    bool endsWith(const std::string& text, const std::string& suffix) {
        return text.size() >= suffix.size() && text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
}

namespace SysMLv2::Files {

    struct Workspace::Impl {
        struct Source {
            std::string name;
            SourceLanguage language = SourceLanguage::SysML;
            std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
            std::vector<std::shared_ptr<ParserError>> errors;
            ResolutionData data;
            std::vector<std::shared_ptr<KerML::Entities::Element>> topLevel;
            std::shared_ptr<KerML::Entities::Namespace> root;
        };

        std::vector<std::unique_ptr<Source>> sources;
        std::vector<UnresolvedReferenceInfo> unresolved;
        std::vector<UnresolvedReferenceInfo> notAttempted;
        std::unique_ptr<Detail::Resolver> resolver;
        size_t resolvedCount = 0;

        static std::shared_ptr<ParserError> makeError(ErrorType type, const std::string& message, int line, int column,
                                                       const std::string& source) {
            return std::make_shared<ParserError>(boost::uuids::random_generator()(), "", type, message, line, column, source);
        }

        static void computeTopLevel(Source& source) {
            std::unordered_set<const KerML::Entities::Element*> owned;
            for (const auto& element : source.elements) {
                if (!element) continue;
                for (const auto& child : element->ownedElements()) owned.insert(child.get());
            }
            if (source.data.root) {
                for (const auto& child : source.data.root->ownedElements()) source.topLevel.push_back(child);
            }
            for (const auto& element : source.elements) {
                if (!element || owned.count(element.get()) != 0) continue;
                if (element == source.data.root) continue;
                source.topLevel.push_back(element);
            }
        }

        // The root namespace of a source: the one the KerML listener created, or, for SysML v2 (where the ownership builder creates
        // it and only the top-level elements refer to it), the namespace that owns an element of the source without being one of them.
        static void findRoot(Source& source) {
            source.root = std::dynamic_pointer_cast<KerML::Entities::Namespace>(source.data.root);
            if (source.root) return;
            std::unordered_set<const KerML::Entities::Element*> own;
            for (const auto& element : source.elements) own.insert(element.get());
            for (const auto& element : source.elements) {
                if (!element) continue;
                auto owner = std::dynamic_pointer_cast<KerML::Entities::Namespace>(element->owner());
                if (owner && own.count(owner.get()) == 0) {
                    source.root = std::move(owner);
                    return;
                }
            }
        }

        void parseKerML(Source& source, const std::string& text) {
            antlr4::ANTLRInputStream input(text);
            auto errorListener = std::make_unique<KerMLErrorListener>();
            auto listener = std::make_unique<KerMLListenerImplementation>();
            KerMLLexer lexer(&input);
            lexer.addErrorListener(errorListener.get());
            antlr4::CommonTokenStream tokens(&lexer);
            KerMLParser parser(&tokens);

            // Parse first, then walk the completed tree with the listener. Running the listener
            // during parsing (addParseListener) exposed it to partially-built, still-recovering
            // contexts; walking a finished tree afterwards does not.
            KerMLParser::StartContext* tree = parseTwoStage(parser, tokens, *errorListener, &KerMLParser::start);

            const auto syntaxErrors = errorListener->getSyntaxErrors();
            source.errors.reserve(syntaxErrors.size());
            for (const auto& error : syntaxErrors) {
                source.errors.push_back(makeError(ErrorType::ERROR, error->message(), error->line(), error->positionInLine(), source.name));
            }

            try {
                antlr4::tree::ParseTreeWalker::DEFAULT.walk(listener.get(), tree);
                source.elements = listener->getElements();
                source.data = listener->takeResolutionData();
            } catch (const std::exception& ex) {
                source.errors.push_back(makeError(ErrorType::ERROR, std::string("internal: ") + ex.what(), -1, -1, source.name));
            } catch (...) {
                source.errors.push_back(makeError(ErrorType::ERROR, "internal: unknown exception while walking the KerML parse tree", -1, -1, source.name));
            }
        }

        void parseSysML(Source& source, const std::string& text) {
            antlr4::ANTLRInputStream input(text);
            SysMLErrorListenener errorListener;
            SysMLv2ListenerImplementation listener;
            SysMLv2Lexer lexer(&input);
            lexer.addErrorListener(&errorListener);
            antlr4::CommonTokenStream tokens(&lexer);
            SysMLv2Parser parser(&tokens);

            // Parse first, then walk the completed tree with the listener (see parseKerML for why).
            SysMLv2Parser::StartContext* tree = parseTwoStage(parser, tokens, errorListener, &SysMLv2Parser::start);

            const auto syntaxErrors = errorListener.getSyntaxErrors();
            source.errors.reserve(syntaxErrors.size());
            for (const auto& error : syntaxErrors) {
                source.errors.push_back(makeError(ErrorType::ERROR, error->message(), error->line(), error->positionInLine(), source.name));
            }

            try {
                antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
                source.elements = listener.getElements();
                source.data = listener.takeResolutionData();
            } catch (const std::exception& ex) {
                source.errors.push_back(makeError(ErrorType::ERROR, std::string("internal: ") + ex.what(), -1, -1, source.name));
            } catch (...) {
                source.errors.push_back(makeError(ErrorType::ERROR, "internal: unknown exception while walking the SysML v2 parse tree", -1, -1, source.name));
            }
        }
    };

    Workspace::Workspace() : impl_(std::make_unique<Impl>()) {}

    Workspace::~Workspace() = default;

    size_t Workspace::addText(std::string text, std::string sourceName, SourceLanguage language) {
        if (language == SourceLanguage::Auto) {
            language = endsWith(sourceName, ".kerml") ? SourceLanguage::KerML : SourceLanguage::SysML;
        }
        auto source = std::make_unique<Impl::Source>();
        source->name = std::move(sourceName);
        source->language = language;
        const size_t index = impl_->sources.size();
        if (language == SourceLanguage::KerML) {
            impl_->parseKerML(*source, text);
        } else {
            impl_->parseSysML(*source, text);
        }
        for (auto& reference : source->data.references) {
            reference.source = index;
        }
        Impl::computeTopLevel(*source);
        Impl::findRoot(*source);
        impl_->sources.push_back(std::move(source));
        impl_->resolver.reset();
        return index;
    }

    size_t Workspace::addFile(const std::string& path) {
        std::ifstream in(path);
        if (!in) {
            auto source = std::make_unique<Impl::Source>();
            source->name = path;
            source->language = endsWith(path, ".kerml") ? SourceLanguage::KerML : SourceLanguage::SysML;
            source->errors.push_back(Impl::makeError(ErrorType::ERROR, "could not open file: " + path, -1, -1, path));
            impl_->sources.push_back(std::move(source));
            impl_->resolver.reset();
            return impl_->sources.size() - 1;
        }
        std::stringstream buffer;
        buffer << in.rdbuf();
        return addText(buffer.str(), path, SourceLanguage::Auto);
    }

    size_t Workspace::loadLibrary(const std::string& directory) {
        namespace fs = std::filesystem;
        std::vector<std::string> files;
        std::error_code ec;
        if (!fs::exists(directory, ec)) return 0;
        for (fs::recursive_directory_iterator it(directory, ec), end; !ec && it != end; it.increment(ec)) {
            if (!it->is_regular_file(ec)) continue;
            const auto extension = it->path().extension().string();
            if (extension == ".kerml" || extension == ".sysml") files.push_back(it->path().string());
        }
        std::sort(files.begin(), files.end());
        for (const auto& file : files) addFile(file);
        return files.size();
    }

    void Workspace::resolve() {
        std::vector<Detail::SourceInput> inputs;
        std::vector<PendingReference*> all;
        inputs.reserve(impl_->sources.size());
        for (auto& source : impl_->sources) {
            inputs.push_back({&source->elements, &source->data});
            for (auto& reference : source->data.references) all.push_back(&reference);
        }
        impl_->resolver = std::make_unique<Detail::Resolver>(std::move(inputs));
        impl_->resolver->run(all);

        impl_->unresolved.clear();
        impl_->notAttempted.clear();
        impl_->resolvedCount = 0;
        for (size_t index = 0; index < impl_->sources.size(); ++index) {
            const auto& source = *impl_->sources[index];
            for (const auto& reference : source.data.references) {
                if (reference.resolved) {
                    ++impl_->resolvedCount;
                    continue;
                }
                UnresolvedReferenceInfo info;
                info.name = reference.name;
                info.kind = reference.kind;
                info.role = reference.role;
                info.sourceName = source.name;
                info.line = reference.line;
                info.column = reference.column;
                info.source = index;
                info.context = reference.context;
                info.placeholder = reference.placeholder;
                (reference.role == ReferenceRole::NotAttempted ? impl_->notAttempted : impl_->unresolved).push_back(std::move(info));
            }
        }
    }

    size_t Workspace::sourceCount() const {
        return impl_->sources.size();
    }

    const std::string& Workspace::sourceName(size_t source) const {
        return impl_->sources.at(source)->name;
    }

    size_t Workspace::findSource(const std::string& name) const {
        for (size_t index = 0; index < impl_->sources.size(); ++index) {
            if (impl_->sources[index]->name == name) return index;
        }
        return impl_->sources.size();
    }

    std::shared_ptr<KerML::Entities::Namespace> Workspace::rootNamespace(size_t source) const {
        return impl_->sources.at(source)->root;
    }

    const std::vector<std::shared_ptr<KerML::Entities::Element>>& Workspace::elements(size_t source) const {
        return impl_->sources.at(source)->elements;
    }

    std::vector<std::shared_ptr<KerML::Entities::Element>> Workspace::elements() const {
        std::vector<std::shared_ptr<KerML::Entities::Element>> all;
        for (const auto& source : impl_->sources) all.insert(all.end(), source->elements.begin(), source->elements.end());
        return all;
    }

    std::vector<std::shared_ptr<KerML::Entities::Element>> Workspace::rootPackages() const {
        std::vector<std::shared_ptr<KerML::Entities::Element>> packages;
        for (const auto& source : impl_->sources) {
            for (const auto& element : source->topLevel) {
                if (std::dynamic_pointer_cast<KerML::Entities::Package>(element)) packages.push_back(element);
            }
        }
        return packages;
    }

    const std::vector<std::shared_ptr<ParserError>>& Workspace::errors(size_t source) const {
        return impl_->sources.at(source)->errors;
    }

    std::vector<std::shared_ptr<ParserError>> Workspace::errors() const {
        std::vector<std::shared_ptr<ParserError>> all;
        for (const auto& source : impl_->sources) all.insert(all.end(), source->errors.begin(), source->errors.end());
        return all;
    }

    const std::vector<UnresolvedReferenceInfo>& Workspace::unresolvedReferences() const {
        return impl_->unresolved;
    }

    const std::vector<UnresolvedReferenceInfo>& Workspace::notAttemptedReferences() const {
        return impl_->notAttempted;
    }

    std::vector<std::shared_ptr<ParserError>> Workspace::unresolvedAsWarnings(size_t source) const {
        std::vector<std::shared_ptr<ParserError>> warnings;
        for (const auto& info : impl_->unresolved) {
            if (info.source != source) continue;
            std::string kind;
            switch (info.kind) {
                case ReferenceKind::Type: kind = "type"; break;
                case ReferenceKind::Classifier: kind = "classifier"; break;
                case ReferenceKind::Feature: kind = "feature"; break;
                case ReferenceKind::Namespace: kind = "namespace"; break;
                default: kind = "element"; break;
            }
            warnings.push_back(Impl::makeError(ErrorType::WARNING, "unresolved reference to " + kind + " '" + info.name + "'",
                                               info.line, info.column, info.sourceName));
        }
        return warnings;
    }

    size_t Workspace::referenceCount() const {
        size_t count = 0;
        for (const auto& source : impl_->sources) count += source->data.references.size();
        return count;
    }

    size_t Workspace::resolvedReferenceCount() const {
        return impl_->resolvedCount;
    }

    std::shared_ptr<KerML::Entities::Element> Workspace::find(const std::string& name,
                                                              const std::shared_ptr<KerML::Entities::Element>& scope,
                                                              ReferenceKind kind) const {
        if (!impl_->resolver) {
            // Sources were added since the last resolve(): build the index without resolving anything.
            std::vector<Detail::SourceInput> inputs;
            for (auto& source : impl_->sources) inputs.push_back({&source->elements, &source->data});
            impl_->resolver = std::make_unique<Detail::Resolver>(std::move(inputs));
        }
        return impl_->resolver->find(name, scope, kind, true);
    }
}
