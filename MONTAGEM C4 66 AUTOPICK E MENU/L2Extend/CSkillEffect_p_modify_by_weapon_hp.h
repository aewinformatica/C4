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

#pragma once

#include "CSkillEffect_p_modify_by_weapon.h"
#include "CCreature.h"

class CSkillEffect_p_modify_by_weapon_hp : public CSkillEffect_p_modify_by_weapon
{
protected:

	double fLowLimit;
	double fHighLimit;

public:

	CSkillEffect_p_modify_by_weapon_hp(const bool* pWeaponTypeFlags,
									double fParam,
									double CCreature::*pMember,
									int nModType,
									double fMinHealth, double fMaxHealth)
		: CSkillEffect_p_modify_by_weapon(pWeaponTypeFlags, fParam, pMember, nModType)
		, fLowLimit(fMinHealth * 0.01)
		, fHighLimit(fMaxHealth * 0.01)
	{}

	virtual void Pump(CObject* pTarget, CSkillInfo* pSkillInfo);
};
