#ifndef MAIN_WINDOW_PROC_H
#define MAIN_WINDOW_PROC_H

#include <windows.h>

LRESULT CALLBACK mainwindowProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK SetFont(HWND child, LPARAM font);

#endif