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

#include "CSkillEffect_p_modify_by_weapon_hp.h"

void CSkillEffect_p_modify_by_weapon_hp::Pump(CObject* pTarget, CSkillInfo* pSkillInfo)
{
	L2SERVER_SHARED_GUARD0;
	TLS_TRACE_BEGIN;

	// TODO maybe this should work similar to p_critical_rate_by_hp1/2.
	// I looked at it briefly in IDA: it sets pCreature->pump_attack to true,
	// then checks some "is_effect_active_hp1/2" flag at 0x0BD0/1.
	// If HP drops below limit, and the flag is 0, then a message is sent
	// to the user that the effect has been activated. If HP is above limit,
	// and the flag is 1, then a message is sent that the effect has been
	// removed.

	CCreature* pCreature = pTarget->CastCreature();

	// I'm not sure what this does, but it is setup this way in existing
	// C4 effects like for example CSkillEffect_p_critical_rate_by_hp2.
	pCreature->pump_attack = true;

	double fCurHP = pCreature->SD->fHP;
	double fMaxHP = pCreature->SD->fMaxHP;

	// The current HP level must be strictly above the lower limit, and
	// below or equal to the upper limit. This is to ensure disjunct level
	// ranges - if we used non-strict ordering on both sides, weird things
	// could happen.
	if (fCurHP > this->fLowLimit * fMaxHP &&
		fCurHP <= this->fHighLimit * fMaxHP)
	{
		this->ApplyEffect(pCreature);
	}

	TLS_TRACE_END;
}
