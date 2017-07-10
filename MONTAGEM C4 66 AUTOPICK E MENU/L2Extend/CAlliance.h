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
#include "CObject.h"
#include "CAllianceSharedData.h"

class CObject;
class CMemberData;
typedef std::map<int, CMemberData*> AMemberData;

class CAlliance : public CObject
{
public:
	/* 0030 */ CRITICAL_SECTION *cs_Alliance;
	/* 0038 */ CAllianceSharedData *pSD;
	/* 0040 */ AMemberData m_AMemberData;
	/* 0058 */ int nPledgeObjectID;

	static CSPointer<CAlliance> GetAllianceSP(int nItemIndex)
	{
		typedef void (*FGetAlliance)(__int64*, CSPointer<CAlliance>*, int);
		CSPointer<CAlliance> tmp;
		FGetAlliance(0x4207E0)((__int64*)0x00C01C20, &tmp, nItemIndex);
		return tmp;
	}

	void AddMemberPledge(CPledge *pPledge);
};