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

/* 04.08.09, by Fyyre - Kamael CSkillInstant_i_soul_gathering
* Function executed from skilldata.txt as {i_soul_gathering;#} where # is a dummy value
* This function calls SetSoul with value of 40, SetSoul takes care of the rest.
*/

#pragma once

#include "CBaseSkillEffect.h"

class CSkillEffect_i_soul_gathering : public CBaseSkillEffect
{
	int x_param1;

public:

	virtual void Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance);

	CSkillEffect_i_soul_gathering(int arg1) {x_param1 = arg1; };
};
