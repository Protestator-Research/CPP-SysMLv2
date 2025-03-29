#ifdef WIN32
#ifdef sysmlv2base_EXPORTS
#define SYSMLV2BASE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2BASE_EXPORT __declspec(dllimport)
#endif
#else
#define SYSMLV2BASE_EXPORT
#endif // WIN32
