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

#include "CSkillEffect_i_cp_per_max.h"
#include "CStatusUpdate.h"
#include "User.h"

INT32 nCSkillEffect_i_cp_per_maxInstant = 0;
void CSkillEffect_i_cp_per_max::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	TLS_TRACE_BEGIN;
	User *pUser = (User*)pSkillUser;
	
	if(pUser->IsValidUser())
	{
		pUser->Lock(__FILEW__, __LINE__);
                pUser->SD->fCP = (pUser->SD->fMaxCP * nPer / 100) + pUser->SD->fCP;
                if(pUser->SD->fCP > pUser->SD->fMaxCP) pUser->SD->fCP = pUser->SD->fMaxCP; 
                pUser->Unlock();
		
		
		CStatusUpdate *pStatus = new CStatusUpdate(pUser->SD->fCP);
		pStatus->AddField(STATUSUPDATE_CUR_CP, pUser->SD->fCP);
		pStatus->ProcessUpdate(pUser);
		delete pStatus;
	}
	TLS_TRACE_END;
};