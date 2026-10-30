//
// Created by Moritz Herzog on 17.03.26.
//

#if defined(_WIN32) && !defined(SYSMLV2_STATIC)
#ifdef sysml_EXPORTS
#define SYSML_EXPORT __declspec(dllexport)
#else
#define SYSML_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SYSML_EXPORT __attribute__((visibility("default")))
#else
#define SYSML_EXPORT
#endif // _WIN32 && !SYSMLV2_STATIC
