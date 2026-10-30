"""Translation between the Python API and the JSON protocol of the native library (German keys). No native code here."""

from __future__ import annotations

import json
from typing import Any, Dict, Iterable, List, Mapping, Optional, Tuple, Union

from ._errors import SysMLv2Error
from ._model import Model
from ._types import Category, CheckResult, Diagnostic, ElementInfo, ErrorKind, RequiredElement, Source

_CATEGORY = {"GRAMMATIK": "GRAMMAR", "LOGIK": "LOGIC", "WARNUNG": "WARNING"}
_SOURCE = {"SYNTAX": "SYNTAX", "UNRESOLVED": "UNRESOLVED", "STRUKTUR": "STRUCTURE", "PFLICHT": "REQUIRED", "VORGABE": "GIVEN_TEXT"}
_ERROR = {"zuGross": ErrorKind.TOO_LARGE, "zuTief": ErrorKind.TOO_DEEP, "zuLang": ErrorKind.TOO_LONG, "zeitueberschreitung": ErrorKind.TIMEOUT}

#: configure() keyword -> key of sysml_konfigurieren
CONFIG_KEYS = {
    "max_bytes": "maxBytes",
    "max_depth": "maxTiefe",
    "max_tokens": "maxTokens",
    "max_chain_length": "maxKette",
    "max_operators": "maxOperatoren",
    "max_parse_ms": "maxMs",
    "max_load_ms": "maxLadeMs",
    "max_diagnostics": "maxDiagnosen",
    "max_model_elements": "maxModellElemente",
}

RequiredLike = Union[RequiredElement, Tuple[str, str]]


def build_request(
    text: str,
    given_text: Optional[str] = None,
    required_elements: Optional[Iterable[RequiredLike]] = None,
    model: bool = False,
    request_id: Any = None,
) -> str:
    """The request JSON (ASCII only, so no encoding problem can occur on the way to the library)."""
    if not isinstance(text, str):
        raise TypeError("text must be a str")
    request: Dict[str, Any] = {"quelltext": text}
    if given_text is not None:
        request["vorgabe"] = given_text
    if required_elements is not None:
        items = []
        for entry in required_elements:
            required = entry if isinstance(entry, RequiredElement) else RequiredElement(*entry)
            items.append({"metaklasse": required.metaclass, "name": required.name})
        request["pflichtelemente"] = items
    if model:
        request["modell"] = True
    if request_id is not None:
        request["id"] = request_id
    try:
        json.dumps(request, ensure_ascii=False).encode("utf-8")
    except UnicodeEncodeError as exc:
        raise ValueError(f"the text contains a character that cannot be encoded as UTF-8 (lone surrogate): {exc}") from exc
    return json.dumps(request, ensure_ascii=True)


def build_config(**limits: Optional[int]) -> Dict[str, int]:
    """The configuration object for sysml_konfigurieren; ``None`` values are left out, bad values raise ValueError."""
    config: Dict[str, int] = {}
    for key, value in limits.items():
        if value is None:
            continue
        if isinstance(value, bool) or not isinstance(value, int) or value < 0 or value >= 2**63:
            raise ValueError(f"{key} must be an integer in [0, 2**63), got {value!r}")
        config[CONFIG_KEYS[key]] = value
    return config


def _enum(enum_type: Any, mapping: Mapping[str, str], raw: Any) -> Any:
    if isinstance(raw, str):
        return enum_type(mapping.get(raw, "UNKNOWN"))
    return enum_type("UNKNOWN")


def _opt_int(value: Any) -> Optional[int]:
    return value if isinstance(value, int) and not isinstance(value, bool) else None


def _opt_str(value: Any) -> Optional[str]:
    return value if isinstance(value, str) else None


def parse_diagnostic(raw: Mapping[str, Any]) -> Diagnostic:
    return Diagnostic(
        category=_enum(Category, _CATEGORY, raw.get("kategorie")),
        source=_enum(Source, _SOURCE, raw.get("quelle")),
        message=str(raw.get("meldung", "")),
        line=_opt_int(raw.get("zeile")),
        column=_opt_int(raw.get("spalte")),
        name=_opt_str(raw.get("name")),
        element=_opt_str(raw.get("element")),
        property_name=_opt_str(raw.get("eigenschaft")),
        raw=dict(raw),
    )


def _list(value: Any) -> List[Any]:
    return value if isinstance(value, list) else []


def parse_result(raw: Dict[str, Any]) -> CheckResult:
    """Builds a CheckResult from the decoded response of the native library. Unknown members and values are tolerated."""
    error: Optional[ErrorKind] = None
    error_message: Optional[str] = None
    fehler = raw.get("fehler")
    if isinstance(fehler, str) and fehler:
        if fehler in _ERROR:
            error = _ERROR[fehler]
        elif fehler.lower().startswith("internal error"):
            error = ErrorKind.INTERNAL
        else:
            error = ErrorKind.INVALID_REQUEST
        error_message = _opt_str(raw.get("meldung")) or fehler
    model = None
    if isinstance(raw.get("modell"), list):
        model = Model(e for e in raw["modell"] if isinstance(e, dict))
    return CheckResult(
        diagnostics=tuple(parse_diagnostic(d) for d in _list(raw.get("diagnosen")) if isinstance(d, dict)),
        given_text_errors=tuple(parse_diagnostic(d) for d in _list(raw.get("vorgabeFehler")) if isinstance(d, dict)),
        elements=tuple(
            ElementInfo(str(e.get("metaklasse", "")), str(e.get("qualifiedName", "")))
            for e in _list(raw.get("elemente"))
            if isinstance(e, dict)
        ),
        model=model,
        more_diagnostics=_opt_int(raw.get("weitereDiagnosen")) or 0,
        more_given_text_errors=_opt_int(raw.get("weitereVorgabeFehler")) or 0,
        model_errors=_opt_int(raw.get("modellFehler")) or 0,
        model_incomplete=raw.get("modellUnvollstaendig") is True,
        error=error,
        error_message=error_message,
        request_id=raw.get("id"),
        raw=raw,
    )


def decode_response(text: str) -> CheckResult:
    decoded = json.loads(text)
    if not isinstance(decoded, dict):
        raise ValueError("response of the native library is not a JSON object")
    version = decoded.get("version", "1")
    if str(version).split(".")[0] != "1":
        raise SysMLv2Error(f"unsupported protocol version {version!r} of the native library (this package speaks 1)")
    return parse_result(decoded)
