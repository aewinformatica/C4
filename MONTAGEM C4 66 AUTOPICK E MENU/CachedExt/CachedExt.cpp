#include "CachedExt.h"
#include "ExtendCachedObjects.h"
#include "CQuestSystem.h"
#include "CInfectedSkillsSystem.h"
#include "CPPFixes.h"
#include "CLevel85System.h"
#include "CAugmentationSystem.h"
#include "CPledgeDB.h"
#include "CPledgeDB.h"

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
			break;
		
		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			break;
	}
    
	return TRUE;
}

void AfterLoad(void *logPointer, CLog::LogType type, const wchar_t* format, ...)
{
	CLevel85System::InitializeAfterStart();

	CLog::Add(type, L"%ls", format);
}

void Initialize()
{
	// Moving Old Crash Logs
	LPSECURITY_ATTRIBUTES attributes = NULL;
	CreateDirectory("CrashLogs",attributes);
	system("move *.bak CrashLogs");
	system("move *.dmp CrashLogs");

	PacketHandler::Initialize();
	CPPFixes::Initialize();
	ExtendCachedObjects::Initialize();

	CQuestSystem::Initialize();
	CInfectedSkillsSystem::Initialize();
	CLevel85System::Initialize();
	CAugmentationSystem::Initialize();
	CPledgeSystem::Initialize();
	CPledgeDB::Initialize();
	CPledgeDB::Initialize();

	WriteInstruction(0x4475F6, (INT32)&AfterLoad, 0, 0xE8);
}
