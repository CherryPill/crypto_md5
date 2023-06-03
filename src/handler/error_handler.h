//
// Created by Roman on 6/3/2023.
//

#ifndef MD5_HASH_TOOL_ERROR_HANDLER_H
#define MD5_HASH_TOOL_ERROR_HANDLER_H

#include <windows.h>
#include "../global/globalVars.h"


void initErrorStruct(TCHAR *failedAction, DWORD statusCode);

/**
 * Handle status error and show the appropriate error to user
 * @param status
 */
void handleError(struct ERROR_INFO errorInfo);

#endif //MD5_HASH_TOOL_ERROR_HANDLER_H
