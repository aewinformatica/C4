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

/* 03.31.09, by Fyyre - Kamael CSkillInstant i_consume_souls
 *
 * This function is called only from skilldata.txt to decrease the current nSoulCount
 * which is set via effect = {{i_consume_souls;#}} where # is the number of souls
 * required by the skill.
 *
 */

#include "CSkillEffect_i_consume_souls.h"
#include "CObjectEx.h"
#include "User.h"

int CSkillEffect_i_consume_soulsInstant = 0;
void CSkillEffect_i_consume_souls::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(CSkillEffect_i_consume_soulsInstant);
	TLS_TRACE_BEGIN;
	if(pSkillUser->IsValidUser())
	{
		User *pUser = (User *)pSkillUser;

		if(pUser->SD->pObjectEx->pGeneralInfo->nSoulCount < nSoulsToSub)
		{
			//haha...
		}
		else
		{
			pUser->SD->pObjectEx->pGeneralInfo->nSoulCount -= nSoulsToSub;
			pUser->SendETCBuffStatus();
		}
	}
	TLS_TRACE_END;
}
