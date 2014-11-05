#ifndef __PLATFORM_CONFIG__
#define __PLATFORM_CONFIG__

#if defined(_MSVC)
#define API_EXPORT          __declspec(dllexport)
#define API_IMPORT          __declspec(dllimport)
#define API_INLINE          __forceinline
#define API_DEPRECATED      __declspec(deprecated)
#define API_ALIGNED(x)      __declspec(align(x))
#elif defined(__GNUG__) && __GNUG__ >= 4
#define API_EXPORT          __attribute__((visibility("default")))
#define API_IMPORT          __attribute__((visibility("default")))
#define API_INLINE          inline __attribute__((always_inline))
#define API_DEPRECATED      __attribute__((deprecated))
#define API_ALIGNED(x)      __attribute__((aligned(x)))
#else
#define API_EXPORT      
#define API_IMPORT      
#define API_INLINE          inline
#define API_DEPRECATED  
#define API_ALIGNED(x)  
#endif

#ifdef DLL_EXPORTS
#define PUBLIC API_EXPORT
#else
#define PUBLIC API_IMPORT
#endif

#if defined(linux) || defined(__linux) || defined(__linux__)
#define PLATFORM_LINUX
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define PLATFORM_WIN32
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#define PLATFORM_MACOS
#else
#warning "Unsupported platform"
#endif

#ifdef __GNUC__
#define likely(p)   __builtin_expect(!!(p), 1)
#define unlikely(p) __builtin_expect(!!(p), 0)
#else
#define likely(p)   (!!(p))
#define unlikely(p) (!!(p))
#endif

#endif // __PLATFORM_CONFIG__