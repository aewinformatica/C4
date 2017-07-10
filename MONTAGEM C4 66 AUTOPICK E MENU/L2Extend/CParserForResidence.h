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
#include "CObject.h"

void InitializeAgit();

class  CResidenceData
{
public:

	/* 0x00 */		CObject     *pResidence;
	/* 0x08 */		int     _dw0008[8];
	/* 0x28h */		INT64   *pAgit0;
	/* 0x30h */		INT64   *pAgit1;
	/* 0x38h */		INT64   *pAgit2;
	/* 0x40h */		INT64   *pAgit3;
	/* 0x48h */		INT		indexAgitPoint;
	/* 0x50h */		INT		 _dw0050[4];
};
