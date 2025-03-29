#ifdef WIN32
#ifdef sysmlv2service_EXPORTS
#define SYSMLV2SERVICE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2SERVICE_EXPORT __declspec(dllimport)
#endif
#else
#define SYSMLV2SERVICE_EXPORT
#endif // WIN32
