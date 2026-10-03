//
// Checker for SysML v2 texts. See Checker.h.
//
#include <sysmlv2/check/Checker.h>

#ifdef SYSMLV2CHECK_STRUCTURE_CHECK
#include <kerml/model/Representation.h>
#endif
#include <kerml/root/elements/Element.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <sysmlv2/ParserError.h>
#include <sysmlv2/Workspace.h>

#include <nlohmann/json.hpp>
#include <cmrc/cmrc.hpp>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <chrono>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <vector>

CMRC_DECLARE(Library);

namespace SysMLv2::Check {

    namespace {
        using nlohmann::json;
        using KerML::Entities::Element;

        constexpr const char* ResponseVersion = "1";
        constexpr const char* LibraryRoot = "sysml.library";
        constexpr const char* VorgabeName = "vorgabe";
        constexpr const char* QuelltextName = "quelltext";

        /// The library packages that are loaded when a Checker is created: Base is the implicit general of every type and feature
        /// (the packages that it imports follow). Parsing the library is the expensive part of a check (up to seconds per file), so
        /// every other package is loaded when a text needs it, and then kept (see Checker::Impl::run).
        constexpr const char* PreloadedPackages[] = {"Base"};

        /// The library package a metaclass name (`PartUsage`) makes necessary: the packages that the implicit specializations of the
        /// elements of that metaclass refer to (`Parts::parts`, ...); a metaclass name that contains Text needs Package. The same table
        /// as SysMLv2::API::InstanceManager uses; it over-approximates (the imports of the library files add the rest).
        struct ImplicitLibraryPackage {
            const char* Text;
            const char* Package;
        };

        constexpr ImplicitLibraryPackage ImplicitLibraryPackages[] = {
            // SysML
            {"Concern", "Requirements"}, {"Requirement", "Requirements"}, {"Satisfy", "Requirements"},
            {"View", "Views"}, {"Rendering", "Views"},
            {"Constraint", "Constraints"},
            {"UseCase", "UseCases"}, {"AnalysisCase", "AnalysisCases"}, {"VerificationCase", "VerificationCases"}, {"Case", "Cases"},
            {"Calculation", "Calculations"},
            {"State", "States"},
            {"Flow", "Flows"},
            {"Action", "Actions"}, {"Transition", "Actions"}, {"Node", "Actions"}, {"Loop", "Actions"},
            {"Interface", "Interfaces"}, {"Allocation", "Allocations"},
            {"Connection", "Connections"}, {"Connector", "Connections"},
            {"Port", "Ports"}, {"Part", "Parts"}, {"Item", "Items"}, {"Metadata", "Metadata"},
            {"Enumeration", "Attributes"}, {"Attribute", "Attributes"},
            {"Occurrence", "Occurrences"}, {"Succession", "Occurrences"},
            // KerML
            {"Metaclass", "Metaobjects"}, {"Structure", "Objects"}, {"Interaction", "Transfers"}, {"Association", "Links"},
            {"Binding", "Links"}, {"Connector", "Links"}, {"Class", "Occurrences"}, {"Predicate", "Performances"},
            {"Function", "Performances"}, {"Behavior", "Performances"}, {"Step", "Performances"}, {"Expression", "Performances"},
            {"Invariant", "Performances"}
        };

        /// The package name of every file of the embedded standard library (`ISQ` -> `sysml.library/.../ISQ.sysml`). The name of a
        /// library file is the name of the package that it defines.
        const std::map<std::string, std::string>& libraryFiles() {
            static const std::map<std::string, std::string> files = [] {
                std::map<std::string, std::string> result;
                const auto fs = cmrc::Library::get_filesystem();
                const auto walk = [&](auto self, const std::string& directory) -> void {
                    for (const auto& entry : fs.iterate_directory(directory)) {
                        const std::string path = directory + "/" + entry.filename();
                        if (entry.is_directory()) {
                            self(self, path);
                        } else if (path.ends_with(".sysml") || path.ends_with(".kerml")) {
                            result.emplace(path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1), path);
                        }
                    }
                };
                walk(walk, LibraryRoot);
                return result;
            }();
            return files;
        }

