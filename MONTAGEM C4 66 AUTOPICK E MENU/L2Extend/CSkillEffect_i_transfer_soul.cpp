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

/* 03.31.09, by Fyyre - Kamael CSkillInstant i_transfer_souls
*
* This function is transfers a soul from Kamael to Kamael.  The opcond in skilldata.txt
* handles subtraction of nSoulCount from the caster, this function handles details for
* the target.
*
*/

#include "CSkillEffect_i_transfer_soul.h"
#include "CObjectEx.h"
#include "CSocket.h"

int nCSkillEffect_i_transfer_soulInstant = 0;
void CSkillEffect_i_transfer_soul::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_transfer_soulInstant);
	TLS_TRACE_BEGIN;

	User *pUser = (User*)pSkillUser;

	if(pUser->IsValidUser())
	{
		User *pPCTarget = (User*)pTarget;

		if(pPCTarget->IsValidUser() && pPCTarget->IsValidCreature() && (pPCTarget->SD->nRace = 5) && (pPCTarget != pUser))
		{

		User *pUser = (User *)pSkillUser;

			if(pUser->SD->pObjectEx->pGeneralInfo->nSoulCount < nTransferSouls)
			{

				pUser->SD->pObjectEx->pGeneralInfo->nSoulCount = 0;
			}

			else
			{
				pPCTarget->Lock(__FILEW__, __LINE__);
				pPCTarget->SD->pObjectEx->pGeneralInfo->nSoulCount += nTransferSouls;
				pPCTarget->Unlock();
				pPCTarget->SendETCBuffStatus();
				pPCTarget->Socket->SendSystemMessage(2162);
			}
		}
	}

	TLS_TRACE_END;
}
