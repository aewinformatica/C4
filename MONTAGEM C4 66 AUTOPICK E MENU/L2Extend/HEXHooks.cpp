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

// Here we should include the bytes we wan't to hex in the memory of L2Server
// Please Always Add Comments of What Each of Those Hexxings Do !

#include "HEXHooks.h"
#include "MenuExt.h"
#include "CSocket.h"
#include "IniFile.h"

void HEXHooks::Initialize()
{
	MenuExt::Install();
	// L2Server Acceptable Game Protocol
	NULLMemory(0x9BA9B3, 3);
	WriteMemoryBYTES(0x9BA9B3, (VOID *)GlobalVars::GVs()->pGeneral->ProtocolVersion.c_str(), GlobalVars::GVs()->pGeneral->ProtocolVersion.size());

	// Remove the Maximum Loadable Items Cap (ItemData.txt) [This Fix Is Crashing, Im Doing Investigations...]
	SetMaxLoadableItems(1000000);
	WriteMemoryDWORD(0xBF71C4, 20000);   // Max Possible Loadable Items

	// Maximum Allowed Item Class ID
	WriteMemoryDWORD(0x95F574, 20000); // originally 10000

	// Maximum Allowed NPC Class ID
	WriteMemoryDWORD(0x95F5A4, 1099000); // originally 1015000

	// Vista 64 / Windows 2008 Server (Incompatibility) [Fixes the Crash During the Loadage of L2Server]
	WriteInstruction(0x6432F6, 0x643307, 0, 0xE9);				// Forced Jump

	// Sell Bug Fix (Memory Cleanup)
	WriteMemoryBYTE(0x87A4EA, 0x44);

	// Allow Updating The Clan List for YourSelf !
	NOPMemory(0x767BD1, 8);

	// Disable Logs Sending to NCSOFT (thx fyyre for idea)
	WriteMemoryBYTE(0x5B7CC0, 0xC3);

	// CTLThread::Pipe Issue
	WriteInstruction(0x61FC2A, 0x61FC59, 0, 0xE9);

	// Disables Kicking After Receiveing UserSocket::DummyPacket
	WriteMemoryBYTE(0x85E172, 0x00);

	// DeadLock
	WriteMemoryDWORD(0x623E7B, GlobalVars::GVs()->pGeneral->nDeadlock);

		if ( GlobalVars::GVs()->pGeneral->Penaltyfix )
	{
	 for(int i = 0; i < 16; i++)
		{
			int val = CIniFile::GetIntValue("Penalty", (char*)PenaltyNames[i],"L2Extend.ini");
			WriteMemoryBYTES(penaltyTable[i], &val, sizeof(val));
		}
	}

#ifdef _CT2_2_
	// Thingy that lets us login with ct2.2
	INT32 writeTo = (INT32)LoadLibrary("AmpeDx64.dll") + 0x4463;
	WriteMemoryBYTE(writeTo, 0x1C);
#endif

}

void HEXHooks::PostLoadHooks()
{
	CLog::Add(CLog::blue, "Performing Post Load Hooks...");
	CLog::Add(CLog::blue, "Penalty Fix");


	/* Fixing Learning Bug (Patching Amped) */
	WriteInstruction(0x866076, (INT32)0x4F0830, 0, 0xE8);

	// Extending Classes
	CSocket::ExtendClass();
}

