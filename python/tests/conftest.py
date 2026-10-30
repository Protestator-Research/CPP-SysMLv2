import pytest

import sysmlv2
from sysmlv2._errors import NativeLibraryError
from sysmlv2._native import get_library


def _native_available() -> bool:
    try:
        get_library()
        return True
    except NativeLibraryError:
        return False


def pytest_collection_modifyitems(config, items):
    if _native_available():
        return
    skip = pytest.mark.skip(reason="native library not available")
    for item in items:
        if "native" in item.keywords:
            item.add_marker(skip)


def pytest_configure(config):
    config.addinivalue_line("markers", "native: needs the native library")


@pytest.fixture(autouse=True)
def _default_limits(request):
    yield
    if request.node.get_closest_marker("native"):
        sysmlv2.configure(max_bytes=100 * 1024, max_diagnostics=200, max_model_elements=20000)
