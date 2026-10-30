"""Checker and parser for SysML v2 textual notation (native library, no dependencies).

>>> import sysmlv2
>>> result = sysmlv2.check("package P { part def A; }")
>>> result.ok
True

Module-level functions use one default in-process :class:`Checker`; create your own (``Checker(isolated=True,
timeout=...)``) to protect a server from inputs that make the native parser run for a very long time.
"""

from __future__ import annotations

from typing import Any, Iterable, Optional

from ._checker import Checker
from ._errors import CheckTimeout, NativeLibraryError, SysMLv2Error, WorkerCrashed
from ._model import Model
from ._protocol import RequiredLike
from ._types import Category, CheckResult, Diagnostic, ElementInfo, ErrorKind, RequiredElement, Source

try:
    from importlib.metadata import version as _version

    __version__ = _version("sysmlv2")
except Exception:  # not installed (source checkout)
    __version__ = "0+unknown"

__all__ = [
    "Category",
    "CheckResult",
    "CheckTimeout",
    "Checker",
    "Diagnostic",
    "ElementInfo",
    "ErrorKind",
    "Model",
    "NativeLibraryError",
    "RequiredElement",
    "Source",
    "SysMLv2Error",
    "WorkerCrashed",
    "check",
    "configure",
    "parse",
    "preload",
]

_default = Checker()


def check(
    text: str,
    *,
    given_text: Optional[str] = None,
    required_elements: Optional[Iterable[RequiredLike]] = None,
    model: bool = False,
    request_id: Any = None,
) -> CheckResult:
    """Checks a SysML v2 text: syntax, name resolution, structure and required elements.

    ``given_text`` is a SysML v2 text ``text`` may refer to (its own errors are reported separately in
    ``given_text_errors``). ``required_elements`` are elements ``text`` must declare (``RequiredElement`` or
    ``(metaclass, name)`` tuples). With ``model=True`` ``result.model`` holds the parsed model.
    The first request that needs standard library packages is slow (seconds); see :func:`preload`.
    """
    return _default.check(text, given_text=given_text, required_elements=required_elements, model=model, request_id=request_id)


def parse(text: str, *, given_text: Optional[str] = None) -> CheckResult:
    """Like :func:`check` with ``model=True``."""
    return _default.parse(text, given_text=given_text)


def preload(packages: Iterable[str]) -> int:
    """Loads standard library packages in advance (``"*"`` for all); returns the number of library files loaded."""
    return _default.preload(packages)


def configure(
    *,
    max_bytes: Optional[int] = None,
    max_depth: Optional[int] = None,
    max_tokens: Optional[int] = None,
    max_chain_length: Optional[int] = None,
    max_operators: Optional[int] = None,
    max_parse_ms: Optional[int] = None,
    max_load_ms: Optional[int] = None,
    max_diagnostics: Optional[int] = None,
    max_model_elements: Optional[int] = None,
) -> None:
    """Sets the input limits of the process-wide checker; ``None`` leaves a limit unchanged. Raises ``ValueError`` if rejected."""
    _default.configure(
        max_bytes=max_bytes,
        max_depth=max_depth,
        max_tokens=max_tokens,
        max_chain_length=max_chain_length,
        max_operators=max_operators,
        max_parse_ms=max_parse_ms,
        max_load_ms=max_load_ms,
        max_diagnostics=max_diagnostics,
        max_model_elements=max_model_elements,
    )
