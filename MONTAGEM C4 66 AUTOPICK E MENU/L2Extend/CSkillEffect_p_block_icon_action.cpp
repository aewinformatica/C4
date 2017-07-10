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

#include "CSkillEffect_p_block_icon_action.h"
#include "CObjectEx.h"
#include "CSkillMod.h"
#include "User.h"

INT32 nCSkillEffect_p_block_icon_actionPump = 0;
void CSkillEffect_p_block_icon_action::Pump(CObject* pTarget, CSkillInfo* pSkillInfo)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_p_block_icon_actionPump);
	TLS_TRACE_BEGIN;

	User *pSkillUser = (User *)pTarget;

	// Should Works Only at User, Also We need to Validate the pTarget otherwise we can crash...
	if ( pSkillUser->IsValidUser() ) { pSkillUser->SD->pObjectEx->pSkillMods->p_block_icon_action = true; }

	TLS_TRACE_END;
}

