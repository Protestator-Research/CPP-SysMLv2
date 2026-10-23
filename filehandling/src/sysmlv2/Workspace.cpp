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
#include <sysmlv2/ParserError.h>
#include <sysmlv2/xmi/XmiReader.h>
#include <sysmlv2/xmi/XmiWriter.h>

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
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#elif !defined(__EMSCRIPTEN__)
#include <pthread.h>
#endif
#include <filesystem>
#include <fstream>
#include <future>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

namespace {
    /// Stack of the thread that parses a text. The parser and the listener walk recurse once per nesting level of the text (and the
    /// parser's prediction recurses deeply for runs of operators), which the 8 MB of an ordinary stack does not always survive.
    [[maybe_unused]] constexpr size_t ParseStackSize = size_t(512) << 20;

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

    /// The language a source is written in, judged by its name: ".kerml" is KerML, ".kermlx", ".sysmlx" and ".xmi" are XMI files, the rest SysML v2.
    SysMLv2::Files::SourceLanguage languageOf(const std::string& name) {
        using SysMLv2::Files::SourceLanguage;
        if (endsWith(name, ".kerml")) return SourceLanguage::KerML;
        if (endsWith(name, ".kermlx") || endsWith(name, ".sysmlx") || endsWith(name, ".xmi")) return SourceLanguage::Xmi;
        return SourceLanguage::SysML;
    }

    /// A path as UTF-8 (the paths between the workspace and the XMI writer are UTF-8, whatever the narrow encoding of the system is); with
    /// "/" as separator if @p generic.
    std::string utf8(const std::filesystem::path& path, bool generic = false) {
        const auto text = generic ? path.generic_u8string() : path.u8string();
        return std::string(text.begin(), text.end());
    }

    /// The lower case of a code point, independent of the locale of the program (std::towlower follows the global C locale, which would make
    /// the keys and the layout of an export depend on it): a fixed simple case folding of ASCII, Latin-1 Supplement, Latin Extended-A, Greek and
    /// Cyrillic letters; everything else is kept.
    char32_t foldedCode(char32_t c) {
        if (c < 0x80) return c >= U'A' && c <= U'Z' ? c + 0x20 : c;
        if (c >= 0xC0 && c <= 0xDE) return c == 0xD7 ? c : c + 0x20;                       // Latin-1 Supplement
        if (c >= 0x100 && c <= 0x17F) {                                                      // Latin Extended-A
            if (c == 0x130 || c == 0x131 || c == 0x138 || c == 0x149 || c == 0x17F) return c;
            if (c == 0x178) return 0xFF;
            if ((c >= 0x139 && c <= 0x148) || (c >= 0x179 && c <= 0x17E)) return (c & 1) != 0 ? c + 1 : c;   // (upper case at odd code points)
            return (c & 1) == 0 ? c + 1 : c;                                                 // (upper case at even code points)
        }
        if (c >= 0x391 && c <= 0x3A9 && c != 0x3A2) return c + 0x20;                         // Greek capitals
        if (c >= 0x410 && c <= 0x42F) return c + 0x20;                                       // Cyrillic
        if (c >= 0x400 && c <= 0x40F) return c + 0x50;
        return c;
    }

#ifdef _WIN32
    /// The upper case of a UTF-8 text the way the file systems of Windows compare names: NTFS (and ReFS) look names up through an upper case
    /// table of the system, which is the simple (one code point to one code point) upper casing of the Unicode data that the system itself
    /// uses. LCMapStringEx with LCMAP_UPPERCASE and the invariant locale is that mapping, independent of the locale of the program and of
    /// the user (no LCMAP_LINGUISTIC_CASING, which would add language specific rules the file system does not know). CompareStringOrdinal
    /// (ignoring the case) compares by the same table but yields no key to put into a hash table, hence this function. The result is the
    /// UTF-16 text as bytes, usable as a key only; nullopt if the system cannot convert the text (the table of foldedCode() is used then).
    std::optional<std::string> upperCaseByTheSystem(const std::u8string& raw) {
        if (raw.empty()) return std::string();
        const char* bytes = reinterpret_cast<const char*>(raw.data());
        const int length = MultiByteToWideChar(CP_UTF8, 0, bytes, static_cast<int>(raw.size()), nullptr, 0);
        if (length <= 0) return std::nullopt;
        std::wstring wide(static_cast<size_t>(length), L'\0');
        if (MultiByteToWideChar(CP_UTF8, 0, bytes, static_cast<int>(raw.size()), wide.data(), length) != length) return std::nullopt;
        std::wstring upper(static_cast<size_t>(length), L'\0');
        if (LCMapStringEx(LOCALE_NAME_INVARIANT, LCMAP_UPPERCASE, wide.c_str(), length, upper.data(), length, nullptr, nullptr, 0) != length) {
            return std::nullopt;
        }
        return std::string(reinterpret_cast<const char*>(upper.data()), upper.size() * sizeof(wchar_t));
    }
#endif