void HEXHooks::SetMaxLoadableItems(int maxItemsInWorld)
{
	if (maxItemsInWorld > 1048575)
	{
		MessageBoxA(NULL, "MaxItems in config is greater than 1048575.", "PP Extender", 0);
		ExitProcess(1);
	}

	// total max is - 1048575
	WriteMemoryDWORD(0xBF71C0, maxItemsInWorld);

	// .text:000000000046E319                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x46E31A, maxItemsInWorld);

	// .text:000000000047467C                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x47467D, maxItemsInWorld);

	// .text:000000000054C854                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x54C855, maxItemsInWorld);

	// .text:000000000054E774                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x54E775, maxItemsInWorld);

	// .text:000000000055220A                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x55220B, maxItemsInWorld);

	// .text:000000000055485F                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x554860, maxItemsInWorld);

	// .text:00000000005548FD                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x5548FE, maxItemsInWorld);

	// .text:0000000000554C7E                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x554C7F, maxItemsInWorld);

	// .text:0000000000554D1C                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x554D1D, maxItemsInWorld);

	// .text:0000000000555071                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x555072, maxItemsInWorld);

	// .text:000000000055C04E                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x55C04F, maxItemsInWorld);

	// .text:00000000005607A4                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x5607A5, maxItemsInWorld);

	// .text:0000000000581971                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x581972, maxItemsInWorld);

	// .text:0000000000612DB7                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x612DB8, maxItemsInWorld);

	// .text:000000000061FBD9                 cmp     edi, 0DBBA0h
	WriteMemoryDWORD(0x61FBDB, maxItemsInWorld);

	// .text:000000000061FC18                 imul    edx, 0DBBA0h
	WriteMemoryDWORD(0x61FC1A, maxItemsInWorld);

	// .text:000000000062ACE5                 cmp     ecx, 0DBBA0h
	WriteMemoryDWORD(0x62ACE7, maxItemsInWorld);

	// .text:000000000062D317                 cmp     r9d, 0DBBA0h
	WriteMemoryDWORD(0x62D31A, maxItemsInWorld);

	// .text:000000000062D59C                 cmp     ebp, 0DBBA0h
	WriteMemoryDWORD(0x62D59E, maxItemsInWorld);

	// .text:000000000062E009                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x62E00A, maxItemsInWorld);

	// .text:000000000067F954                 cmp     [rsp+0F8h+var_88], 0DBBA0h
	WriteMemoryDWORD(0x67F958, maxItemsInWorld);

	// .text:0000000000752D83                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x752D84, maxItemsInWorld);

	// .text:0000000000752F94                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x752F95, maxItemsInWorld);

	// .text:000000000078B1EF                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x78B1F0, maxItemsInWorld);

	// .text:000000000078C1BE                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x78C1BF, maxItemsInWorld);

	// .text:00000000007CDA83                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x7CDA84, maxItemsInWorld);

	// .text:00000000007F02A5                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x7F02A6, maxItemsInWorld);

	// .text:00000000007F9D19                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x7F9D1A, maxItemsInWorld);

	// .text:00000000007FB03A                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x7FB03B, maxItemsInWorld);

	// .text:000000000080CA98                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x80CA99, maxItemsInWorld);

	// .text:00000000008411D0                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8411D1, maxItemsInWorld);

	// .text:0000000000841B99                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x841B9A, maxItemsInWorld);

	// .text:000000000086C9D7                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x86C9D8, maxItemsInWorld);

	// .text:000000000086CF3E                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x86CF3F, maxItemsInWorld);

	// .text:00000000008702FE                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8702FF, maxItemsInWorld);

	// .text:00000000008721F9                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8721FA, maxItemsInWorld);

	// .text:0000000000879610                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x879611, maxItemsInWorld);

	// .text:0000000000879DA2                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x879DA3, maxItemsInWorld);

	// .text:00000000008A188F                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8A1890, maxItemsInWorld);

	// .text:00000000008A219F                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8A21A0, maxItemsInWorld);

	// .text:00000000008B1C60                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B1C61, maxItemsInWorld);

	// .text:00000000008B249E                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B249F, maxItemsInWorld);

	// .text:00000000008B2CCB                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B2CCC, maxItemsInWorld);

	// .text:00000000008B374F                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B3750, maxItemsInWorld);

	// .text:00000000008B3F7B                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B3F7C, maxItemsInWorld);

	// .text:00000000008B47B2                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B47B3, maxItemsInWorld);

	// .text:00000000008B4D1D                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B4D1E, maxItemsInWorld);

	// .text:00000000008B55EB                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B55EC, maxItemsInWorld);

	// .text:00000000008B63C0                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B63C1, maxItemsInWorld);

	// .text:00000000008B6CCB                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8B6CCC, maxItemsInWorld);

	// .text:00000000008C05C5                 cmp     eax, 0DBBA0h
	WriteMemoryDWORD(0x8C05C6, maxItemsInWorld);

	// .text:0000000000956B5D                 lea     r11, [rbx-0DBBA0h]
	//WriteMemoryDWORD(0x, maxItemsInWorld);

	// .text:0000000000956B64                 mov     eax, 0DBBA0h
	WriteMemoryDWORD(0x956B65, maxItemsInWorld);

	// .text:0000000000956BC6                 mov     r8d, 0DBBA0h    ; size_t
	WriteMemoryDWORD(0x956BC8, maxItemsInWorld);

	// .text:000000000061FC30                 lea     rdx, [rbx+rsi*4+0DBBA8h]
	WriteMemoryDWORD(0x61FC34, maxItemsInWorld);

	// .text:000000000062AE08                 mov     [rsi+rdi*4+0DBBA8h], eax
	WriteMemoryDWORD(0x62AE0B, maxItemsInWorld);

	// .text:0000000000956B41                 mov     [rbx-0DBBA8h], esi
	//WriteMemoryDWORD(0x, maxItemsInWorld);
}