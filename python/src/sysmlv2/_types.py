"""Result types of the checker."""

from __future__ import annotations

import enum
from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional, Tuple

from ._model import Model


class _ForwardCompatible(str, enum.Enum):
    """str enum whose unknown values (from a newer native library) become ``UNKNOWN`` instead of raising."""

    @classmethod
    def _missing_(cls, value: object) -> Any:
        return cls.__members__["UNKNOWN"]

    def __str__(self) -> str:
        return str(self.value)


class Category(_ForwardCompatible):
    """Severity class of a diagnostic."""

    GRAMMAR = "GRAMMAR"  #: syntax error of the text
    LOGIC = "LOGIC"  #: unresolved name, missing required element, structure violation, misused keyword
    WARNING = "WARNING"  #: warning of the parser
    UNKNOWN = "UNKNOWN"  #: a value this version of the package does not know (see ``Diagnostic.raw``)


class Source(_ForwardCompatible):
    """Which check produced a diagnostic."""

    SYNTAX = "SYNTAX"
    UNRESOLVED = "UNRESOLVED"
    STRUCTURE = "STRUCTURE"
    REQUIRED = "REQUIRED"
    GIVEN_TEXT = "GIVEN_TEXT"
    UNKNOWN = "UNKNOWN"


class ErrorKind(_ForwardCompatible):
    """Why a request was rejected as a whole (``CheckResult.error``)."""

    TOO_LARGE = "TOO_LARGE"  #: text or token count above the limit
    TOO_DEEP = "TOO_DEEP"  #: nesting or operator chain too deep
    TOO_LONG = "TOO_LONG"  #: feature chain / qualified name too long
    TIMEOUT = "TIMEOUT"  #: parse or library load deadline passed
    INVALID_REQUEST = "INVALID_REQUEST"  #: any other rejection
    INTERNAL = "INTERNAL"  #: internal error of the native library
    UNKNOWN = "UNKNOWN"


@dataclass(frozen=True)
class Diagnostic:
    """One finding. ``line`` is 1-based, ``column`` 0-based in Unicode code points; both ``None`` if unknown."""

    category: Category
    source: Source
    message: str
    line: Optional[int] = None
    column: Optional[int] = None
    name: Optional[str] = None
    element: Optional[str] = None
    property_name: Optional[str] = None
    raw: Dict[str, Any] = field(default_factory=dict, compare=False, repr=False)

    def __str__(self) -> str:
        where = f"{self.line}:{self.column}: " if self.line is not None else ""
        return f"{where}{self.category.value}/{self.source.value}: {self.message}"


@dataclass(frozen=True)
class ElementInfo:
    """A named element of the text."""

    metaclass: str
    qualified_name: str


@dataclass(frozen=True)
class RequiredElement:
    """An element the text must declare: ``metaclass`` (e.g. ``"PartDefinition"``) and ``name`` (declared, short or qualified)."""

    metaclass: str
    name: str


@dataclass(frozen=True)
class CheckResult:
    """The answer to one request."""

    diagnostics: Tuple[Diagnostic, ...] = ()
    given_text_errors: Tuple[Diagnostic, ...] = ()
    elements: Tuple[ElementInfo, ...] = ()
    model: Optional[Model] = None
    more_diagnostics: int = 0
    more_given_text_errors: int = 0
    model_errors: int = 0
    model_incomplete: bool = False
    error: Optional[ErrorKind] = None
    error_message: Optional[str] = None
    request_id: Any = None
    raw: Dict[str, Any] = field(default_factory=dict, compare=False, repr=False)

    @property
    def ok(self) -> bool:
        """No GRAMMAR or LOGIC diagnostic and the request was not rejected."""
        return self.error is None and not self.errors

    @property
    def errors(self) -> List[Diagnostic]:
        """The diagnostics of category GRAMMAR or LOGIC."""
        return [d for d in self.diagnostics if d.category in (Category.GRAMMAR, Category.LOGIC)]

    @property
    def warnings(self) -> List[Diagnostic]:
        """The diagnostics of category WARNING."""
        return [d for d in self.diagnostics if d.category is Category.WARNING]
