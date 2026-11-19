#include "StackRunner.h"

#include <cstdint>
#include <memory>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#elif !defined(__EMSCRIPTEN__)
#include <pthread.h>
#endif

namespace SysMLv2::Evaluation {

    namespace {
        constexpr std::size_t UnknownStackBytes = std::size_t(1) << 20;
        constexpr std::size_t InlineReserveBytes = std::size_t(128) << 10;
        constexpr std::size_t SmallestStack = std::size_t(4) << 20;

        /// The lowest address of the stack of this thread (0: unknown); measured once per thread (the lookup of the stack of the main
        /// thread reads /proc on Linux).
        std::uintptr_t stackLow() {
#if defined(_WIN32)
            thread_local const std::uintptr_t low = [] {
                ULONG_PTR lowest = 0, highest = 0;
                GetCurrentThreadStackLimits(&lowest, &highest);
                return static_cast<std::uintptr_t>(lowest);
            }();
            return low;
#elif defined(__EMSCRIPTEN__)
            return 0;
#elif defined(__APPLE__)
            thread_local const std::uintptr_t low = [] {
                const auto top = reinterpret_cast<std::uintptr_t>(pthread_get_stackaddr_np(pthread_self()));
                return top - pthread_get_stacksize_np(pthread_self());
            }();
            return low;
#else
            thread_local const std::uintptr_t low = [] {
                pthread_attr_t attributes;
                if (pthread_getattr_np(pthread_self(), &attributes) != 0) return std::uintptr_t(0);
                void* lowest = nullptr;
                std::size_t size = 0;
                const int result = pthread_attr_getstack(&attributes, &lowest, &size);
                pthread_attr_destroy(&attributes);
                return result == 0 ? reinterpret_cast<std::uintptr_t>(lowest) : std::uintptr_t(0);
            }();
            return low;
#endif
        }

        struct Start {
            const std::function<void()>* Function;
        };

#if defined(_WIN32)
        DWORD WINAPI runThread(LPVOID argument) {
            (*static_cast<Start*>(argument)->Function)();
            return 0;
        }
#elif !defined(__EMSCRIPTEN__)
        void* runThread(void* argument) {
            (*static_cast<Start*>(argument)->Function)();
            return nullptr;
        }
#endif
    }

    std::size_t remainingStackBytes() {
        const std::uintptr_t low = stackLow();
        char here = 0;
        const auto address = reinterpret_cast<std::uintptr_t>(&here);
        return low != 0 && address > low ? static_cast<std::size_t>(address - low) : 0;
    }

    std::size_t inlineStackBytes() {
        const std::size_t remaining = remainingStackBytes();
        if (remaining == 0) return UnknownStackBytes;
        return remaining > InlineReserveBytes ? remaining - InlineReserveBytes : 0;
    }

    std::size_t runOnStack(std::size_t stackSize, const std::function<void()>& function) {
#if defined(__EMSCRIPTEN__)
        (void)stackSize;
        (void)function;
        return 0;
#else
        Start start{&function};
        for (std::size_t size = stackSize; size >= SmallestStack; size /= 2) {
#if defined(_WIN32)
            HANDLE thread = CreateThread(nullptr, size, runThread, &start, STACK_SIZE_PARAM_IS_A_RESERVATION, nullptr);
            if (thread == nullptr) continue;
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);
            return size;
#else
            pthread_attr_t attributes;
            if (pthread_attr_init(&attributes) != 0) continue;
            pthread_t thread;
            bool started = pthread_attr_setstacksize(&attributes, size) == 0 && pthread_create(&thread, &attributes, runThread, &start) == 0;
            pthread_attr_destroy(&attributes);
            if (!started) continue;
            pthread_join(thread, nullptr);
            return size;
#endif
        }
        return 0;
#endif
    }
}
