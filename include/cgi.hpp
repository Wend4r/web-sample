//--------------------------------------------------------------
// Purpose: Utilities for reading CGI arguments
// Author:  John Gauch, Vladimir Ezhikov
// Date:    Spring 2002, Autumn 2024
//--------------------------------------------------------------

#ifndef _INCLUDE_CGI_HPP_
#	define _INCLUDE_CGI_HPP_

#	pragma once

#	include <stddef.h>

#	define CGI_MAX_ARGUMENTS 1024

class CGI
{
public:
	CGI();
	~CGI();

public:
	void Parse();

public:
	size_t GetArguemntCount() const;
	const char *GetArguemnt(const char szName[]) const;

public:
	const char *GetName(size_t nIndex) const;
	const char *GetValue(size_t nIndex) const;

private:
	size_t m_nArgumentCount;

	char *m_pszNames[CGI_MAX_ARGUMENTS];
	char *m_pszValues[CGI_MAX_ARGUMENTS];
};

#endif // _INCLUDE_CGI_HPP_
