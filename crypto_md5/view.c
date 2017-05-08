#include <tchar.h>
#include "globalVars.h"
#include "view.h"
TCHAR *labels[] = {
	_T("No file loaded"),
	_T(" loaded")
};
void createMainArea(HWND parentWindow) {
	createButtons(parentWindow);
	createLabels(parentWindow);
	createHashEditText(parentWindow);
	createProgressBar(parentWindow);
}

void createProgressBar(HWND parent) {
progressBarCntrl = CreateWindowEx(0, PROGRESS_CLASS, NULL,
			WS_CHILD | WS_VISIBLE,
			labelDimensionsData[0] + controlsMargin,
			labelDimensionsData[1] + controlsMargin,
			hashEditTextDimensionsData[0],
			hashEditTextDimensionsData[1],
			parent, NULL, ghInstance, NULL);
			SendMessage(progressBarCntrl, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
}
void createButtons(HWND parent) {
	CreateWindowEx(
		0,
		"Button",
		buttonData[0],
		WS_CHILD | WS_VISIBLE,
		labelDimensionsData[0] + controlsMargin,
		0,
		buttonDimensionsData[0],
		buttonDimensionsData[1],
		parent,
		(HMENU)BUTTON_FILE_OPEN,
		NULL,
		NULL);
	CreateWindowEx(
		0,
		"Button",
		buttonData[1],
		WS_CHILD | WS_VISIBLE,
		labelDimensionsData[0] + controlsMargin*2 + buttonDimensionsData[0] + controlsMargin,
		0,
		buttonDimensionsData[0],
		buttonDimensionsData[1],
		parent,
		(HMENU)BUTTON_DATA_CLEAR,
		NULL,
		NULL);
}
void createLabels(HWND parent) {
	CreateWindowEx(
		0,
		_T("Static"),
		labels[0],
		WS_CHILD | WS_VISIBLE | SS_CENTER,
		0,
		controlsMargin,
		labelDimensionsData[0],
		labelDimensionsData[1],
		parent,
		(HMENU)FILE_LABEL,
		NULL,
		NULL);
	CreateWindowEx(
		0,
		"Static",
		hashLabelData,
		WS_CHILD | WS_VISIBLE | SS_CENTER,
		0,
		labelDimensionsData[1] + controlsMargin *2,
		labelDimensionsData[0],
		labelDimensionsData[1],
		parent,
		(HMENU)COMPUTED_HASH_LABEL,
		NULL,
		NULL);
}
void createHashEditText(HWND parent) {
	CreateWindowEx(
		0,
		"Edit",
		"",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		labelDimensionsData[0] + controlsMargin,
		labelDimensionsData[1] + controlsMargin,
		hashEditTextDimensionsData[0],
		hashEditTextDimensionsData[1],
		parent,
		(HMENU)EDIT_TEXT_HASH,
		NULL,
		NULL);
}
//modifying

void changeFileLabelText(HWND parent, TCHAR *fileNameShort) {
	HWND fileLabelHandle = GetDlgItem(parent, FILE_LABEL);
	SetWindowText(fileLabelHandle, fileNameShort);
}
void changeHashEditText(HWND parent, char *hashText) {
	HWND hashTextHandle = GetDlgItem(parent, EDIT_TEXT_HASH);
	SetWindowText(hashTextHandle, hashText);
	int sentinel = 10;
}
void toggleShowProgressPart(BOOL v, HWND parent) {
	SetWindowText(GetDlgItem(parent, COMPUTED_HASH_LABEL), "0%");
	ShowWindow(progressBarCntrl, parseShowValue(v));
}
void toggleShowHashPart(BOOL v, HWND parent) {
	SetWindowText(GetDlgItem(parent, COMPUTED_HASH_LABEL), hashLabelData);
	ShowWindow(GetDlgItem(parent, EDIT_TEXT_HASH), parseShowValue(v));
}
INT32 parseShowValue(BOOL v){
	INT32 flag = -1;
	if (v == TRUE) {
		flag = SW_SHOW;
	}
	else {
		flag = SW_HIDE;
	}
	return flag;
}
void toggleProgressBarVisibility(BOOL v, HWND hwnd) {
	toggleShowProgressPart(v, hwnd);
	toggleShowHashPart(!v, hwnd);
}