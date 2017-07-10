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

#pragma once

#define INDEXDOOR 1000

class CStaticObject
{
public:
	CStaticObject(){};
	~CStaticObject(){};

	static void InitializeStaticObject();

	static BYTE pIndex[];
	static INT64 pStatic[];
	static INT64 pIndex2[];
	static INT64 pStaticObj[];

	static void Code_7DF72A();
	static void Code_7DF73E();
	static void Code_7DF74C();
	static void Code_7E096B();
	static void Code_9604EE();
	static void Code_7E09A4();
	static void Code_960509();
	static void Code_7DFC30();
	static void Code_7DFC1B();
	static void Code_96051D();
	static void Code_7DFB1C();
	static void Code_7DFB2E();
};
