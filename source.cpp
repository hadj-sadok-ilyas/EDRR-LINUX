#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

string DetectOS() {
#if defined(_WIN64) || defined(_WIN32)
    return "Windows";

# elif  defined(__linux__)
    return "Linux";

#endif
}

void WindowsFIM() {
    cout << "what file would you like to monitor? Filename:" << endl;
    wstring dir;
    wcin >> dir;
    LPCWSTR dir2 = dir.c_str();
    HANDLE hDir = CreateFileW(
        dir2,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE |
        FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE)
    {
        printf("Failed to open directory. Error: %lu\n",
               GetLastError());
    }

    BYTE buffer[4096];
    DWORD bytesReturned;

    printf("Watching the directory\n");

    while (1)
    {
        BOOL success = ReadDirectoryChangesW(
            hDir,
            buffer,
            sizeof(buffer),
            FALSE, // TRUE = include subfolders
            FILE_NOTIFY_CHANGE_FILE_NAME |
            FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_LAST_WRITE |
            FILE_NOTIFY_CHANGE_SIZE,
            &bytesReturned,
            NULL,
            NULL
        );

        if (!success)
        {
            printf("ReadDirectoryChangesW failed. Error: %lu\n",
                   GetLastError());
            break;
        }

        FILE_NOTIFY_INFORMATION* info =
            (FILE_NOTIFY_INFORMATION*)buffer;

        while (1)
        {
            const wchar_t* action = L"UNKNOWN";

            switch (info->Action)
            {
            case FILE_ACTION_ADDED:
                action = L"CREATED";
                break;

            case FILE_ACTION_REMOVED:
                action = L"DELETED";
                break;

            case FILE_ACTION_MODIFIED:
                action = L"MODIFIED";
                break;

            case FILE_ACTION_RENAMED_OLD_NAME:
                action = L"RENAMED FROM";
                break;

            case FILE_ACTION_RENAMED_NEW_NAME:
                action = L"RENAMED TO";
                break;
            }

            wprintf(
            L"[%ls] %.*ls\n",
                action,
                info->FileNameLength / sizeof(WCHAR),
                info->FileName
            );

            if (info->NextEntryOffset == 0)
                break;

            info = (FILE_NOTIFY_INFORMATION*)
                ((BYTE*)info + info->NextEntryOffset);
        }
    }

    CloseHandle(hDir);
}




