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
#include <map>
#include <vector>
#include "CObject.h"
#include "CDoorSharedData.h"

class CObject;

// size: Original 0x200?
class CDoor : public CObject
{
	public:
		/* 0030 */ INT64 _dw0030;
		/* 0038 */ CRITICAL_SECTION *cs_Door;
		/* 0040 */ int	 _dw0040[38];
		/* 00D8 */ WCHAR wName[56]; // maybe less 56 but not more
		/* 0148 */ int	dw0148;
		/* 014C */ int	dw014C;
		/* 0150 */ int	dw0150[44];

	bool IsValidDoor();
	bool Open(bool bByParent);
	bool Close(bool bByParent);
};

typedef std::map<int,CDoor*> DoorData;

class CDoorDB : public L2ServerFunctions
{
	public:
	/* 0030 */ CRITICAL_SECTION *cs_DoorDB;
	/* 0038 */ CDoorSharedData *pSD;
	/* 0040 */ DoorData m_Door;

	static void SetDoorOpen(bool bOpen);
	static CDoor* GetDoor(WCHAR* name);
	static CDoor* GetDoor(int nID);
};