        /// The short names of the library packages (`<USCU> USCustomaryUnits` -> `USCU`) and the package they stand for. A short name
        /// can be used like the name: `import USCU::*;`.
        const std::map<std::string, std::string>& libraryShortNames() {
            static const std::map<std::string, std::string> shortNames = [] {
                std::map<std::string, std::string> result;
                const auto fs = cmrc::Library::get_filesystem();
                for (const auto& [name, path] : libraryFiles()) {
                    const auto file = fs.open(path);
                    const std::string head(file.begin(), file.begin() + std::min<size_t>(file.size(), 512));
                    const size_t package = head.find("package");
                    const size_t open = package == std::string::npos ? std::string::npos : head.find_first_not_of(" \t\r\n", package + 7);
                    if (open == std::string::npos || head[open] != '<') continue;
                    const size_t close = head.find('>', open);
                    if (close == std::string::npos) continue;
                    result.emplace(head.substr(open + 1, close - open - 1), name);
                }
                return result;
            }();
            return shortNames;
        }

        /// The name of the library package that @p name (a name or a short name) stands for; empty if there is none.
        std::string libraryPackage(const std::string& name) {
            if (libraryFiles().count(name) != 0) return name;
            const auto found = libraryShortNames().find(name);
            return found == libraryShortNames().end() ? std::string() : found->second;
        }

        /// The name a reference starts with: `ScalarValues::Real` -> `ScalarValues`, `'Some Name'.x` -> `Some Name`.
        std::string firstSegment(const std::string& name) {
            std::string segment;
            bool quoted = false;
            for (const char c : name) {
                if (c == '\'') {
                    quoted = !quoted;
                    continue;
                }
                if (!quoted && (c == ':' || c == '.')) break;
                segment.push_back(c);
            }
            return segment;
        }

        /// A name without its quotes and escapes: `'Mein Auto'` -> `Mein Auto`, `'it\'s'` -> `it's`. An unquoted name is unchanged.
        std::string unquote(const std::string& name) {
            if (name.size() < 2 || name.front() != '\'' || name.back() != '\'') return name;
            std::string result;
            for (size_t i = 1; i + 1 < name.size(); ++i) {
                if (name[i] == '\\' && i + 2 < name.size()) ++i;
                result.push_back(name[i]);
            }
            return result;
        }

        /// A qualified name (`P::'Mein Auto'::x`) with every segment unquoted; the segments are joined by `::` again.
        std::string normalizeQualified(const std::string& name) {
            std::string result;
            std::string segment;
            bool quoted = false;
            const auto flush = [&] {
                if (!result.empty() || !segment.empty()) result += unquote(segment);
                segment.clear();
            };
            for (size_t i = 0; i < name.size(); ++i) {
                const char c = name[i];
                if (quoted && c == '\\' && i + 1 < name.size()) {
                    segment.push_back(c);
                    segment.push_back(name[++i]);
                    continue;
                }
                if (c == '\'') quoted = !quoted;
                if (!quoted && c == ':' && i + 1 < name.size() && name[i + 1] == ':') {
                    flush();
                    result += "::";
                    ++i;
                    continue;
                }
                segment.push_back(c);
            }
            flush();
            return result;
        }

        /// What a text looks like before it is parsed, counted by a simple scan of its tokens that follows the lexer (comments, strings and
        /// quoted names are single tokens). An unterminated comment, string or quoted name is not skipped: the lexer reads on after it,
        /// so the scan counts the rest as ordinary tokens (it may count more than the parser sees, never less).
        struct InputScan {
            size_t depth = 0;     // deepest nesting of `{`, `(` and `[`
            size_t tokens = 0;    // number of tokens
            size_t chain = 0;     // most segments of a feature chain / qualified name (`a.b.c`, `A::b`)
            size_t prefix = 0;    // longest run of prefix operators (`- - -x`, `not not x`): the parser recurses once per operator
            size_t operators = 0; // most operator tokens between two `;`, `{` or `}`: a chain `1 + 1 + ...` makes the parser recurse once per operator
        };

