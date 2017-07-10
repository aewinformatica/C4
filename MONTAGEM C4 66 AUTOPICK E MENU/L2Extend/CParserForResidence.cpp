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

#include "CParserForResidence.h"

void InitializeAgit()
{
	//Manor, Agit and Castle
	WriteMemoryDWORD(0x779083, 0xA6C0*2);
	WriteMemoryDWORD(0x656853, 0xF6C0*2);
	WriteMemoryBYTE(0x77961B, 0x1F);
	WriteMemoryBYTE(0x779620, 5);
	WriteMemoryBYTE(0x779149, 0x1F);
	WriteMemoryBYTE(0x77914E, 5);
	WriteMemoryBYTE(0x658624, 0x1F);
	WriteMemoryBYTE(0x65862B, 0x1F);
	WriteMemoryBYTE(0x658630, 5);
};
