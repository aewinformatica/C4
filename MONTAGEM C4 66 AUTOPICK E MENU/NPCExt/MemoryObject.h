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

/*
	A NOTE ON OBJECT TYPE CONVERSIONS
	=================================

	MemoryObject only has a few, but there are plenty of IsType and AsType
	functions in CObject and further. IsType functions are mostly redundant,
	since their AsType conterparts return null if the object is not of the
	desired type. Thus it is safe (and recommended) to use AsType.

	CastType functions behave differently in different classes.
	The default implementations in MemoryObject cause access violation by
	assigning *(char*)0 = 1. Therefore it's always necessary to check IsType
	before calling CastType. Although some classes change their behaviour to
	that of AsType, you still have to check IsType.
*/

class MemoryObject
{
public:
/* 0008 */  int	nRefCount;
/* 000C */  int	nIdentity; 
/* 0010 */  int	nInTimer;
/* 0014 */  int	nDeleteCount;



/* 0000 */  virtual void          Release(const char* file, int line, int nWorkType, bool flag) = 0;
/* 0008 */  virtual MemoryObject* AddRef(const char* file, int line, int nWorkType) = 0;
/* 0010 */  virtual bool        _vfunc010() = 0;
/* 0018 */  virtual             ~MemoryObject() {};
};
