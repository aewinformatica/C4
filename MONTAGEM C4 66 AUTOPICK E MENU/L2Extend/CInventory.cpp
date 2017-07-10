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

#include "CInventory.h"
#include "User.h"
#include "CPet.h"
#include "L2ServerFunctions.h"

//WAGNER 2014 AUTOPICK
bool CInventory::CheckAddable(int nClassId, int  nAmount)
{
	typedef bool (__thiscall*_TICA)(CInventory*, int, int);
	_TICA _ICA = (_TICA)0x618830;
	return _ICA(this, nClassId, nAmount);
}
//WAGNER 2014 AUTOPICK
CItem * CInventory::GetFirstItemByClassID(int nItemID)
{
	typedef CItem* (*t)(CInventory*,int);
	t f = (t) 0x00613A10;
	return f(this, nItemID);
}

bool CInventory::CheckAddable(int index) 
{
        typedef bool (*t)(CInventory*, int);
        t f = (t)0x00617520;
        return f(this, index);
};

CItem * CInventory::GetFirstItemByID(int nItemID)
{
	typedef CItem* (*t)(CInventory*,int);
	t f = (t) 0x00613A10;
	return f(this, nItemID);
}

CItem* CInventory::GetNextItemByClassID(int ItemClassID)
{
        typedef CItem* (*t)(CInventory*, int);
        t f = (t)0x00613E50;
        return f(this, ItemClassID);
};

CItem* CInventory::GetItemByIndex(int nItemIndex)
{
	typedef CItem* (*t)(CInventory*, int);
	t f = (t) 0x00612B40; //byIndex

	if(nItemIndex >= 0)
		return f(this, nItemIndex);
	else
		return NULL;
}

// 01-add, 02-modify, 03-remove
void CInventory::SetInventoryChanged(CItem *pItem, int inventoryUpdateType)
{
	typedef void (*t)(CInventory*, CItem*, int);
	t f = (t)0x61C0B0;
	f(this, pItem, inventoryUpdateType);
}

bool CInventory::CreateOrAddItem(int nItemDBId, int nItemClassId, int nAmount)
{
	typedef bool (*t)(CInventory*, int, int, int);
	t f = (t)0x61C6D0;
	return f(this, nItemDBId, nItemClassId, nAmount);
}

void CInventory::WriteLock(const wchar_t* file = NULL, int line = 0)
{
        typedef void (*t)(CInventory*, const wchar_t* , int );
        t f = (t)0x0442EF0;
        f(this, file, line);
};

void CInventory::WriteUnlock()
{
        typedef void (*t)(CInventory*);
        t f = (t)0x04438D0;
        f(this);
};

void CInventory::Push(int nIndex)
{
	typedef void (__thiscall * __PUSH)(CInventory *pInventory, int Index);
	__PUSH xPush = (__PUSH) 0x00615EF0L;
	xPush(this, nIndex);
}

bool CInventory::Pop(int itemIndex, bool flag)
{
	typedef bool (*t)(CInventory* pInventory, int itemIndex, bool flag);
	t f = (t)0x06166C0;
	return f(this, itemIndex, flag);
}

int CInventory::GetAdenaAmount()
{
	typedef int (*t)(CInventory*);
	t f = (t)0x6130F0;
	return f(this);
}

int CInventory::GetAdenaDBID()
{
	typedef int (*t)(CInventory*);
	t f = (t)0x613580;
	return f(this);
}

INT32 nGetUser = 0;
User *CInventory::GetUser()
{
	L2SERVER_SHARED_GUARD(nGetUser);
	TLS_TRACE_BEGIN;

	INT64 nUserPTR = (INT64)this;
	nUserPTR -= 0x5A0;
	User *pUser = (User *)nUserPTR;

	if ( pUser->IsValidUser() )
	{
		TLS_TRACE_END;
		return pUser;
	}

	TLS_TRACE_END;
	return NULL;
}

INT32 nGetPet = 0;
CPet *CInventory::GetPet()
{
	L2SERVER_SHARED_GUARD(nGetPet);
	TLS_TRACE_BEGIN;

	INT64 nPetPTR = (INT64)this;
	nPetPTR -= 0x5A0;
	CPet *pPet = (CPet *)nPetPTR;

	if ( pPet->IsValidPet() )
	{
		TLS_TRACE_END;
		return pPet;
	}

	TLS_TRACE_END;
	return NULL;
}

CCreature *CInventory::GetOwner(void)
{
	typedef CCreature* (*t)(CInventory*);
	t f = (t)0x615140;
	return f(this);	
}

CObject* CInventory::GetFirstItemByClassIDEnchanted(int nClassID, int nEnchanted)
{
	typedef CObject* (*t)(CInventory*, int nClassID, int nEnchanted);
	t f = (t)0x613A10;
	return f(this, nClassID, nEnchanted);	
}