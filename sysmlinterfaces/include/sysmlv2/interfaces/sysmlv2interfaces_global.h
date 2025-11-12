#ifdef WIN32
#ifdef sysmlv2interfaces_EXPORTS
#define SYSMLV2INTERFACE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2INTERFACE_EXPORT __declspec(dllimport)
#endif
#else
#define SYSMLV2INTERFACE_EXPORT
#endif // WIN32
