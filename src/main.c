#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "global/globalVars.h"
#include "proc/mainWindowProc.h"
#include "util/utility.h"
#include "res/resource1.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {

    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);

    MSG msg;
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = programClass;
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = mainwindowProc;
    wc.hIcon = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    wc.hIconSm = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL,
                   "Window class registration failed",
                   "Error",
                   MB_ICONERROR);
        return FALSE;
    }
    ghInstance = hInstance;
    POINT initialWindowPosition = {0};
    centerWindow(&initialWindowPosition);
    mainWindowHandle = CreateWindowEx(
            0,
            wc.lpszClassName,
            (LPCSTR) L"MD5 hash generation",
            WS_OVERLAPPED
            | WS_BORDER
            | WS_CAPTION
            | WS_SYSMENU
            | WS_MINIMIZEBOX
            | WS_CLIPCHILDREN,
            initialWindowPosition.x,
            initialWindowPosition.y,
            mainWindowWidth,
            mainWindowHeight,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    ShowWindow(mainWindowHandle, nCmdShow);
    UpdateWindow(mainWindowHandle);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}
