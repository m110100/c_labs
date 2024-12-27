#ifndef FIB_STATIC_HPP
#define FIB_STATIC_HPP

#ifdef FIB_STATIC_EXPORTS
    #define FIB_STATIC_API __declspec(dllexport)
#elif defined(FIB_STATIC_DLL)
    #define FIB_STATIC_API __declspec(dllimport)
#else
    #define FIB_STATIC_API
#endif

namespace FibStatic {
    FIB_STATIC_API int Fibonacci(int n);
}

#endif