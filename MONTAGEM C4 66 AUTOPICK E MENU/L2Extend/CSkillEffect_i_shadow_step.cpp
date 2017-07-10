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
#define _USE_MATH_DEFINES

#include "CSkillEffect_i_shadow_step.h"
#include "CObjectEx.h"
#include "User.h"
#include <cmath>


INT32 nCSkillEffect_i_shadow_stepInstant = 0;
void CSkillEffect_i_shadow_step::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_shadow_stepInstant);
	TLS_TRACE_BEGIN;

	if (CCreature* pTg = pTarget->AsCreature())
	{
		int x=0,y=0,z=0;
		double angle;

		pTg->Lock(__FILEW__, __LINE__);
		int px = pTg->SD->x;
		int py = pTg->SD->y;

		angle = pTg->SD->fCollisionHeight / 182.044444444;
		angle +=180;

		angle = (M_PI * angle) / 180;

		x = (int) (px + (25 * cos(angle)));
		y = (int) (py + (25 * sin(angle)));
		z = pTg->SD->z;

		FVector vpos;
		vpos.x = pSkillUser->SD->x;
		vpos.y = pSkillUser->SD->y;
		vpos.z = pSkillUser->SD->z;
		CSPacket OutPacket;
		OutPacket.set(1024);
		OutPacket << (UINT8)0xc5;
		OutPacket << (INT32)pSkillUser->nObjectID;
		OutPacket << (INT32)x;
		OutPacket << (INT32)y;
		OutPacket << (INT32)z;
		OutPacket << (INT32)pSkillUser->SD->x;
		OutPacket << (INT32)pSkillUser->SD->y;
		OutPacket << (INT32)pSkillUser->SD->z;
		OutPacket << (INT32)2;
		L2ServerFunctions::BroadcastToNeighbor(pSkillUser->nObjectID,vpos,&OutPacket);
		pTg->Unlock();
	}

	TLS_TRACE_END;
};
