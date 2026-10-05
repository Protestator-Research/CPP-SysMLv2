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
#include <exception>
#include <iostream>
#include <mutex>
#include <functional>
#if defined(_WIN32)
#include <windows.h>
#elif !defined(__EMSCRIPTEN__)
#include <pthread.h>
#endif
#include <filesystem>
#include <fstream>
#include <future>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace {
    /// Stack of the thread that parses a text. The parser and the listener walk recurse once per nesting level of the text (and the
    /// parser's prediction recurses deeply for runs of operators), which the 8 MB of an ordinary stack does not always survive.
    constexpr size_t ParseStackSize = size_t(512) << 20;

    /// Runs @p function on a thread with a large stack and waits for it. Where no thread can be created (and with Emscripten, which
    /// has one stack for everything, see STACK_SIZE in check/cmake/Emscripten.cmake) it runs on the calling thread.
    void runOnLargeStack(const std::function<void()>& function) {
#if defined(__EMSCRIPTEN__)
        function();
#elif defined(_WIN32)
        struct Context { const std::function<void()>* function; };
        Context context{&function};
        HANDLE thread = CreateThread(nullptr, ParseStackSize, [](LPVOID argument) -> DWORD {
            (*static_cast<Context*>(argument)->function)();
            return 0;
        }, &context, STACK_SIZE_PARAM_IS_A_RESERVATION, nullptr);
        if (thread == nullptr) {
            function();
            return;
        }
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
#else
        pthread_attr_t attributes;
        pthread_t thread;
        bool started = false;
        if (pthread_attr_init(&attributes) == 0) {
            if (pthread_attr_setstacksize(&attributes, ParseStackSize) == 0) {
                started = pthread_create(&thread, &attributes, [](void* argument) -> void* {
                    (*static_cast<const std::function<void()>*>(argument))();
                    return nullptr;
                }, const_cast<std::function<void()>*>(&function)) == 0;
            }
            pthread_attr_destroy(&attributes);
        }
        if (started) {
            pthread_join(thread, nullptr);
        } else {
            static std::once_flag warned;
            std::call_once(warned, [] {
                std::cerr << "sysmlv2parser: cannot create a thread with a " << (ParseStackSize >> 20)
                          << " MB stack; parsing on the calling thread (deeply nested texts can overflow its stack)\n";
            });
            function();
        }
#endif
    }

    /// Thrown by DeadlineTokenStream; not derived from ParseCancellationException, which parseTwoStage handles.
    struct DeadlineReached {};

    /**
     * A token stream that checks a deadline while the parser reads tokens (every prediction step reads them), so that a parse that
     * runs for too long can be abandoned by throwing DeadlineReached.
     */
    class DeadlineTokenStream : public antlr4::CommonTokenStream {
    public:
        DeadlineTokenStream(antlr4::TokenSource* source, std::optional<std::chrono::steady_clock::time_point> deadline)
            : antlr4::CommonTokenStream(source), Deadline(deadline) {}

        // Only a look-ahead (k >= 1) and consume() throw. LT(-1) is called by Parser::exitRule from the destructor of a scope guard,
        // which must never throw (the exception would end the process).
        antlr4::Token* LT(ssize_t k) override {
            if (k >= 1) check();
            return antlr4::CommonTokenStream::LT(k);
        }
        size_t LA(ssize_t i) override {
            if (i >= 1) check();
            return antlr4::CommonTokenStream::LA(i);
        }
        void consume() override {
            check();
            antlr4::CommonTokenStream::consume();
        }

    private:
        void check() {
            if (Deadline && (++Calls & 0xFF) == 0 && std::chrono::steady_clock::now() > *Deadline) throw DeadlineReached();
        }
        std::optional<std::chrono::steady_clock::time_point> Deadline;
        size_t Calls = 0;
    };

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
            int level = 0;
            std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
            std::vector<std::shared_ptr<ParserError>> errors;
            ResolutionData data;
            std::vector<std::shared_ptr<KerML::Entities::Element>> topLevel;
            std::shared_ptr<KerML::Entities::Namespace> root;
        };

        std::vector<std::shared_ptr<Source>> sources;
        std::optional<std::chrono::steady_clock::time_point> deadline;
        std::vector<UnresolvedReferenceInfo> unresolved;
        std::vector<UnresolvedReferenceInfo> notAttempted;
        std::unique_ptr<Detail::Resolver> resolver;
        size_t resolvedCount = 0;

        /// ANTLR messages can contain the whole list of expected tokens; they are cut to this many bytes (at a character boundary).
        static constexpr size_t MaxMessageLength = 200;

        static std::string shortened(const std::string& message) {
            if (message.size() <= MaxMessageLength) return message;
            size_t end = MaxMessageLength;
            while (end > 0 && (static_cast<unsigned char>(message[end]) & 0xC0) == 0x80) --end;  // do not split a UTF-8 sequence
            return message.substr(0, end) + "...";
        }

        static std::shared_ptr<ParserError> makeError(ErrorType type, const std::string& message, int line, int column,
                                                       const std::string& source) {
            return std::make_shared<ParserError>(boost::uuids::random_generator()(), "", type, message, line, column, source);
        }

        static void computeTopLevel(std::shared_ptr<Source> source) {
            std::unordered_set<std::shared_ptr<KerML::Entities::Element>> owned;
            for (const auto& element : source->elements) {
                if (!element) continue;

                const auto& ownedElements = element->ownedElements();

                for (const auto& child : ownedElements)
                    owned.insert(child);
            }
            if (source->data.root) {
                for (const auto& child : source->data.root->ownedElements()) source->topLevel.push_back(child);
            }
            for (const auto& element : source->elements) {
                if (!element || owned.count(element) != 0) continue;
                if (element == source->data.root) continue;
                source->topLevel.push_back(element);
            }
        }

        // The root namespace of a source: the one the KerML listener created, or, for SysML v2 (where the ownership builder creates
        // it and only the top-level elements refer to it), the namespace that owns an element of the source without being one of them.
        static void findRoot(std::shared_ptr<Source> source) {
            source->root = std::dynamic_pointer_cast<KerML::Entities::Namespace>(source->data.root);
            if (source->root) return;
            std::unordered_set<std::shared_ptr<KerML::Entities::Element>> own;
            for (const auto& element : source->elements) own.insert(element);
            for (const auto& element : source->elements) {
                if (!element) continue;
                auto owner = std::dynamic_pointer_cast<KerML::Entities::Namespace>(element->owner());
                if (owner && own.count(owner) == 0) {
                    source->root = std::move(owner);
                    return;
                }
            }
        }

        void parseKerML(std::shared_ptr<Source> source, const std::string& text) {
            antlr4::ANTLRInputStream input(text);
            auto errorListener = std::make_unique<KerMLErrorListener>();
            auto listener = std::make_unique<KerMLListenerImplementation>();
            KerMLLexer lexer(&input);
            lexer.removeErrorListeners();  // no ConsoleErrorListener: nothing is written to stderr
            lexer.addErrorListener(errorListener.get());
            DeadlineTokenStream tokens(&lexer, deadline);
            KerMLParser parser(&tokens);

            // Parse first, then walk the completed tree with the listener. Running the listener
            // during parsing (addParseListener) exposed it to partially-built, still-recovering
            // contexts; walking a finished tree afterwards does not.
            KerMLParser::StartContext* tree = parseTwoStage(parser, tokens, *errorListener, &KerMLParser::start);

            const auto syntaxErrors = errorListener->getSyntaxErrors();
            source->errors.reserve(syntaxErrors.size());
            for (const auto& error : syntaxErrors) {
                source->errors.push_back(makeError(ErrorType::ERROR, shortened(error->message()), error->line(), error->positionInLine(), source->name));
            }

            try {
                antlr4::tree::ParseTreeWalker::DEFAULT.walk(listener.get(), tree);
                source->elements = listener->getElements();
                source->data = listener->takeResolutionData();
            } catch (const std::exception& ex) {
                source->errors.push_back(makeError(ErrorType::ERROR, std::string("internal: ") + ex.what(), -1, -1, source->name));
            } catch (...) {
                source->errors.push_back(makeError(ErrorType::ERROR, "internal: unknown exception while walking the KerML parse tree", -1, -1, source->name));
            }
        }

        void parseSysML(std::shared_ptr<Source> source, const std::string& text) {
            antlr4::ANTLRInputStream input(text);
            SysMLErrorListenener errorListener;
            SysMLv2ListenerImplementation listener;
            SysMLv2Lexer lexer(&input);
            lexer.removeErrorListeners();  // no ConsoleErrorListener: nothing is written to stderr
            lexer.addErrorListener(&errorListener);
            DeadlineTokenStream tokens(&lexer, deadline);
            SysMLv2Parser parser(&tokens);

            // Parse first, then walk the completed tree with the listener (see parseKerML for why).
            SysMLv2Parser::StartContext* tree = parseTwoStage(parser, tokens, errorListener, &SysMLv2Parser::start);

            const auto syntaxErrors = errorListener.getSyntaxErrors();
            source->errors.reserve(syntaxErrors.size());
            for (const auto& error : syntaxErrors) {
                source->errors.push_back(makeError(ErrorType::ERROR, shortened(error->message()), error->line(), error->positionInLine(), source->name));
            }

            try {
                antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
                source->elements = listener.getElements();
                source->data = listener.takeResolutionData();
            } catch (const std::exception& ex) {
                source->errors.push_back(makeError(ErrorType::ERROR, std::string("internal: ") + ex.what(), -1, -1, source->name));
            } catch (...) {
                source->errors.push_back(makeError(ErrorType::ERROR, "internal: unknown exception while walking the SysML v2 parse tree", -1, -1, source->name));
            }
        }

        /// Breaks the reference cycles of the model of a source that is thrown away (see KerML::Entities::disposeLinks), so that it is
        /// freed as soon as nobody else holds a pointer to it. The elements are detached afterwards.
        static void dispose(Source& source) {
            std::unordered_set<KerML::Entities::Element*> seen;
            std::vector<std::shared_ptr<KerML::Entities::Element>> pending;
            const auto add = [&](const std::shared_ptr<KerML::Entities::Element>& element) {
                if (element && seen.insert(element.get()).second) pending.push_back(element);
            };
            for (const auto& element : source.elements) add(element);
            for (const auto& element : source.topLevel) add(element);
            add(source.root);
            add(source.data.root);
            for (const auto& reference : source.data.references) {
                add(reference.placeholder);
                add(reference.context);
                add(reference.specific);
            }
            for (size_t index = 0; index < pending.size(); ++index) {
                for (const auto& child : pending[index]->ownedElements()) add(child);
            }
            for (const auto& element : pending) KerML::Entities::disposeLinks(*element);
            source.elements.clear();
            source.topLevel.clear();
            source.root.reset();
            source.data = ResolutionData();
        }

        /// Parses @p text into a new source whose references are recorded for the source index @p index.
        std::shared_ptr<Source> makeSource(const std::string& text, std::string name, SourceLanguage language, size_t index, int level) {
            auto source = std::make_shared<Source>();
            source->level = level;
            source->name = std::move(name);
            source->language = language;
            std::exception_ptr failure;
            runOnLargeStack([&] {
                try {
                    if (language == SourceLanguage::KerML) {
                        parseKerML(source, text);
                    } else {
                        parseSysML(source, text);
                    }
                } catch (...) {
                    failure = std::current_exception();   // rethrown on the calling thread
                }
            });
            if (failure) {
                try {
                    std::rethrow_exception(failure);
                } catch (const DeadlineReached&) {
                    throw ParseTimeout();
                }
            }
            for (auto& reference : source->data.references) {
                reference.source = index;
            }
            computeTopLevel(source);
            findRoot(source);
            return source;
        }
    };

    Workspace::Workspace() : impl_(std::make_unique<Impl>()) {}

    Workspace::~Workspace() = default;

    void Workspace::setParseDeadline(std::chrono::steady_clock::time_point deadline) {
        impl_->deadline = deadline;
    }

    void Workspace::clearParseDeadline() {
        impl_->deadline.reset();
    }

    size_t Workspace::addText(std::string text, std::string sourceName, SourceLanguage language, int level) {
        if (language == SourceLanguage::Auto) {
            language = endsWith(sourceName, ".kerml") ? SourceLanguage::KerML : SourceLanguage::SysML;
        }
        const size_t index = impl_->sources.size();
        impl_->sources.push_back(impl_->makeSource(text, std::move(sourceName), language, index, level));
        impl_->resolver.reset();
        return index;
    }

    void Workspace::replaceSource(size_t source, std::string text, SourceLanguage language) {
        const auto old = impl_->sources.at(source);
        if (language == SourceLanguage::Auto) language = old->language;

        // The new source is built first: if parsing throws, the workspace is unchanged.
        auto replacement = impl_->makeSource(text, old->name, language, source, old->level);

        // The references that the old source had resolved no longer count; resolve() recounts everything.
        for (const auto& reference : old->data.references) {
            if (reference.resolved && impl_->resolvedCount > 0) --impl_->resolvedCount;
        }
        const auto belongsToSource = [source](const UnresolvedReferenceInfo& info) { return info.source == source; };
        impl_->unresolved.erase(std::remove_if(impl_->unresolved.begin(), impl_->unresolved.end(), belongsToSource), impl_->unresolved.end());
        impl_->notAttempted.erase(std::remove_if(impl_->notAttempted.begin(), impl_->notAttempted.end(), belongsToSource), impl_->notAttempted.end());

        // The new source takes the index and the name of the old one; the other sources are not touched.
        impl_->sources[source] = std::move(replacement);
        impl_->resolver.reset();
        Impl::dispose(*old);
    }

    size_t Workspace::addFile(const std::string& path, int level) {
        std::ifstream in(path);
        if (!in) {
            auto source = std::make_unique<Impl::Source>();
            source->name = path;
            source->language = endsWith(path, ".kerml") ? SourceLanguage::KerML : SourceLanguage::SysML;
            source->level = level;
            source->errors.push_back(Impl::makeError(ErrorType::ERROR, "could not open file: " + path, -1, -1, path));
            impl_->sources.push_back(std::move(source));
            impl_->resolver.reset();
            return impl_->sources.size() - 1;
        }
        std::stringstream buffer;
        buffer << in.rdbuf();
        return addText(buffer.str(), path, SourceLanguage::Auto, level);
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
            inputs.push_back({&source->elements, &source->data, source->level});
            for (auto& reference : source->data.references) all.push_back(&reference);
        }
        impl_->resolver = std::make_unique<Detail::Resolver>(std::move(inputs));
        try {
            impl_->resolver->run(all, impl_->deadline);
        } catch (const Detail::ResolveDeadlineReached&) {
            impl_->resolver.reset();   // what was resolved stays resolved; the unresolved list is not updated
            throw ParseTimeout();
        }

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

    void Workspace::setSourceLevel(size_t source, int level) {
        impl_->sources.at(source)->level = level;
        impl_->resolver.reset();
    }

    int Workspace::sourceLevel(size_t source) const {
        return impl_->sources.at(source)->level;
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

    std::vector<std::string> Workspace::referenceNames(size_t source) const {
        std::vector<std::string> names;
        for (const auto& reference : impl_->sources.at(source)->data.references) {
            if (reference.role != ReferenceRole::NotAttempted) names.push_back(reference.name);
        }
        return names;
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
            for (auto& source : impl_->sources) inputs.push_back({&source->elements, &source->data, source->level});
            impl_->resolver = std::make_unique<Detail::Resolver>(std::move(inputs));
        }
        return impl_->resolver->find(name, scope, kind, true);
    }
}
