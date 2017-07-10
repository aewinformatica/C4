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
//#include "CCursedWeapons.h"
//#include "CSoulSystem.h"

INT32 nOnCreatureDie = 0;
bool CGameEvents::OnCreatureDie(CCreature *pCreature, CCreature *pEnemy)
{
	L2SERVER_SHARED_GUARD(nOnCreatureDie);
	
	TLS_TRACE_BEGIN;

	// Functions
	typedef bool (__fastcall *_CD) (CCreature *, CCreature *);
	_CD xCreatureDie = (_CD)0x00511D70L;

	pCreature->SD->pObjectEx->pGeneralInfo->pLastKiller = pEnemy;

	// Calling Original Function
	bool bReturn = xCreatureDie(pCreature, pEnemy);

	if (bReturn && pCreature->IsValidCreature())
	{
		// Cursed Weapon System (Creature Die Procedure)
		//CCursedWeapons::OnCreatureDie(pEnemy, pCreature);

		/*if (pEnemy->IsValidUser())
			CSoulSystem::ModifySoulsOnCriticalHitOrKill((User*)pEnemy, 1, 0);*/
	}
	
	TLS_TRACE_END;

	return bReturn;
}