# sysmlv2

Checker and parser for SysML v2 textual notation. A thin, typed Python API (ctypes, no runtime dependencies) around the
native C++ library of [CPP-SysMLv2](https://github.com/Protestator-Research/CPP-SysMLv2): syntax errors, unresolved names,
structure violations, required elements and (optionally) the full parsed model in the SysML v2 API JSON format.

```python
import sysmlv2

result = sysmlv2.check("package P { part def Vehicle; part v : Vehicle; }",
                       required_elements=[("PartDefinition", "Vehicle")])
print(result.ok)                       # True
for d in sysmlv2.check("package P { part x : Unknown; }").diagnostics:
    print(d)                           # 1:20: LOGIC/UNRESOLVED: ...

model = sysmlv2.parse("package P { part def A; }").model
part = model.of_type("PartDefinition")[0]
print(part["declaredName"], model.find("P").get("qualifiedName"))
```

## API

* `check(text, *, given_text=None, required_elements=None, model=False, request_id=None) -> CheckResult`
* `parse(text, *, given_text=None) -> CheckResult` (`check` with `model=True`)
* `preload(packages) -> int` loads standard library packages (`"Parts"`, `"ISQ"`, `"*"` = all) in advance
* `configure(*, max_bytes, max_depth, max_tokens, max_chain_length, max_operators, max_parse_ms, max_load_ms, max_diagnostics, max_model_elements)`
  sets input limits (`ValueError` if the library rejects them)
* `Checker(*, isolated=False, timeout=None)` with the same methods; see below
* `CheckResult`: `diagnostics`, `given_text_errors`, `elements`, `model`, `more_diagnostics`, `more_given_text_errors`, `model_errors`,
  `model_incomplete`, `error`, `error_message`, `request_id`, `raw` (the decoded JSON), and `ok` / `errors` / `warnings`
* `Diagnostic(category, source, message, line, column, name, element, property_name)`; `line` is 1-based, `column` 0-based
* Enums (`str` valued): `Category` (`GRAMMAR`, `LOGIC`, `WARNING`), `Source` (`SYNTAX`, `UNRESOLVED`, `STRUCTURE`, `REQUIRED`, `GIVEN_TEXT`),
  `ErrorKind` (`TOO_LARGE`, `TOO_DEEP`, `TOO_LONG`, `TIMEOUT`, `INVALID_REQUEST`, `INTERNAL`). Values a newer native library adds map to `UNKNOWN`
  (the original is in `raw`).
* `Model`: `elements`, `root`, `by_id`, `resolve`, `of_type`, `find`, `owned_relationships`, `owned_elements`. Elements stay plain dicts.
  The `@id`s are random per request. Library elements appear only as `{"@id": ...}` references; implied relationships are not materialized.
* Exceptions: `SysMLv2Error` (base), `CheckTimeout`, `NativeLibraryError`, `WorkerCrashed`.

The first request that needs standard library packages (every `part`, `import ISQ::*;`, ...) takes seconds because the library is
parsed on demand; later ones take milliseconds. Call `preload([...])` at start-up.

### Servers: use an isolated Checker

The native parser cannot be interrupted and may need very long for hostile input. The input limits keep honest input fast, but a
server must still be able to abort a check:

```python
if __name__ == "__main__":                       # required: the worker is started with "spawn"
    checker = sysmlv2.Checker(isolated=True, timeout=10)
    checker.configure(max_bytes=50_000)
    checker.preload(["Parts"])
    try:
        result = checker.check(untrusted_text)
    except sysmlv2.CheckTimeout:
        ...                                       # the worker was terminated; the next call starts a new one
```

Starting a worker, the replay of the configuration and of the preloads happen without a time limit, so the cold start does not count
against `timeout`. Every request carries a sequence number and any exception during a call (also `KeyboardInterrupt`) kills the worker, so
a later call can never see the answer of an earlier one. `close()` kills the worker without waiting for a running call (also done when the
`Checker` is garbage collected). `timeout` must be > 0 and needs `isolated=True`. An isolated `Checker` cannot be created inside a daemonic
process (`multiprocessing` daemons may not have children), and after `fork()` the child starts its own worker. A `Checker` serializes its calls; use several for
parallelism. The default (in-process) checker used by the module functions shares one process-wide native context.

The library is found next to the package; `SYSMLV2_NATIVE_LIBRARY` overrides the path.

## Building the wheel

The native library (`sysmlv2check_native`, built by `check/python/CMakeLists.txt`) is self-contained: all dependencies are linked statically
and only the five C functions are exported. The wheel is `py3-none-<platform>` (ctypes, no Python ABI) and holds the library next to the
Python sources. On Windows the MSVC runtime is linked statically (no `MSVCP140.dll` / `VCRUNTIME140.dll` needed).

scikit-build-core does not run Conan, so install the dependencies first. `python/tools/conan_deps.py` runs `conan install` with the static
options, finds `conan_toolchain.cmake` and the CMake generator Conan configured and exports both as `CMAKE_TOOLCHAIN_FILE` /
`CMAKE_GENERATOR` (CMake >= 3.21 honors them), so scikit-build-core configures with exactly what Conan prepared.

Requirements: Python >= 3.9, Conan 2, CMake >= 3.21 and a C++20 compiler (Visual Studio 2022 on Windows). `pip` installs
`scikit-build-core` itself in the isolated build environment.

```bash
# one step (installs the dependencies, writes python/THIRD_PARTY_LICENSES.txt, then runs `pip wheel`); keep paths SHORT on Windows (MAX_PATH)
python python/tools/conan_deps.py --output-folder C:/b/whl/conan --wheel C:/b/whl/dist -- --config-settings=build-dir=C:/b/whl/sk

# or two steps
eval "$(python python/tools/conan_deps.py --format sh)"            # PowerShell: ... --format powershell | Invoke-Expression ; cmd: --format cmd
python -m pip wheel . --no-deps -w dist                            # or: python -m build --wheel
```

The licenses of the statically linked dependencies (ANTLR4, Boost, pugixml, nlohmann_json, ...) are collected from the Conan packages
into `python/THIRD_PARTY_LICENSES.txt` (generated, not versioned) and shipped in the wheel's `dist-info/licenses`.

**The sdist is not self-contained:** building from it needs the Conan step above (CMake must find the dependencies through
`CMAKE_TOOLCHAIN_FILE`), exactly like a build from a checkout.

**cibuildwheel:** environment variables exported in `CIBW_BEFORE_BUILD` do not reach the build. Either use a fixed `--output-folder` and put the
printed `CMAKE_TOOLCHAIN_FILE` / `CMAKE_GENERATOR` into `CIBW_ENVIRONMENT`, or call the helper with `--wheel` (it runs `pip wheel` itself). Target
`manylinux_2_28`; the helper runs `conan profile detect --exist-ok` and always uses C++20.

The wheel is tagged `py3-none-<platform>`: the library does not depend on the Python version, so there is one wheel per platform and
architecture (build it with any CPython >= 3.9; no per-version builds).

macOS: build one wheel per architecture (`--arch armv8` or `--arch x86_64`, or via `ARCHFLAGS` / `_PYTHON_HOST_PLATFORM`; `MACOSX_DEPLOYMENT_TARGET` becomes
`os.version`), not universal2. Windows ARM64 (`--arch armv8` on x64) is a Conan cross build. Other Conan settings go through `--conan-arg=...`. Test the wheel:

```bash
python -m venv venv && venv/bin/pip install dist/sysmlv2-*.whl pytest && venv/bin/python -m pytest python/tests
```

The tests that need no native library (`test_protocol.py`) also run from a source checkout (`PYTHONPATH=python/src`); with
`SYSMLV2_NATIVE_LIBRARY` pointing to a built library the others run, too.

License: GPL-3.0-only.