        InputScan scanInput(const std::string& text, size_t maxTokens) {
            InputScan scan;
            size_t depth = 0;
            size_t run = 0;        // separators in the current chain
            size_t unary = 0;      // prefix operators in a row
            size_t ops = 0;        // operator tokens in the current statement
            enum { Other, Word, Separator } last = Other;
            const auto isWord = [](char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || (static_cast<unsigned char>(c) & 0x80); };
            for (size_t i = 0; i < text.size() && scan.tokens <= maxTokens; ++i) {
                const char c = text[i];
                if (std::isspace(static_cast<unsigned char>(c))) continue;
                if (c == '/' && i + 1 < text.size() && text[i + 1] == '/') {
                    while (i < text.size() && text[i] != '\n') ++i;
                    continue;
                }
                if (c == '/' && i + 1 < text.size() && text[i + 1] == '*') {
                    const size_t end = text.find("*/", i + 2);
                    if (end != std::string::npos) {
                        i = end + 1;
                        ++scan.tokens;
                        last = Other;
                        continue;
                    }
                    // unterminated: `/` and `*` are ordinary tokens
                }
                ++scan.tokens;
                if (c == '"' || c == '\'' || c == '.' || c == ':') unary = 0;
                if (c == '"' || c == '\'') {
                    size_t end = i + 1;
                    while (end < text.size() && text[end] != c) end += text[end] == '\\' ? 2 : 1;
                    if (end < text.size()) {
                        i = end;
                        last = Word;   // a quoted name is a word of a chain
                        continue;
                    }
                    last = Other;      // unterminated: the quote is an ordinary token
                    continue;
                }
                if (isWord(c)) {
                    const size_t begin = i;
                    while (i + 1 < text.size() && isWord(text[i + 1])) ++i;
                    {
                        const std::string word = text.substr(begin, i - begin + 1);
                        if (word == "or" || word == "and" || word == "xor" || word == "implies" || word == "if" || word == "else" || word == "as" || word == "hastype" || word == "istype" || word == "meta" || word == "not") {
                            scan.operators = std::max(scan.operators, ++ops);
                        }
                    }
                    if (i - begin == 2 && text.compare(begin, 3, "not") == 0) {
                        scan.prefix = std::max(scan.prefix, ++unary);
                    } else {
                        unary = 0;
                    }
                    if (last != Separator) run = 0;
                    last = Word;
                    scan.chain = std::max(scan.chain, run + 1);
                    continue;
                }
                if (c == '.' || c == ':') {
                    if (last == Word) {
                        ++run;
                        last = Separator;
                    } else {
                        last = Other;
                        run = 0;
                    }
                    // a `::` is one separator: the second colon does not count
                    if (c == ':' && i + 1 < text.size() && text[i + 1] == ':') {
                        ++i;
                    }
                    continue;
                }
                last = Other;
                run = 0;
                if (c == ';' || c == '{' || c == '}') {
                    ops = 0;
                } else if (std::strchr("+-*/%^&|<>=?!~@", c) != nullptr) {
                    scan.operators = std::max(scan.operators, ++ops);
                }
                if (c == '-' || c == '+' || c == '~' || c == '!' || c == '#' || c == '@') {
                    scan.prefix = std::max(scan.prefix, ++unary);
                } else {
                    unary = 0;
                }
                if (c == '{' || c == '(' || c == '[') {
                    scan.depth = std::max(scan.depth, ++depth);
                } else if ((c == '}' || c == ')' || c == ']') && depth > 0) {
                    --depth;
                }
            }
            return scan;
        }

