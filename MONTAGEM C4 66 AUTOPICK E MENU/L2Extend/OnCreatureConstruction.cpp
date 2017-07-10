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
#include "CCreature.h"
#include "CObjectEx.h"
#include <algorithm>

CCreature *CGameEvents::OnCreatureConstruction(CCreature *pCreature)
{
	// call the original constructor first
	typedef CCreature* (*FCreatureConstructor)(CCreature*);
	FCreatureConstructor(0x4D6030)(pCreature);

	// additional initialization
	pCreature->SD->pObjectEx = new CObjectEx(pCreature);
	std::fill_n(pCreature->SD->nExtEquipment, (int)CSharedData::EXT_SLOTS, -1);

	return pCreature;
}

CCreature *CGameEvents::OnCreatureConstructionOther(CCreature *pCreature, const CCreature *pOther)
{
	// call the original constructor first
	typedef CCreature* (*FCreatureCopyConstructor)(CCreature*, const CCreature*);
	FCreatureCopyConstructor(0x4D74C0)(pCreature, pOther);

	// additional initialization
	pCreature->SD->pObjectEx = new CObjectEx(pCreature);
	std::fill_n(pCreature->SD->nExtEquipment, (int)CSharedData::EXT_SLOTS, -1);

	return pCreature;
}