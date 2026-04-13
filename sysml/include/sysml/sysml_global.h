//
// Created by Moritz Herzog on 17.03.26.
//

#ifdef WIN32
#ifdef sysml_EXPORTS
#define SYSML_EXPORT __declspec(dllexport)
#else
#define SYSML_EXPORT __declspec(dllimport)
#endif
#else
#define SYSML_EXPORT
#endif // WIN32
