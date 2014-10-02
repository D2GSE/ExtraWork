/*
*	ExtraWork Client - Loads an ExtraWork DLL for information
*	Copyright (C) 2014  xboi209 (xboi209@gmail.com)
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include "Main.h"

using namespace std;

//Example:	Client IX86ExtraWork.dll 0x3 4
//		Program DLL Gametype Length
int main(int argc, char ** argv)
{
	HINSTANCE		hLib;
	ExtraWorkProc	lpfnExtraWork;
	BOOL			bReturn = NULL;
	EXTRAWORK		ew;
	char			*dllname;


	if (argc != 1 && argc != 4)
	{
		cout << "Invalid number of arguments" << endl;
		return 0;
	}
	else if (argc == 1)	//Default values if no arguments are passed
	{
		dllname = "IX86ExtraWork.dll";
		ew.GameType = 0x3;
		ew.Length = 4;
	}
	else //4 arguments
	{
		dllname = argv[1];
		ew.GameType = (WORD)strtoul(argv[2], NULL, 16);
		ew.Length = atoi(argv[3]);
	}
	*ew.OutBuffer = 0;


	if (hLib = LoadLibrary(dllname))
	{
		if (lpfnExtraWork = (ExtraWorkProc)GetProcAddress(hLib, "ExtraWork"))
		{
			bReturn = (*lpfnExtraWork)(&ew);

			cout << "ExtraWork returned " << (bReturn ? "TRUE" : "FALSE") << endl;
			cout << "GameType: " << ew.GameType << "\t\t" << "Length: " << ew.Length << endl;
			cout << "Message: " << ew.OutBuffer << endl;
		}

		FreeLibrary(hLib);
	}

	if (!bReturn)
	{
		cout << "Could not load " << dllname << endl;
	}


	return 0;
}