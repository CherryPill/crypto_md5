#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "hashing.h"
#include "../global/globalVars.h"
#include "../ui/view.h"
#include "../handler/error_handler.h"
#include "../consts/text_consts.h"

void cleanUpResources(HCRYPTPROV prov, HCRYPTHASH hash, HANDLE pVoid);

void generateHash(TCHAR *filePath, char *hash) {

    char percentageDisplay[5] = {0};
    int previousProgress = 0;
    int currentProgress = 0;

    DWORD dwStatus = 0;
    BOOL bResult = FALSE;
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile = NULL;
    BYTE rgbFile[BUFSIZE];
    DWORD cbRead = 0;
    DWORD totalBytesRead = 0;
    BYTE rgbHash[MD5LEN];
    DWORD cbHash = 0;
    TCHAR rgbDigits[] = _T("0123456789abcdef");


    hFile = CreateFile(filePath,
                       GENERIC_READ,
                       NULL,
                       NULL,
                       OPEN_EXISTING,
                       FILE_FLAG_SEQUENTIAL_SCAN,
                       NULL);
    LARGE_INTEGER totalBytes;

    GetFileSizeEx(hFile, &totalBytes);

    if (hFile == INVALID_HANDLE_VALUE) {
        enum ErrorMsgResolver errorMsgIdx = OpenFileError;
        struct ERROR_INFO errorInfo = {errorMessages[errorMsgIdx], GetLastError()};
        handleError(errorInfo);
    }
    // Get handle to the crypto provider
    if (!CryptAcquireContext(&hProv,
                             NULL,
                             NULL,
                             PROV_RSA_FULL,
                             CRYPT_VERIFYCONTEXT)) {
        CloseHandle(hFile);

        enum ErrorMsgResolver errorMsgIdx = CryptAcquireCtxError;
        struct ERROR_INFO errorInfo = {errorMessages[errorMsgIdx], GetLastError()};
        handleError(errorInfo);
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {

        CloseHandle(hFile);
        CryptReleaseContext(hProv, 0);

        enum ErrorMsgResolver errorMsgIdx = CryptCreateHashError;
        struct ERROR_INFO errorInfo = {errorMessages[errorMsgIdx], GetLastError()};
        handleError(errorInfo);
    }
    bResult = ReadFile(hFile, rgbFile, BUFSIZE,
                       &cbRead, NULL);
    while (bResult) {
        if (0 == cbRead) {
            break;
        }
        if (!CryptHashData(hHash, rgbFile, cbRead, 0)) {
            cleanUpResources(hProv, hHash, hFile);
            enum ErrorMsgResolver errorMsgIdx = CryptHashDataError;
            struct ERROR_INFO errorInfo = {errorMessages[errorMsgIdx], GetLastError()};
            handleError(errorInfo);
        }
        totalBytesRead += cbRead;
        currentProgress = ((double) totalBytesRead / totalBytes.QuadPart) * 100;
        SendMessage(progressBarCntrl, PBM_SETPOS, currentProgress, 0);
        if (currentProgress > previousProgress) {
            sprintf(percentageDisplay, "%d%%", currentProgress);
            SetWindowText(GetDlgItem(mainWindowHandle, COMPUTED_HASH_LABEL), percentageDisplay);
            memset(percentageDisplay, 0, sizeof(percentageDisplay));
            previousProgress = currentProgress;
        }
        bResult = ReadFile(hFile, rgbFile, BUFSIZE,
                           &cbRead, NULL);
    }


    if (!bResult) {
        cleanUpResources(hProv, hHash, hFile);
        enum ErrorMsgResolver errorMsgIdx = FileReadError;
        struct ERROR_INFO errorInfo = {errorMessages[errorMsgIdx], GetLastError()};
    }
    cbHash = MD5LEN;
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)) {
        for (DWORD i = 0; i < cbHash; i++) {
            char hashHexPart[3] = {0};

            sprintf(hashHexPart, "%c%c",
                    rgbDigits[rgbHash[i] >> 4],
                    rgbDigits[rgbHash[i] & 0xf]);
            strcat(hash, hashHexPart);
        }
        hash[strlen(hash) + 1] = '\0';
    } else {
        dwStatus = GetLastError();
    }

    cleanUpResources(hProv, hHash, hFile);
}

void cleanUpResources(HCRYPTPROV prov, HCRYPTHASH hash, HANDLE pVoid) {
    CryptDestroyHash(hash);
    CryptReleaseContext(prov, 0);
    CloseHandle(pVoid);
}
