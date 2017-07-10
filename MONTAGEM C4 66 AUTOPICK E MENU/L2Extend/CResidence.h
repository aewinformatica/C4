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

#include "CResidenceSharedData.h"

#pragma once

class CResidence
{
public:
	/* 0x00 */ int unk_00[6];
	/* 0x18 */ CResidenceSharedData *pSD;
	/* 001C */ int _unk1C;
	/* 0020 */ int _unk20;
	/* 0024 */ int nSiegeTimePeriod;
	/* 0028 */ int nSiegeTimeToStart;
	/* 002C */ int nSiegeElapsedTime;
	/* 0030 */ int nPledgeObjectID;

	
public:
	CResidence* GetResidence(PWCHAR wsName);
	CPledge*	GetResidenceOwnerPledge();
	void SetPledge(CPledge *pPledge);
};
extern "C"
{
	CResidence* GetResidence(int id);
};
