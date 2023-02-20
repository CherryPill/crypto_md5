#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "fileIO.h"
#include "../util/utility.h"

int openFileDiag(HWND mainWindow, TCHAR *loadedFilePath, TCHAR *fileNoPath) {
    OPENFILENAME fileName;
    TCHAR szFile[MAX_PATH];
    ZeroMemory(&fileName, sizeof(fileName));
    fileName.lStructSize = sizeof(fileName);
    fileName.hwndOwner = mainWindow;
    fileName.nMaxFile = sizeof(szFile);
    fileName.lpstrFile = szFile;
    fileName.lpstrFile[0] = _T('\0');
    fileName.lpstrFilter = _T("All Files (*.*)\0*.*\0");
    fileName.Flags =
            OFN_PATHMUSTEXIST
            | OFN_OVERWRITEPROMPT
            | OFN_EXPLORER
            | OFN_HIDEREADONLY;

    if (GetOpenFileName(&fileName)) {
        _tcscpy(loadedFilePath, fileName.lpstrFile);
        getFileNameFromPath(loadedFilePath, fileNoPath);
        return 0;
    } else {
        //window was dismissed
        return 1;
    }
}