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

#include "CDestroyItem.h"
#include "CItem.h"
#include "CPet.h"
#include "User.h"

void CDestroyItem::Initialize()
{
	//take code after CInventory_GetDBID function
	WriteInstruction(0x87012F, (INT32)&Code_87012F, 3, 0xE9);
};

//	insert this function to fix	the problem client disconnect
//	when player try to destroy item from pet's inventory
int nIsItemOnOtherCreature = 0;
bool CDestroyItem::IsItemOnOtherCreature(User* pUser, CItem *pItem)
{
	bool result = false;

	L2SERVER_SHARED_GUARD(nIsItemOnOtherCreature);
	TLS_TRACE_BEGIN;
	CPet *pPet;

	//is item on pet?
	if(pPet = pUser->GetPet())
	{
		if(pPet->GetInventory()->GetFirstItemByID(pItem->nObjectType))
		{
			result = true;
		}
	}
	//is item in inventory
	if(pUser->nObjectType == -1)
	{
		CLog::Add(CLog::red, "destructing wrong item(%d). userID[%d]", pItem->nSID, pUser->nSID);
		result = true;
	}

	TLS_TRACE_END;
	return result;
};
