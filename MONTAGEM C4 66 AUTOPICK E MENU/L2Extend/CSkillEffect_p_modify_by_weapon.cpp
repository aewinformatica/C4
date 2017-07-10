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
*/

#include "CSkillEffect_p_modify_by_weapon.h"

bool CSkillEffect_p_modify_by_weapon::CheckPumpCondition(CObject* pTarget)
{
	L2SERVER_SHARED_GUARD0;
	TLS_TRACE_BEGIN;

	bool bResult = false;

	if (pTarget->IsCreature())
	{
		bResult = this->CheckWeapon(pTarget->CastCreature());
	}

	TLS_TRACE_END;
	return bResult;
}

void CSkillEffect_p_modify_by_weapon::Pump(CObject* pTarget, CSkillInfo* pSkillInfo)
{
	L2SERVER_SHARED_GUARD0;
	TLS_TRACE_BEGIN;

	this->ApplyEffect(pTarget->CastCreature());

	TLS_TRACE_END;
}