    /// The text two paths are compared by when they must not be written to the same file: the case is ignored (the file systems of Windows
    /// do not tell "A.sysmlx" from "a.sysmlx"; elsewhere a clash of the names of the files is just as confusing, and the file systems of
    /// macOS are insensitive as well; where the file system is sensitive, the warning that comes of it is a false alarm at worst).
    /// On Windows the case is folded by the system (upperCaseByTheSystem()), so that exactly the names the file system takes for one
    /// collide; elsewhere, and if the system fails, by the fixed table of foldedCode().
    std::string foldedKey(const std::filesystem::path& path) {
        std::u32string text;
        const std::u8string raw = path.generic_u8string();
#ifdef _WIN32
        if (auto upper = upperCaseByTheSystem(raw)) return *upper;
#endif
        // (UTF-8 to code points, then lower case, see foldedCode())
        for (size_t i = 0; i < raw.size();) {
            const unsigned char lead = static_cast<unsigned char>(raw[i]);
            size_t length = lead < 0x80 ? 1 : (lead >> 5) == 0x6 ? 2 : (lead >> 4) == 0xE ? 3 : (lead >> 3) == 0x1E ? 4 : 1;
            if (i + length > raw.size()) length = 1;
            char32_t code = length == 1 ? lead : (length == 2 ? lead & 0x1F : length == 3 ? lead & 0x0F : lead & 0x07);
            for (size_t k = 1; k < length; ++k) code = (code << 6) | (static_cast<unsigned char>(raw[i + k]) & 0x3F);
            i += length;
            text.push_back(foldedCode(code));
        }
        return std::string(reinterpret_cast<const char*>(text.data()), text.size() * sizeof(char32_t));
    }
}

namespace SysMLv2::Files {

    struct Workspace::Impl {
        struct Source {
            std::string name;
            /// The directory the source was loaded from (loadLibrary()); empty if it was added on its own. The name based file key of an
            /// export starts from it when the source is not below the export root.
            std::string loadRoot;
            SourceLanguage language = SourceLanguage::SysML;
            int level = 0;
            std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
            std::vector<std::shared_ptr<ParserError>> errors;
            ResolutionData data;
            std::vector<std::shared_ptr<KerML::Entities::Element>> topLevel;
            std::shared_ptr<KerML::Entities::Namespace> root;
            /// XMI sources: the document (ids, references) and the specializations it contributes to the name resolution as
            /// references that are resolved already (rebuilt by every resolve()).
            std::shared_ptr<XmiDocument> xmi;
            std::vector<PendingReference> xmiGeneralizations;
        };

        std::vector<std::shared_ptr<Source>> sources;
        /// The ids of the elements of all XMI sources.
        XmiIndex xmiIndex;
        std::optional<std::chrono::steady_clock::time_point> deadline;
        std::vector<UnresolvedReferenceInfo> unresolved;
        std::vector<UnresolvedReferenceInfo> notAttempted;
        std::unique_ptr<Detail::Resolver> resolver;
        size_t resolvedCount = 0;
        /// Which source holds an element. Built for one write and discarded with it: the model may change (resolve(), edits of the
        /// elements, replaceSource()) between two writes, so nothing of it is kept in the workspace.
        struct Lookup {
            /// The source of every element of every source: what the source lists and everything the model owns below it.
            std::unordered_map<const KerML::Entities::Element*, size_t> owner;
            /// The same for the elements that a source lists itself (elements() and the root namespace), without what the model owns on top.
            std::unordered_map<const KerML::Entities::Element*, size_t> listed;
            size_t sourceCount = 0;

            /// The index of the source that holds @p element, or the number of sources.
            size_t sourceOf(const KerML::Entities::Element& element) const {
                const auto found = owner.find(&element);
                return found == owner.end() ? sourceCount : found->second;
            }

            /// True if @p element is one of the elements the source @p index lists itself (not something the classes of the model created).
            bool listedBy(size_t index, const KerML::Entities::Element& element) const {
                const auto found = listed.find(&element);
                return found != listed.end() && found->second == index;
            }
        };

        Lookup buildLookup() const {
            Lookup lookup;
            lookup.sourceCount = sources.size();
            for (size_t index = 0; index < sources.size(); ++index) {
                std::vector<std::shared_ptr<KerML::Entities::Element>> pending;
                const auto add = [&](const std::shared_ptr<KerML::Entities::Element>& candidate) {
                    if (candidate) lookup.listed.emplace(candidate.get(), index);
                    if (candidate && lookup.owner.emplace(candidate.get(), index).second) pending.push_back(candidate);
                };
                for (const auto& candidate : sources[index]->elements) add(candidate);
                add(sources[index]->root);
                add(sources[index]->data.root);
                // (the elements below the root that the list of the source does not name, such as the memberships of a text)
                const auto addOwned = [&](const std::shared_ptr<KerML::Entities::Element>& candidate) {
                    if (candidate && lookup.owner.emplace(candidate.get(), index).second) pending.push_back(candidate);
                };
                for (size_t next = 0; next < pending.size(); ++next) {
                    for (const auto& child : pending[next]->ownedElements()) addOwned(child);
                }
            }
            return lookup;
        }

