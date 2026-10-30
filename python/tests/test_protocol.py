"""Tests that do not need the native library: mapping of the JSON protocol."""

import json

import pytest

from sysmlv2 import Category, Checker, ErrorKind, Model, RequiredElement, Source, SysMLv2Error
from sysmlv2._protocol import build_config, build_request, decode_response, parse_result


def test_category_and_source_mapping():
    raw = {
        "diagnosen": [
            {"kategorie": "GRAMMATIK", "quelle": "SYNTAX", "zeile": 3, "spalte": 14, "meldung": "m"},
            {"kategorie": "LOGIK", "quelle": "UNRESOLVED", "name": "X", "meldung": "u"},
            {"kategorie": "LOGIK", "quelle": "STRUKTUR", "element": "Part", "eigenschaft": "p", "meldung": "s"},
            {"kategorie": "LOGIK", "quelle": "PFLICHT", "meldung": "r"},
            {"kategorie": "WARNUNG", "quelle": "SYNTAX", "meldung": "w"},
        ],
        "vorgabeFehler": [{"kategorie": "GRAMMATIK", "quelle": "VORGABE", "meldung": "g"}],
        "elemente": [{"metaklasse": "PartDefinition", "qualifiedName": "P::A"}],
        "weitereDiagnosen": 4,
        "weitereVorgabeFehler": 1,
        "id": {"a": 1},
    }
    result = parse_result(raw)
    d = result.diagnostics
    assert [x.category for x in d] == [Category.GRAMMAR, Category.LOGIC, Category.LOGIC, Category.LOGIC, Category.WARNING]
    assert [x.source for x in d] == [Source.SYNTAX, Source.UNRESOLVED, Source.STRUCTURE, Source.REQUIRED, Source.SYNTAX]
    assert (d[0].line, d[0].column) == (3, 14)
    assert d[1].name == "X" and d[2].element == "Part" and d[2].property_name == "p"
    assert result.given_text_errors[0].source is Source.GIVEN_TEXT
    assert result.elements[0].qualified_name == "P::A"
    assert result.more_diagnostics == 4 and result.more_given_text_errors == 1
    assert result.request_id == {"a": 1}
    assert not result.ok
    assert len(result.errors) == 4 and len(result.warnings) == 1
    assert result.model is None and result.error is None


@pytest.mark.parametrize(
    "fehler,kind",
    [
        ("zuGross", ErrorKind.TOO_LARGE),
        ("zuTief", ErrorKind.TOO_DEEP),
        ("zuLang", ErrorKind.TOO_LONG),
        ("zeitueberschreitung", ErrorKind.TIMEOUT),
        ("quelltext fehlt", ErrorKind.INVALID_REQUEST),
        ("internal error: boom", ErrorKind.INTERNAL),
    ],
)
def test_error_mapping(fehler, kind):
    result = parse_result({"fehler": fehler, "meldung": "text", "diagnosen": []})
    assert result.error is kind
    assert result.error_message == "text"
    assert not result.ok


def test_error_message_falls_back_to_code():
    assert parse_result({"fehler": "boom"}).error_message == "boom"


def test_ok_and_warnings_only():
    result = parse_result({"diagnosen": [{"kategorie": "WARNUNG", "quelle": "SYNTAX", "meldung": "w"}]})
    assert result.ok and len(result.warnings) == 1


def test_unknown_values_do_not_crash():
    result = parse_result({"diagnosen": [{"kategorie": "NEU", "quelle": "ANDERS", "meldung": "x", "zeile": "1"}]})
    d = result.diagnostics[0]
    assert d.category is Category.UNKNOWN and d.source is Source.UNKNOWN
    assert d.line is None and d.raw["kategorie"] == "NEU"
    assert result.ok  # UNKNOWN is neither GRAMMAR nor LOGIC
    assert Category("whatever") is Category.UNKNOWN


def test_model_in_result():
    raw = {"modell": [{"@id": "a", "@type": "Namespace"}], "modellFehler": 2, "modellUnvollstaendig": True}
    result = parse_result(raw)
    assert isinstance(result.model, Model)
    assert result.model_errors == 2 and result.model_incomplete is True


def test_build_request():
    request = json.loads(
        build_request("package P;", "package Q;", [RequiredElement("PartDefinition", "A"), ("Package", "P")], True, 7)
    )
    assert request == {
        "quelltext": "package P;",
        "vorgabe": "package Q;",
        "pflichtelemente": [{"metaklasse": "PartDefinition", "name": "A"}, {"metaklasse": "Package", "name": "P"}],
        "modell": True,
        "id": 7,
    }
    assert json.loads(build_request("x")) == {"quelltext": "x"}
    assert json.loads(build_request("part def 'Käfer';"))["quelltext"] == "part def 'Käfer';"
    with pytest.raises(TypeError):
        build_request(b"x")  # type: ignore[arg-type]


def test_lone_surrogate_rejected():
    with pytest.raises(ValueError):
        build_request("package " + chr(0xD800) + ";")
    with pytest.raises(ValueError):
        build_request("package P;", given_text=chr(0xDFFF))


def test_response_version_checked():
    assert decode_response('{"version": "1.2", "diagnosen": []}').ok
    assert decode_response('{"diagnosen": []}').ok
    with pytest.raises(SysMLv2Error):
        decode_response('{"version": "2", "diagnosen": []}')


def test_build_config():
    assert build_config(max_bytes=10, max_depth=None, max_parse_ms=5) == {"maxBytes": 10, "maxMs": 5}
    with pytest.raises(ValueError):
        build_config(max_bytes=-1)
    with pytest.raises(ValueError):
        build_config(max_bytes=True)
    with pytest.raises(ValueError):
        build_config(max_bytes=2**63)
    assert build_config(max_bytes=2**63 - 1) == {"maxBytes": 2**63 - 1}


def test_checker_timeout_validation():
    for bad in (0, -1, True, "5"):
        with pytest.raises(ValueError):
            Checker(isolated=True, timeout=bad)  # type: ignore[arg-type]
    with pytest.raises(ValueError):
        Checker(timeout=5)  # in-process checks cannot be interrupted
    checker = Checker(isolated=True, timeout=5)
    with pytest.raises(ValueError):
        checker.timeout = 0
    checker.timeout = None
    checker.close()


def test_model_single_dict_reference():
    model = Model([{"@id": "a", "ownedRelationship": {"@id": "m"}}, {"@id": "m", "ownedRelatedElement": {"@id": "a"}}])
    assert model.owned_relationships(model.root) == [model.elements[1]]
    assert model.owned_elements(model.root) == [model.root]


def test_model_helpers():
    elements = [
        {"@id": "ns", "@type": "Namespace", "ownedRelationship": [{"@id": "m"}]},
        {"@id": "m", "@type": "OwningMembership", "ownedRelatedElement": [{"@id": "a"}, {"@id": "lib"}]},
        {"@id": "a", "@type": "PartDefinition", "declaredName": "A", "qualifiedName": "P::A", "ownedRelationship": []},
    ]
    model = Model(elements)
    assert len(model) == 3 and model.root is elements[0]
    assert model.by_id("a") is elements[2] and model.by_id("zz") is None
    assert model.resolve({"@id": "a"}) is elements[2]
    assert model.resolve([{"@id": "a"}, {"@id": "lib"}]) == [elements[2]]
    assert model.resolve(None) is None
    assert model.of_type("PartDefinition") == [elements[2]]
    assert model.find("P::A") is elements[2]
    assert model.owned_relationships(elements[0]) == [elements[1]]
    assert model.owned_elements(elements[0]) == [elements[2]]
    assert list(model) == elements
