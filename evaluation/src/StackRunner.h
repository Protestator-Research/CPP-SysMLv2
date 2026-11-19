#pragma once

// Private: the native stack that an evaluation runs on. Every nested call of a user function costs several KB of stack, so an evaluation
// first runs on the thread of the caller with limits that follow what is left of its stack, and only if it reaches such a limit it runs
// again (evaluations have no side effects) on a thread with a large stack.

#include <cstddef>
#include <functional>

namespace SysMLv2::Evaluation {

    /// The bytes of stack that the calling thread has left, or 0 if that is not known (WebAssembly).
    std::size_t remainingStackBytes();

    /// The stack that an evaluation on the calling thread may count on: what is left less a reserve for the callers of the evaluator and
    /// for the natives; 1 MB (the smallest stack of a platform) where it cannot be measured.
    std::size_t inlineStackBytes();

    /// Runs @p function on a new thread with a stack of @p stackSize bytes (then half, then a quarter of it if the system refuses; not
    /// below 4 MB) and waits for it; @p function must not throw. Returns the stack that the thread got, or 0 if no thread could be made
    /// (also with WebAssembly): then @p function has not run.
    std::size_t runOnStack(std::size_t stackSize, const std::function<void()>& function);
}
