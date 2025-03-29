#ifdef WIN32
#ifdef sysmlv2rest_EXPORTS
#define SYSMLV2REST_EXPORT __declspec(dllexport)
#else
#define SYSMLV2REST_EXPORT __declspec(dllimport)
#endif
#else
#define SYSMLV2REST_EXPORT
#endif // WIN32
