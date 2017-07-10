#pragma once

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

#include "CBaseSkillEffect.h"

class CSkillEffect_i_death : public CBaseSkillEffect
{
protected:

	double fChance1; // effect 1 probability in percent
	double fChance2; // effect 2 probability in percent
	double fChanceOverall; // fChance1 + fChance2

public:

	CSkillEffect_i_death(double f1, double f2)
		: fChance1(f1)
		, fChance2(f2)
		, fChanceOverall(f1 + f2)
	{}

	virtual void Instant(CCreature* pCaster, CObject* pTarget, CSkillInfo* pSkillInfo, CSkillAction2* pAction, double fDistance);
};