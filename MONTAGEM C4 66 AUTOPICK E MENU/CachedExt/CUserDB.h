#pragma once
#include "CUser.h"
#include "CObjectSP.h"

class CUserDB
{
public:
	static CUserDB* I();

	int GetUser(CObjectSP *unk, int nUserId, bool bLoadIfNotExist);
private:
	static CUserDB *CUserDBStatic;
};
