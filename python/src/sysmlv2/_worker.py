"""Child process of an isolated Checker: runs the native calls it receives over a pipe."""

from __future__ import annotations

import signal
from typing import Any


def worker_main(conn: Any) -> None:
    """Loop: receive ``(seq, op, argument)``, answer ``(seq, "ok", result)`` or ``(seq, "error", exception_name, message)``."""
    try:
        signal.signal(signal.SIGINT, signal.SIG_IGN)  # Ctrl+C is the parent's business; the parent terminates the worker
    except (ValueError, OSError):
        pass
    from ._native import get_library

    while True:
        try:
            message = conn.recv()
        except (EOFError, OSError):
            return
        if message is None:
            return
        seq, operation, argument = message
        try:
            library = get_library()
            if operation == "check":
                result: Any = library.check(argument)
            elif operation == "preload":
                result = library.preload(argument)
            elif operation == "configure":
                result = library.configure(argument)
            elif operation == "warmup":
                result = library.preload("[]")  # creates the process-wide native context (loads the base library)
            else:
                raise ValueError(f"unknown operation {operation!r}")
            conn.send((seq, "ok", result))
        except Exception as exc:  # reported to the parent, never kills the loop silently
            conn.send((seq, "error", type(exc).__name__, str(exc)))
