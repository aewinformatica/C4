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

#include "CSkillEffect_p_disarm.h"
#include "CObjectEx.h"
#include "CSkillMod.h"
#include "User.h"

INT32 nCSkillEffect_p_disarmCheckPumpCondition = 0;
bool CSkillEffect_p_disarm::CheckPumpCondition(CObject* pTarget)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_p_disarmCheckPumpCondition);
	TLS_TRACE_BEGIN;

	bool bResult = false;

	User *pUser = (User*)pTarget;

	if(pUser->IsValidUser())
	{
		if( !pUser->SD->pObjectEx->pSkillMods->p_block_equip_weapon )
		{
			bResult = true;
		}
	}

	TLS_TRACE_END;
	return bResult;
}

INT32 nCSkillEffect_p_disarmPump;
void CSkillEffect_p_disarm::Pump(CObject* pTarget, CSkillInfo* pSkillInfo)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_p_disarmPump);
	TLS_TRACE_BEGIN;

	//CLog::Add(CLog::blue, "i_disarm::Pump activated");
	User *user = (User*)pTarget;
	if(user->IsValidUser())
	{
		if(user->GetEquipedWeapon() != NULL)
		{
			CItem *weapon =(CItem*)L2ServerFunctions::GetObject(user->GetEquipedWeapon()->nDBID);
			if(weapon != NULL)
			{
				if(weapon->SD != NULL)
				{
					user->UnequipItem(7);
					user->SD->pObjectEx->pSkillMods->p_block_equip_weapon = true;
				}
			}
		}
	}

	TLS_TRACE_END;
}
