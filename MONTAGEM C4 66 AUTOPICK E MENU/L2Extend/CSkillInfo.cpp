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
*/

#include "CSkillInfo.h"

CSkillInfo* CSkillInfo::Construct()
{
	// call the original constructor first
	typedef CSkillInfo* (*FConstructor)(CSkillInfo*);
	FConstructor(0x79B800)(this);

	// extended initialization
	new(&this->trigger_skill_name) std::wstring();
	this->trigger_skill_info = NULL;
	this->trigger_type = 0;
	this->trigger_rate = 0.0;

	return this;
}

void CSkillInfo::Destroy()
{
	this->trigger_skill_name.~basic_string();

	// I can't find the original destructor, but it doesn't
	// matter much, since CSkillInfo instances are probably
	// never destroyed.
}

void CSkillInfo::extendClass()
{
	WriteMemoryDWORD(0x8EF74A, sizeof(CSkillInfo));
	WriteInstructionCALLme(0x8EF760, 0x8EF765, &CSkillInfo::Construct);
}
