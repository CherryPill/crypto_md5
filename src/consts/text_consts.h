//
// Created by Roman on 6/3/2023.
//

#ifndef MD5_HASH_TOOL_TEXT_CONSTS_H
#define MD5_HASH_TOOL_TEXT_CONSTS_H

#include <tchar.h>

enum ErrorMsgResolver {
    OpenFileError = 0,
    CryptAcquireCtxError,
    CryptCreateHashError,
    CryptHashDataError,
    FileReadError,
    ClipboardError
};

static TCHAR* errorMessages[] = {
        _T("Error opening file"),
        _T("CryptAcquireContext failed"),
        _T("CryptCreateHash failed"),
        _T("CryptHashData failed"),
        _T("Couldn't read file"),
        _T("Clipboard error"),
};
#endif //MD5_HASH_TOOL_TEXT_CONSTS_H
