#!/usr/bin/env python3
"""Installs the Conan dependencies (static build) for the Python wheel and prepares the environment for scikit-build-core.

scikit-build-core does not run Conan. This script runs ``conan install`` with the options of the self-contained native
library (static libraries, no REST / services / online part), finds the generated ``conan_toolchain.cmake`` and the CMake
generator Conan configured, collects the licenses of the statically linked dependencies into
``python/THIRD_PARTY_LICENSES.txt`` (shipped in the wheel), and either prints the environment for your shell or builds the wheel:

    python python/tools/conan_deps.py --output-folder C:/b/whl/conan --wheel dist -- --config-settings=build-dir=C:/b/whl/sk
    python python/tools/conan_deps.py --output-folder C:/b/whl/conan --format powershell | Invoke-Expression
    eval "$(python python/tools/conan_deps.py --format sh)"                    # then: python -m build --wheel

Everything after ``--`` is passed to ``pip wheel``; unknown arguments before it are an error.

CMake (>= 3.21) reads the environment variables CMAKE_TOOLCHAIN_FILE and CMAKE_GENERATOR, so scikit-build-core configures with the
toolchain and generator Conan prepared (on Windows the Visual Studio generator; Ninja would need a developer prompt and a matching
``--conan-arg=-c --conan-arg=tools.cmake.cmaketoolchain:generator=Ninja``).

cibuildwheel: environment variables set in CIBW_BEFORE_BUILD do NOT reach the build. Use a fixed ``--output-folder`` and set
CMAKE_TOOLCHAIN_FILE (and CMAKE_GENERATOR) in CIBW_ENVIRONMENT to the paths printed here, or let this script run the build with ``--wheel``.
Target Linux wheels manylinux_2_28 (Conan profile with compiler.libcxx=libstdc++11).

Architecture: ``--arch``, else ARCHFLAGS (macOS), _PYTHON_HOST_PLATFORM, else the machine; x86_64 / armv8 (arm64, aarch64, ARM64 map to
armv8). A different architecture than the machine's is a cross build (``-s:h arch=...``). macOS: MACOSX_DEPLOYMENT_TARGET becomes
``-s os.version=``; build one wheel per architecture, not universal2.
"""

from __future__ import annotations

import argparse
import json
import os
import platform
import re
import shlex
import subprocess
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional

ROOT = Path(__file__).resolve().parents[2]
LICENSES_FILE = ROOT / "python" / "THIRD_PARTY_LICENSES.txt"

OPTIONS = [
    "shared=False",
    "with_online=False",
    "with_check=True",
    "with_rest=False",
    "with_services=False",
]

_ARCH = {"x86_64": "x86_64", "amd64": "x86_64", "x64": "x86_64", "arm64": "armv8", "aarch64": "armv8", "armv8": "armv8"}


def run(command: List[str], env: Optional[Dict[str, str]] = None, capture: bool = False) -> str:
    print("+ " + " ".join(shlex.quote(c) for c in command), file=sys.stderr, flush=True)
    result = subprocess.run(command, check=True, cwd=ROOT, env=env, stdout=subprocess.PIPE if capture else sys.stderr, text=capture, encoding="utf-8" if capture else None)
    return result.stdout if capture else ""


def normalize_arch(value: str) -> str:
    try:
        return _ARCH[value.strip().lower()]
    except KeyError:
        raise SystemExit(f"unsupported architecture {value!r} (x86_64, armv8)")


def requested_arch(explicit: Optional[str]) -> str:
    if explicit:
        return normalize_arch(explicit)
    archflags = re.findall(r"-arch\s+(\S+)", os.environ.get("ARCHFLAGS", ""))
    if len(set(archflags)) == 1:
        return normalize_arch(archflags[0])
    host_platform = os.environ.get("_PYTHON_HOST_PLATFORM", "")  # e.g. macosx-11.0-arm64, linux-aarch64, win-arm64
    for key in _ARCH:
        if host_platform.lower().endswith(key):
            return _ARCH[key]
    return normalize_arch(platform.machine() or "x86_64")


def conan_install(args: argparse.Namespace) -> Dict[str, Any]:
    run(["conan", "profile", "detect", "--exist-ok"])
    out = Path(args.output_folder).resolve()
    command = ["conan", "install", str(ROOT), "-of", str(out), "-s", f"build_type={args.build_type}", "-s", "compiler.cppstd=20"]
    for option in OPTIONS:
        command += ["-o", f"&:{option}"]
    arch = requested_arch(args.arch)
    native = normalize_arch(platform.machine() or "x86_64")
    command += ["-s:h", f"arch={arch}"] if arch != native else ["-s", f"arch={arch}"]  # cross build: only the host context
    if args.static_crt and sys.platform == "win32":
        command += ["-s", "compiler.runtime=static"]  # MSVC /MT: no MSVCP140.dll / VCRUNTIME140.dll needed
    if sys.platform == "darwin" and os.environ.get("MACOSX_DEPLOYMENT_TARGET"):
        command += ["-s", f"os.version={os.environ['MACOSX_DEPLOYMENT_TARGET']}"]
    command += ["-b", "missing", "-c", "tools.build:skip_test=True", "--format=json"] + args.conan_arg
    output = run(command, capture=True)
    try:
        return json.loads(output)
    except json.JSONDecodeError as exc:
        raise SystemExit(f"cannot parse the JSON output of conan install: {exc}")


