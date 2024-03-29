#ifndef VIEW_H
#define VIEW_H


#include <windows.h>
#include <commctrl.h>
#include <tchar.h>

#define FILE_LABEL 1
#define COMPUTED_HASH_LABEL 2
#define BUTTON_FILE_OPEN 3
#define BUTTON_DATA_RESET 4
#define EDIT_TEXT_HASH 5
#define INFO_HOLDER_LABEL 6
/*width and height*/
static const int labelDimensionsData[] = {
        2 << 6,
        2 << 4,
        2 << 7
};
static const int hashEditTextDimensionsData[2] = {
        160,
        26
};
static const int buttonDimensionsData[2] = {
        74,
        26
};
static int controlsMargin = 5;
static char *hashLabelData = "Computed hash: ";
extern TCHAR *labels[];
static char *buttonData[2] = {
        "Open",
        "Reset"
};

//creating controls
void createMainArea(HWND);

void createButtons(HWND);

void createLabels(HWND);

void createHashEditText(HWND);

void createProgressBar(HWND);

//modifying controls
void changeFileLabelText(HWND, TCHAR *);

void changeHashEditText(HWND, char *str);

void resetClipboardLabel(HWND parent);

void resetLabels(HWND parent);

//progress bar and hash text alternation
INT32 parseShowValue(BOOL);

void toggleProgressBarVisibility(BOOL, HWND);

void toggleShowHashPart(BOOL, HWND);

void toggleShowProgressPart(BOOL, HWND);

#endif