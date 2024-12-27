#include <iostream>
#include "fib_static.hpp"
#include "keyboard.hpp"
#include <vector>
#include <string>

int main() {
    // Static linking example
    int n;
    std::cout << "Enter the position of the Fibonacci number: ";
    std::cin >> n;
    std::cout << "Fibonacci(" << n << ") = " << FibStatic::Fibonacci(n) << std::endl;

    // Keyboard logging example
    Keyboard::StartKeyboardLogger();
    std::cout << "Keyboard logger started. Press keys and then press Enter to retrieve logged keys.\n";
    std::cin.ignore();
    std::cin.get();

    std::vector<char> lastKeys = Keyboard::GetLastKeys();
    std::cout << "Last 10 keys: ";
    for (char key : lastKeys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    Keyboard::StopKeyboardLogger();
    return 0;
}
