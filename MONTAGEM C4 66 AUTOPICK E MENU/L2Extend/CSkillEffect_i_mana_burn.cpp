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

#include "CSkillEffect_i_mana_burn.h"
#include "CStatusUpdate.h"
#include "User.h"

INT32 nCSkillEffect_i_mana_burnInstant = 0;

/* You dont need to use locks in this skill effect- ncsoft didnt use in i_target_cancel_instant */
void CSkillEffect_i_mana_burn::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_mana_burnInstant);
	TLS_TRACE_BEGIN;
	CCreature *pTg = (CCreature*)pTarget;
	if(pSkillUser->IsValidCreature() && pTg->IsValidCreature())
	{
		int nLandRate = rand() % 100 + 1;

		//Adding skill magic level dependence
		nLandRate *= pTg->SD->nLevel;
		nLandRate /= pSkillInfo->magic_level;
		
		if(nLandRate < nChance)
		{
			int nManaAmount = (sqrt(pSkillUser->SD->fMAtk)*nPower*(pTg->SD->fMaxMP/97))/pTg->SD->fMDef;

			pTg->Lock(__FILEW__, __LINE__);
			pTg->SD->fMP -= nManaAmount;
			pTg->Unlock();

			CStatusUpdate *pStatus = new CStatusUpdate(pTg->SD->nObjectID);
			pStatus->AddField(STATUSUPDATE_CUR_MP, pTg->SD->fMP);
			pStatus->ProcessUpdate(pTg);
			delete pStatus;
		}
	}
	TLS_TRACE_END;
};