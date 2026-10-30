#if defined(_WIN32) && !defined(SYSMLV2_STATIC)
#ifdef sysmlv2parser_EXPORTS
#define SYSMLV2FILE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2FILE_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SYSMLV2FILE_EXPORT __attribute__((visibility("default")))
#else
#define SYSMLV2FILE_EXPORT
#endif // _WIN32 && !SYSMLV2_STATIC
