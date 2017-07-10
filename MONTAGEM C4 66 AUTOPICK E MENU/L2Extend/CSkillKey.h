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

#pragma once

#include "Global.h"

#define SKILL_LEVEL_BITS 8
#define SKILL_LEVEL_MASK ((1U << SKILL_LEVEL_BITS) - 1U)

#if (SKILL_LEVEL_BITS != 8) && (SKILL_LEVEL_BITS != 16)
#error SKILL_LEVEL_BITS must be either 8 or 16!
#endif


struct CSkillKey
{
	unsigned short skill_id;
	unsigned short level;

	CSkillKey()
		: skill_id(0), level(0) {}

	CSkillKey(unsigned short id, unsigned short lvl)
		: skill_id(id), level(lvl) {}

	CSkillKey(unsigned int from_pch)
		: skill_id(from_pch >> SKILL_LEVEL_BITS)
		, level(from_pch & SKILL_LEVEL_MASK) {}

	operator unsigned int() const
	{
		return (unsigned int)(level & SKILL_LEVEL_MASK)
			| ((unsigned int)skill_id << SKILL_LEVEL_BITS);
	}

	bool operator< (const CSkillKey& other) const
	{
		if (this->skill_id < other.skill_id) return true;
		if (this->skill_id > other.skill_id) return false;
		return this->level < other.level;
	}
};
