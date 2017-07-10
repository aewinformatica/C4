#include "Global.h"

CUserDB *CUserDB::CUserDBStatic;

CUserDB* CUserDB::I()
{
	if (CUserDBStatic == NULL)
	{
		CUserDBStatic = (CUserDB*) 0x1E95A58;
	}

	return CUserDBStatic;
}


__declspec(naked) int CUserDB::GetUser(CObjectSP *unk, int nUserId, bool bLoadIfNotExist)
{
	__asm
	{
		mov eax, 4AFCF0h
		jmp	eax
	}
}
