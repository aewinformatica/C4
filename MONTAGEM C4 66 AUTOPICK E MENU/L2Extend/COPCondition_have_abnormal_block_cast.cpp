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

#include "CCreature.h"
#include "User.h"
#include "COPCondition_have_abnormal_block_cast.h"

INT32 nCOPCondition_have_abnormal_block_cast = 0;
bool COPCondition_have_abnormal_block_cast::CanUse(CCreature *pSkillUser, CObject *pTargetObject)
{
	L2SERVER_SHARED_GUARD(nCOPCondition_have_abnormal_block_cast);
	TLS_TRACE_BEGIN;

	bool bResult = true;

	if (pTargetObject->IsCreature())
	{
		CCreature* pCreature = (CCreature*)pSkillUser;
		if (this->foundAbnormal(pCreature)){
			bResult = false;
		}
		
	}

	TLS_TRACE_END;
	return bResult;
}

bool COPCondition_have_abnormal_block_cast::foundAbnormal(CCreature *pCreature)
{
	L2EXTEND_AUTOLOCK(buff, pCreature->lockBuff, true);

	for (size_t i = 0; i < pCreature->vBuff.size(); i++)
	{
		if (this->nAbnormalType == pCreature->vBuff[i].pSkillInfo->abnormal_type)
			return true;
	}
	return false;
}