"""The Checker class: in-process or isolated in a child process."""

from __future__ import annotations

import json
import multiprocessing
import os
import threading
import time
import weakref
from typing import Any, Dict, Iterable, List, Optional

from ._errors import CheckTimeout, NativeLibraryError, SysMLv2Error, WorkerCrashed
from ._native import get_library
from ._protocol import RequiredLike, build_config, build_request, decode_response
from ._types import CheckResult


class _InProcessBackend:
    def call(self, operation: str, argument: Any, timeout: Optional[float]) -> Any:
        library = get_library()
        if operation == "check":
            return library.check(argument)
        if operation == "preload":
            return library.preload(argument)
        if operation == "configure":
            return library.configure(argument)
        raise ValueError(operation)

    def abort(self) -> None:
        pass


class _Replay:
    """What a restarted worker must be told again: the merged configuration and the preloaded packages."""

    def __init__(self) -> None:
        self.config: Dict[str, int] = {}
        self.packages: List[str] = []

    def add_packages(self, names: Iterable[str]) -> None:
        for name in names:
            if name not in self.packages:
                self.packages.append(name)


class _ProcessBackend:
    """A worker process (spawn context).

    Every request carries a sequence number and replies with another number are discarded, so an interrupted exchange can never
    make a later call return the result of an earlier one; on ANY exception during an exchange the worker is killed.
    A timeout terminates the worker; the next call starts a new one (warm-up and replay are not subject to the timeout).
    """

    def __init__(self, replay: _Replay) -> None:
        self._replay = replay
        self._process: Any = None
        self._conn: Any = None
        self._pid: Optional[int] = None
        self._seq = 0
        self._state_lock = threading.Lock()

    def _start(self) -> None:
        context = multiprocessing.get_context("spawn")
        parent, child = context.Pipe()
        from ._worker import worker_main

        process = context.Process(target=worker_main, args=(child,), daemon=True, name="sysmlv2-worker")
        try:
            process.start()
        except AssertionError as exc:  # "daemonic processes are not allowed to have children"
            parent.close()
            child.close()
            raise SysMLv2Error(f"cannot start the worker process (an isolated Checker cannot be used inside a daemonic process): {exc}") from exc
        child.close()
        with self._state_lock:
            self._process, self._conn, self._pid = process, parent, os.getpid()
        try:
            self._exchange("warmup", None, None)  # untimed: creates the native context (loads the base library)
            if self._replay.config:
                if self._exchange("configure", json.dumps(self._replay.config), None) != 1:
                    raise WorkerCrashed("the restarted worker rejected the configuration")
            if self._replay.packages:
                if self._exchange("preload", json.dumps(self._replay.packages), None) < 0:
                    raise WorkerCrashed("the restarted worker rejected the preload")
        except BaseException:
            self.abort()
            raise

    def abort(self) -> None:
        """Kills the worker; safe to call from any thread, does not wait for a running call."""
        with self._state_lock:
            process, conn = self._process, self._conn
            self._process = self._conn = self._pid = None
        if conn is not None:
            try:
                conn.close()
            except OSError:
                pass
        if process is not None:
            try:
                if process.is_alive():
                    process.terminate()
                process.join(10)
                if process.is_alive():
                    process.kill()
                    process.join(10)
            except (OSError, ValueError, AssertionError):
                pass

    def _exchange(self, operation: str, argument: Any, timeout: Optional[float]) -> Any:
        conn = self._conn
        if conn is None:
            raise WorkerCrashed("the worker process is not running")
        self._seq += 1
        seq = self._seq
        try:
            conn.send((seq, operation, argument))
            deadline = None if timeout is None else time.monotonic() + timeout
            while True:
                remaining = None if deadline is None else max(0.0, deadline - time.monotonic())
                if not conn.poll(remaining):
                    self.abort()
                    raise CheckTimeout(f"the check did not finish within {timeout} s; the worker process was terminated")
                reply = conn.recv()
                if reply[0] == seq:
                    break  # replies of earlier, interrupted requests are discarded
        except CheckTimeout:
            raise
        except (EOFError, OSError) as exc:
            self.abort()
            raise WorkerCrashed(f"the worker process died ({exc!r}); it restarts on the next call") from exc
        except BaseException:  # KeyboardInterrupt, gevent / alarm timeouts, ...: the pipe state is unknown
            self.abort()
            raise
        if reply[1] == "ok":
            return reply[2]
        if reply[2] == "NativeLibraryError":
            raise NativeLibraryError(reply[3])
        raise SysMLv2Error(f"worker error {reply[2]}: {reply[3]}")

    def call(self, operation: str, argument: Any, timeout: Optional[float]) -> Any:
        if self._pid is not None and self._pid != os.getpid():
            # forked child: the handles belong to the parent; drop them without terminating or closing anything
            with self._state_lock:
                self._process = self._conn = self._pid = None
        process = self._process
        if process is None or not process.is_alive():
            self.abort()
            self._start()
        return self._exchange(operation, argument, timeout)


