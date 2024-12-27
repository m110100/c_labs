#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#ifdef KEYBOARD_EXPORTS
    #define KEYBOARD_API __declspec(dllexport)
#else
    #define KEYBOARD_API __declspec(dllimport)
#endif

#include <vector>

namespace Keyboard {
    KEYBOARD_API void StartKeyboardLogger();
    KEYBOARD_API std::vector<char> GetLastKeys();
    KEYBOARD_API void StopKeyboardLogger();
}

#endif