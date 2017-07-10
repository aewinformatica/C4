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

#include "MemoryTools.h"
#include "CLog.h"
#include <cstdlib> // strtoul
#include <map>

typedef std::pair<INT64, INT64> Int64Pair;

struct Int64PairLess
{
	bool operator()(Int64Pair a, Int64Pair b) const
	{
		if (a.first < b.first) return true;
		if (a.first > b.first) return false;
		return a.second < b.second;
	}
};

static INT64 ReportDisabledFunction(
	INT64 rcx, INT64 rdx, INT64 r8, INT64 r9,
	const char* file, int line,
	const char* func, int argc,
	INT64 funcAddr, INT64 retAddr)
{
	static std::map<Int64Pair, bool, Int64PairLess> reportedMap;
	bool& reported = reportedMap[std::make_pair(funcAddr, retAddr)];

	if (reported) return 0;
	reported = true;

	std::string args("  function addr=0x%lX");
	if (argc > 0) args.append("  rcx=0x%lX");
	if (argc > 1) args.append("  rdx=0x%lX");
	if (argc > 2) args.append("  r8=0x%lX");
	if (argc > 3) args.append("  r9=0x%lX");

	CLog::Add(CLog::red, "%s was called after being disabled!", func);
	CLog::Add(CLog::red, "  disabled from %s:%d", file, line);
	CLog::Add(CLog::red, args.c_str(), funcAddr, rcx, rdx, r8, r9);
	CLog::Add(CLog::red, "  return addr=0x%lX", retAddr);

	return 0;
}

/*
	DisableFunction writes code that calls ReportDisabledFunction, at
	the specified address. There must be at least 80 bytes available
	for patching. When the disabled function is called, a message will
	be written to CLog containing the function's name, address, up to
	4 parameters passed to it, return address, and location from where
	the function was disabled.
*/
void DisableFunction(INT64 addr, const char* func, int argc, const char* file, int line)
{
	WriteMemoryBYTES(addr+0x00, "48 83 EC 48");     //  sub     rsp, 48h
	WriteMemoryBYTES(addr+0x04, "48 B8");           //  mov     rax, imm64
	WriteMemoryQWORD(addr+0x06, (INT64)file);
	WriteMemoryBYTES(addr+0x0E, "48 89 44 24 20");  //  mov     [rsp+20h], rax
	WriteMemoryBYTES(addr+0x13, "C7 44 24 28");     //  mov     [rsp+28h], imm32
	WriteMemoryDWORD(addr+0x17, (INT32)line);
	WriteMemoryBYTES(addr+0x1B, "48 B8");           //  mov     rax, imm64
	WriteMemoryQWORD(addr+0x1D, (INT64)func);
	WriteMemoryBYTES(addr+0x25, "48 89 44 24 30");  //  mov     [rsp+30h], rax
	WriteMemoryBYTES(addr+0x2A, "C7 44 24 38");     //  mov     [rsp+38h], imm32
	WriteMemoryDWORD(addr+0x2E, (INT32)argc);
	WriteMemoryBYTES(addr+0x32, "48 8D 05");        //  lea     rax, [addr]
	WriteMemoryDWORD(addr+0x35, -0x39);
	WriteMemoryBYTES(addr+0x39, "48 89 44 24 40");  //  mov     [rsp+40h], rax

	WriteInstructionCALL(addr+0x3E, addr+0x43, ReportDisabledFunction);

	WriteMemoryBYTES(addr+0x43, "48 83 C4 48");     //  add     rsp, 48h
	WriteMemoryBYTES(addr+0x47, "C3");              //  ret
}

void WriteInstruction(INT32 Address, INT32 NewAddress, INT32 NopZone, INT8 Instruction)
{
	DWORD OLDPROTECT;
	SIZE_T BytesWritten;
	CHAR *MyAddress = (CHAR *)Address;
	INT32 JAddress = NewAddress - (Address+5);
	
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());

	if ( Server )
	{
		// Unlocking the current address space in order to create the new jump.
		VirtualProtectEx(Server, (VOID *)Address, 5+NopZone, PAGE_WRITECOPY, &OLDPROTECT);

		WriteProcessMemory(Server,MyAddress,(CHAR *)&Instruction,1,&BytesWritten);
		WriteProcessMemory(Server,MyAddress+1,(CHAR *)&JAddress,4,&BytesWritten);
													 // COPYING THE ADDRESS TO THE ADDRESS SPACE.
		NOPMemory((INT32)MyAddress+5, NopZone);	         // NOPING THE REST OF THE ZONE YOU WANTED PATCHED.
		VirtualProtectEx(Server, (VOID *)Address, 5+NopZone, OLDPROTECT, &OLDPROTECT);
	}

	CloseHandle(Server);
}

void WriteInstructionCALL(INT64 start, INT64 end, void* target)
{
	INT64 size = end - start;
	if (size >= 5)
		WriteInstruction((INT32)start, (INT32)target, (INT32)(size-5), 0xE8);
}

void WriteInstructionJUMP(INT64 start, INT64 end, void* target)
{
	INT64 size = end - start;
	if (size >= 5)
		WriteInstruction((INT32)start, (INT32)target, (INT32)(size-5), 0xE9);
}

void NOPMemory(INT32 Address, INT32 len)
{
	BYTE Byte = 0x90;
	DWORD OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		for ( int i = 0 ; i < len ; i++ )
		{
			INT32 ADDR = Address+i;
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, PAGE_WRITECOPY, &OLDPROTECT);
			WriteProcessMemory(Server,(LPVOID)ADDR,&Byte,1,&BW);
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, OLDPROTECT, &OLDPROTECT);
		}
	}
	CloseHandle(Server);
}

