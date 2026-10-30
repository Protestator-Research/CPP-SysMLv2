#if defined(_WIN32) && !defined(SYSMLV2_STATIC)
#ifdef sysmlv2interfaces_EXPORTS
#define SYSMLV2INTERFACE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2INTERFACE_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define SYSMLV2INTERFACE_EXPORT __attribute__((visibility("default")))
#else
#define SYSMLV2INTERFACE_EXPORT
#endif // _WIN32 && !SYSMLV2_STATIC
