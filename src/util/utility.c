#include <Windows.h>
#include <tchar.h>
#include "utility.h"
#include "../global/globalVars.h"

void centerWindow(POINT *position) {
    int userMonitorWidth = GetSystemMetrics(SM_CXSCREEN);
    int userMonitorHeight = GetSystemMetrics(SM_CYSCREEN);
    position->x = userMonitorWidth / 2 - mainWindowWidth / 2;
    position->y = userMonitorHeight / 2 - mainWindowHeight / 2;
}

void getFileNameFromPath(TCHAR *fullPath, TCHAR *fileName) {
    TCHAR fullPathTempBuff[256] = {0};
    _tcscpy(fullPathTempBuff, fullPath);
#define fullPath fullPathTempBuff
    TCHAR *ptr = _tcstok(fullPath, _T("\\"));
    TCHAR *prevInstance;
    while (ptr != NULL) {
        prevInstance = ptr;
        ptr = _tcstok(NULL, _T("\\"));
    }
    _tcscpy(fileName, prevInstance);
#undef fullPath
}

//turns verylongfilename.zip into very..name.zip
TCHAR *shortenPath(TCHAR *path) {
    static TCHAR shortenedPath[256] = {0};
    TCHAR *lastPart = NULL;
    TCHAR *extensionPart[256] = {0};
    _tcsncpy(shortenedPath, path, 4);
    _tcscat(shortenedPath, _T(".."));
    path += 4 + 1;
    separateNameAndExt(path, extensionPart);
    lastPart = path + _tcslen(path) - 4;
    _tcscat(shortenedPath, lastPart);
    _tcscat(shortenedPath, extensionPart);
    memset(path, 0, sizeof(path));
    return shortenedPath;
}

void separateNameAndExt(TCHAR *fullPath, TCHAR *ext) {
    int c = _tcslen(fullPath) - 1;
    TCHAR *extLoc = fullPath + c;
    TCHAR singleChar;
    do {
        singleChar = *extLoc;
        if (singleChar == _T('.')) {
            break;
        }
        --c;
        extLoc = fullPath + c;
    } while (extLoc != fullPath);
    _tcscpy(ext, extLoc);
    fullPath[c] = _T('\0');
}