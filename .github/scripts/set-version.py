#!/usr/bin/env python3
"""Sets project.version in pyproject.toml from a release/branch name: "v1.2.3" -> 1.2.3, "1.0-main" -> 1.0.dev0.
Usage: set-version.py <version>. An empty or invalid name leaves the version of pyproject.toml (a warning is printed for the latter)."""
import re
import sys
from pathlib import Path

raw = (sys.argv[1] if len(sys.argv) > 1 else "").strip()
if not raw:
    sys.exit(0)
name = raw[1:] if raw[:1] in "vV" else raw
name = re.sub(r"^(\d+(?:\.\d+)*)-main$", r"\1.dev0", name)
try:
    from packaging.version import InvalidVersion, Version
    version = str(Version(name))
except InvalidVersion:
    print(f"::warning::'{raw}' is not a PEP 440 version, keeping the version of pyproject.toml")
    sys.exit(0)
path = Path(__file__).resolve().parents[2] / "pyproject.toml"
text = path.read_text(encoding="utf-8")
new, count = re.subn(r'(?m)^version = "[^"]*"', f'version = "{version}"', text, count=1)
if count != 1:
    sys.exit("version line not found in pyproject.toml")
path.write_text(new, encoding="utf-8", newline="")
print(f"package version: {version}")
