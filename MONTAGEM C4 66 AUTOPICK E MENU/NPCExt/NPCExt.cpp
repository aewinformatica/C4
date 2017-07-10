#include "NPCExt.h"

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

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			Initialize();
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
    
	return TRUE;
}

void Initialize()
{
	// Moving Old Crash Logs
	LPSECURITY_ATTRIBUTES attributes = NULL;
	CreateDirectory("CrashLogs",attributes);
	system("move *.bak CrashLogs");
	system("move *.dmp CrashLogs");

	//Initializing SharedFactory
	CSharedFactory::Initialize();

	//Initializing Agit
	InitializeAgit();

	//Initializing StaticObject
	CStaticObject::InitializeStaticObject();

	//Initializing ScriptAccessible
	CScriptAccessible::Initialize();

	//Initializing Socket
	CNPCPacketRecv::Initialize();
}