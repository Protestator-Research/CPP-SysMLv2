#if defined(_WIN32) && !defined(SYSMLV2_STATIC)
#ifdef kerml_EXPORTS
#define KERML_EXPORT __declspec(dllexport)
#else
#define KERML_EXPORT __declspec(dllimport)
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define KERML_EXPORT __attribute__((visibility("default")))
#else
#define KERML_EXPORT
#endif // _WIN32 && !SYSMLV2_STATIC
