#pragma once

// Private helpers for the compiler: the recursion of the evaluation (EvaluationContext::evaluate -> hook -> native function ->
// EvaluationContext::evaluate ...) costs native stack per level of depth, so the cold paths (messages, string building) are kept out
// of the frames on that path.

#if defined(_MSC_VER)
#define SYSMLV2_COLD_PATH __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define SYSMLV2_COLD_PATH __attribute__((noinline))
#else
#define SYSMLV2_COLD_PATH
#endif
