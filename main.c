#include <windows.h>

HHOOK handleHook = NULL;
HWND activeWindow = NULL;
RECT windowRect;
BOOL isRestricted = FALSE;

void restrictCursor() {
    if (activeWindow) {
        GetClientRect(activeWindow, &windowRect);
        MapWindowPoints(activeWindow, NULL, (LPPOINT)&windowRect, 2);
        ClipCursor(&windowRect);
    }
}

LRESULT CALLBACK handleHotkey(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;

        if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && pKeyboard->vkCode == VK_CAPITAL) {
            if (!isRestricted) {
                activeWindow = GetForegroundWindow();
                restrictCursor();
                isRestricted = TRUE;
            } else {
                ClipCursor(NULL);
                isRestricted = FALSE;
            }
        }
    }

    return CallNextHookEx(handleHook, nCode, wParam, lParam);
}

void setHook() {
    handleHook = SetWindowsHookEx(WH_KEYBOARD_LL, handleHotkey, NULL, 0);
}

void releaseHook() {
    UnhookWindowsHookEx(handleHook);
}

int WINAPI main(HINSTANCE handleInstace, HINSTANCE handlePrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    MSG msg;
    setHook();

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    releaseHook();

    return (int)msg.wParam;
}