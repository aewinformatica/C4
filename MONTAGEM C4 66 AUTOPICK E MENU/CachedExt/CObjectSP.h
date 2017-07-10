#pragma once

#include "CUser.h"
#include "CItem.h"

class CObjectSP
{
public:
	void* pObject;
	int ObjectType;

	void Release();
	CUser* GetSafeUser();
	CWareHouse* GetSafeWareHouse();
	static CItem* __thiscall ObjItem(CUser* pUserSP, CObjectSP* ItemSP, int num = 0, int num2 = 1);
};
