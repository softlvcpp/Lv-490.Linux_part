#ifndef EXPORTCONFIG_H
#define EXPORTCONFIG_H

// Header that just defines export macros

#define EXTERN_C extern "C"

#ifdef _WIN32
#define USES_MSVC
#define OS_WINDOWS

// define for .dll
#ifdef LOGGERLIBRARY_EXPORTS
// I use VS to create dynamic library .dll file
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#elif defined(__unix__)
#define USES_CMAKE
#define OS_LINUX

#ifdef LOGGERLIBRARY_LIBRARY
#define LOGGER_API
#else
#define LOGGER_API
#endif

#endif // Export/import defines




#endif // EXPORTCONFIG_H
