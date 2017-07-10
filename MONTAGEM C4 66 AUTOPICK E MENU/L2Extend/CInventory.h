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

#include <windows.h>
#include "CItem.h"

class CCreature;
class CPet;
class User;
class CSharedRWLock;

struct RWLock
{
	/* 0000 */  CRITICAL_SECTION cs;
	/* 0028 */  HANDLE      hSemaphore;
	/* 0030 */  INT32       _unk0030;
	/* 0034 */  INT32       _pad0034;
};

enum InventoryUpdateType
{
	INVENTORY_ADD = 1,
	INVENTORY_MODIFY = 2,
	INVENTORY_REMOVE = 3,
};

class CInventory
{
public:

	bool CheckAddable(int nClassId, int  nAmount); //WAGNER 2014 AUTOPICK
	CItem* GetFirstItemByClassID(int nItemID);//WAGNER 2014 AUTOPICK

	/* 0000 */  int         nCreatureIndex; // == pCreature->SD->dw0028
	/* 0004 */  int        _unk0004;
	/* 0008 */  CSharedRWLock* pSharedRWLock;
	/* 0010 */  int         nCurrentWeight;
	/* 0014 */  int         _unk0014;
	/* 0018 */  INT64       _xstd;
	/* 0020 */  void*       _p_xstd;
	/* 0028 */  INT64       _unk0028;
	/* 0030 */  RWLock      rwlock;

	bool CheckAddable(int index);

	CItem* GetFirstItemByID(int nItemID);
	CItem* GetNextItemByClassID(int ItemClassID);
	CItem* GetItemByIndex(int nItemIndex);
	void SetInventoryChanged(CItem *pItem, int inventoryUpdateType);
	bool CreateOrAddItem(int nItemDBId, int nItemClassId, int nAmount);

	int GetAdenaAmount();
	int GetAdenaDBID();

	void WriteLock(const wchar_t* file, int line);
	void WriteUnlock();

	void Push(int nIndex);
	bool Pop(int itemIndex, bool flag);
	User *GetUser();
	CPet *GetPet();
	CCreature *GetOwner(void);
	CObject* GetFirstItemByClassIDEnchanted(int nClassID, int nEnchanted);
};
