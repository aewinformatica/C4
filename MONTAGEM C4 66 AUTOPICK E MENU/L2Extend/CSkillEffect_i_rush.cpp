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

#include "CSkillEffect_i_rush.h"
#include "CCreature.h"

INT32 nCSkillEffect_i_rushInstant = 0;
void CSkillEffect_i_rush::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_rushInstant);
	TLS_TRACE_BEGIN;

	//CLog::Add(CLog::blue, "i_rush::Instant activated");
	CCreature *target = (CCreature *)pTarget;
	if(pSkillUser->IsValidUser())
	{
		pSkillUser->Lock(__FILEW__, __LINE__);
		target->Lock(__FILEW__, __LINE__);
		FVector vpos;
		vpos.x = pSkillUser->SD->x;
		vpos.y = pSkillUser->SD->y;
		vpos.z = pSkillUser->SD->z;
		CSPacket OutPacket;
		OutPacket.set(1024);
		OutPacket << (UINT8)0xc5;
		OutPacket << (INT32)pSkillUser->nObjectID;
		OutPacket << (INT32)target->SD->x-40;
		OutPacket << (INT32)target->SD->y-40;
		OutPacket << (INT32)target->SD->z-40;
		OutPacket << (INT32)pSkillUser->SD->x;
		OutPacket << (INT32)pSkillUser->SD->y;
		OutPacket << (INT32)pSkillUser->SD->z;
		OutPacket << (INT32)rushId;
		L2ServerFunctions::BroadcastToNeighbor(pSkillUser->nObjectID,vpos,&OutPacket);
		pSkillUser->SD->x = target->SD->x;
		pSkillUser->SD->y = target->SD->y;
		pSkillUser->SD->z = target->SD->z;
		pSkillUser->Unlock();
		target->Unlock();
	}

	TLS_TRACE_END;
}