        /// The name of the XMI file a source is written to: ".sysml" becomes ".sysmlx", ".kerml" ".kermlx"; XMI sources keep their name.
        static std::string xmiName(const std::string& name, SourceLanguage language) {
            if (language == SourceLanguage::Xmi) return name;
            const bool kerml = language == SourceLanguage::KerML;
            if (endsWith(name, kerml ? ".kerml" : ".sysml")) return name + "x";
            return name + (kerml ? ".kermlx" : ".sysmlx");
        }

        /// Where the sources are written, and what identifies them in the ids.
        struct Layout {
            /// The file of every source.
            std::vector<std::filesystem::path> files;
            /// The path of every file relative to the export root, with "/" as separator (UTF-8): the identity of the file in the name based ids.
            std::vector<std::string> keys;
            /// Sources that were given another file name because they would have overwritten another file.
            struct Note {
                size_t source = 0;
                /// The name of the source, the file key it would have had and the one it got.
                std::string name;
                std::string wanted;
                std::string got;
                /// Why the keys are the same (the end of the sentence, in brackets).
                std::string reason;
            };
            std::vector<Note> notes;
            /// Things about a source that the caller should know and that are no collision (a key that had to be replaced, a comparison that
            /// depends on the working directory).
            struct Remark {
                size_t source = 0;
                std::string text;
            };
            std::vector<Remark> remarks;
            /// A source whose name and a root (the export root or its load root) are not both relative or both absolute.
            struct Mixed {
                size_t source = 0;
                std::string name;
                std::string root;
                bool exportRoot = false;
            };
            std::vector<Mixed> mixed;

            /// One WARNING text per distinct (root, kind) pair of the sources for which @p include is true: the number of the sources and a few
            /// of their names, in the order of the first source of each pair.
            std::vector<std::string> mixedTexts(const std::function<bool(size_t)>& include) const {
                struct Group {
                    std::string root;
                    bool exportRoot = false;
                    size_t count = 0;
                    std::vector<std::string> examples;
                };
                std::vector<Mixed> sorted = mixed;
                std::stable_sort(sorted.begin(), sorted.end(), [](const Mixed& a, const Mixed& b) { return a.source < b.source; });
                std::vector<Group> groups;
                for (const auto& entry : sorted) {
                    if (include && !include(entry.source)) continue;
                    auto found = std::find_if(groups.begin(), groups.end(), [&](const Group& group) {
                        return group.root == entry.root && group.exportRoot == entry.exportRoot;
                    });
                    if (found == groups.end()) {
                        groups.push_back(Group{entry.root, entry.exportRoot, 0, {}});
                        found = groups.end() - 1;
                    }
                    ++found->count;
                    if (found->examples.size() < 3) found->examples.push_back(entry.name);
                }
                std::vector<std::string> texts;
                for (const auto& group : groups) {
                    std::string names;
                    for (const auto& example : group.examples) names += (names.empty() ? "'" : ", '") + example + "'";
                    std::string who;
                    if (group.count == 1) {
                        who = "the source " + names;
                    } else {
                        who = std::to_string(group.count) + " sources (" + (group.count > group.examples.size() ? "for example " : "") + names + ")";
                    }
                    texts.push_back(who + " and the " + (group.exportRoot ? "export root" : "load root") + " '" + group.root +
                                    "' are not both relative or both absolute; they were compared as absolute paths against the current working "
                                    "directory, so the file key of the source depends on it (give both as absolute paths, or both relative to the "
                                    "same directory)");
                }
                return texts;
            }
        };

        /// The path of @p name relative to @p root, if @p name is a file below @p root (the components are compared without regard to the case
        /// on Windows); nullopt otherwise, or if the relative path would start with ".." (it would leave the directory it is meant for).
        /// Both are compared as they are; if only one of them is relative, both are made absolute first (against the working directory,
        /// so the answer depends on it) and @p mixed, if given, is set.
        static std::optional<std::filesystem::path> belowRoot(const std::filesystem::path& name, const std::filesystem::path& root,
                                                              bool* mixed = nullptr) {
            namespace fs = std::filesystem;
            fs::path file = name.lexically_normal();
            fs::path base = root.lexically_normal();
            if (file.is_absolute() != base.is_absolute()) {
                if (mixed) *mixed = true;
                std::error_code ec;
                file = fs::absolute(file, ec).lexically_normal();
                if (ec) return std::nullopt;
                base = fs::absolute(base, ec).lexically_normal();
                if (ec) return std::nullopt;
            }
            const auto componentsOf = [](const fs::path& path) {
                std::vector<fs::path> components;
                for (const auto& component : path) {
                    if (!component.empty() && component != ".") components.push_back(component);
                }
                return components;
            };
            const std::vector<fs::path> fileParts = componentsOf(file);
            const std::vector<fs::path> baseParts = componentsOf(base);
            if (fileParts.size() <= baseParts.size()) return std::nullopt;
            for (size_t i = 0; i < baseParts.size(); ++i) {
                if (!sameComponent(baseParts[i], fileParts[i])) return std::nullopt;
            }
            fs::path relative;
            for (size_t i = baseParts.size(); i < fileParts.size(); ++i) relative /= fileParts[i];
            if (!isPlainRelative(relative)) return std::nullopt;
            return relative;
        }

