#ifndef EXPORTCONFIG_H
#define EXPORTCONFIG_H

// Header that just defines export macros

// Defines for Windows
#if defined(_WIN32)
#if !defined(USES_MSVC)
#define USES_MSVC
#endif
#if !defined(OS_WINDOWS)
#define OS_WINDOWS
#endif

#ifdef LOGGERLIBRARY_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

// Defines for Linux
#elif defined(__unix__)
#if !defined(USES_CMAKE)
#define USES_CMAKE
#endif
#if !defined(OS_LINUX)
#define OS_LINUX
#endif

// Leave empty
#define LOGGER_API

#endif // Export/import defines

#endif // EXPORTCONFIG_H
