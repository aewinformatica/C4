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

#include "Global.h"

class CObject;
class CItem;
class CCreature;
class User;

/*
	A NOTE ON OBJECT TYPE CONVERSIONS
	=================================

	MemoryObject only has a few, but there are plenty of IsType and AsType
	functions in CObject and further. IsType functions are mostly redundant,
	since their AsType conterparts return null if the object is not of the
	desired type. Thus it is safe (and recommended) to use AsType.

	CastType functions behave differently in different classes.
	The default implementations in MemoryObject cause access violation by
	assigning *(char*)0 = 1. Therefore it's always necessary to check IsType
	before calling CastType. Although some classes change their behaviour to
	that of AsType, you still have to check IsType.
*/

class MemoryObject
{
protected:
/* 0008 */  int	nRefCount;
/* 000C */  int	nIdentity; 
/* 0010 */  int	nInTimer;
/* 0014 */  int	nDeleteCount;


public:
/* 0000 */  virtual void          Release(const char* file, int line, int nWorkType, bool flag) = 0;
/* 0008 */  virtual MemoryObject* AddRef(const char* file, int line, int nWorkType) = 0;
/* 0010 */  virtual bool        _vfunc010() = 0;
/* 0018 */  virtual             ~MemoryObject() {}

/* 0020 */  virtual bool        IsObject() = 0;
/* 0028 */  virtual bool        IsUser() = 0;
/* 0030 */  virtual bool        IsItem() = 0;
/* 0038 */  virtual bool        IsCreature() = 0;

/* 0040 */  virtual CObject*    AsObject() = 0;
/* 0048 */  virtual CItem*      CastItem() = 0;
/* 0050 */  virtual CCreature*  CastCreature() = 0;
/* 0058 */  virtual User*       CastUser() = 0;

/* 0060 */  virtual void        ReleaseError() = 0;
/* 0068 */  virtual int         RefCount() = 0;
/* 0070 */  virtual void        ReportOrt(const char* file, int line, int nWorkType) = 0;

public:

	CCreature*  AsCreature()		{ return this->IsCreature() ? (CCreature*)this : 0; }
	CItem*      AsItem()			{ return this->IsItem() ? (CItem*)this : 0; }
	User*       AsUser()			{ return this->IsUser() ? (User*)this : 0; }
	INT32		TimerStat()			{ return this->nInTimer;}

	enum ORT_TABLE
	{
		ORT_ANONYMOUS,
		ORT_CREATE_DELETE,
		ORT_TIMER,
		ORT_IO_RETAIN,
		ORT_BUFFER_RETAIN,
		ORT_IOCP_MESSAGE_RETAIN,
		ORT_SIGHT_MESSAGE,
		ORT_OBJECT_MAP,
		ORT_OBJECT_NAME_MAP,
		ORT_OBJECT_INDEX,
		ORT_OBJECT_STORAGE,
		ORT_FIND_OBJECT,
		ORT_USER_DB,
		ORT_TL_MAP,
		ORT_SHARED_CONTAINER,
		ORT_SMART_ID,
		ORT_WORLD_COLLISION,
		ORT_SERIALIZED_WORLD_THREAD,
		ORT_NEIGHBOR_LIST,
		ORT_GET_INVENTORY,
		ORT_TEMP_USE,
		ORT_CACHED,
		ORT_WAREHOUSE_GET_WAREHOUSE,
		ORT_USER_LOAD,
		ORT_ACCOUNT_ADD_MAP,
		ORT_FUNCTION_LOCAL,
		ORT_FUNCTION_CHAIN,
		ORT_EVENT_RETAIN,
		ORT_INVENTORY_CHANGE_MAP,
		WORK_ID_ITEM_TOCACHE_DESTROY_ITEM
	};
};
