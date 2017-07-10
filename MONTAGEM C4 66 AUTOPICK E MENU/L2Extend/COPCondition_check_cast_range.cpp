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

#include "COPCondition_check_cast_range.h"
#include "CCreature.h"

bool COPCondition_check_cast_range::CanUse(CCreature *pSkillUser, CObject *pTargetObject)
{
	// TODO maybe make this work on CStaticObject, or CVehicle, too?

	if (pTargetObject->IsCreature())
	{
		CCreature *pTarget = (CCreature*)pTargetObject;
		double dx = pTarget->SD->x - pSkillUser->SD->x;
		double dy = pTarget->SD->y - pSkillUser->SD->y;
		double dz = pTarget->SD->z - pSkillUser->SD->z;
		double fRealDist2 = dx * dx + dy * dy + dz * dz;
		double fMinimalDist2 = (double)nDist * nDist;

		// we can avoid the slow compuattion of sqrt(fRealDist2) by
		// comparing fRealDist2 to nDist**2 - as long as nDist >= 0,
		// it gives the same results, and is faster

		return fRealDist2 >= fMinimalDist2;
	}

	return false;
}
