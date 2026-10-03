# C++ SysML v2 Implementation
This library gives an implementation of the SysML v2 standard and KerML standard. This allows developers to implment own applications with this library. The existence of this library is the proof, that SysML v2 can be implemented in C++.

## Table of Contents

[toc]

## Build Status
The System and Tests: [![C/C++ CI](https://github.com/Protestator-Research/CPP-SysMLv2/actions/workflows/mainbuild.yml/badge.svg)](https://github.com/Protestator-Research/CPP-SysMLv2/actions/workflows/mainbuild.yml)

## Licensing 

This software is licensed under the GPL v3, allowing a free and open source editing of the code. We want to offer you the option to use this libary also for commercial project. This will be done in a later step, since we are currently developing this from the ground up.



## Building and usage

We offer the build work flow with conan and standalone.

### Conan Build

One of the Todos we have is to offer this library in the conan central repositories. But this can be done, if the implementation is done. You will be informed.

With this build the conan file is provided, allowing you to install the dependencies and then to build the files.

```bash
mkdir build && cd build
conan install ..
conan build ..
```



### Standalone Build

Please install the dependencies required for the build:

#### Dependencies

| Dependency        | Minimum Version |
| ----------------- |-----------------|
| antlr4-cppruntime | 4.13.1          |
| boost             | Min 1.83.0      |
| nlohmann_json     | Min 3.11.2      |
| date              | 3.0.1           |
| gtest             | 1.14.0          |

We are working on an option to only use a part of the dependencies. This will be depended on the modules that are used.

#### Build

For the build we require you to have CMake installed. This allows to have one implementation for all operating systems.

To generate the build files for your system use the following command.

```bash
mkdir build && cd build
cmake ..
make
```

For the install option use the following command install.

```bash
make install 
```

#### Build options

| CMake option                            | Conan option    | Default | Meaning |
| --------------------------------------- | --------------- | ------- | ------- |
| `BUILD_WITH_REST`                       | `with_rest`     | ON      | the SysML v2 REST entities |
| `BUILD_WITH_SERVICES`                   | `with_services` | ON      | the services (`InstanceManager`, ...) |
| `BUILD_WITH_PARSING`                    | `with_parsing`  | ON      | the KerML / SysML v2 parser, `Workspace`, the embedded standard library |
| `BUILD_WITH_ONLINE`                     | `with_online`   | ON      | the online part of the services (`SysMLAPIImplementation`, the client of a SysML v2 API server) |
| `BUILD_WITH_CHECK`                      | `with_check`    | OFF     | `sysmlv2check`, the checker for SysML v2 texts (see below) |
| `SYSMLV2_WERROR`                        | -               | ON      | compiler warnings are errors (switch off for Emscripten or optimized builds with new compilers) |

##### BUILD_WITH_ONLINE

The online part of `sysmlv2service` (`services/*/online/*`, `SysMLAPIImplementation`) talks to a SysML v2 API server and is the only part of the
library that needs libcurl. With `BUILD_WITH_ONLINE=OFF` (`conan install .. -o with_online=False`) these files are neither built nor linked, the
libcurl requirement is dropped from the Conan recipe (`date`, which is only used by the REST entities through `date/date.h`, is switched to its header-only
variant, because its time zone library needs libcurl, too), and the remaining services such as `InstanceManager` work as before. The default is ON, so nothing changes for existing users.

##### sysmlv2check

`sysmlv2check` (`check/`, `BUILD_WITH_CHECK=ON`, requires `BUILD_WITH_PARSING`) checks a SysML v2 text and answers with JSON diagnoses
(`GRAMMATIK`: syntax errors, `LOGIK`: unresolved names / missing required elements, `WARNUNG`: parser warnings, each with line and column where
known). The request and the response are documented in `check/include/sysmlv2/check/Checker.h`; in short:

```json
{ "quelltext": "package P { part x : Unknown; }", "vorgabe": "<optional SysML v2 text the text may refer to>",
  "pflichtelemente": [ { "metaklasse": "PartDefinition", "name": "Vehicle" } ] }
```

All variants share one long-living checking context (`SysMLv2::Check::Checker`): the embedded standard library packages are parsed only when
a text needs them (an `import ISQ::*;`, a `part` needs `Parts`, ...) and are then kept; for every request only the source of the text is
exchanged (`Workspace::replaceSource`). Parsing library files is slow (seconds for the first request that needs `Parts` or `ISQ`/`SI`, then
milliseconds), so keep the process or the module alive.

* C interface: `const char* sysml_pruefe(const char* anfrageJson)` returns the response (UTF-8 JSON, free it with `sysml_freigeben`).
  `sysml_vorwaermen("[\"ISQ\",\"SI\",\"Parts\"]")` loads library packages in advance, `sysml_konfigurieren("{\"maxBytes\":100000,\"maxTiefe\":64}")`
  sets the input limits.
* Command line: `sysmlv2check < request.json > response.json` reads stdin as one request; `sysmlv2check --lines` reads one request per
  line (JSON Lines) and writes one response line per request, keeping the context between the lines (use this from another program).
  `--vorwaermen=ISQ,SI,Parts` loads these packages (and what they import) before the first request; `--max-bytes=N` and `--max-tiefe=N` set the
  input limits (`--max-tokens=`, `--max-kette=`, `--max-operatoren=`, `--max-ms=`, `--max-lade-ms=`, `--max-diagnosen=` too; an unusable number ends the program with exit code 2). An `id` in a request is returned unchanged in its response; only response lines are
  written to stdout.
* Input limits: a `quelltext` or `vorgabe` larger than 100 KB or with more than 20000 tokens (`zuGross`), nesting `{`, `(`, `[` deeper than 64 levels
  (`zuTief`) or with a feature chain / qualified name of more than 64 segments (`zuLang`) is refused before it is parsed, with `"fehler"` set in
  the response. The scan follows the lexer: an unterminated comment or string does not hide anything. As a safety net parsing has a deadline
  (`maxMs`, default 20 s, `zeitueberschreitung`; once for parsing and once for resolving); loading library files is exempt from it, but a
  request may spend at most `maxLadeMs` (default 60 s, also `zeitueberschreitung`) loading packages that are not loaded yet. **Production:** start the
  process with `--vorwaermen=alle` (C interface: `sysml_vorwaermen("[\"*\"]")`), which loads the whole standard library once (about 20-35 s); without it
  the first request that imports many packages needs that long. More than 64 prefix operators in a row (`- - -x`, `not not x`) count as nesting
  (`zuTief`); texts are parsed on a thread with a large stack. At most 200 diagnoses are returned (`maxDiagnosen`), the rest is counted in
  `weitereDiagnosen`. The parser needs far more time for deeply nested
  input than the size suggests and cannot be interrupted, so the host must always run a check where it can be aborted by a timeout.
* Recommended settings for production: a release build (the numbers above are from Debug builds with a Debug ANTLR runtime), the process
  started with `--lines --vorwaermen=alle --max-ms=10000 --max-lade-ms=5000` (the short load limit only makes sense together with
  `--vorwaermen=alle`; an interrupted load is completed by the following requests, but they then answer `zeitueberschreitung` until it is
  done), the host aborts a check that takes much longer than the deadlines (see above), and the host recycles the process regularly (for
  example after some thousand requests or when its memory has grown), because the parser keeps caches.
* Positions (`zeile`, `spalte`): the line is 1-based, the column 0-based and counts Unicode code points (a tab counts 1).
* `vorgabeFehler` in the response lists the syntax errors and unresolved names of the optional `vorgabe` (source `VORGABE`), so that the author
  of an exercise can validate the given text.
* Source levels: the library, the `vorgabe` and the `quelltext` are sources of different levels (`Workspace::setSourceLevel`); a name only
  resolves to elements of the same or a lower level, so a text that defines a package with the name of a library package cannot change what the
  library refers to.
* Operators: at most 256 operators (`+ - * ** and or implies if else ...`) between two `;`, `{` or `}` (`maxOperatoren`, `zuTief`): the parser recurses once per operator of a chain (`1 + 1 + ...`), which overflows small host stacks (V8 in a browser fails at about 3000). Together with the nesting depth and prefix operator limits this keeps every accepted text far below the stack.
* Structure check (`STRUKTUR`, category `LOGIK`): `KerML::Entities::validateRepresentation()` (generated by
  `kerml/tools/generate_abstract_syntax.py`, `kerml/src/kerml/model/Representation.cpp`) checks the elements of the `quelltext` (not the
  `vorgabe`, not the library, no derived properties) for missing mandatory references, violated multiplicities and null / duplicate entries.
  Switch: CMake option `SYSMLV2CHECK_VALIDATE_REPRESENTATION` (default ON). The message is `<Class.property>: <problem>`, at most 200
  characters; the diagnoses count against `maxDiagnosen`. Valid models (also the whole standard library as input) produce none; a syntax error
  leaves half-built elements behind, which are not reported again: with a `GRAMMATIK` error in the text there is no `STRUKTUR` diagnosis, and a missing reference next to an `UNRESOLVED` one is skipped (an alias of an unknown name is exactly one Logik diagnosis). The check does not evaluate OCL constraints (for example `[3..1]`).
  The cost is small (about 0-3 % of a warm request, Debug build).
* Tests: `sysmlv2check-test` (with `BUILD_TESTING=ON`).
* WebAssembly (Emscripten, tested with emsdk 5.0.2 and Node 24): `check/cmake/build-wasm.sh` runs the Conan install (profile `check/cmake/emscripten.profile`:
  static libraries, `-fwasm-exceptions`, `boost` header-only, `date` header-only, no curl), configures CMake (`check/cmake/Emscripten.cmake`, the same
  variables as the preset `emscripten-check` in `check/cmake/EmscriptenPresets.json`; `-O2`, no LTO) and builds `build/wasm/out/sysmlv2check.js` (ES module,
  `MODULARIZE`/`EXPORT_ES6`, `ENVIRONMENT=web,worker,node`) with `sysmlv2check.wasm` next to it. The standard library is embedded in the module. Exports:
  `sysml_pruefe`, `sysml_freigeben`, `sysml_vorwaermen`, `sysml_konfigurieren`, `malloc`, `free` (and `ccall`, `cwrap`, `UTF8ToString`). There is one stack of 64 MB
  (`STACK_SIZE`), no parse thread (the 512 MB stack thread is only used on other platforms; the nesting limits protect the stack). Use one module instance per
  worker and terminate the worker on a timeout (a check cannot be interrupted). Smoke test: `node check/tests/wasm-smoke.mjs [sysmlv2check.js]` (11 cases:
  valid model, syntax error, `UNRESOLVED`, `PFLICHT`, library import, `STRUKTUR`, invalid requests, limits, parse deadline). Measured with Node 24 (Release `-O2`):
  `.wasm` 4.6 MB raw / 0.95 MB gzip (+16 KB JS), module start 12 ms, `sysml_vorwaermen(["*"])` (whole library, 41 files) 1.9 s, a warm request about 43 ms. Memory: the linear memory starts at 64 MB (`INITIAL_MEMORY`), is 77 MB after the first request, 159 MB with the whole library, and may grow to 1 GB (`MAXIMUM_MEMORY`); `sysml_speicher()` returns its size in bytes (a host can recycle the instance above a threshold). The shadow stack is 16 MB.
  `-flto` makes the module 5 % bigger without being faster.

```bash
conan install .. -o with_check=True
conan build ..
echo '{"quelltext":"package P { part def A; part a : A; }"}' | ./out/sysmlv2check
```

# Autors

## Main Authors:

- Moritz Herzog

## Other Authors:

- Tizian Hoffmann
- Pascal Grabowsky

## SysML v2

The SysML v2 Standard is developed and published by the Object Modelling Group (OMG).
