#include "MemoryObject.h"

__declspec(naked) void MemoryObject::MemoryObjectConstructor()
{
	__asm
	{
		mov		eax, 450A80h
		jmp		eax
	}
}