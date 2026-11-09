"""Loading of the native library (ctypes) and thin, memory-safe wrappers around its functions."""

from __future__ import annotations

import ctypes
import os
import sys
import threading
from pathlib import Path
from typing import Optional

from ._errors import NativeLibraryError

ENV_VAR = "SYSMLV2_NATIVE_LIBRARY"


def library_filename() -> str:
    if sys.platform == "win32":
        return "sysmlv2check_native.dll"
    if sys.platform == "darwin":
        return "libsysmlv2check_native.dylib"
    return "libsysmlv2check_native.so"


def find_library() -> Path:
    """``$SYSMLV2_NATIVE_LIBRARY`` if set, else the library next to this module."""
    override = os.environ.get(ENV_VAR)
    if override:
        path = Path(override)
        if not path.is_file():
            raise NativeLibraryError(f"{ENV_VAR}={override!r} does not exist")
        return path
    path = Path(__file__).resolve().parent / library_filename()
    if not path.is_file():
        raise NativeLibraryError(
            f"native library {path.name} not found next to the sysmlv2 package ({path.parent}); set {ENV_VAR} to its path"
        )
    return path


class NativeLibrary:
    """The loaded library. The library serializes calls itself."""

    def __init__(self, path: Optional[Path] = None) -> None:
        self.path = Path(path) if path is not None else find_library()
        try:
            lib = ctypes.CDLL(str(self.path))
        except OSError as exc:
            raise NativeLibraryError(f"cannot load {self.path}: {exc}") from exc
        try:
            self._check = lib.sysml_pruefe
            self._preload = lib.sysml_vorwaermen
            self._configure = lib.sysml_konfigurieren
            self._memory = lib.sysml_speicher
            self._free = lib.sysml_freigeben
        except AttributeError as exc:
            raise NativeLibraryError(f"{self.path} does not export the sysmlv2 C interface: {exc}") from exc
        # c_void_p, not c_char_p: ctypes would copy a c_char_p result and the original pointer could not be freed.
        self._check.restype = ctypes.c_void_p
        self._check.argtypes = [ctypes.c_char_p]
        self._preload.restype = ctypes.c_int
        self._preload.argtypes = [ctypes.c_char_p]
        self._configure.restype = ctypes.c_int
        self._configure.argtypes = [ctypes.c_char_p]
        self._memory.restype = ctypes.c_uint
        self._memory.argtypes = []
        self._free.restype = None
        self._free.argtypes = [ctypes.c_void_p]

    def check(self, request_json: str) -> str:
        pointer = self._check(request_json.encode("utf-8"))
        if not pointer:
            raise NativeLibraryError("the native library returned no response (out of memory)")
        try:
            return ctypes.string_at(pointer).decode("utf-8")
        finally:
            self._free(pointer)

    def preload(self, packages_json: str) -> int:
        return int(self._preload(packages_json.encode("utf-8")))

    def configure(self, config_json: str) -> int:
        return int(self._configure(config_json.encode("utf-8")))

    def memory(self) -> int:
        return int(self._memory())


_library: Optional[NativeLibrary] = None
_lock = threading.Lock()


def get_library() -> NativeLibrary:
    """The process-wide library, loaded on first use."""
    global _library
    with _lock:
        if _library is None:
            _library = NativeLibrary()
        return _library
