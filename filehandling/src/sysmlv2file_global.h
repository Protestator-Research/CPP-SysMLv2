#ifdef WIN32
#ifdef sysmlv2file_EXPORTS
#define SYSMLV2FILE_EXPORT __declspec(dllexport)
#else
#define SYSMLV2FILE_EXPORT __declspec(dllimport)
#endif
#else
#define SYSMLV2FILE_EXPORT
#endif // WIN32
