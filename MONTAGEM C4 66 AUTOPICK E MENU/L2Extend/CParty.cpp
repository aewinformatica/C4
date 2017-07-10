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

#include "CParty.h"
#include "User.h"


void CParty::WithDraw(User *pUser)
{
	typedef void (__thiscall *_WITHDRAW) (CParty *, User *);
	_WITHDRAW xWithdraw = (_WITHDRAW)0x0071FFF0L;
	xWithdraw(this, pUser);
}

int CParty::GetPartyRoutingType()
{
	typedef INT32 (__thiscall *_GPRT) (CParty *);
	_GPRT xGPRT = (_GPRT)0x00716800L;
	return xGPRT(this);
}

bool CParty::IsValidParty()
{
	if(this > (CParty*)0xC019FF)
		if(*(INT64*)this == 0xA40418)
			return true;
	return false;
}

//WAGNER 2014 AUTOPICK
void CParty::DistributeAdena(int nAmount, int nTraceChar, int nItemDBID, CItem* pItem) 
{
	typedef void (__thiscall*_TPRI)(CParty*, int, int, int, CItem*);
	_TPRI _PRI = (_TPRI)0x71E450;
	_PRI(this, nAmount, nTraceChar, nItemDBID, pItem);
}
//WAGNER 2014 AUTOPICK
void CParty::RouteItem(CItem *pItem, User *pPicker) 
{
	typedef void (__thiscall*_TPRI)(CParty*, CItem*, User*);
	_TPRI _PRI = (_TPRI)0x71A5F0;
	_PRI(this, pItem, pPicker);
}