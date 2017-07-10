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

#include "CSkillEffect_i_augment.h"
//#include "CAugmentationSystem.h"
#include "User.h"

INT32 CSkillEffect_i_augmentInstant = 0;
void CSkillEffect_i_augment::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(CSkillEffect_i_augmentInstant);
	TLS_TRACE_BEGIN;

	pSkillUser->Lock(__FILEW__, __LINE__);

	if(pSkillUser->IsValidUser())
	{
		User *pUser = (User*)pSkillUser;

		CSharedItemData *equipedSD = pUser->GetEquipedWeapon();
		CItem *pItem = (CItem*)L2ServerFunctions::GetObject(equipedSD->nObjectID);

		if(equipedSD != NULL && equipedSD->exInfo->augmentationId > 0)
		{
			//CAugmentationSystem::ActivateAugmentation(pUser, pItem);

			pUser->SendUserInfo(false);
			pUser->SendCharInfo(false);
		}
	}
	pSkillUser->Unlock();

	TLS_TRACE_END;
}
