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

#include "CGameEvents.h"
#include "CItem.h"
#include "CParty.h"

INT32 nGetPartyRoutingType = 0;
INT32 CGameEvents::GetPartyRoutingType(CParty *pParty, CItem *pItem)
{
	L2SERVER_SHARED_GUARD(nGetPartyRoutingType);
	TLS_TRACE_BEGIN;

	INT32 nPartyRoutingType = pParty->GetPartyRoutingType();

	// You can set it to Zero, to do not route the items randomly !
	// nPartyRoutingType = 0;
	if (pItem->IsHerbItem())
		nPartyRoutingType = 0;

	TLS_TRACE_END;
	return nPartyRoutingType;
}