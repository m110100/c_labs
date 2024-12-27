#include "keyboard.hpp"
#include <windows.h>
#include <thread>
#include <mutex>
#include <vector>

const size_t BUFFER_SIZE = 10;
std::vector<char> keyBuffer(BUFFER_SIZE);
std::mutex bufferMutex;
std::thread keyLoggerThread;
bool loggingActive = false;
size_t bufferStart = 0;
size_t bufferEnd = 0;
size_t bufferCount = 0;

void KeyboardLogger() {
    while (loggingActive) {
        for (int key = 8; key <= 255; ++key) {
            if (GetAsyncKeyState(key) & 0x0001) {
                std::lock_guard<std::mutex> lock(bufferMutex);
                keyBuffer[bufferEnd] = static_cast<char>(key);
                bufferEnd = (bufferEnd + 1) % BUFFER_SIZE;

                if (bufferCount < BUFFER_SIZE) {
                    ++bufferCount;
                } else {
                    bufferStart = (bufferStart + 1) % BUFFER_SIZE; // Overwrite old data
                }
            }
        }
        Sleep(10);
    }
}

namespace Keyboard {
    void StartKeyboardLogger() {
        if (!loggingActive) {
            loggingActive = true;
            keyLoggerThread = std::thread(KeyboardLogger);
        }
    }

    std::vector<char> GetLastKeys() {
        std::lock_guard<std::mutex> lock(bufferMutex);
        std::vector<char> result;
        for (size_t i = 0; i < bufferCount; ++i) {
            size_t index = (bufferStart + i) % BUFFER_SIZE;
            result.push_back(keyBuffer[index]);
        }
        return result;
    }

    void StopKeyboardLogger() {
        if (loggingActive) {
            loggingActive = false;
            if (keyLoggerThread.joinable()) {
                keyLoggerThread.join();
            }
        }
    }
}
