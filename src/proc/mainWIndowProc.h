#pragma once
#include <windows.h>
LRESULT CALLBACK mainwindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SetFont(HWND child, LPARAM font);