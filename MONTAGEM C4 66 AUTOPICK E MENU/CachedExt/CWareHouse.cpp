#include "CWareHouse.h"

__declspec(naked) void CWareHouse::WriteLock()
{
	__asm
	{
		mov		eax, 4B1830h
		jmp		eax
	}
}

__declspec(naked) void CWareHouse::WriteUnlock()
{
	__asm
	{
		mov		eax, 4B18E0h
		jmp		eax
	}
}

__declspec(naked) void CWareHouse::SaveUnsavedItems()
{
	__asm
	{
		mov		eax, 4B9A10h
		jmp		eax
	}
}

__declspec(naked) CItemSP CWareHouse::GetItem(int nItemID)
{
	__asm
	{
		mov		eax, 4BC120h
		jmp		eax
	}
}
