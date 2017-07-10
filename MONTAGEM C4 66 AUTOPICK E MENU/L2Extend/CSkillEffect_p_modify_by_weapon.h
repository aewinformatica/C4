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

#include "CBaseSkillEffect.h"
#include "CCreature.h"

// this should be the base for new effects of the form
// {p_critical_rate_by_weapon;{sword;pole};3.3;diff}

class CSkillEffect_p_modify_by_weapon : public CBaseSkillEffect
{
protected:

	// CCreature must be fully defined, otherwise CCreature::* would
	// have invalid size! I don't know why, but it is so in VC2005.
	enum { ENSURE_CCREATURE_DEFINED = sizeof(CCreature) };

	enum { NUM_WEAPON_TYPES = 11 };

	double  CCreature::*pModifiedMember;
	double  fIncrease;
	double  fMultiplier;
	bool    bEnableEffect[NUM_WEAPON_TYPES];

protected:

	void ApplyEffect(CCreature* pCreature) const
	{
		double& rfValue = pCreature->*(this->pModifiedMember);
		rfValue = rfValue * this->fMultiplier + this->fIncrease;
	}

	bool CheckWeapon(int nWeaponType) const
	{
		if (nWeaponType >= 0 && nWeaponType < NUM_WEAPON_TYPES)
			return this->bEnableEffect[nWeaponType];
		else
			return false;
	}

	bool CheckWeapon(CCreature* pCreature) const
	{
		return CheckWeapon(pCreature->SD->nWeaponType);
	}

public:

	CSkillEffect_p_modify_by_weapon(const bool* pWeaponTypeFlags,
									double fParam,
									double CCreature::*pMember,
									int nModType)
		: pModifiedMember(pMember)
		, fIncrease(nModType == modify_diff ? fParam : 0.0)
		, fMultiplier(nModType == modify_per ? (fParam + 100) / 100 : 1.0)
	{
		for (int i = 0; i < NUM_WEAPON_TYPES; ++i)
			this->bEnableEffect[i] = !!pWeaponTypeFlags[i];
	}

	virtual bool CheckPumpCondition(CObject* pTarget);
	virtual void Pump(CObject* pTarget, CSkillInfo* pSkillInfo);
};
