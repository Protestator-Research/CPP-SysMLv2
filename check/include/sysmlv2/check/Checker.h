//
// Checker for SysML v2 texts: syntax, name resolution, structure and required elements, against a long-living context that
// holds the standard library.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/check/sysmlv2check_global.h>
//---------------------------------------------------------

namespace SysMLv2::Check {

    /**
     * @class Checker
     * @brief Checks SysML v2 texts. Holds one SysMLv2::Files::Workspace with the embedded standard library (the long-living
     * context) and exchanges only the sources of the text to check for every request.
     *
     * Construction loads the package Base (with what it imports). Parsing the library is the expensive part of a check, so every
     * other library package is loaded when a request needs it and kept for all later requests: the packages that the
     * implicit specializations of the language elements of the text refer to (a `part` needs `Parts`, ...) and every package that a
     * name of the text starts with and that is not loaded yet (`import ISQ::*;`, `SI::kg`), with everything these import. A request
     * puts the text (and the optional `vorgabe`, a given SysML v2 text that the text may refer to) into two fixed sources of
     * the workspace with Workspace::replaceSource(), so a request never sees anything of an earlier one.
     *
     * A Checker is not thread safe: use one per thread, or serialize the calls (the C interface does).
     *
     * The request (JSON, UTF-8):
     * @code
     * { "quelltext": "<SysML v2 text>",
     *   "vorgabe": "<SysML v2 text, optional>",
     *   "pflichtelemente": [ { "metaklasse": "PartDefinition", "name": "Vehicle" }, ... ] }   // optional
     * @endcode
     * The response (JSON):
     * @code
     * { "version": "1",
     *   "diagnosen": [ { "kategorie": "GRAMMATIK" | "LOGIK" | "WARNUNG",
     *                    "quelle": "SYNTAX" | "UNRESOLVED" | "STRUKTUR" | "PFLICHT",
     *                    "zeile": 3, "spalte": 14,      // 1-based line, 0-based column in Unicode code points (a tab counts 1); only if known
     *                    "name": "...", "element": "...", "eigenschaft": "...", "meldung": "..." }, ... ],
     *   "vorgabeFehler": [ { "kategorie": ..., "quelle": "VORGABE", "zeile": ..., "meldung": ... }, ... ],
     *   "elemente": [ { "metaklasse": "PartDefinition", "qualifiedName": "P::Vehicle" }, ... ] }
     * @endcode
     *  - GRAMMATIK / SYNTAX: a syntax error of `quelltext` (also internal errors while the parse tree was processed).
     *  - WARNUNG / SYNTAX: a warning of the parser for `quelltext`.
     *  - LOGIK / UNRESOLVED: a name of `quelltext` that cannot be resolved (`name`: the name as written).
     *  - LOGIK / STRUKTUR: KerML::Entities::validateRepresentation() found a structural violation in an element of `quelltext`: a missing
     *    mandatory reference, a violated multiplicity, a null or duplicate entry (`meldung`: "<property>: <problem>", at most 200 characters;
     *    `element`: its metaclass, `name`: its declared name if any, `eigenschaft`: the property). Derived properties are not checked. Only
     *    present if the library is built with SYSMLV2CHECK_VALIDATE_REPRESENTATION (default ON, see check/CMakeLists.txt). Not reported twice: with a
     *    GRAMMATIK error in the text there is no STRUKTUR diagnosis (the half-built elements are consequences), and a missing reference next to an
     *    UNRESOLVED one is skipped.
     *  - LOGIK / PFLICHT: no element of `quelltext` has the metaclass `metaklasse` and the name `name` (the declared name,
     *    the short name or the qualified name; `element` repeats the metaclass).
     *  - "vorgabeFehler": the syntax errors, warnings and unresolved names of `vorgabe` (empty if there is none), so that the author
     *    of an exercise can validate the given text. They are not part of "diagnosen".
     *  - Names are compared and reported without their quotes: `part def 'Mein Auto';` is `Mein Auto` in "pflichtelemente" and
     *    in "qualifiedName" (`P::Mein Auto`).
     *  - "elemente": the named elements of `quelltext` (not of `vorgabe` or the library) that are no relationships.
     * "weitereDiagnosen" and "weitereVorgabeFehler" count the diagnoses that were left out because of Limits::maxDiagnostics.
     * A request that is an object may carry an `id` (any JSON value, also null); the response, also an error response, contains it
     * unchanged. A request that is not valid JSON, or whose `quelltext` is not a string, yields
     * `{ "version": "1", "fehler": "<text>", "diagnosen": [], "vorgabeFehler": [], "elemente": [] }`.
     *
     * Input limits (see Limits, checked before anything is parsed): a `quelltext` or `vorgabe` with more than maxTextBytes bytes is
     * answered with `"fehler": "zuGross"`, one that nests `{`, `(` or `[` deeper than maxNestingDepth (or has more than that many prefix operators in a row, `- - - x`, `not not x`: the parser recurses once per operator) (comments, strings and quoted
     * names do not count) with `"fehler": "zuTief"`, one with more than maxTokens tokens with `"zuGross"`, one with a feature chain or qualified
     * name of more than maxChainLength segments with `"zuLang"` (all plus a "meldung"); "diagnosen" and "elemente" are empty then. The parser needs
     * far more time than the size of a text suggests for deeply nested input, and parsing cannot be interrupted: the limits keep
     * the time in bounds for honest input, but THE HOST MUST STILL ABORT A CHECK THAT TAKES TOO LONG (run it in a process or worker that
     * can be terminated) and must not wait for a check forever. As a safety net the parse of the two texts has a deadline (maxParseMillis):
     * `"fehler": "zeitueberschreitung"`. The scan of the limits counts tokens like the lexer does, an unterminated comment or string
     * does not hide anything from it; the deadline is checked while the parser reads tokens, so it can overrun if one step takes long.
     *
     * Names that are only known to the library are not loaded before they are needed; the first request that needs `Parts`, `ISQ`, ...
     * is slow (seconds, the parser is slow for library files), the following ones are fast. preload() loads packages in advance.
     *
     * Order of work for a request: the texts are parsed; if they need library packages that are not loaded yet, they are taken out of
     * the workspace again, the packages are loaded and resolved alone, and only then the texts are put in and resolved. In addition the
     * sources have levels (library < vorgabe < quelltext, see Workspace::setSourceLevel), so a library name never resolves to an element
     * of a text that happens to use the name of a library package.
     */
    class SYSMLV2CHECK_EXPORT Checker {
    public:
        Checker();
        ~Checker();
        Checker(const Checker&) = delete;
        Checker& operator=(const Checker&) = delete;