def find_toolchain(out: Path, build_type: str) -> Path:
    """The deterministic location: multi-config generators write to build/generators, single-config ones to build/<type>/generators."""
    for candidate in (out / "build" / build_type / "generators", out / "build" / "generators", out / "generators"):
        if (candidate / "conan_toolchain.cmake").is_file():
            return candidate / "conan_toolchain.cmake"
    raise SystemExit(f"conan_toolchain.cmake not found below {out} (looked in build/{build_type}/generators, build/generators, generators)")


def configured_generator(toolchain: Path) -> Dict[str, str]:
    """The generator Conan chose, from the CMakePresets.json it wrote next to the toolchain."""
    env: Dict[str, str] = {}
    for candidate in (toolchain.parent / "CMakePresets.json", toolchain.parent.parent / "CMakePresets.json"):
        if not candidate.is_file():
            continue
        for preset in json.loads(candidate.read_text(encoding="utf-8")).get("configurePresets", []):
            if "generator" in preset:
                env["CMAKE_GENERATOR"] = preset["generator"]
                for key, name in (("toolset", "CMAKE_GENERATOR_TOOLSET"), ("architecture", "CMAKE_GENERATOR_PLATFORM")):
                    value = preset.get(key)
                    if value:
                        env[name] = value if isinstance(value, str) else str(value.get("value", ""))
                return {k: v for k, v in env.items() if v}
    return env


def collect_licenses(graph: Dict[str, Any]) -> int:
    """Writes the license files of all host (= statically linked) packages into LICENSES_FILE; returns the number of packages."""
    nodes = graph.get("graph", {}).get("nodes", {})
    sections = []
    for node in nodes.values():
        folder = node.get("package_folder")
        if node.get("context") != "host" or not folder or not node.get("name"):
            continue
        files = sorted(p for p in (Path(folder) / "licenses").rglob("*") if p.is_file()) if (Path(folder) / "licenses").is_dir() else []
        if not files:
            continue
        header = f"{node['name']}/{node.get('version', '?')}  (license: {node.get('license') or 'see text'})"
        body = "\n\n".join(f"--- {f.name} ---\n{f.read_text(encoding='utf-8', errors='replace').strip()}" for f in files)
        sections.append(f"{'=' * 78}\n{header}\n{'=' * 78}\n{body}\n")
    LICENSES_FILE.write_text(
        "Third-party software statically linked into the native library of the sysmlv2 package.\n"
        "The package itself is GPL-3.0-only (see LICENSE).\n\n" + "\n".join(sorted(sections)),
        encoding="utf-8",
    )
    print(f"{len(sections)} dependency license(s) written to {LICENSES_FILE}", file=sys.stderr)
    return len(sections)


def emit(env: Dict[str, str], fmt: str) -> str:
    if fmt == "json":
        return json.dumps(env, indent=2)
    lines = []
    for key, value in env.items():
        if fmt == "cmd":
            lines.append(f'set "{key}={value}"')
        elif fmt == "powershell":
            lines.append("$env:%s = '%s'" % (key, value.replace("'", "''")))
        elif fmt == "github":
            lines.append(f"{key}={value}")
        else:
            lines.append(f"export {key}={shlex.quote(value)}")
    return "\n".join(lines)


def main() -> int:
    argv = sys.argv[1:]
    pip_args: List[str] = []
    if "--" in argv:
        split = argv.index("--")
        argv, pip_args = argv[:split], argv[split + 1:]
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--output-folder", "-of", default=str(ROOT / "build-python" / "conan"),
                        help="Conan output folder (Windows: keep the path SHORT, MAX_PATH; default: <repo>/build-python/conan)")
    parser.add_argument("--build-type", default="Release")
    parser.add_argument("--arch", help="x86_64 or armv8 (aliases arm64, aarch64, amd64)")
    parser.add_argument("--no-static-crt", dest="static_crt", action="store_false", help="MSVC: dynamic CRT (default: static)")
    parser.add_argument("--conan-arg", action="append", default=[], help="additional argument for 'conan install' (repeatable, use --conan-arg=VALUE)")
    parser.add_argument("--format", choices=["sh", "cmd", "powershell", "github", "json"], default="cmd" if os.name == "nt" else "sh",
                        help="how to print CMAKE_TOOLCHAIN_FILE / CMAKE_GENERATOR (github: lines for $GITHUB_ENV)")
    parser.add_argument("--wheel", metavar="DIR", help="after installing, build the wheel into DIR with 'pip wheel'")
    args = parser.parse_args(argv)
    if pip_args and not args.wheel:
        parser.error("arguments after -- are only used with --wheel")

    graph = conan_install(args)
    collect_licenses(graph)
    toolchain = find_toolchain(Path(args.output_folder).resolve(), args.build_type)
    env = {"CMAKE_TOOLCHAIN_FILE": str(toolchain)}
    env.update(configured_generator(toolchain))

    if args.wheel:
        full = dict(os.environ, **env)
        run([sys.executable, "-m", "pip", "wheel", str(ROOT), "--no-deps", "-w", str(Path(args.wheel).resolve())] + pip_args, full)
        for key, value in env.items():
            print(f"{key}={value}", file=sys.stderr)
    else:
        print(emit(env, args.format))
    return 0


if __name__ == "__main__":
    sys.exit(main())
