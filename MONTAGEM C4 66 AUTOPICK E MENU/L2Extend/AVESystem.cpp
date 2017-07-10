/*
    This file is part of L2Extend.

    L2Extend is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    L2Extend is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with L2Extend.  If not, see <http://www.gnu.org/licenses/>.

	You May Not Make Commercial Use of any of our content, and any kind
	of newer implementations will be need to be shared and commited.
*/

#include "AVESystem.h"
#include <fstream>
#include <sstream>

map<wstring, INT32> m_AveEffects;

void InitializeAVEs()
{
	// Hooking
	WriteInstruction(0x8F0E36, (INT32)AVESystem_Hook, 2, 0xE9);

	ifstream file;
	string fileName ="..\\Script\\AVEffects.txt";
	file.open(fileName.c_str());

	if (file)
	{
		string lineread;

		while(getline(file, lineread))
		{
			stringstream ss(lineread);

			string identifier;
			ss >> identifier;

			if ( identifier.find("ave_begin") != string::npos )
			{
				string ave_name, aveid;
				ss >> ave_name >> aveid;
				m_AveEffects[A2U(ave_name)] = atoi(aveid.c_str());
			}
		}
	}
}

INT32 AVESystem_FindAVEIDByName(WCHAR *AVEName)
{
	if ( m_AveEffects.find(AVEName) != m_AveEffects.end() )
	{
		//LOG->Add(1,"AVE : %ls - 0x%08X, Found !", AVEName, (INT32)m_AveEffects[AVEName]);
		return (INT32)m_AveEffects[AVEName];
	}
	else
	{
		//LOG->Add(1,"AVE : %ls, Not Found !", AVEName);
		return 0;
	}
}

INT32 AVESystem_FindAVEID(WCHAR *AVEName)
{
	__try
	{
		//LOG->AddToFile("Querying AVE : %ls", AVEName);
		return AVESystem_FindAVEIDByName(AVEName);
	}

	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//LOG->AddToFile("Error trying to Query the AVE Effect, Bad Memory Reference !");
		return 0;
	}
}