        /// The elements @p element owns: its owned elements, the owned members of a namespace and the owned related elements of a
        /// relationship.
        std::vector<std::shared_ptr<Element>> ownedChildren(const std::shared_ptr<Element>& element) {
            std::vector<std::shared_ptr<Element>> children = element->ownedElements();
            if (const auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(element)) {
                const auto members = ns->ownedMember();
                children.insert(children.end(), members.begin(), members.end());
            }
            if (const auto relationship = std::dynamic_pointer_cast<KerML::Entities::Relationship>(element)) {
                const auto related = relationship->ownedRelatedElement();
                children.insert(children.end(), related.begin(), related.end());
            }
            return children;
        }

        /// Sets the qualified name of every named, non-relationship element below @p root from the chain of the owning
        /// namespaces. An unnamed element gets none and adds no segment to the names of what it owns.
        void assignQualifiedNames(const std::shared_ptr<Element>& root) {
            if (!root) return;
            std::unordered_set<const Element*> visited;
            const auto visit = [&visited](auto self, const std::shared_ptr<Element>& element, const std::string& parent) -> void {
                if (!element || !visited.insert(element.get()).second) return;
                std::string name;
                if (element->declaredName().has_value() && !element->declaredName()->empty())
                    name = unquote(element->declaredName().value());
                else if (element->declaredShortName().has_value() && !element->declaredShortName()->empty())
                    name = unquote(element->declaredShortName().value());
                std::string qualifiedName = parent;
                if (!name.empty() && std::dynamic_pointer_cast<KerML::Entities::Relationship>(element) == nullptr) {
                    qualifiedName = parent.empty() ? name : parent + "::" + name;
                    element->setQualifiedName(qualifiedName);
                }
                for (const auto& child : ownedChildren(element)) self(self, child, qualifiedName);
            };
            for (const auto& child : ownedChildren(root)) visit(visit, child, "");
        }

        json diagnosis(const char* category, const char* source, const std::string& message) {
            json result = {{"kategorie", category}, {"quelle", source}};
            if (!message.empty()) result["meldung"] = message;
            return result;
        }

        void setPosition(json& result, int line, int column) {
            if (line >= 0) result["zeile"] = line;
            if (column >= 0 && line >= 0) result["spalte"] = column;
        }

