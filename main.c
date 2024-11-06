#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void displayFileContent(const char* filePath) {
    HANDLE handleFile = CreateFile(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (handleFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file for read: %d\n", GetLastError());
        
        return;
    }

    DWORD bytesRead;
    char buffer[1024];

    printf("File content:\n");
    while (ReadFile(handleFile, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        printf("%.*s", bytesRead, buffer);
    }

    CloseHandle(handleFile);
}
void appendCreationTime(const char* filePath) {
    FILETIME creationTime, lastAccessTime, lastWriteTime;
    HANDLE handleFile = CreateFile(filePath, FILE_WRITE_DATA | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (handleFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file for write: %d\n", GetLastError());
        
        return;
    }

    if (GetFileTime(handleFile, &creationTime, &lastAccessTime, &lastWriteTime) == 0) {
        printf("Failed to get file time: %d\n", GetLastError());

        CloseHandle(handleFile);

        return;
    }

    SYSTEMTIME systemTime;
    FileTimeToSystemTime(&creationTime, &systemTime);

    char time[100];
    sprintf(time, "\nTime of file creation: %02d-%02d-%04d %02d:%02d:%02d\n", 
        systemTime.wDay, 
        systemTime.wMonth, 
        systemTime.wYear, 
        systemTime.wHour, 
        systemTime.wMinute,
        systemTime.wSecond
    );

    SetFilePointer(handleFile, 0, NULL, FILE_END);
    DWORD bytesWritten;
    WriteFile(handleFile, time, strlen(time), &bytesWritten, NULL);

    printf("\nTime of file creation appended\n");

    CloseHandle(handleFile);
}

int main() {
    OPENFILENAME ofn;
    char filePath[MAX_PATH] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = sizeof(filePath);
    ofn.lpstrFilter = "Text Files\0*.txt\0All Files\0*.*\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        printf("Selected file: %s\n", filePath);

        displayFileContent(filePath);

        appendCreationTime(filePath);
    } else {
        printf("Files was not selected.\n");
    }

    return 0;
}
