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

#include "CItem.h"
#include "CLog.h"

bool CItem::IsValidSD()
{
    if(this)
	{
        __try
		{ 
			if(this->SD && this->SD > (CSharedItemData *)0xC019FF) { double A = this->SD->x; return true; }
		}
        __except(EXCEPTION_EXECUTE_HANDLER)
		{ 
			/* Invalid pointer */
			/* Preventing Crash ;) */
		}
    }

	return false;
}

bool CItem::IsValidItem()
{
	if (IsValidObject(VMTCItem)
		|| IsValidObject(VMTCWeapon)
		|| IsValidObject(VMTCEtcItem)
		|| IsValidObject(VMTCAsset)
		|| IsValidObject(VMTCArmor)
		|| IsValidObject(VMTCAccessary)
		|| IsValidObject(VMTCQuestItem))
	{
		if (IsValidSD())
		{
			return true;
		}
	}

	return false;
}

bool CItem::IsValidCWeapon()
{
	if (IsValidObject(VMTCWeapon) && IsValidSD())
		return true;

	return false;
}

bool CItem::IsValidCEtcWeapon()
{
	if (IsValidObject(VMTCEtcItem) && IsValidSD())
		return true;

	return false;
}

bool CItem::IsValidCAsset()
{
	if (IsValidObject(VMTCAsset) && IsValidSD())
		return true;

	return false;
}

bool CItem::IsValidCArmor()
{
	if (IsValidObject(VMTCArmor) && IsValidSD())
		return true;

	return false;
}

bool CItem::IsValidCAccessary()
{
	if (IsValidObject(VMTCAccessary) && IsValidSD())
		return true;

	return false;
}

bool CItem::IsValidCQuestItem()
{
	if (IsValidObject(VMTCQuestItem) && IsValidSD())
		return true;

	return false;
}

bool CItem::IsHerbItem()
{
	if (
			this->nObjectType >= 8154 && this->nObjectType <= 8157 || 
			this->nObjectType >= 8600 && this->nObjectType <= 8614
		)
	{ return true; }
	
	return false;
}

void CItem::CItemConstructor(CSharedItemData *itemSharedData)
{
	__try
	{
		if (itemSharedData->exInfo == NULL)
		{
			itemSharedData->exInfo = new ItemExInfo();

			itemSharedData->exInfo->augmentationId = 0;
			itemSharedData->exInfo->mana = -1;
			itemSharedData->exInfo->nAtkAttrElement = 0;
			itemSharedData->exInfo->nAtkAttrValue = 0;
			itemSharedData->exInfo->nDefAttrFire = 0;
			itemSharedData->exInfo->nDefAttrWater = 0;
			itemSharedData->exInfo->nDefAttrWind = 0;
			itemSharedData->exInfo->nDefAttrEarth = 0;
			itemSharedData->exInfo->nDefAttrHoly = 0;
			itemSharedData->exInfo->nDefAttrUnholy = 0;
		}
		else
		{
			CLog::Add(CLog::red, "[%s][%d] Item already contains instance of exInfo", __FILE__, __LINE__);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CLog::Add(CLog::red, "[%s][%d] Exception occured !", __FILE__, __LINE__);
	}
}

void CItem::CItemDestructor(CSharedItemData *itemSharedData)
{
	__try
	{
		if (itemSharedData->exInfo != NULL)
		{
			delete itemSharedData->exInfo;
		}
		else
		{
			CLog::Add(CLog::red, "[%s][%d] Item doesn't contain exInfo", __FILE__, __LINE__);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CLog::Add(CLog::red, "[%s][%d] Exception occured !", __FILE__, __LINE__);
	}
}
