#if defined(_WIN32) && !defined(SYSMLV2_STATIC)
#ifdef sysmlv2rest_EXPORTS
#define SYSMLV2REST_EXPORT __declspec(dllexport)
#else
#define SYSMLV2REST_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SYSMLV2REST_EXPORT __attribute__((visibility("default")))
#else
#define SYSMLV2REST_EXPORT
#endif // _WIN32 && !SYSMLV2_STATIC
