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

#include "CSharedData.h"

#ifdef BUILD_L2EXTEND

#include "Utils.h"
CompileTimeOffsetCheck(CSharedData, nExp64, 0xBE0);

#endif // BUILD_L2EXTEND

void CSharedData::AddAbnormalStatus(int nAbnormalType, int nLevel)
{
	typedef void(*aas)(CSharedData*, int, int);
	aas _aas = (aas) 0x004D9640;
	_aas(this, nAbnormalType, nLevel);
}

void CSharedData::DeleteAbnormalStatus(int nAbnormalType)
{
	typedef void (*das)(CSharedData*, int);
	das _das = (das) 0x004D9510;
	_das(this, nAbnormalType);
}

void CSharedData::DeleteAllAbnormalStatus()
{
	typedef void (*das)(CSharedData*);
	das _das = (das) 0x004D22C0;
	_das(this);
}
