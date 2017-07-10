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

#include "CSkillEffect_i_death.h"
#include "CStatusUpdate.h"
#include "CSocket.h"

/*
	Chronicle 5 - Skills and Magic

	http://www.lineage2.com/news/chronicle5_04.html

	20. Lethal Strike's effect has been increased.

		* Effect 1: At a low probability, it lowers monsters' HP by 50% and players' CP to 1.
		* Effect 2: At an extremely low probability, it lowers monsters' HP to 1 and players' CP and HP to 1.
*/

INT32 nCSkillEffect_i_deathInstant = 0;
void CSkillEffect_i_death::Instant(CCreature* pCaster, CObject* pTarget, CSkillInfo* pSkillInfo, CSkillAction2* pAction, double fDistance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_deathInstant);
	TLS_TRACE_BEGIN;

	// Original CSkillEffect_i_death::Instant doesn't lock pTarget
	// before updating HP/CP, so I didn't lock it either.

	if (pCaster->IsUser() && pTarget->IsCreature())
	{
		User* pAttacker = pCaster->CastUser();
		CCreature* pVictim = pTarget->CastCreature();

		if (pVictim->IsBoss() || pVictim->IsMinion())
		{
			// i_death must not work on boss monsters - although this
			// could be achieved through dDefAttribute[attr_death], it
			// is safer to disable it explicitly, than to rely on some
			// variable value.
		}
		else if (pSkillInfo->magic_level < pVictim->SD->nLevel)
		{
			// skill level too low (was in original i_death)
		}
		else
		{
			double fDice = (100.0 * rand()) / RAND_MAX;
			double fDefAttrValue = pVictim->GetDefenseAttributeValue(pSkillInfo->attribute);
			double fDefAttrBonus = pVictim->GetAttributeBonus(pAttacker);
			double fScale = fDefAttrValue * fDefAttrBonus;

			if (fDice < fScale * this->fChanceOverall)
			{
				CStatusUpdate status(pVictim->SD->nObjectID);

				// 1667 [Lethal Strike!]
				pAttacker->Socket->SendSystemMessage(1667);

				if (fDice < fScale * this->fChance1)
				{
					// Effect 1: lowers monsters' HP by 50% and players' CP to 1
					if (pVictim->IsUser())
					{
						// 1668 [Your lethal strike was successful!]
						pAttacker->Socket->SendSystemMessage(1668);
						pVictim->SD->fCP = 1;
						status.AddField(STATUSUPDATE_CUR_CP, pVictim->SD->fCP);
					}
					else
					{
						pVictim->SD->fHP *= 0.5;
						status.AddField(STATUSUPDATE_CUR_HP, pVictim->SD->fHP);
					}
				}
				else
				{
					// Effect 2: lowers monsters' HP to 1 and players' CP and HP to 1
					if (pVictim->IsUser())
					{
						// 1668 [Your lethal strike was successful!]
						pAttacker->Socket->SendSystemMessage(1668);
						pVictim->SD->fCP = 1;
						status.AddField(STATUSUPDATE_CUR_CP, pVictim->SD->fCP);
					}
					pVictim->SD->fHP = 1;
					status.AddField(STATUSUPDATE_CUR_HP, pVictim->SD->fHP);
				}

				status.ProcessUpdate(pVictim);
			}
		}
	}

	TLS_TRACE_END;
}
