#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------
// Function for copying a substring.
//--------------------------------------------------------------
char *copy_string(const char *pszFrom, size_t nStartIndex, size_t nEndIndex)
{
	size_t nLength = nStartIndex - nEndIndex;

	// Create string
	char *pResult = (char *)malloc(nLength + 1);

	if(!pResult)
	{
		return NULL;
	}

	strncpy(pResult, pszFrom, nLength);

	return pResult;
}

//--------------------------------------------------------------
// Function for decoding CGI strings.
//--------------------------------------------------------------
void decode_string(const char szSource[], char sOutput[])
{
	const char szDigits[] = "0123456789ABCDEF";

	size_t nLength = strlen(szSource);

	size_t nOutPosition = 0;

	for(size_t nPosition = 0; nPosition < nLength; nPosition++)
	{
		// Handle white space.
		if(szSource[nPosition] == '+')
		{
			sOutput[nOutPosition++] = ' ';
		}

		// Handle hex characters.
		else if(szSource[nPosition] == '%')
		{
			char ch1 = toupper(szSource[++nPosition]), 
			     ch2 = toupper(szSource[++nPosition]);

			sOutput[nOutPosition++] = 16 * (strchr(szDigits, ch1) - strchr(szDigits,'0')) + strchr(szDigits, ch2) - strchr(szDigits,'0');
		}
		else // Handle remaining characters.
		{
			sOutput[nOutPosition++] = szSource[nPosition];
		}
	}

	// Mark end of string.
	sOutput[nOutPosition] = '\0';
}
