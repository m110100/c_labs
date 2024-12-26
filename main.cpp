#include <iostream>
#include "fib_static.h"
#include <Windows.h>
#include <vector>
#include <string>

typedef void (*StartKeyboardLoggerFunc)();
typedef std::vector<char> (*GetLastKeysFunc)();

int main() {
    // Static linking example
    int n;
    std::cout << "Enter the position of the Fibonacci number: ";
    std::cin >> n;
    std::cout << "Fibonacci(" << n << ") = " << Fibonacci(n) << std::endl;

    // Dynamic linking example
    HMODULE hKeyboardDll = LoadLibrary("keyboard.dll");
    if (!hKeyboardDll) {
        std::cerr << "Failed to load keyboard.dll\n";
        return 1;
    }

    StartKeyboardLoggerFunc StartKeyboardLogger = (StartKeyboardLoggerFunc)GetProcAddress(hKeyboardDll, "StartKeyboardLogger");
    GetLastKeysFunc GetLastKeys = (GetLastKeysFunc)GetProcAddress(hKeyboardDll, "GetLastKeys");

    if (!StartKeyboardLogger || !GetLastKeys) {
        std::cerr << "Failed to load functions from keyboard.dll\n";
        FreeLibrary(hKeyboardDll);
        return 1;
    }

    StartKeyboardLogger();
    std::cout << "Keyboard logger started. Press keys and then press Enter to retrieve logged keys.\n";
    std::cin.ignore();
    std::cin.get();

    std::vector<char> lastKeys = GetLastKeys();
    std::cout << "Last 10 keys: ";
    for (char key : lastKeys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    FreeLibrary(hKeyboardDll);
    return 0;
}
