#include "MemoryTools.h"

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

void WriteInstruction64(INT64 Address, INT64 NewAddress, INT32 NopZone, INT8 Instruction)
{
	DWORD OLDPROTECT;
	SIZE_T BytesWritten;
	CHAR *MyAddress = (CHAR *)Address;
	INT64 JAddress = NewAddress - (Address+5);
	
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

void WriteMemoryBYTES(INT32 Address, VOID *bytes, INT32 len)
{
	DWORD OLDPROTECT;
	SIZE_T BW;
	HANDLE Server = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE, false, GetCurrentProcessId());
	if ( Server )
	{
		VirtualProtectEx(Server, (LPVOID)Address, len, PAGE_WRITECOPY, &OLDPROTECT);
		WriteProcessMemory(Server,(LPVOID)Address,bytes,len,&BW);
		VirtualProtectEx(Server, (LPVOID)Address, len, OLDPROTECT, &OLDPROTECT);
	}
	CloseHandle(Server);
}

void WriteMemoryBYTES(INT32 Address, INT32 len, ...)
{
	char *memory = new char[len];
	va_list vl;
	va_start(vl, len);

	for (int i = 0; i < len; i++)
		memory[i] = va_arg(vl, char);

	va_end(vl);
	WriteMemoryBYTES(Address, memory, len);

	delete[] memory;
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

	WriteMemoryDWORD((INT32)nAddressToPatch, (INT32)nRelativeAddress);

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

