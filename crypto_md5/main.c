#include <windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "resource.h"
#include "globalVars.h"
#include "mainWindowProc.h"
#include "utility.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	MSG msg;
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = programClass;
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = mainwindowProc;
	wc.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, NULL);
	wc.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, NULL);
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
		L"MD5 hash generation",
		WS_OVERLAPPED | WS_BORDER
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
	return (int)msg.wParam;
}
