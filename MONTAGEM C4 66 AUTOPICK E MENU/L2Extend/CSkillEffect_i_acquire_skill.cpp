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

#include "CSkillEffect_i_acquire_skill.h"
#include "User.h"

INT32 nCSkillEffect_i_acquire_skillInstant = 0;
void CSkillEffect_i_acquire_skill::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_acquire_skillInstant);
	TLS_TRACE_BEGIN;

	if (User* pUser = pSkillUser->AsUser())
	{
		pUser->Lock(__FILEW__, __LINE__);
		pUser->SendAcquiredSkillToDB(skill_id, 1, false);
		pUser->AcquireSkill(skill_id, 1);
		pUser->ValidateSkillList();
		pUser->Unlock();
	}

	TLS_TRACE_END;
}
