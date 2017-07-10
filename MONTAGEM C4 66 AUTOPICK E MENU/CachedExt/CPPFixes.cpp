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

#include "CPPFixes.h"

void CPPFixes::Initialize()
{
	DeadlockLimit(6000000);
	AddItemDataFix();

	// Fix the Exit (Process Keeping Up) Bug
	WriteInstruction(0x422B5B, (INT32)ExitProcess, 0, 0xE8);
}

void CPPFixes::AddItemDataFix()
{
	// .text:00404CB0 CAddData::AddItemData
	//
	// Loading items with IDs beyond 9999 fails, because only 4 digits
	// are read. Luckily there's one more unused WCHAR beyond bufID...
	//
	// .text:00404E8C                 mov     [esp+1098h+bufID+8], ax
	// .fixd:00404E8C                 nop
	// .fixd:00404E8D                 mov     dword ptr [esp+1098h+bufID+8], eax
	WriteMemoryBYTE(0x404E8C, 0x90);
	// .text:00404F1D                 cmp     esi, 5
	// .fixd:0x404F1D                 cmp     esi, 6
	WriteMemoryBYTE(0x404F1F, 0x06);
}

void CPPFixes::DeadlockLimit(int limit)
{
	// deadlock limit
	WriteMemoryDWORD(0x441229, limit);
	// .text:0043D77F                 push    0EA60h
	WriteMemoryDWORD(0x43D780, limit);
	// .text:0043D8B0                 push    0EA60h
	WriteMemoryDWORD(0x43D8B1, limit);
}
