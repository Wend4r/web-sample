//--------------------------------------------------------------
// Purpose: Utilities for reading CGI arguments
// Author:  John Gauch, Vladimir Ezhikov
// Date:    Spring 2002, Autumn 2024
//--------------------------------------------------------------

#ifndef _INCLUDE_CGI_UTILS_H_
#	define _INCLUDE_CGI_UTILS_H_

#	include <stddef.h>

char *copy_string(const char *pszFrom, size_t nStartIndex, size_t nEndIndex);
void decode_string(const char szSource[], char sOutput[]);

#endif // _INCLUDE_CGI_UTILS_H_
