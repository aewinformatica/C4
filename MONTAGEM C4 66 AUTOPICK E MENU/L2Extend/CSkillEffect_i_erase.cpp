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

#include "CSkillEffect_i_erase.h"
#include "CSummon.h"
#include "User.h"

INT32 nCSkillEffect_i_eraseInstant = 0;
void CSkillEffect_i_erase::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_eraseInstant);
	TLS_TRACE_BEGIN;

	pSkillUser->Lock(__FILEW__, __LINE__);
	if(pSkillUser->IsValidUser())
	{
		CSummon* sTarget = (CSummon*)pTarget;
		if(sTarget->IsValidSummon())
		{
			User* sMaster = sTarget->GetMaster();
			if(sMaster->IsValidUser()) 
			{
				int nLandRate = rand() % 100 + 1;

				//Adding skill magic level dependence
				nLandRate *= sTarget->SD->nLevel;
				nLandRate /= pSkillInfo->magic_level;
				
				//I've read somewhere that erase shouldn't remove summon
				//if the user have more 12 levels of difference. (e.g : summon is 78 and player skill 40)
				//remove if this wrong
				int nLevelDiff = sTarget->SD->nLevel - pSkillInfo->magic_level;

				if(nLandRate < nChance && nLevelDiff <= 12)
					sMaster->DespawnSummon();
			}
		}
	}
	pSkillUser->Unlock();

	TLS_TRACE_END;
};
