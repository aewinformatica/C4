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

#include "COPCondition_remain_cp_per.h"
#include "CObjectEx.h"
#include "User.h"

INT32 nCOPCondition_have_cp = 0;
bool COPCondition_remain_cp_per::CanUse(CCreature *pSkillUser, CObject *pTargetObject)
{
	User *caster = (User*)pSkillUser;
	
	if(caster->IsValidUser())
	{
		caster->Lock(__FILEW__, __LINE__);
		int nCurrentCpPer = (caster->SD->fCP / caster->SD->fMaxCP) * 100;
		caster->Unlock();

		if(nCurrentCpPer >= nCpAmount)
		{
			return true;
			
		}
		return false;
		
	}

	return false;
};