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

#pragma once

#include "Global.h"

class CSkillInfo;

class CSkillAction2
{
	public:
	
	/* 0h */ void* _vtable;
	/* 8h */ int caster_sid;
	/* 0Ch */ int dw0C;
	/* 10h */ int dw10;
	/* 14h */ int skill_id;
	/* 18h */ int skill_level;
	/* 1Ch */ int dw1C;
	/* 20h */ bool bForce;
	/* 21h */ bool bHasTarget;
	/* 22h */ bool b22h_ary[6];
	/* 28h */ double fOne; // == 1.0
	/* 30h */ char foo30[0x38];
	/* 68h */ CSkillInfo *pSI;
	/* 70h */ int dw70[8];
	/* 90h */ int seed_sid;
	/* 94h */ int seed_type; // i.e. CItem->nObjectType
};