        /// Serializes @p value; bytes that are no valid UTF-8 (the JSON serializer rejects them) are replaced.
        std::string utf8Dump(const json& value) {
            return value.dump(-1, ' ', false, json::error_handler_t::replace);
        }

#ifdef SYSMLV2CHECK_STRUCTURE_CHECK
        std::string declaredNameOf(const Element& element) {
            if (element.declaredName().has_value()) return unquote(element.declaredName().value());
            if (element.declaredShortName().has_value()) return unquote(element.declaredShortName().value());
            return "";
        }
#endif
    }

    struct Checker::Impl {
        /// The levels of the sources (Workspace::setSourceLevel): a reference only resolves to the same or a lower level, so the
        /// library never sees the given text or the model, and the model sees both.
        static constexpr int LibraryLevel = 0;
        static constexpr int VorgabeLevel = 1;
        static constexpr int ModelLevel = 2;

        SysMLv2::Files::Workspace workspace;
        Limits limits;
        size_t vorgabeSource = 0;
        size_t userSource = 0;
        std::set<std::string> loaded;   // package names (library files) that are in the workspace
        size_t libraryCount = 0;
        /// While a request loads library packages: when it has to stop (Limits::maxLoadMillis).
        std::optional<std::chrono::steady_clock::time_point> loadDeadline;
        /// A load that was interrupted (Limits::maxLoadMillis) leaves the library without its fixed point: files that were added are
        /// not resolved, and the packages they import are not loaded. The next request has to complete it.
        bool libraryIncomplete = false;

        struct LoadTimeout {};

        Impl() {
            // The two request sources come first and keep their index; the library files follow.
            vorgabeSource = workspace.addText("", VorgabeName, SysMLv2::Files::SourceLanguage::SysML, VorgabeLevel);
            userSource = workspace.addText("", QuelltextName, SysMLv2::Files::SourceLanguage::SysML, ModelLevel);
            for (const char* name : PreloadedPackages) loadPackage(name);
            resolveLibrary();
        }

        /// Adds the standard library file of package @p name once.
        bool loadPackage(const std::string& requested) {
            const std::string name = libraryPackage(requested);
            const auto& files = libraryFiles();
            const auto found = files.find(name);
            if (found == files.end() || loaded.count(name) != 0) return false;
            if (loadDeadline && std::chrono::steady_clock::now() > *loadDeadline) throw LoadTimeout();
            try {
                const auto fs = cmrc::Library::get_filesystem();
                const auto data = fs.open(found->second);
                const std::string_view path(found->second);
                workspace.addText(std::string(data.begin(), data.end()), found->second,
                                  path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML,
                                  LibraryLevel);
            } catch (const std::system_error&) {
                return false;
            }
            loaded.insert(name);
            ++libraryCount;
            return true;
        }

        /// Resolves everything; every unresolved reference that starts with the name of a library package that is not loaded yet
        /// loads that package, and the files loaded in one round can name further packages, so this is repeated. Used while the
        /// two request sources are empty: the library is brought to its fixed point without any model in the workspace.
        void resolveLibrary() {
            for (;;) {
                workspace.resolve();
                bool added = false;
                for (const auto& reference : workspace.unresolvedReferences()) {
                    if (loadPackage(firstSegment(reference.name))) added = true;
                }
                if (!added) break;
            }
        }

        /// The library packages that the implicit specializations of the elements of the two request sources refer to (chosen by the
        /// metaclasses that occur there, see ImplicitLibraryPackages) and the packages that the names of their references start with,
        /// as far as they are not loaded yet.
        std::set<std::string> missingPackages() const {
            std::set<std::string> wanted;
            std::set<std::string> metaclasses;
            for (const size_t source : {vorgabeSource, userSource}) {
                for (const auto& element : workspace.elements(source)) {
                    if (element) metaclasses.insert(element->getType());
                }
                for (const auto& name : workspace.referenceNames(source)) wanted.insert(firstSegment(name));
            }
            for (const auto& metaclass : metaclasses) {
                for (const auto& entry : ImplicitLibraryPackages) {
                    if (metaclass.find(entry.Text) != std::string::npos) wanted.insert(entry.Package);
                }
            }
            std::set<std::string> missing;
            for (const auto& name : wanted) {
                const std::string package = libraryPackage(name);
                if (!package.empty() && loaded.count(package) == 0) missing.insert(package);
            }
            return missing;
        }

        /// Loads library packages by name (with everything they import). The request sources are empty afterwards.
        /// @return the number of library files that were added.
        size_t preload(const std::vector<std::string>& packages) {
            const size_t before = libraryCount;
            workspace.replaceSource(vorgabeSource, "");
            workspace.replaceSource(userSource, "");
            for (const auto& name : packages) {
                if (name == "*" || name == "alle") {
                    for (const auto& entry : libraryFiles()) loadPackage(entry.first);   // the whole standard library
                } else {
                    loadPackage(name);
                }
            }
            resolveLibrary();
            return libraryCount - before;
        }

        /// Puts the two texts into their sources and resolves. The library is brought to its fixed point first, while the texts are
        /// not in the workspace, whenever the texts need packages that are not loaded yet.
        void install(const std::string& given, const std::string& text) {
            // Only the parse of the two texts has a deadline; loading the library does not.
            const auto putIn = [&] {
                workspace.setParseDeadline(std::chrono::steady_clock::now() + std::chrono::milliseconds(limits.maxParseMillis));
                workspace.replaceSource(vorgabeSource, given);
                workspace.replaceSource(userSource, text);
                workspace.clearParseDeadline();
            };
            putIn();
            const auto missing = missingPackages();
            if (!missing.empty() || libraryIncomplete) {
                workspace.replaceSource(vorgabeSource, "");
                workspace.replaceSource(userSource, "");
                loadDeadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(limits.maxLoadMillis);
                libraryIncomplete = true;
                try {
                    for (const auto& name : missing) loadPackage(name);
                    resolveLibrary();   // also loads what the files that an earlier, interrupted request added import
                } catch (...) {
                    loadDeadline.reset();
                    throw;           // libraryIncomplete stays set: the next request continues
                }
                loadDeadline.reset();
                libraryIncomplete = false;
                putIn();
            }
            // Resolving the texts has its own deadline: a model with very many references takes long to resolve.
            workspace.setParseDeadline(std::chrono::steady_clock::now() + std::chrono::milliseconds(limits.maxParseMillis));
            workspace.resolve();
            workspace.clearParseDeadline();
        }

        json refuse(const char* code, const std::string& message) const {
            return {{"version", ResponseVersion}, {"fehler", code}, {"meldung", message}, {"diagnosen", json::array()},
                    {"vorgabeFehler", json::array()}, {"elemente", json::array()}};
        }

        /// The diagnoses of the given text (source index) as JSON entries: syntax, parser warnings and unresolved names.
        void collect(size_t source, const char* syntaxSource, const char* unresolvedSource, json& out, size_t& more) const {
            const auto full = [&] {
                if (out.size() < limits.maxDiagnostics) return false;
                ++more;
                return true;
            };
            for (const auto& error : workspace.errors(source)) {
                if (full()) continue;
                const bool isError = error->errorType() == SysMLv2::Files::ErrorType::ERROR;
                json entry = diagnosis(isError ? "GRAMMATIK" : "WARNUNG", syntaxSource, error->description());
                setPosition(entry, error->getLine(), error->getColumn());
                out.push_back(std::move(entry));
            }
            for (const auto& info : workspace.unresolvedReferences()) {
                if (info.source != source || full()) continue;
                json entry = diagnosis("LOGIK", unresolvedSource, "unresolved reference '" + info.name + "'");
                entry["name"] = info.name;
                if (info.context) entry["element"] = info.context->getType();
                setPosition(entry, info.line, info.column);
                out.push_back(std::move(entry));
            }
        }

        /// Checks one request whose `quelltext` is a string; returns the response.
        json run(const json& request) {
            const std::string text = request.at("quelltext").get<std::string>();
            const std::string given = request.contains("vorgabe") && request["vorgabe"].is_string() ? request["vorgabe"].get<std::string>() : "";

            for (const std::string* input : {&text, &given}) {
                if (input->size() > limits.maxTextBytes) {
                    return refuse("zuGross", "the text has " + std::to_string(input->size()) + " bytes, the limit is " + std::to_string(limits.maxTextBytes));
                }
                const InputScan scan = scanInput(*input, limits.maxTokens);
                if (scan.tokens > limits.maxTokens) {
                    return refuse("zuGross", "the text has more than " + std::to_string(limits.maxTokens) + " tokens");
                }
                if (scan.depth > limits.maxNestingDepth || scan.prefix > limits.maxNestingDepth) {
                    return refuse("zuTief", "the text nests deeper than " + std::to_string(limits.maxNestingDepth) + " levels (or has more prefix operators in a row)");
                }
                if (scan.operators > limits.maxOperators) {
                    return refuse("zuTief", "a statement has more than " + std::to_string(limits.maxOperators) + " operators");
                }
                if (scan.chain > limits.maxChainLength) {
                    return refuse("zuLang", "a name or feature chain has more than " + std::to_string(limits.maxChainLength) + " segments");
                }
            }

            try {
                install(given, text);
            } catch (const SysMLv2::Files::ParseTimeout&) {
                // The sources keep what the last successful replacement put there; the next request replaces them again.
                workspace.clearParseDeadline();
                return refuse("zeitueberschreitung", "parsing or resolving took longer than " + std::to_string(limits.maxParseMillis) + " ms");
            } catch (const LoadTimeout&) {
                // The packages that were loaded stay loaded; the next request continues with the others.
                return refuse("zeitueberschreitung", "loading library packages took longer than " + std::to_string(limits.maxLoadMillis) + " ms");
            }

            json diagnoses = json::array();
            json givenDiagnoses = json::array();
            json elementsJson = json::array();

            // Syntax (errors and warnings of the parser) and names that cannot be resolved.
            size_t more = 0;
            collect(userSource, "SYNTAX", "UNRESOLVED", diagnoses, more);
            // The same for the given text: reported separately, so that the author of the exercise can validate it.
            size_t givenMore = 0;
            collect(vorgabeSource, "VORGABE", "VORGABE", givenDiagnoses, givenMore);

            assignQualifiedNames(workspace.rootNamespace(userSource));
            const auto& elements = workspace.elements(userSource);

#ifdef SYSMLV2CHECK_STRUCTURE_CHECK
            // Logic: violated multiplicities, missing mandatory references and duplicate entries in the elements of the user's text
            // (workspace.elements(userSource) holds neither the given text nor the library). Derived properties are not checked
            // (includeDerived = false): the parser does not fill them. The messages are cut to 200 characters; the number of
            // diagnoses is limited like the others.
            // Not reported twice: after a syntax error the parser leaves half-built elements behind (the GRAMMATIK diagnosis says it all), and an
            // element with an unresolved reference is already reported as UNRESOLVED (its missing target is the same problem); placeholders are skipped.
            bool syntaxErrors = false;
            for (const auto& error : workspace.errors(userSource)) {
                if (error->errorType() == SysMLv2::Files::ErrorType::ERROR) syntaxErrors = true;
            }
            std::unordered_set<const Element*> unresolvedContext;
            std::unordered_set<const Element*> unresolvedNeighbours;
            for (const auto& info : workspace.unresolvedReferences()) {
                if (info.source != userSource || !info.context) continue;
                unresolvedContext.insert(info.context.get());
                // a missing reference of a relationship owned by the element that holds the unresolved reference (an alias, a membership)
                for (const auto& child : info.context->ownedElements()) {
                    if (child) unresolvedNeighbours.insert(child.get());
                }
            }
            for (const auto& element : elements) {
                if (!element || syntaxErrors || SysMLv2::Files::isUnresolved(element) || unresolvedContext.count(element.get()) != 0) continue;
                if (diagnoses.size() >= limits.maxDiagnostics) {
                    ++more;
                    continue;
                }
                for (const auto& issue : KerML::Entities::validateRepresentation(*element, false)) {
                    if (diagnoses.size() >= limits.maxDiagnostics) {
                        ++more;
                        continue;
                    }
                    if (issue.message == "Required property is missing" && unresolvedNeighbours.count(element.get()) != 0) continue;
                    std::string message = issue.property + ": " + issue.message;
                    if (message.size() > 200) message.resize(200);
                    json entry = diagnosis("LOGIK", "STRUKTUR", message);
                    entry["element"] = element->getType();
                    entry["eigenschaft"] = issue.property;
                    const std::string name = declaredNameOf(*element);
                    if (!name.empty()) entry["name"] = name;
                    diagnoses.push_back(std::move(entry));
                }
            }
#endif

            // Logic: required elements.
            if (request.contains("pflichtelemente") && request["pflichtelemente"].is_array()) {
                std::unordered_set<const Element*> own;
                for (const auto& element : elements) own.insert(element.get());
                for (const auto& required : request["pflichtelemente"]) {
                    if (!required.is_object()) continue;
                    const std::string metaclass = required.value("metaklasse", std::string());
                    const std::string name = required.value("name", std::string());
                    if (!hasElement(elements, own, metaclass, name)) {
                        if (diagnoses.size() >= limits.maxDiagnostics) {
                            ++more;
                            continue;
                        }
                        json entry = diagnosis("LOGIK", "PFLICHT",
                                               "required element missing: " + (metaclass.empty() ? std::string("element") : metaclass) + " '" + name + "'");
                        entry["name"] = name;
                        if (!metaclass.empty()) entry["element"] = metaclass;
                        diagnoses.push_back(std::move(entry));
                    }
                }
            }

            for (const auto& element : elements) {
                if (!element || std::dynamic_pointer_cast<KerML::Entities::Relationship>(element)) continue;
                if (!element->qualifiedName().has_value() || element->qualifiedName()->empty()) continue;
                elementsJson.push_back({{"metaklasse", element->getType()}, {"qualifiedName", element->qualifiedName().value()}});
            }

            return {{"version", ResponseVersion}, {"diagnosen", std::move(diagnoses)}, {"vorgabeFehler", std::move(givenDiagnoses)},
                    {"weitereDiagnosen", more}, {"weitereVorgabeFehler", givenMore}, {"elemente", std::move(elementsJson)}};
        }

        /// Whether the text has an element of the metaclass @p metaclass (empty: any) that is called @p name: through the scoped
        /// lookup of the workspace (qualified and simple names, aliases) or through the declared name, short name or qualified name
        /// of one of its elements (nested elements). Quotes are not significant: `'Mein Auto'` and `Mein Auto` are the same name.
        bool hasElement(const std::vector<std::shared_ptr<Element>>& elements, const std::unordered_set<const Element*>& own,
                        const std::string& metaclass, const std::string& name) const {
            if (name.empty()) return false;
            const auto accepts = [&](const std::shared_ptr<Element>& element) {
                return element && own.count(element.get()) != 0 && !SysMLv2::Files::isUnresolved(element) &&
                       (metaclass.empty() || element->getType() == metaclass);
            };
            if (accepts(workspace.find(name, workspace.rootNamespace(userSource)))) return true;
            const std::string wanted = normalizeQualified(name);
            for (const auto& element : elements) {
                if (!accepts(element)) continue;
                if ((element->declaredName().has_value() && unquote(element->declaredName().value()) == wanted) ||
                    (element->declaredShortName().has_value() && unquote(element->declaredShortName().value()) == wanted) ||
                    (element->qualifiedName().has_value() && element->qualifiedName().value() == wanted))
                    return true;
            }
            return false;
        }
    };

    Checker::Checker() : impl_(std::make_unique<Impl>()) {}

    Checker::~Checker() = default;

    size_t Checker::loadedLibraryCount() const {
        return impl_->libraryCount;
    }

    void Checker::setLimits(const Limits& limits) {
        impl_->limits = limits;
    }

    Checker::Limits Checker::limits() const {
        return impl_->limits;
    }

    size_t Checker::preload(const std::vector<std::string>& packages) {
        try {
            return impl_->preload(packages);
        } catch (...) {
            return 0;
        }
    }

    std::string Checker::check(const std::string& requestJson) {
        json id;   // the `id` of the request, returned unchanged in every answer
        bool hasId = false;
        const auto failure = [&](const std::string& message) {
            json result = {{"version", ResponseVersion}, {"fehler", message}, {"diagnosen", json::array()},
                           {"vorgabeFehler", json::array()}, {"elemente", json::array()}};
            if (hasId) result["id"] = id;
            return utf8Dump(result);
        };
        try {
            const json request = json::parse(requestJson, nullptr, false);
            if (request.is_discarded() || !request.is_object()) return failure("request is not a JSON object");
            if (request.contains("id")) {
                id = request["id"];
                hasId = true;
            }
            if (!request.contains("quelltext") || !request["quelltext"].is_string()) return failure("quelltext must be a string");
            json result = impl_->run(request);
            if (hasId) result["id"] = id;
            return utf8Dump(result);
        } catch (const std::exception& ex) {
            return failure(std::string("internal error: ") + ex.what());
        } catch (...) {
            return failure("internal error");
        }
    }
}
