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

#pragma once
#pragma warning( disable : 4312 ) 
#pragma warning( disable : 4996 ) 
#pragma warning( disable : 4309 )
#pragma warning( disable : 4311 )

#include <windows.h>

#define ALIGN_QWORD(x) ((((x) + 7) >> 3) << 3)
#define ALIGN_OWORD(x) ((((x) + 15) >> 4) << 4)

#define ASM_CALL 0xE8
#define ASM_JUMP 0xE9

void WriteInstruction(INT32 Address, INT32 NewAddress, INT32 NopZone, INT8 Instruction);
void WriteInstructionCALL(INT64 start, INT64 end, void* target);
void WriteInstructionJUMP(INT64 start, INT64 end, void* target);

#ifdef __cplusplus

// Doing this properly, so that only function pointers are allowed as
// parameters, would require variadic templates, or a lot of overloads.
// Since variadic templates are not available in VC2005, and too many
// overloads suck, this note must suffice.
//
// Also note that you can't obtain the address of a particular virtual
// function override this way - the expression &Class::vfunc will only
// give you the address of a thunk function that performs a regular
// virtual function call (through vftable).

template <typename FuncT>
inline INT64 FunctionAddress(FuncT* target)
{
	return static_cast<INT64>(target);
}

template <typename ClassT, typename FuncT>
inline INT64 FunctionAddress(FuncT ClassT::*target)
{
	return *reinterpret_cast<INT64*>(&target); // dirty, but works
}

// I could just overload WriteInstructionCALL, but I think it's better
// to explicitly state you really want a non-static member function to
// be called. Hence the 'me' suffix.

template <typename ClassT, typename FuncT>
inline void WriteInstructionCALLme(INT64 start, INT64 end, FuncT ClassT::*target)
{
	WriteInstructionCALL(start, end, *reinterpret_cast<void**>(&target));
}

#endif // __cplusplus

void NOPMemory(INT32 Address, INT32 len);
void NULLMemory(INT32 Address, INT32 len);

void WriteMemoryBYTES(uintptr_t addr, const void* data, size_t len);
void WriteMemoryBYTES(uintptr_t addr, const char* text);
void WriteMemoryBYTES(uintptr_t addr, size_t len, ...);
void WriteMemoryQWORD(INT32 Address, INT64 value);
void WriteMemoryFWORD(INT32 Address, INT64 value);
void WriteMemoryDWORD(INT32 Address, INT32 value);
void WriteMemoryWORD(INT32 Address, INT16 value);
void WriteMemoryBYTE(INT32 Address, INT8 value);

INT32 WriteDirectJMP(INT32 address, INT32 newFunc);

void EnlargeMemoryDWORD(INT32 Address, INT32 value);
void EnlargeMemoryWORD(INT32 Address, INT16 value);

void ReadMemoryBYTES(INT32 Address, VOID *bytes, INT32 len);
void ReadMemoryQWORD(INT32 Address, INT64 *Value);
void ReadMemoryDWORD(INT32 Address, INT32 *Value);
void ReadMemoryWORD(INT32 Address, INT16 *Value);
void ReadMemoryBYTE(INT32 Address, INT8 *Value);
INT32 ReadJumpAddress(INT32 address);

// Process Tools
INT64 GetModuleAddress(CHAR *pModule);

// Array Tools
UINT64 WriteRelativeAddress(INT64 nOrgAddress, INT64 nWriteFrom, VOID *pArray, INT64 nOffsetIndex);

void DisableFunction(INT64 addr, const char* func, int argc, const char* file, int line);
