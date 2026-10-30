#if defined(_WIN32) && !defined(SYSMLV2_STATIC)
#ifdef sysmlv2service_EXPORTS
#define SYSMLV2SERVICE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2SERVICE_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SYSMLV2SERVICE_EXPORT __attribute__((visibility("default")))
#else
#define SYSMLV2SERVICE_EXPORT
#endif // _WIN32 && !SYSMLV2_STATIC
