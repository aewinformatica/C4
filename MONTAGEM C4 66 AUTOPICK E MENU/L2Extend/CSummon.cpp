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

#include "Global.h"
#include "CSummon.h"

User* CSummon::GetMaster()
{
	typedef User* (__thiscall *_GETM) (CSummon *Myself);
	_GETM xGetM = (_GETM)0x0074CAA0L;
	return (xGetM(this));
}

bool CSummon::Die(CCreature* pEnemy)
{
	typedef bool (*t)(CSummon*, CCreature*);
    t f = (t)0x074CE40;
    return f(this, pEnemy);
}
