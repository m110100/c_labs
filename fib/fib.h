#pragma once

#ifndef FIB_H
#define FIB_H

#ifdef FIB_EXPORTS
#define FIB_API __declspec(dllexport)
#elif defined(FIB_DLL)
#define FIB_API __declspec(dllimport)
#else
#define FIB_API
#endif

extern "C" FIB_API int Fibonacci(int n);

#endif