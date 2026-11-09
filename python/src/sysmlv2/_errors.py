"""Exceptions of the sysmlv2 package."""

from __future__ import annotations


class SysMLv2Error(Exception):
    """Base class of all errors raised by this package."""


class NativeLibraryError(SysMLv2Error):
    """The native library could not be found, loaded or called."""


class CheckTimeout(SysMLv2Error):
    """An isolated check did not finish in time; the worker process was terminated (and restarts on the next call)."""


class WorkerCrashed(SysMLv2Error):
    """The worker process of an isolated Checker died or could not be (re)started; it restarts on the next call."""
