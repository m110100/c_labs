#include <iostream>
#include "fib.h"
#include <vector>
#include <string>
#include <windows.h>

typedef void (*StartKeyboardLoggerFunc)();
typedef void (*GetLastKeysFunc)(char* buffer, int* size);

int main() {
    int n;
    std::cout << "Enter the position of the Fibonacci number: ";
    std::cin >> n;
    std::cout << "Fibonacci(" << n << ") = " << Fibonacci(n) << std::endl;

    HMODULE hKeyboardDll = LoadLibrary(L"../x64/Debug/keyboard_logger.dll");
    if (!hKeyboardDll) {
        std::cerr << "Failed to load keyboard_logger.dll\n";
        return 1;
    }

    StartKeyboardLoggerFunc StartKeyboardLogger = (StartKeyboardLoggerFunc)GetProcAddress(hKeyboardDll, "StartKeyboardLogger");
    GetLastKeysFunc GetLastKeys = (GetLastKeysFunc)GetProcAddress(hKeyboardDll, "GetLastKeys");

    if (!StartKeyboardLogger || !GetLastKeys) {
        std::cerr << "Failed to load functions from keyboard_logger.dll\n";
        FreeLibrary(hKeyboardDll);
        return 1;
    }

    StartKeyboardLogger();
    std::cout << "Keyboard logger started. Press keys and then press Enter to retrieve logged keys.\n";

    std::cin.ignore();
    std::cin.get();

    char buffer[10];
    int size = sizeof(buffer);
    GetLastKeys(buffer, &size);

    std::cout << "Last " << size << " keys: ";
    for (int i = 0; i < size; ++i) {
        std::cout << buffer[i] << " ";
    }
    std::cout << std::endl;

    FreeLibrary(hKeyboardDll);

    return 0;
}
