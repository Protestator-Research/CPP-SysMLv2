//
// sysmlv2check: command line interface of the checker for SysML v2 texts.
//
//   sysmlv2check            reads all of stdin as ONE request (JSON), writes the response (JSON, one line) to stdout.
//   sysmlv2check --lines    reads one request per line (empty lines are skipped) and writes one response line per request,
//                           flushed after every line. The checking context (standard library) is created once and reused for all
//                           requests, so a long-living process is much faster than one process per request.
// Options: --vorwaermen=ISQ,SI,Parts  loads these library packages (and what they import) before the first request (also warms the
//                                     parser: later requests are faster); --max-bytes=N / --max-tiefe=N  the input limits
//                                     (default 102400 bytes, nesting depth 64).
//          --max-tokens=N / --max-kette=N / --max-ms=N / --max-lade-ms=N / --max-diagnosen=N  the token limit, the chain length limit,
//          the parse deadline and the limit for loading library packages during a request (milliseconds), the number of diagnoses.
//          --vorwaermen=alle loads the whole standard library at the start (recommended in production: the first request that needs
//          many packages would take half a minute). A number that cannot be read ends the program with exit code 2.
// An "id" in a request is returned unchanged in its response. Only response lines are written to stdout: whatever the library prints
// to stdout while it works is redirected to stderr.
// The exit code is 0 unless the input could not be read. Request and response: see SysMLv2::Check::Checker.
//
#include <sysmlv2/check/Checker.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace {
    /// The real stdout is kept for the responses; file descriptor 1 is redirected to stderr, so that nothing the library or its
    /// dependencies print with std::cout or printf can end up between the response lines.
    FILE* takeStdout() {
        std::fflush(stdout);
#ifdef _WIN32
        const int saved = _dup(1);
        _dup2(2, 1);
        return _fdopen(saved, "w");
#else
        const int saved = dup(1);
        dup2(2, 1);
        return fdopen(saved, "w");
#endif
    }

    void respond(FILE* out, const std::string& line) {
        std::fwrite(line.data(), 1, line.size(), out);
        std::fputc('\n', out);
        std::fflush(out);
    }
}

namespace {
    /// The number after `option=`; an unusable value ends the program with a message and exit code 2.
    size_t number(const std::string& argument, size_t prefixLength) {
        const std::string text = argument.substr(prefixLength);
        size_t used = 0;
        unsigned long long value = 0;
        try {
            if (!text.empty() && text[0] != '-') value = std::stoull(text, &used);
        } catch (const std::exception&) {
            used = 0;
        }
        if (used == 0 || used != text.size()) {
            std::cerr << "sysmlv2check: " << argument.substr(0, prefixLength) << " needs a non-negative number, got '" << text << "'\n";
            std::exit(2);
        }
        return static_cast<size_t>(value);
    }
}

int main(int argc, char** argv) {
    bool lines = false;
    std::vector<std::string> preload;
    SysMLv2::Check::Checker::Limits limits;
    for (int i = 1; i < argc; ++i) {
        const std::string argument = argv[i];
        if (argument == "--lines" || argument == "--zeilen") {
            lines = true;
        } else if (argument.rfind("--vorwaermen=", 0) == 0) {
            std::stringstream names(argument.substr(13));
            for (std::string name; std::getline(names, name, ',');) {
                if (!name.empty()) preload.push_back(name == "alle" ? "*" : name);
            }
        } else if (argument.rfind("--max-bytes=", 0) == 0) {
            limits.maxTextBytes = number(argument, 12);
        } else if (argument.rfind("--max-tiefe=", 0) == 0) {
            limits.maxNestingDepth = number(argument, 12);
        } else if (argument.rfind("--max-tokens=", 0) == 0) {
            limits.maxTokens = number(argument, 13);
        } else if (argument.rfind("--max-kette=", 0) == 0) {
            limits.maxChainLength = number(argument, 12);
        } else if (argument.rfind("--max-operatoren=", 0) == 0) {
            limits.maxOperators = number(argument, 17);
        } else if (argument.rfind("--max-ms=", 0) == 0) {
            limits.maxParseMillis = number(argument, 9);
        } else if (argument.rfind("--max-lade-ms=", 0) == 0) {
            limits.maxLoadMillis = number(argument, 14);
        } else if (argument.rfind("--max-diagnosen=", 0) == 0) {
            limits.maxDiagnostics = number(argument, 16);
        } else {
            std::cerr << "usage: sysmlv2check [--lines] [--vorwaermen=alle|ISQ,SI,...] [--max-bytes=N] [--max-tiefe=N] [--max-tokens=N] [--max-kette=N] [--max-operatoren=N] [--max-ms=N] [--max-lade-ms=N] [--max-diagnosen=N] < request.json\n";
            return argument == "--help" ? 0 : 2;
        }
    }
    FILE* out = takeStdout();

    SysMLv2::Check::Checker checker;
    checker.setLimits(limits);
    if (!preload.empty()) checker.preload(preload);
    if (lines) {
        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
            respond(out, checker.check(line));
        }
        return 0;
    }
    const std::string request((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
    if (std::cin.bad()) return 1;
    respond(out, checker.check(request));
    return 0;
}
