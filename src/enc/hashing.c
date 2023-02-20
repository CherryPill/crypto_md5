#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "hashing.h"
#include "../global/globalVars.h"
#include "../ui/view.h"

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
		dwStatus = GetLastError();
		MessageBox(NULL,"Error opening file","Error",MB_OK|MB_ICONERROR);
		return 1;
	}
	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT)) {
		dwStatus = GetLastError();
		MessageBox(NULL, "CryptAcquireContext failed", "Error", MB_OK | MB_ICONERROR);
		CloseHandle(hFile);
		return dwStatus;
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
		dwStatus = GetLastError();
		MessageBox(NULL, "CryptCreateHash failed", "Error", MB_OK | MB_ICONERROR);
		CloseHandle(hFile);
		CryptReleaseContext(hProv, 0);
		return dwStatus;
	}
	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE,
		&cbRead, NULL)) {
		if (0 == cbRead) {
			break;
		}
		if (!CryptHashData(hHash, rgbFile, cbRead, 0)) {
			dwStatus = GetLastError();
			MessageBox(NULL, "CryptHashData failed", "Error", MB_OK | MB_ICONERROR);
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hFile);
			return dwStatus;
		}
		totalBytesRead += cbRead;
		currentProgress = ((double)totalBytesRead/totalBytes.QuadPart)*100;
		SendMessage(progressBarCntrl, PBM_SETPOS, currentProgress, 0);
		if (currentProgress > previousProgress)
		{
			sprintf(percentageDisplay, "%d%%", currentProgress);
			SetWindowText(GetDlgItem(mainWindowHandle, COMPUTED_HASH_LABEL), percentageDisplay);
			memset(percentageDisplay, 0, sizeof(percentageDisplay));
			previousProgress = currentProgress;
		}
	}
	if (!bResult) {
		dwStatus = GetLastError();
		MessageBox(NULL, "ReadFile failed", "Error", MB_OK | MB_ICONERROR);
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hFile);
		return dwStatus;
	}
	cbHash = MD5LEN;
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)){
		for (DWORD i = 0; i < cbHash; i++) {
			char hashHexPart[3] = { 0 };
			
			sprintf(hashHexPart, "%c%c", 
				rgbDigits[rgbHash[i] >> 4], 
				rgbDigits[rgbHash[i] & 0xf]);
			strcat(hash, hashHexPart);
		}
		hash[strlen(hash) + 1] = '\0';
	}
	else {
		dwStatus = GetLastError();
	}
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);
}