#!/usr/bin/env python3
"""Checks that the wheels in a directory match the release version before they are uploaded to PyPI.
Usage: check-dist-version.py <version> <dist-dir>. <version> is normalized like set-version.py does (a leading "v"/"V" is stripped, then
packaging.version.Version); it must be a valid PEP 440 version. The directory must hold at least one file and every file must be named
cpp_sysmlv2-<normalized version>-*.whl. Otherwise a ::error:: message is printed and the exit code is 1."""
import sys
from pathlib import Path

from packaging.version import InvalidVersion, Version


def fail(message):
    print(f"::error::{message}")
    sys.exit(1)


if len(sys.argv) != 3:
    sys.exit("usage: check-dist-version.py <version> <dist-dir>")
raw = sys.argv[1].strip()
name = raw[1:] if raw[:1] in "vV" else raw
try:
    version = str(Version(name))
except InvalidVersion:
    fail(f"'{raw}' is not a PEP 440 version; set-version.py would keep the version of pyproject.toml and the upload cannot be undone")
dist = Path(sys.argv[2])
files = sorted(p for p in dist.iterdir() if p.is_file()) if dist.is_dir() else []
if not files:
    fail(f"no files in '{dist}': nothing to upload")
prefix = f"cpp_sysmlv2-{version}-"
wrong = [p.name for p in files if not (p.name.startswith(prefix) and p.name.endswith(".whl"))]
if wrong:
    fail(f"files in '{dist}' are not named {prefix}*.whl: {', '.join(wrong)}")
if not any(p.name.endswith(".whl") for p in files):
    fail(f"no wheel in '{dist}'")
print(f"{len(files)} wheel(s) for cpp-sysmlv2 {version}")