        /// Limits of the input of a request, see the class description.
        struct Limits {
            size_t maxTextBytes = 100 * 1024;
            size_t maxNestingDepth = 64;
            /// Most tokens of a text (comments, strings and quoted names count as one).
            size_t maxTokens = 20000;
            /// Most operators (`+ - * ** and or implies if else ...`) in one statement, i.e. between two `;`, `{` or `}` (`zuTief`): the parser
            /// recurses once per operator of a chain, which overflows small stacks (V8 in a browser: about 3000 operators).
            size_t maxOperators = 256;
            /// Most segments of a feature chain or qualified name (`a.b.c`, `A::b`).
            size_t maxChainLength = 64;
            /// Deadline in milliseconds for parsing the text and the given text of one request, and again for resolving them (loading library
            /// files is exempt, see maxLoadMillis).
            size_t maxParseMillis = 20000;
            /// Time a request may spend loading library packages that are not loaded yet (`zeitueberschreitung` when it has passed,
            /// checked between the files; what was loaded stays loaded). A text that imports the whole library needs about 30 s and
            /// more on a fresh process: start production processes with preload({"*"}) (CLI `--vorwaermen=alle`).
            size_t maxLoadMillis = 60000;
            /// Most entries in "diagnosen" and in "vorgabeFehler"; the rest is counted in "weitereDiagnosen" and "weitereVorgabeFehler".
            size_t maxDiagnostics = 200;
        };
        void setLimits(const Limits& limits);
        Limits limits() const;

        /**
         * Loads library packages (by name, `"ISQ"`, `"SI"`, `"Parts"`, ...) and everything they import now, so that no request has to
         * do it. Parsing them also warms the caches of the parser, which makes the requests that follow faster. Unknown names are
         * ignored. The name `*` (or `alle`) loads the whole standard library.
         * @return the number of library files added.
         */
        size_t preload(const std::vector<std::string>& packages);

        /// Checks one request (see the class description). Never throws.
        std::string check(const std::string& requestJson);

        /// Number of library packages (files) in the context; grows when a request needs a package that was not loaded yet.
        size_t loadedLibraryCount() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
