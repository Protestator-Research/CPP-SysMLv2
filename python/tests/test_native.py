"""Tests against the native library."""

import pytest

import sysmlv2
from sysmlv2 import Category, Checker, CheckTimeout, ErrorKind, RequiredElement, Source

pytestmark = pytest.mark.native


@pytest.fixture(scope="module", autouse=True)
def _preload_library():
    """The first request that needs Parts takes long (parsing the library); do it once."""
    sysmlv2.preload(["Parts"])


def test_valid_text():
    result = sysmlv2.check("package P { part def A; part a : A; }")
    assert result.ok and result.error is None
    assert not result.diagnostics
    assert {(e.metaclass, e.qualified_name) for e in result.elements} >= {("PartDefinition", "P::A")}
    assert result.model is None


def test_syntax_error_has_line():
    result = sysmlv2.check("package P {\n  part def A\n}")
    assert not result.ok
    grammar = [d for d in result.diagnostics if d.category is Category.GRAMMAR]
    assert grammar and grammar[0].source is Source.SYNTAX
    assert grammar[0].line == 3


def test_unresolved_name():
    result = sysmlv2.check("package P { part x : Unknown; }")
    unresolved = [d for d in result.diagnostics if d.source is Source.UNRESOLVED]
    assert unresolved and unresolved[0].category is Category.LOGIC and unresolved[0].name == "Unknown"
    assert not result.ok


def test_required_elements():
    result = sysmlv2.check(
        "package P { part def A; }",
        required_elements=[RequiredElement("PartDefinition", "A"), ("PartDefinition", "Missing")],
    )
    required = [d for d in result.diagnostics if d.source is Source.REQUIRED]
    assert len(required) == 1 and required[0].name == "Missing" and required[0].category is Category.LOGIC
    assert not result.ok


def test_given_text_errors_are_separate():
    result = sysmlv2.check("package P { part def A; }", given_text="package G { part def B }")
    assert result.ok  # the given text's errors do not count against the text
    assert result.given_text_errors and all(d.source is not None for d in result.given_text_errors)
    assert result.given_text_errors[0].category is Category.GRAMMAR


def test_given_text_is_usable():
    result = sysmlv2.check("package P { import G::*; part x : B; }", given_text="package G { part def B; }")
    assert result.ok, result.diagnostics


def test_model_contents():
    result = sysmlv2.parse("package P { part def A; }")
    assert result.ok and result.model is not None and not result.model_incomplete and result.model_errors == 0
    model = result.model
    assert model.root is not None and model.root["@type"] == "Namespace"
    (part,) = model.of_type("PartDefinition")
    assert part["declaredName"] == "A" and model.find("P::A") is part
    assert model.by_id(part["@id"]) is part
    assert model.resolve(part["owner"]) is model.find("P")
    package = model.find("P")
    assert part in model.owned_elements(package)
    assert package in model.owned_elements(model.root)
    # every non-null reference to a text element resolves consistently
    for element in model:
        ref = element.get("owningNamespace")
        if ref is not None:
            assert model.resolve(ref) is not None


def test_check_with_model_flag_and_request_id():
    result = sysmlv2.check("package P;", model=True, request_id="r-1")
    assert result.model is not None and result.request_id == "r-1"


def test_too_large_with_configure():
    sysmlv2.configure(max_bytes=50)
    result = sysmlv2.check("package P { " + "part def A; " * 20 + "}")
    assert result.error is ErrorKind.TOO_LARGE and not result.ok
    assert result.error_message


def test_configure_validation():
    with pytest.raises(ValueError):
        sysmlv2.configure(max_bytes=-5)
    sysmlv2.configure()  # no-op


def test_preload_validation():
    assert sysmlv2.preload(["Parts"]) >= 0
    with pytest.raises(TypeError):
        sysmlv2.preload("Parts")  # type: ignore[arg-type]


def test_unicode_text():
    result = sysmlv2.check("package P { part def 'Käfer €'; }", required_elements=[("PartDefinition", "Käfer €")])
    assert result.ok, result.diagnostics


def test_isolated_checker():
    with Checker(isolated=True, timeout=300) as checker:
        checker.configure(max_bytes=60)
        assert checker.preload(["Parts"]) >= 0
        ok = checker.check("package P;")
        assert ok.ok
        big = checker.check("package P { " + "part def A; " * 20 + "}")
        assert big.error is ErrorKind.TOO_LARGE
        assert checker.parse("package P;").model is not None


def test_isolated_timeout_and_recovery():
    checker = Checker(isolated=True, timeout=0.05)
    try:
        # needs a library package that the fresh worker has not loaded: takes seconds, so the timeout is real
        with pytest.raises(CheckTimeout):
            checker.check("package P { import ISQ::*; part def A; }")
        checker.timeout = 300
        assert checker.check("package P { part def A; part a : A; }").ok
    finally:
        checker.close()


class _InterruptedOnce:
    """Connection proxy whose recv() raises KeyboardInterrupt once, like Ctrl+C or a gevent timeout between send and recv."""

    def __init__(self, conn):
        self._conn = conn
        self.armed = True

    def recv(self):
        if self.armed:
            self.armed = False
            raise KeyboardInterrupt
        return self._conn.recv()

    def __getattr__(self, name):
        return getattr(self._conn, name)


def test_isolated_interrupted_exchange_does_not_desync():
    with Checker(isolated=True, timeout=300) as checker:
        assert checker.check("package P;").ok
        backend = checker._backend
        backend._conn = _InterruptedOnce(backend._conn)
        with pytest.raises(KeyboardInterrupt):
            checker.check("package Q { part x : Unknown; }")  # the answer of this request must not leak into the next call
        assert backend._process is None  # the worker was killed
        result = checker.check("package R { part def A; }", model=True)
        assert result.ok and result.model is not None and result.model.find("R::A") is not None


def test_isolated_stale_reply_is_discarded():
    with Checker(isolated=True, timeout=300) as checker:
        assert checker.check("package P;").ok
        backend = checker._backend
        # a leftover answer of an earlier request (wrong sequence number) sits in the pipe before the real one
        backend._conn.send((9999, "check", '{"quelltext": "package Stale { part x : Unknown; }"}'))
        result = checker.check("package Fresh { part def A; }")
        assert result.ok and any(e.qualified_name == "Fresh::A" for e in result.elements)


def test_isolated_close_does_not_wait_and_restarts():
    checker = Checker(isolated=True, timeout=300)
    assert checker.check("package P;").ok
    checker.close()
    assert checker._backend._process is None
    assert checker.check("package P;").ok
    checker.close()


def test_isolated_replay_after_restart():
    with Checker(isolated=True, timeout=300) as checker:
        checker.configure(max_bytes=60)
        checker.preload(["Parts"])
        checker._backend.abort()  # simulate a crash / timeout
        big = checker.check("package P { " + "part def A; " * 20 + "}")
        assert big.error is ErrorKind.TOO_LARGE
        assert checker._replay.config == {"maxBytes": 60} and checker._replay.packages == ["Parts"]


def test_in_process_checker_rejects_timeout():
    with pytest.raises(ValueError):
        Checker(timeout=1)
    with pytest.raises(ValueError):
        Checker().check("package P;", timeout=1)
