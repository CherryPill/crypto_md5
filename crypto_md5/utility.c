#pragma once
#include <Windows.h>
#include <tchar.h>
#include "globalVars.h"
#include "utility.h"
void centerWindow(POINT *position) {
	int userMonitorWidth = GetSystemMetrics(SM_CXSCREEN);
	int userMonitorHeight = GetSystemMetrics(SM_CYSCREEN);
	position->x = userMonitorWidth / 2 - mainWindowWidth / 2;
	position->y = userMonitorHeight / 2 - mainWindowHeight / 2;
	int sentinel = 10;
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
	TCHAR *extensionPart;
	_tcsncpy(shortenedPath, path, 4);
	_tcscat(shortenedPath, _T(".."));

	path+=4+1;
	_tcstok(path, _T("."));
	lastPart = path+_tcslen(path)-4;
	_tcscat(shortenedPath, lastPart);
	path = _tcstok(NULL, _T("."));
	_tcscat(shortenedPath, _T("."));
	_tcscat(shortenedPath, path);
	memset(path, 0, sizeof(path));
	
	int sentinel = 0xf;
	return shortenedPath;
}