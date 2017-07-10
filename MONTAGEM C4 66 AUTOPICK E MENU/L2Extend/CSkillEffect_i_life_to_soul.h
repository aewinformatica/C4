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

/* 03.31.09, by Fyyre - Kamael CSkillInstant i_life_to_soul
*
*  This function performs allows the Kamael skill "s_life_to_soul" to function
*  correctly - adding to the nSoulCount + nAddSouls where nAddSouls is set in
*  skilldata.txt as {i_life_to_soul;#} where # is the number of souls to add, which
*  has a default value of five.
*
*/

#pragma once

#include "CBaseSkillEffect.h"

class CSkillEffect_i_life_to_soul : public CBaseSkillEffect
{
	int nAddSouls;

public:

	virtual void Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance);

	CSkillEffect_i_life_to_soul(int arg1) { nAddSouls = arg1; };
};
