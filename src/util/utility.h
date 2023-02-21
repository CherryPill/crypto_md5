#ifndef UTILITY_H
#define UTILITY_H

void centerWindow(POINT *);

void getFileNameFromPath(TCHAR *fullPath, TCHAR *fileName);

TCHAR *shortenPath(TCHAR *);

void separateNameAndExt(TCHAR *fullPath, TCHAR *ext);

#endif