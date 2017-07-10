#include "CObjectSP.h"

char *error = __FILE__;
__declspec(naked) void CObjectSP::Release()
{
	__asm
	{
		push    esi
		mov     esi, ecx
		mov     ecx, [esi]
		test    ecx, ecx
		jz		isempty
		mov     edx, [esi+4]
		mov     eax, [ecx]
		mov     eax, [eax]
		push    0
		push    edx
		push    94h
		push	error
		call	eax
		mov     dword ptr [esi], 0
isempty:
		pop		esi
		retn
	}
}

__declspec(naked) CUser* CObjectSP::GetSafeUser()
{
	__asm
	{
			mov		eax, 4064F0h
			jmp		eax
	}
}

__declspec(naked) CWareHouse* CObjectSP::GetSafeWareHouse()
{
	__asm
	{
			mov		eax, 4064F0h
			jmp		eax
	}
}

__declspec(naked) CItem* CObjectSP::ObjItem(CUser*, CObjectSP*, int, int)
{
	__asm
	{
		mov		eax, 4A9D30h
		jmp		eax
	}
}
