//
// C interface of sysmlv2check (see SysMLv2::Check::Checker for the request and response).
//
#pragma once

#include <sysmlv2/check/sysmlv2check_global.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Checks one request with the process-wide checking context (created at the first call, then reused; calls are serialized).
 * @param anfrageJson the request as zero-terminated UTF-8 JSON.
 * @return the response as zero-terminated UTF-8 JSON (null only if there is no memory left for it). Free it with sysml_freigeben().
 * The check can take seconds (and for hostile input much longer): call it where it can be aborted by a timeout.
 */
SYSMLV2CHECK_EXPORT const char* sysml_pruefe(const char* anfrageJson);

/**
 * Loads standard library packages in advance (and warms the parser). Optional; the packages a text needs are loaded by sysml_pruefe().
 * @param paketeJson a JSON array of package names, for example `["ISQ","SI","Parts"]`.
 * @return the number of library files loaded, or -1 if the argument is not a JSON array of strings.
 */
SYSMLV2CHECK_EXPORT int sysml_vorwaermen(const char* paketeJson);

/**
 * Sets the limits of the input (see SysMLv2::Check::Checker::Limits).
 * @param konfigJson a JSON object with the optional members "maxBytes", "maxTiefe" (nesting), "maxTokens", "maxKette" (chain length) and "maxMs" (parse deadline in milliseconds), "maxLadeMs" (time a request may spend loading library packages) and "maxDiagnosen", for example `{"maxBytes":50000,"maxTiefe":32,"maxMs":10000}`.
 * @return 1, or 0 if the argument is not such an object.
 */
SYSMLV2CHECK_EXPORT int sysml_konfigurieren(const char* konfigJson);

/// Size of the linear memory of the WebAssembly module in bytes (it only grows); 0 outside of WebAssembly. For recycling a module instance.
SYSMLV2CHECK_EXPORT unsigned int sysml_speicher(void);

/// Frees a response returned by sysml_pruefe(). Accepts null.
SYSMLV2CHECK_EXPORT void sysml_freigeben(const char* antwort);

#ifdef __cplusplus
}
#endif
