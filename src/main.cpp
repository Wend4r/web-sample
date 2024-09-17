//--------------------------------------------------------------
// Purpose: Main entry point.
// Author:  John Gauch, Vladimir Ezhikov
// Date:    Spring 2002, Autumn 2024
//--------------------------------------------------------------

#include <cgi.hpp>

#include <stdio.h>

/*--------------------------------------------------------------
Main program parses HTML and adds a user to the database.
--------------------------------------------------------------*/
int main()
{
	CGI aCGI;

	aCGI.Parse();

	for(size_t n = 0, nCount = aCGI.GetArguemntCount(); n < nCount; n++)
	{
		printf("%s: %s\n", aCGI.GetName(n), aCGI.GetValue(n));
	}

	return 0;
}
