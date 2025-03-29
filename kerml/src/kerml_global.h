#ifdef WIN32
#ifdef kerml_EXPORTS
#define KERML_EXPORT __declspec(dllexport)
#else
#define KERML_EXPORT __declspec(dllimport)
#endif
#else
#define KERML_EXPORT
#endif // WIN32