void NULLMemory(INT32 Address, INT32 len)
{
	DWORD OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		for ( int i = 0 ; i < len ; i++ )
		{
			INT32 ADDR = Address+i;
			CHAR Byte = 0x00;
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, PAGE_WRITECOPY, &OLDPROTECT);
			WriteProcessMemory(Server,(LPVOID)ADDR,&Byte,1,&BW);
			VirtualProtectEx(Server, (LPVOID)ADDR, 1, OLDPROTECT, &OLDPROTECT);
		}
	}
	CloseHandle(Server);
}

void WriteMemoryBYTES(uintptr_t addr, const void* data, size_t len)
{
	DWORD OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		VirtualProtectEx(Server, (LPVOID)addr, len, PAGE_WRITECOPY, &OLDPROTECT);
		WriteProcessMemory(Server,(LPVOID)addr, data, len, &BW);
		VirtualProtectEx(Server, (LPVOID)addr, len, OLDPROTECT, &OLDPROTECT);
	}
	CloseHandle(Server);
}

void WriteMemoryBYTES(uintptr_t addr, const char* text)
{
	std::basic_string<unsigned char> buf;
	char* end = 0;

	for (;; text = end)
	{
		unsigned long value = strtoul(text, &end, 16);
		if (text == end)
			break;
		buf.push_back((unsigned char)value);
	}

	if (buf.size() > 0)
	{
		WriteMemoryBYTES(addr, buf.c_str(), buf.size());
	}
}

void WriteMemoryBYTES(uintptr_t addr, size_t len, ...)
{
	if (len <= 0) return;

	BYTE* bytes = (BYTE*)alloca(len);
	va_list ap;
	va_start(ap, len);

	for (int i = 0; i < len; i++)
	{
		bytes[i] = va_arg(ap, BYTE);
	}
	va_end(ap);

	WriteMemoryBYTES(addr, bytes, len);
}

void WriteMemoryQWORD(INT32 Address, INT64 value)     { WriteMemoryBYTES(Address, &value, 8); }
void WriteMemoryFWORD(INT32 Address, INT64 value)     { WriteMemoryBYTES(Address, &value, 6); }
void WriteMemoryDWORD(INT32 Address, INT32 value)     { WriteMemoryBYTES(Address, &value, 4); }
void WriteMemoryWORD(INT32 Address, INT16 value)      { WriteMemoryBYTES(Address, &value, 2); }
void WriteMemoryBYTE(INT32 Address, INT8 value)       { WriteMemoryBYTES(Address, &value, 1); }

UINT64 WriteRelativeAddress(INT64 nOrgAddress, INT64 nWriteFrom, VOID *pArray, INT64 nOffsetIndex) 
{ 
	UINT64 nAddressToPatch  = nOrgAddress+nWriteFrom;
	UINT64 nRIPAddress      = nOrgAddress+nWriteFrom+4;
	UINT64 nPointerAddress  = (UINT64)pArray;
	UINT64 nRelativeAddress = ((nPointerAddress + nOffsetIndex) - nRIPAddress);

	//char MyBigBuffer[256];
	//sprintf(MyBigBuffer, "IDA Address : 0x%04X\nRIP Address : 0x%04X\nDB Address : 0x%04X\nRelative Address 0x%04X", nOrgAddress, nRIPAddress, nPointerAddress, nRelativeAddress);
	//MessageBox( NULL, MyBigBuffer, "", 0 );

	WriteMemoryDWORD((UINT32)nAddressToPatch, (UINT32)nRelativeAddress);

	return nRelativeAddress;
}

void ReadMemoryBYTES(INT32 Address, VOID *bytes, INT32 len)
{
	SIZE_T BR;
	HANDLE Client = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Client )
		ReadProcessMemory(Client,(LPVOID)Address,bytes,len,&BR);
	CloseHandle(Client);
}

void ReadMemoryQWORD(INT32 Address, INT64 *Value) {	ReadMemoryBYTES(Address, Value, 8); }
void ReadMemoryDWORD(INT32 Address, INT32 *Value) {	ReadMemoryBYTES(Address, Value, 4); }
void ReadMemoryWORD(INT32 Address, INT16 *Value)  {	ReadMemoryBYTES(Address, Value, 2); }
void ReadMemoryBYTE(INT32 Address, INT8 *Value)   {	ReadMemoryBYTES(Address, Value, 1); }

INT64 GetModuleAddress(CHAR *pModule)
{
	INT64 nAddress = (INT64)GetModuleHandle(pModule);
	return nAddress;
}

INT32 ReadRIPPointer(INT32 address, int instructionSize, int addrPosition)
{
	INT32 RIPPointer;
	INT32 result;
	INT8 instruction;

	ReadMemoryBYTE(address, &instruction);
	if (instruction == 0xE9)
	{
		ReadMemoryDWORD(address + addrPosition, &RIPPointer);
		result = RIPPointer + address + instructionSize;
	}
	else
	{
		result = address;
	}

	return result;
}

INT32 ReadJumpAddress(INT32 address)
{
	return ReadRIPPointer(address, 5, 1);
}

INT32 WriteDirectJMP(INT32 address, INT32 newFunc)
{
	LONG_PTR realNewFunc = ReadJumpAddress(newFunc);

	WriteInstruction(address, (INT32)realNewFunc, 0, 0xE9);
	return (INT32)realNewFunc;
}

void EnlargeMemoryDWORD(INT32 Address, INT32 value)
{
	INT32 old;
	ReadMemoryDWORD(Address, &old);
	WriteMemoryDWORD(Address, old + value);
}

void EnlargeMemoryWORD(INT32 Address, INT16 value)
{
	INT16 old;
	ReadMemoryWORD(Address, &old);
	WriteMemoryWORD(Address, old + value);
}