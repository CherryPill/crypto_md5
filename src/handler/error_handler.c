//
// Created by Roman on 6/3/2023.
//

#include <tchar.h>
#include <stdio.h>
#include "error_handler.h"

void handleError(struct ERROR_INFO errorInfo) {

    UINT style = MB_OK | MB_ICONERROR;

    TCHAR errorBuff[256] = {0};
    TCHAR statusCodeBuff[5] = {0};

    _stprintf(statusCodeBuff, "%ld", errorInfo.statusCode);
    _tcscpy(errorBuff, errorInfo.failedAction);
    _tcscat(errorBuff, ", statusCode: ");
    _tcscat(errorBuff, statusCodeBuff);

    MessageBox(NULL, errorBuff, "Error", style);
}

void initErrorStruct(TCHAR *failedAction, DWORD statusCode) {
    struct ERROR_INFO errorInfo = {_T(""),1};
}