        /// True for a path that stays below the directory it is relative to: not empty, no root, no "." or ".." component (so neither "."
        /// nor "a/../b" is a key).
        static bool isPlainRelative(const std::filesystem::path& path) {
            if (path.empty() || path.has_root_path()) return false;
            return std::none_of(path.begin(), path.end(), [](const std::filesystem::path& component) {
                return component.empty() || component == "." || component == "..";
            });
        }

        /// True if two components of a path name the same directory entry: the file systems of Windows do not tell "C:" from "c:" (nor "Dir"
        /// from "dir"), elsewhere the case counts.
        static bool sameComponent(const std::filesystem::path& a, const std::filesystem::path& b) {
#ifdef _WIN32
            return foldedKey(a) == foldedKey(b);
#else
            return a == b;
#endif
        }

        /// The files the sources are written to below @p directory (empty: the files themselves, as writeXmi() references them) and the keys
        /// that identify them in the ids.
        /// The key of a source comes from its own name and from nothing else (never from the other sources, the working directory or the
        /// directories above the export root): its path relative to @p exportRoot if it is a file below the root, else relative to the directory
        /// it was loaded from (loadLibrary()) if it is below that, else its file name. The components are compared without regard to the case
        /// on Windows. Two sources that would write the same file (the comparison ignores the case, as the file systems of Windows do) get a
        /// number appended to the file name of the later one. With @p directory empty the file of a source is the file it lives in (an XMI
        /// source: its name; a text source: its name with the extension of the XMI file) whatever its key is, and a number is appended to it
        /// only if it is the file of another source; sources with the same file name in different directories keep their own files.
        /// A name without a usable file name gets source_<n> after all other sources have their names.
        /// Which one is the later one: the sources that are XMI files first (their name is the file they live in, so the key they have
        /// without a collision is the one the references into that file must find), each group in the order the sources were added. So the
        /// result does not depend on whether a text source or the XMI file with the same name was loaded first.
        Layout layout(const std::string& directory, const std::string& exportRoot) const {
            namespace fs = std::filesystem;
            Layout result;
            result.keys.resize(sources.size());
            result.files.resize(sources.size());
            /// The holder of a (folded) key: the key it has, whether it got it by being renamed, where it lives, and its name.
            struct Holder {
                std::string key;
                bool renamed = false;
                fs::path location;
                std::string name;
            };
            std::unordered_map<std::string, Holder> used;
            std::vector<size_t> order;
            for (size_t index = 0; index < sources.size(); ++index) {
                if (sources[index]->language == SourceLanguage::Xmi) order.push_back(index);
            }
            for (size_t index = 0; index < sources.size(); ++index) {
                if (sources[index]->language != SourceLanguage::Xmi) order.push_back(index);
            }
            /// With @p directory empty, the (folded) files that sources have been given; a file is renamed only when it is the file of another source.
            std::unordered_set<std::string> usedFiles;
            std::vector<size_t> deferred;
            /// Gives the source its key and file; false (nothing done) for a name without a usable file name unless @p synthesizing, which is
            /// the second pass: the names source_<n> are given after all real names, so that a real file called source_<n>.sysmlx is never
            /// renamed because of a synthesized one.
            const auto place = [&](const size_t index, const bool synthesizing) -> bool {
                const Source& source = *sources[index];
                const fs::path name = fs::path(xmiName(source.name, source.language)).lexically_normal();
                std::error_code ec;
                const fs::path absolute = fs::absolute(name, ec);
                const fs::path location = (ec ? name : absolute).lexically_normal();
                fs::path relative;
                bool byFileName = false;
                bool replaced = false;
                std::vector<Layout::Mixed> mixedRoots;
                if (!exportRoot.empty()) {
                    bool mixed = false;
                    if (auto below = belowRoot(name, fs::path(exportRoot), &mixed)) relative = *below;
                    if (mixed) mixedRoots.push_back({index, utf8(name), exportRoot, true});
                }
                if (relative.empty() && !source.loadRoot.empty()) {
                    bool mixed = false;
                    if (auto below = belowRoot(name, fs::path(source.loadRoot), &mixed)) relative = *below;
                    if (mixed) mixedRoots.push_back({index, utf8(name), source.loadRoot, false});
                }
                if (relative.empty()) {
                    relative = name.filename();
                    byFileName = true;
                }
                if (!isPlainRelative(relative)) {
                    if (!synthesizing) return false;
                    // (a name without a usable file name, such as "." or "")
                    relative = fs::path("source_" + std::to_string(index + 1) + ".sysmlx");
                    replaced = true;
                    result.remarks.push_back({index, "the source '" + utf8(name) + "' has no file name to make a file key of; it is called '" + utf8(relative, true) + "'"});
                }
                result.mixed.insert(result.mixed.end(), mixedRoots.begin(), mixedRoots.end());
                fs::path candidate = relative;
                bool renamed = false;
                for (int n = 2; !used.emplace(foldedKey(candidate), Holder{utf8(candidate, true), false, location, utf8(name)}).second; ++n) {
                    fs::path stem = relative.stem();
                    stem += "_" + std::to_string(n);
                    stem += relative.extension();
                    candidate = relative.parent_path() / stem;
                    renamed = true;
                }
                if (renamed) {
                    used.at(foldedKey(candidate)).renamed = true;
                    // (the holder of the key the source wanted decides why they collide)
                    const Holder& first = used.at(foldedKey(relative));
                    Layout::Note note;
                    note.source = index;
                    note.name = utf8(name);
                    note.wanted = utf8(relative, true);
                    note.got = utf8(candidate, true);
                    if (first.renamed) {
                        note.reason = "that key was given to the source '" + first.name + "' when it was renamed to avoid an earlier collision";
                    } else if (first.key != note.wanted) {
                        note.reason = "the names differ in case at most";
                    } else if (first.location == location) {
                        note.reason = "both have the same path";
                    } else if (byFileName) {
                        note.reason = "they have the same file name, and neither is below the export root or a directory it was loaded from, which would tell them apart";
                    } else {
                        note.reason = "they have the same path relative to the root";
                    }
                    result.notes.push_back(std::move(note));
                }
                result.keys[index] = utf8(candidate, true);
                if (!directory.empty()) {
                    result.files[index] = fs::path(directory) / candidate;
                } else {
                    // (writeXmi(): the file the source lives in, whatever the key is; it is renamed only for the file of another source)
                    const fs::path own = replaced ? location.parent_path() / relative : location;
                    fs::path file = own;
                    for (int n = 2; !usedFiles.insert(foldedKey(file)).second; ++n) {
                        fs::path stem = own.stem();
                        stem += "_" + std::to_string(n);
                        stem += own.extension();
                        file = own.parent_path() / stem;
                    }
                    result.files[index] = file;
                }
                return true;
            };
            for (const size_t index : order) {
                if (!place(index, false)) deferred.push_back(index);
            }
            for (const size_t index : deferred) place(index, true);
            // (in the order of the sources, whatever the order of the layout was)
            const auto bySource = [](const auto& a, const auto& b) { return a.source < b.source; };
            std::stable_sort(result.notes.begin(), result.notes.end(), bySource);
            std::stable_sort(result.remarks.begin(), result.remarks.end(), bySource);
            return result;
        }

