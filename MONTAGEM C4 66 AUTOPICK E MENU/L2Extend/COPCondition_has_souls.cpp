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

/* op_has_souls, by Fyyre
 * skilldata.txt -->> operate_cond = {{has_souls;#}} <<-- # == amount...
 */

#include "COPCondition_has_souls.h"
#include "CObjectEx.h"
#include "User.h"

int nCOPCondition_has_souls = 0;
bool COPCondition_has_souls::CanUse(CCreature *pSkillUser, CObject *pTargetObject)
{
	User *pCaster = (User*)pSkillUser;

	if(pCaster->IsValidUser())
	{
		pCaster->Lock(__FILEW__, __LINE__);
		int nCurrentSoulCount = (pCaster->SD->pObjectEx->pGeneralInfo->nSoulCount);
		pCaster->Unlock();

		if(nCurrentSoulCount >= nSoulAmount)
		{
			return true;
		}
	}
	return false;
}
