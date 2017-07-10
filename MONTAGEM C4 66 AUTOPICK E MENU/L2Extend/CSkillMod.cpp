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

#include "CSkillMod.h"
#include "CCreature.h"
#include "User.h"

CSkillMod::CSkillMod(CCreature *ptrCreature)
{
	pCreature = ptrCreature;
	InitializeCriticalSection(&ObjectLock);
}

CSkillMod::~CSkillMod()
{
	DeleteCriticalSection(&ObjectLock);
}

void CSkillMod::ResetSkillMods()
{
	/* Add here the Skill Mods That Need's to be Disabled ! */
	p_block_icon_action = false;
	p_block_equip_weapon = false;
	p_block_equip_armor = false;
	p_charm_of_courage = false;
}

void inline CSkillMod::Lock() { EnterCriticalSection(&this->ObjectLock); }
void inline CSkillMod::Unlock() { LeaveCriticalSection(&this->ObjectLock); }