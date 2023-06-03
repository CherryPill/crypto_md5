#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include <windows.h>

extern HWND mainWindowHandle;
extern HINSTANCE ghInstance;
extern HWND progressBarCntrl;
extern char *programClass;
extern int mainWindowHeight;
extern int mainWindowWidth;

struct ERROR_INFO {
    TCHAR *failedAction;
    DWORD statusCode;
};
#endif