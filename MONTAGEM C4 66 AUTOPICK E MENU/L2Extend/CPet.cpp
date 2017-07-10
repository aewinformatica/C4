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

#include "CPet.h"

bool CPet::DropItem(CItem* pItem, unsigned nAmount)
{
	typedef bool (*FDropItem)(CPet*, CItem*, unsigned, FVector*);
	FVector vPos = { this->SD->x, this->SD->y, this->SD->z };
	return FDropItem(0x749E70)(this, pItem, nAmount, &vPos);
}

bool CPet::UseItem(CItem *pItem, int nForce)
{
	typedef bool (*_USE_ITEM)(CPet *, CItem *, int nForce);
	_USE_ITEM xUseItem = (_USE_ITEM)0x004F9C40;
	return xUseItem(this, pItem, nForce);
}

bool CPet::Usable(CItem *pItem)
{
	typedef bool (*_USABLE)(CPet *, CItem *);
	_USABLE xUsable = (_USABLE)0x0074aeb0;
	return xUsable(this, pItem);
}
