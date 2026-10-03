#ifdef WIN32
#ifdef sysmlv2check_EXPORTS
#define SYSMLV2CHECK_EXPORT __declspec(dllexport)
#else
#define SYSMLV2CHECK_EXPORT __declspec(dllimport)
#endif
#else
#define SYSMLV2CHECK_EXPORT
#endif // WIN32
