#include "keyboard.h"
#include <windows.h>
#include <thread>
#include <mutex>
#include <deque>

std::deque<char> keyBuffer;
std::mutex bufferMutex;
std::thread keyLoggerThread;
bool loggingActive = false;

void KeyboardLogger() {
    while (loggingActive) {
        for (int key = 8; key <= 255; ++key) {
            if (GetAsyncKeyState(key) & 0x0001) {
                std::lock_guard<std::mutex> lock(bufferMutex);
                keyBuffer.push_back(static_cast<char>(key));
                if (keyBuffer.size() > 10) {
                    keyBuffer.pop_front();
                }
            }
        }
        Sleep(10);
    }
}

extern "C" void StartKeyboardLogger() {
    if (!loggingActive) {
        loggingActive = true;
        keyLoggerThread = std::thread(KeyboardLogger);
    }
}

extern "C" std::vector<char> GetLastKeys() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    return std::vector<char>(keyBuffer.begin(), keyBuffer.end());
}
