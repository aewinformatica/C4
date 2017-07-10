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

#include "CSummon.h"

class CPet : public CSummon
{
	public:

		bool DropItem(CItem* pItem, unsigned nAmount);
		bool UseItem(CItem *pItem, int nForce);
		bool Usable(CItem *pItem);

	/* 1A78 */ int _dw1A78[8];
	/* 1A98 */ int nItem1DBID; // armor or weapon
	/* 1A9C */ int nItem2DBID; // armor or weapon
	/* 1AA0 sizeof */
};