#include <Windows.h>
#include <tchar.h>
#include "mainWIndowProc.h"
#include "../ui/view.h"
#include "../io/fileIO.h"
#include "../util/utility.h"
#include "../enc/hashing.h"
#include "../consts/text_consts.h"

void copyToClipBoard(HWND parent, const char *hashText);

LRESULT CALLBACK mainwindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            createMainArea(hwnd);
            toggleProgressBarVisibility(FALSE, hwnd);
            EnumChildWindows(hwnd, (WNDENUMPROC) SetFont, (LPARAM) GetStockObject(DEFAULT_GUI_FONT));
            break;
        }
        case WM_COMMAND: {
            WORD receivedOp = LOWORD(wParam);
            switch (receivedOp) {
                case BUTTON_FILE_OPEN: {
                    TCHAR filePathBuff[256] = {0};
                    TCHAR filePathShortBuff[256] = {0};
                    TCHAR filePathShortBuffComplete[256] = {0};
                    TCHAR *shortened = NULL;
                    if (!openFileDiag(hwnd, filePathBuff, filePathShortBuff)) {
                        if (_tcslen(filePathShortBuff) > 22) {
                            shortened = shortenPath(filePathShortBuff);
                            _tcscpy(filePathShortBuffComplete, shortened);
                        } else {
                            _tcscpy(filePathShortBuffComplete, filePathShortBuff);
                        }
                        _tcscat(filePathShortBuffComplete, _T(" loaded"));
                        changeFileLabelText(hwnd, filePathShortBuffComplete);
                        char computedHash[1024] = {0};
                        toggleProgressBarVisibility(TRUE, hwnd);
                        generateHash(filePathBuff, computedHash);
                        toggleProgressBarVisibility(FALSE, hwnd);
                        changeHashEditText(hwnd, computedHash);
                        copyToClipBoard(hwnd, computedHash);
                    }
                    break;
                }
                case BUTTON_DATA_RESET: {
                    resetLabels(hwnd);
                    changeHashEditText(hwnd, "");
                    break;
                }
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}


void copyToClipBoard(HWND parent, const char *hashText) {

    if (hashText != NULL) {
        const size_t hashCharLen = _tcslen(hashText) * sizeof(TCHAR) + 1;
        HGLOBAL allocatedMem = GlobalAlloc(GMEM_MOVEABLE, hashCharLen);
        memcpy(GlobalLock(allocatedMem), hashText, hashCharLen);

        HWND infoHolderLabel = GetDlgItem(parent, INFO_HOLDER_LABEL);

        if (OpenClipboard(parent)) {
            EmptyClipboard();
            SetClipboardData(CF_TEXT, allocatedMem);
            CloseClipboard();
            SetWindowText(infoHolderLabel, "Copied to clipboard");
        } else {
            enum ErrorMsgResolver errorMsgIdx = ClipboardError;
            SetWindowText(infoHolderLabel, errorMessages[errorMsgIdx]);
        }
    }
}

BOOL CALLBACK SetFont(HWND child, LPARAM font) {
    SendMessage(child, WM_SETFONT, (WPARAM) font, MAKELPARAM(TRUE, 0));
    return TRUE;
}