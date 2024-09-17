//--------------------------------------------------------------
// Purpose: Utilities for reading CGI arguments
// Author:  John Gauch, Vladimir Ezhikov
// Date:    Spring 2002, Autumn 2024
//--------------------------------------------------------------

#include <cgi.hpp>
#include <cgi/utils.hpp>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------
// Constructor function reads and parses CGI arguments.
//--------------------------------------------------------------
CGI::CGI()
 :  m_nArgumentCount(0)
{
	for(size_t nPosition = 0; nPosition < CGI_MAX_ARGUMENTS; nPosition++)
	{
		m_pszNames[nPosition] = m_pszValues[nPosition] = NULL;
	}
}

//--------------------------------------------------------------
// Destructor function releases memory.
//--------------------------------------------------------------
CGI::~CGI()
{
	for(size_t n = 0; n < m_nArgumentCount; n++)
	{
		{
			char *pszName = m_pszNames[n];

			if(pszName)
			{
				free(pszName);
			}
		}

		{
			char *pszValue = m_pszValues[n];

			if(pszValue)
			{
				free(pszValue);
			}
		}
	}
}

//--------------------------------------------------------------
// Constructor function reads and parses CGI arguments.
//--------------------------------------------------------------
void CGI::Parse()
{
	// Read environment variables.
	char *pszRequestMethod = getenv("REQUEST_METHOD"), 
	     *pszQueryString = getenv("QUERY_STRING"), 
	     *pszContentLength = getenv("CONTENT_LENGTH");

#ifdef DEBUG
	printf("Request method: \"%s\"\n", pszRequestMethod);
	printf("Query string: \"%s\"\n", pszQueryString);
	printf("Content length: \"%s\"\n", pszContentLength);
#endif

	// Check a request method variable.
	if(pszRequestMethod == NULL)
	{
		return;
	}

	size_t nQueryLength = 0;

	// Handle GET requests.
	if(!strcmp(pszRequestMethod, "GET"))
	{
		if(!pszQueryString)
		{
#ifdef DEBUG
			puts("Query string is empty");
#endif

			return;
		}

		nQueryLength = pszContentLength ? strlen(pszQueryString) : (size_t)atol(pszContentLength);
	}

	// Handle POST requests.
	if(!strcmp(pszRequestMethod, "POST"))
	{
		if(pszContentLength)
		{
			nQueryLength = (size_t)atol(pszContentLength);
		}
		else
		{
#ifdef DEBUG
			puts("Query length is empty");
#endif

			return;
		}

		pszQueryString = (char *)malloc(nQueryLength);

		if(pszQueryString == NULL)
		{
#ifdef DEBUG
			puts("Query string is empty");
#endif

			return;
		}

		fgets(pszQueryString, nQueryLength, stdin);
	}

	// Separate query string into arguments.
	{
		size_t nStartName, nEndName, nStartValue, nEndValue = -1;

		while(nEndValue < nQueryLength)
		{
			// Find argument name.
			{
				nStartName = nEndName = nEndValue + 1;

				while((nEndName < nQueryLength) && (pszQueryString[nEndName] != '='))
				{
					nEndName++;
				}
			}

			auto &sName = m_pszNames[m_nArgumentCount];

			// Copy and decode name string.
			sName = copy_string(pszQueryString, nStartName, nEndName);
			decode_string(sName, sName);

			// Find argument value.
			{
				nStartValue = nEndValue = nEndName + 1;

				while((nEndValue < nQueryLength) && (pszQueryString[nEndValue] != '&'))
				{
					nEndValue++;
				}
			}

			auto &sValue = m_pszNames[m_nArgumentCount];

			// Copy and decode value string.
			sValue = copy_string(pszQueryString, nStartValue, nEndValue);
			decode_string(sValue, sValue);

			m_nArgumentCount++;
		}
	}
}

//--------------------------------------------------------------
// Return number of CGI arguments.
//--------------------------------------------------------------
size_t CGI::GetArguemntCount() const
{
	return m_nArgumentCount;
}

//--------------------------------------------------------------
// Argument lookup by name.
//--------------------------------------------------------------
const char *CGI::GetArguemnt(const char szName[]) const
{
	// Lookup argument by name.
	for(size_t nArgument = 0; nArgument < m_nArgumentCount; nArgument++)
	{
		if(!strcmp(szName, m_pszNames[nArgument]))
		{
			return m_pszValues[nArgument];
		}
	}

	// Return NULL if not found.
	return NULL;
}

//--------------------------------------------------------------
// Argument name lookup by number.
//--------------------------------------------------------------
const char *CGI::GetName(size_t nIndex) const
{
	assert(0 <= nIndex && nIndex < m_nArgumentCount);

	// Lookup argument by location.
	return m_pszNames[nIndex];
}

//--------------------------------------------------------------
// Argument value lookup by number.
//--------------------------------------------------------------
const char *CGI::GetValue(size_t nIndex) const
{
	assert(0 <= nIndex && nIndex < m_nArgumentCount);

	// Lookup argument by location.
	return m_pszValues[nIndex];
}
