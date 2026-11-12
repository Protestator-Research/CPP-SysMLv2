//
// Hooks for the tests of the workspace. Not part of the interface of the library: this header is not installed, and nothing in it is supported or
// stable across versions (the ABI included).
//
#pragma once

#include <cstddef>
#include <sysmlv2/sysmlv2file_global.h>

namespace SysMLv2::Files::detail {

    /**
     * Changes where the texts of every workspace of the process are parsed (see the limits of the nesting of a text in Workspace.h). With
     * @p inlineParsing true the parse runs on the calling thread, whose remaining stack decides the limits (what happens where no thread with a large
     * stack can be made); else it runs on a thread with @p stackBytes of stack (0: the default, the largest of 512, 128 and 32 MB that the system
     * gives). Global state: not to be called while a workspace is parsing.
     */
    SYSMLV2FILE_EXPORT void setParseStackForTesting(bool inlineParsing, size_t stackBytes = 0);

    /// How many times the prediction caches of the generated parsers were emptied since the process started (see the prediction caches in Workspace.h).
    SYSMLV2FILE_EXPORT size_t predictionCacheCleanups();
}
