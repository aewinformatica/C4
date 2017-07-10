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

#include "CSkillEffect_i_target_me_chance.h"
#include "CCreature.h"

INT32 nCSkillEffect_i_target_me_chanceInstant = 0;
void CSkillEffect_i_target_me_chance::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_target_me_chanceInstant);
	TLS_TRACE_BEGIN;
	CCreature *pTg = (CCreature*)pTarget;
	if(pSkillUser->IsValidCreature() && pTg->IsValidCreature())
	{
		int nLandRate = rand() % 100 + 1;

		nLandRate *= pTg->SD->nLevel;
		nLandRate /= pSkillInfo->magic_level;
		
		if(nLandRate < nChance)
		{
			typedef void (__thiscall *_I_TARGET_ME_INSTANT) (CBaseSkillEffect *, CCreature *, CCreature *, CSkillInfo *, CSkillAction2 *, double);
			_I_TARGET_ME_INSTANT _i_target_me_instant = (_I_TARGET_ME_INSTANT)0x007B7640;
			_i_target_me_instant(this, pSkillUser, pTg, pSkillInfo, pAction, distance);			
		}
	}
	TLS_TRACE_END;
};