        /// The state of one export, writeXmi() or exportXmi(): the lookup of the sources, the layout and the table of the ids of every source,
        /// which the references between the files are made from. It lives as long as the call.
        struct XmiExport {
            using IdTable = std::unordered_map<const KerML::Entities::Element*, std::string>;

            const Impl& impl;
            Lookup lookup;
            Layout layout;
            XmiWriteOptions base;
            /// The one source that is written, if there is one (writeXmi()): the include and keepsId of the caller are meant for its file only.
            std::optional<size_t> only;

            XmiExport(const Impl& owner, Layout files, XmiWriteOptions options, std::optional<size_t> written = std::nullopt)
                : impl(owner), lookup(owner.buildLookup()), layout(std::move(files)), base(std::move(options)), only(written) {}

            /// The options a source is written with (the ones of the caller, completed by what only the workspace knows). Also the ones the ids of
            /// the source are assigned with, so that its table and its file agree. When only one source is written, the include of the caller
            /// is for that source; the other sources (whose ids the references need) are listed as they are. The keepsId of the caller counts
            /// for all of them: the files of the other sources are written with the same options, and the ids in the references must be the
            /// ones those files get (the elements read from an XMI file keep their ids in any case).
            XmiWriteOptions optionsFor(size_t index) const {
                XmiWriteOptions options = base;
                if (only && *only != index) options.include = nullptr;
                options.fileKey = layout.keys[index];
                options.listed = [this, index](const KerML::Entities::Element& element) { return lookup.listedBy(index, element); };
                const auto userKeeps = options.keepsId;
                options.keepsId = [this, userKeeps](const KerML::Entities::Element& element) {
                    if (userKeeps && userKeeps(element)) return true;
                    const size_t owner = lookup.sourceOf(element);
                    return owner < impl.sources.size() && impl.sources[owner]->language == SourceLanguage::Xmi;
                };
                options.foreignId = [this](const KerML::Entities::Element& element) -> std::optional<std::string> {
                    const size_t other = lookup.sourceOf(element);
                    if (other >= impl.sources.size()) return std::nullopt;
                    const IdTable& table = idsOf(other);
                    const auto found = table.find(&element);
                    if (found == table.end()) return std::nullopt;
                    return found->second;
                };
                return options;
            }

            /// The ids of one source and what went wrong when they were assigned.
            struct Table {
                IdTable ids;
                /// Set if the table could not be built (a callback of the caller throws): what the exception said. The table is then empty.
                std::optional<std::string> failure;
                /// The errors that assigning the ids reported (an id that two elements share, ...).
                std::vector<std::shared_ptr<ParserError>> errors;
            };