def _validate_timeout(timeout: Optional[float]) -> Optional[float]:
    if timeout is None:
        return None
    if isinstance(timeout, bool) or not isinstance(timeout, (int, float)) or not timeout > 0:
        raise ValueError(f"timeout must be a number > 0 (seconds) or None, got {timeout!r}")
    return float(timeout)


class Checker:
    """Checks SysML v2 texts.

    ``isolated=False`` (default) calls the native library in this process: simplest and fastest, but a check cannot be
    interrupted, and the library may need very long for hostile input (see the limits in :meth:`configure`).
    **Servers that process untrusted text should use** ``isolated=True``: every call runs in a child process (started
    with the *spawn* method, so scripts need the usual ``if __name__ == "__main__":`` guard, and an isolated Checker cannot be
    created inside a daemonic process); when a call exceeds ``timeout`` seconds the process is terminated,
    :class:`~sysmlv2.CheckTimeout` is raised and a fresh process serves the next call. Starting a worker (loading the base
    library), replaying the configuration and the preloads happens without time limit; the library packages that earlier requests
    loaded are lost with the process, so use :meth:`preload` for what you need.

    A Checker serializes its calls with a lock; use several isolated Checkers for parallelism. :meth:`close` (also called when
    the Checker is garbage collected) kills the worker without waiting for a running call. In-process Checkers share the one
    process-wide native context (and its limits). ``timeout`` needs ``isolated=True``.
    """

    def __init__(self, *, isolated: bool = False, timeout: Optional[float] = None) -> None:
        self._isolated = isolated
        self._timeout: Optional[float] = None
        self._replay = _Replay()
        self._lock = threading.Lock()
        if isolated:
            self._backend: Any = _ProcessBackend(self._replay)
            weakref.finalize(self, self._backend.abort)
        else:
            self._backend = _InProcessBackend()
        self.timeout = timeout

    @property
    def timeout(self) -> Optional[float]:
        """Seconds a call may take (isolated only); ``None``: no limit."""
        return self._timeout

    @timeout.setter
    def timeout(self, value: Optional[float]) -> None:
        value = _validate_timeout(value)
        if value is not None and not self._isolated:
            raise ValueError("timeout needs an isolated Checker: an in-process check cannot be interrupted")
        self._timeout = value

    @property
    def isolated(self) -> bool:
        return self._isolated

    def __enter__(self) -> "Checker":
        return self

    def __exit__(self, *exc_info: object) -> None:
        self.close()

    def close(self) -> None:
        """Kills the worker process of an isolated Checker without waiting for a running call (that call fails with
        :class:`WorkerCrashed`). A later call starts a new worker."""
        self._backend.abort()

    def check(
        self,
        text: str,
        *,
        given_text: Optional[str] = None,
        required_elements: Optional[Iterable[RequiredLike]] = None,
        model: bool = False,
        request_id: Any = None,
        timeout: Optional[float] = None,
    ) -> CheckResult:
        """Checks ``text``; see :func:`sysmlv2.check`. ``timeout`` overrides ``Checker.timeout`` for this call (isolated only)."""
        request = build_request(text, given_text, required_elements, model, request_id)
        effective = self._timeout if timeout is None else _validate_timeout(timeout)
        if effective is not None and not self._isolated:
            raise ValueError("timeout needs an isolated Checker")
        with self._lock:
            response = self._call("check", request, effective)
        try:
            return decode_response(response)
        except ValueError as exc:  # JSONDecodeError
            raise SysMLv2Error(f"invalid response of the native library: {exc}") from exc

    def _call(self, operation: str, argument: Any, timeout: Optional[float]) -> Any:
        try:
            return self._backend.call(operation, argument, timeout)
        except UnicodeError as exc:  # response that is not valid UTF-8
            raise SysMLv2Error(f"invalid response of the native library: {exc}") from exc

    def parse(self, text: str, *, given_text: Optional[str] = None, timeout: Optional[float] = None) -> CheckResult:
        """Like :meth:`check` with ``model=True``: ``result.model`` holds the parsed model."""
        return self.check(text, given_text=given_text, model=True, timeout=timeout)

    def preload(self, packages: Iterable[str]) -> int:
        """Loads standard library packages (``"Parts"``, ``"ISQ"``, ``"*"`` for all) in advance; returns the number of files loaded."""
        if isinstance(packages, str):
            raise TypeError("packages must be an iterable of package names, not a str")
        names = [str(p) for p in packages]
        with self._lock:
            count = self._call("preload", json.dumps(names), None)
            if count < 0:
                raise ValueError("preload failed: argument is not a list of package names")
            self._replay.add_packages(names)
        return count

    def configure(
        self,
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
        """Sets input limits (``None`` leaves a limit unchanged). Raises ValueError for invalid values."""
        config = build_config(
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
        if not config:
            return
        with self._lock:
            if self._call("configure", json.dumps(config), None) != 1:
                raise ValueError("the native library rejected the configuration")
            self._replay.config.update(config)
