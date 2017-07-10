#pragma once

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

#pragma warning( disable : 4312 ) 
#pragma warning( disable : 4996 ) 
#pragma warning( disable : 4309 )
#pragma warning( disable : 4311 )

#include "windows.h"
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#define ASM_CALL 0xE8
#define ASM_JUMP 0xE9

void WriteInstruction(INT32 Address, INT32 NewAddress, INT32 NopZone, INT8 Instruction);
void WriteInstruction64(INT64 Address, INT64 NewAddress, INT32 NopZone, INT8 Instruction);
void NOPMemory(INT32 Address, INT32 len);
void NULLMemory(INT32 Address, INT32 len);

void WriteMemoryBYTES(INT32 Address, VOID *bytes, INT32 len);
void WriteMemoryBYTES(INT32 Address, INT32 len, ...);
void WriteMemoryQWORD(INT32 Address, INT64 value);
void WriteMemoryFWORD(INT32 Address, INT64 value);
void WriteMemoryDWORD(INT32 Address, INT32 value);
void WriteMemoryWORD(INT32 Address, INT16 value);
void WriteMemoryBYTE(INT32 Address, INT8 value);

void ReadMemoryBYTES(INT32 Address, VOID *bytes, INT32 len);
void ReadMemoryQWORD(INT32 Address, INT64 *Value);
void ReadMemoryDWORD(INT32 Address, INT32 *Value);
void ReadMemoryWORD(INT32 Address, INT16 *Value);
void ReadMemoryBYTE(INT32 Address, INT8 *Value);

// Array Tools
UINT64 WriteRelativeAddress(INT64 nOrgAddress, INT64 nWriteFrom, VOID *pArray, INT64 nOffsetIndex);

inline void bitsetn(INT32 & i, unsigned bitposition) { i|= 1<<(bitposition); }
inline INT32 readbitn(INT32 i, unsigned bitposition) { return (i>>(bitposition))&1; }