            /// The table of every source that is written (built when it is first needed, once; a failure is kept with it).
            const Table& tableOf(size_t index) const {
                if (tables.size() != impl.sources.size()) tables.resize(impl.sources.size());
                if (!tables[index]) {
                    Table table;
                    const auto& root = impl.sources[index]->root;
                    try {
                        if (root) table.ids = XmiWriter::assignIds(root, utf8(layout.files[index]), table.errors, optionsFor(index));
                    } catch (const std::exception& ex) {
                        table.ids.clear();
                        table.failure = ex.what();
                    } catch (...) {
                        table.ids.clear();
                        table.failure = "unknown exception";
                    }
                    tables[index] = std::move(table);
                }
                return *tables[index];
            }

            /// The id of every element of a source that is written. A table that cannot be built stays empty: nothing of that source can be
            /// referenced (see failureOf()), and the source itself reports the failure when it is written.
            const IdTable& idsOf(size_t index) const { return tableOf(index).ids; }

            /// Why the ids of a source could not be assigned; nullopt if they could.
            const std::optional<std::string>& failureOf(size_t index) const { return tableOf(index).failure; }

            /// The path of the file an element of another source is written to; nullopt if the source does not write it to its file. A source
            /// whose ids could not be assigned still has its file (the reference is refused for want of an id, and the caller says why).
            /// Remembers the sources that are located (referenced()).
            std::optional<std::string> locate(size_t index, const KerML::Entities::Element& element) const {
                const size_t other = lookup.sourceOf(element);
                if (other >= impl.sources.size() || other == index) return std::nullopt;
                if (!failureOf(other) && idsOf(other).count(&element) == 0) return std::nullopt;
                located.insert(other);
                return utf8(layout.files[other]);
            }

            /// The sources that references were made to by locate().
            const std::set<size_t>& referenced() const { return located; }

            /// The errors that assigning the ids of a source reported.
            const std::vector<std::shared_ptr<ParserError>>& assignmentErrors(size_t index) const { return tableOf(index).errors; }

        private:
            mutable std::vector<std::optional<Table>> tables;
            mutable std::set<size_t> located;
        };

        /// Writes the file of one source. Nothing escapes: an exception is reported as an INTERNAL_ERROR, and the file is replaced as a whole
        /// or not at all (the text goes to a temporary file first), so that a failure never leaves a truncated target.
        std::vector<std::shared_ptr<ParserError>> writeXmiFile(const XmiExport& context, size_t index) const {
            namespace fs = std::filesystem;
            std::vector<std::shared_ptr<ParserError>> result;
            const auto& source = *sources[index];
            const fs::path& file = context.layout.files[index];
            std::string target = source.name;
            try {
                target = utf8(file);
                if (!source.root) {
                    result.push_back(makeError(ErrorType::INTERNAL_ERROR, "the source '" + source.name + "' has no elements and is not written", -1, -1, target));
                    return result;
                }
                // (the sources this file refers to whose ids could not be assigned: the writer can only say that an id is not known)
                std::set<size_t> failed;
                const auto locate = [&context, &failed, index](const KerML::Entities::Element& element) {
                    auto file = context.locate(index, element);
                    if (file) {
                        const size_t other = context.lookup.sourceOf(element);
                        if (context.failureOf(other)) failed.insert(other);
                    }
                    return file;
                };
                const std::string text = XmiWriter::write(source.root, target, locate, result, context.optionsFor(index));
                for (const size_t other : failed) {
                    result.push_back(makeError(ErrorType::LOGICAL_ERROR,
                                               "the ids of the file '" + utf8(context.layout.files[other]) + "' could not be assigned: " + *context.failureOf(other) +
                                                   "; the references into it are not written",
                                               -1, -1, target));
                }
                if (text.empty()) {
                    result.push_back(makeError(ErrorType::INTERNAL_ERROR, "nothing could be written for the source '" + source.name + "'; the file is not written", -1, -1, target));
                    return result;
                }
                std::error_code ec;
                if (file.has_parent_path()) fs::create_directories(file.parent_path(), ec);
                fs::path temporary = file;
                temporary += ".tmp";
                {
                    std::ofstream out(temporary, std::ios::out | std::ios::binary | std::ios::trunc);
                    if (!out) {
                        result.push_back(makeError(ErrorType::INTERNAL_ERROR, "could not open file for writing: " + target, -1, -1, target));
                        return result;
                    }
                    out.write(text.data(), static_cast<std::streamsize>(text.size()));
                    out.close();
                    if (!out) {
                        fs::remove(temporary, ec);
                        result.push_back(makeError(ErrorType::INTERNAL_ERROR, "could not write file: " + target, -1, -1, target));
                        return result;
                    }
                }
                fs::rename(temporary, file, ec);
                if (ec) {
                    std::error_code ignored;
                    fs::remove(temporary, ignored);
                    result.push_back(makeError(ErrorType::INTERNAL_ERROR, "could not replace file: " + target + " (" + ec.message() + ")", -1, -1, target));
                }
            } catch (const std::exception& ex) {
                result.push_back(makeError(ErrorType::INTERNAL_ERROR, std::string("internal: writing the source '") + source.name + "' failed: " + ex.what(), -1, -1, target));
            } catch (...) {
                result.push_back(makeError(ErrorType::INTERNAL_ERROR, "internal: writing the source '" + source.name + "' failed with an unknown exception", -1, -1, target));
            }
            return result;
        }

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
                source->errors.push_back(makeError(SysMLv2::
                	Files::SYNTAX_ERROR, shortened(error->message()), error->line(), error->positionInLine(), source->name));
            }

            try {
                antlr4::tree::ParseTreeWalker::DEFAULT.walk(listener.get(), tree);
                source->elements = listener->getElements();
                source->data = listener->takeResolutionData();
            } catch (const std::exception& ex) {
                source->errors.push_back(makeError(ErrorType::INTERNAL_ERROR, std::string("internal: ") + ex.what(), -1, -1, source->name));
            } catch (...) {
                source->errors.push_back(makeError(ErrorType::INTERNAL_ERROR, "internal: unknown exception while walking the KerML parse tree", -1, -1, source->name));
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
                source->errors.push_back(makeError(ErrorType::SYNTAX_ERROR, shortened(error->message()), error->line(), error->positionInLine(), source->name));
            }

            try {
                antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
                source->elements = listener.getElements();
                source->data = listener.takeResolutionData();
            } catch (const std::exception& ex) {
                source->errors.push_back(makeError(ErrorType::INTERNAL_ERROR, std::string("internal: ") + ex.what(), -1, -1, source->name));
            } catch (...) {
                source->errors.push_back(makeError(ErrorType::INTERNAL_ERROR, "internal: unknown exception while walking the SysML v2 parse tree", -1, -1, source->name));
            }
        }

        void readXmi(std::shared_ptr<Source> source, const std::string& text) {
            std::shared_ptr<XmiDocument> document = XmiReader::read(text, source->name);
            source->errors = document->errors();
            source->elements = document->elements();
            source->data = document->resolutionData();
            source->xmi = std::move(document);
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
                    if (language == SourceLanguage::Xmi) {
                        readXmi(source, text);
                    } else if (language == SourceLanguage::KerML) {
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
        if (language == SourceLanguage::Auto) language = languageOf(sourceName);
        const size_t index = impl_->sources.size();
        impl_->sources.push_back(impl_->makeSource(text, std::move(sourceName), language, index, level));
        if (impl_->sources.back()->xmi) impl_->xmiIndex.add(*impl_->sources.back()->xmi);
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
        if (old->xmi) impl_->xmiIndex.remove(*old->xmi);
        replacement->loadRoot = old->loadRoot;   // (the file keys of an export must not change with the text)
        impl_->sources[source] = std::move(replacement);
        if (impl_->sources[source]->xmi) impl_->xmiIndex.add(*impl_->sources[source]->xmi);
        impl_->resolver.reset();
        Impl::dispose(*old);
    }

    size_t Workspace::addFile(const std::string& path, int level) {
        const SourceLanguage language = languageOf(path);
        std::ifstream in(path, language == SourceLanguage::Xmi ? std::ios::in | std::ios::binary : std::ios::in);
        if (!in) {
            auto source = std::make_unique<Impl::Source>();
            source->name = path;
            source->language = language;
            source->level = level;
            source->errors.push_back(Impl::makeError(ErrorType::INTERNAL_ERROR, "could not open file: " + path, -1, -1, path));
            impl_->sources.push_back(std::move(source));
            impl_->resolver.reset();
            return impl_->sources.size() - 1;
        }
        std::stringstream buffer;
        buffer << in.rdbuf();
        return addText(buffer.str(), path, language, level);
    }

    size_t Workspace::loadLibrary(const std::string& directory) {
        namespace fs = std::filesystem;
        std::vector<std::string> files;
        std::error_code ec;
        if (!fs::exists(directory, ec)) return 0;
        for (fs::recursive_directory_iterator it(directory, ec), end; !ec && it != end; it.increment(ec)) {
            if (!it->is_regular_file(ec)) continue;
            const auto extension = it->path().extension().string();
            if (extension == ".kerml" || extension == ".sysml" || extension == ".kermlx" || extension == ".sysmlx" || extension == ".xmi") {
                files.push_back(it->path().string());
            }
        }
        std::sort(files.begin(), files.end());
        for (const auto& file : files) impl_->sources[addFile(file)]->loadRoot = directory;
        return files.size();
    }

    void Workspace::resolve() {
        // The references of the XMI sources are resolved by id over the ids of all XMI sources; what they resolve to is not resolved again
        // by name, but the resolver learns the specializations from the XMI sources (inherited members).
        for (auto& source : impl_->sources) {
            if (!source->xmi) continue;
            XmiReader::link(*source->xmi, impl_->xmiIndex);
            source->errors = source->xmi->errors();   // (the document keeps the errors of reading and of linking)
            source->xmiGeneralizations = source->xmi->generalizations();
        }
        std::vector<Detail::SourceInput> inputs;
        std::vector<PendingReference*> all;
        inputs.reserve(impl_->sources.size());
        for (auto& source : impl_->sources) {
            inputs.push_back({&source->elements, &source->data, source->level});
            for (auto& reference : source->data.references) all.push_back(&reference);
            for (auto& reference : source->xmiGeneralizations) all.push_back(&reference);
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
            if (source.xmi) {
                for (auto& reference : source.xmi->unresolved()) {
                    UnresolvedReferenceInfo info;
                    info.name = std::move(reference.name);
                    info.kind = reference.kind;
                    info.sourceName = source.name;
                    info.line = reference.line;
                    info.source = index;
                    info.context = std::move(reference.context);
                    info.placeholder = std::move(reference.placeholder);
                    impl_->unresolved.push_back(std::move(info));
                }
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

    std::vector<std::shared_ptr<ParserError>> Workspace::writeXmi(size_t source, const std::string& path, const XmiWriteOptions& options) const {
        (void)impl_->sources.at(source);
        try {
            auto layout = impl_->layout(std::string(), options.exportRoot);
            layout.files[source] = std::filesystem::path(path);
            const Impl::XmiExport context(*impl_, std::move(layout), options, source);
            auto result = impl_->writeXmiFile(context, source);
            // The sources that collided with another one for their file: the written source, whose ids depend on its key, and the ones that
            // this file refers to (it refers to the file they would have without the collision otherwise).
            for (const auto& note : context.layout.notes) {
                if (note.source != source && context.referenced().count(note.source) == 0) continue;
                const bool written = note.source == source;
                result.push_back(Impl::makeError(ErrorType::WARNING,
                                                 "the source '" + note.name + "' would have the file key '" + note.wanted + "' of another source (" + note.reason + "); " +
                                                     (written ? "its ids are made from the key '" + note.got + "'"
                                                              : "its file is '" + utf8(context.layout.files[note.source]) + "', where the references to it point"),
                                                 -1, -1, path));
            }
            for (const auto& remark : context.layout.remarks) {
                if (remark.source != source && context.referenced().count(remark.source) == 0) continue;
                result.push_back(Impl::makeError(ErrorType::WARNING, remark.text, -1, -1, path));
            }
            for (const auto& text : context.layout.mixedTexts([&](size_t other) { return other == source || context.referenced().count(other) != 0; })) {
                result.push_back(Impl::makeError(ErrorType::WARNING, text, -1, -1, path));
            }
            // The ids of the files this one refers to were assigned with the same options: what that reported is not reported by their own
            // writing here, but it makes the references ambiguous.
            for (const size_t other : context.referenced()) {
                for (const auto& error : context.assignmentErrors(other)) result.push_back(error);
            }
            return result;
        } catch (const std::exception& ex) {
            return {Impl::makeError(ErrorType::INTERNAL_ERROR, std::string("internal: writing the source failed: ") + ex.what(), -1, -1, path)};
        } catch (...) {
            return {Impl::makeError(ErrorType::INTERNAL_ERROR, "internal: writing the source failed with an unknown exception", -1, -1, path)};
        }
    }

    std::vector<std::shared_ptr<ParserError>> Workspace::exportXmi(const std::string& directory, const XmiWriteOptions& options) const {
        std::vector<std::shared_ptr<ParserError>> result;
        try {
            auto layout = impl_->layout(directory.empty() ? "." : directory, options.exportRoot);
            for (const auto& note : layout.notes) {
                result.push_back(Impl::makeError(ErrorType::WARNING,
                                                 "the source '" + note.name + "' would be written to the file '" + note.wanted + "' of another source (" + note.reason +
                                                     "); it is written to '" + note.got + "'",
                                                 -1, -1, directory));
            }
            for (const auto& remark : layout.remarks) {
                result.push_back(Impl::makeError(ErrorType::WARNING, remark.text, -1, -1, directory));
            }
            for (const auto& text : layout.mixedTexts(nullptr)) {
                result.push_back(Impl::makeError(ErrorType::WARNING, text, -1, -1, directory));
            }
            const Impl::XmiExport context(*impl_, std::move(layout), options);
            // The ids of all files first: an id must not be used in two files (the references between the files are looked up by id).
            std::unordered_map<std::string, size_t> idOwner;
            for (size_t index = 0; index < impl_->sources.size(); ++index) {
                // (a source whose ids cannot be assigned has an empty table and is reported when its file is written; the others go on)
                for (const auto& entry : context.idsOf(index)) {
                    const std::string& id = entry.second;
                    const auto inserted = idOwner.emplace(id, index);
                    if (!inserted.second && inserted.first->second != index) {
                        const std::string file = utf8(context.layout.files[index]);
                        result.push_back(Impl::makeError(ErrorType::LOGICAL_ERROR,
                                                         "the id '" + id + "' of an element is also used in the file '" + utf8(context.layout.files[inserted.first->second]) + "'",
                                                         -1, -1, file));
                    }
                }
            }
            for (size_t index = 0; index < impl_->sources.size(); ++index) {
                auto errors = impl_->writeXmiFile(context, index);
                result.insert(result.end(), errors.begin(), errors.end());
            }
        } catch (const std::exception& ex) {
            result.push_back(Impl::makeError(ErrorType::INTERNAL_ERROR, std::string("internal: the export failed: ") + ex.what(), -1, -1, directory));
        } catch (...) {
            result.push_back(Impl::makeError(ErrorType::INTERNAL_ERROR, "internal: the export failed with an unknown exception", -1, -1, directory));
        }
        return result;
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
