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

#include "CDoor.h"

void CDoorDB::SetDoorOpen(bool bOpen)
{
	typedef void (*t)(VOID*, bool );
    t f = (t)0x059ACD0;
    f((VOID*)0x155E250, bOpen);
}

CDoor* CDoorDB::GetDoor(WCHAR* name)
{
	typedef CDoor*(*t)(VOID*, WCHAR* );
    t f = (t)0x0599800;
	return f((VOID*)0x155E250, name);
}

CDoor* CDoorDB::GetDoor(int nID)
{
	typedef CDoor*(*t)(VOID*, int );
    t f = (t)0x0599B00;
	return f((VOID*)0x155E250, nID);
}

bool CDoor::IsValidDoor()
{
	if( IsValidObject(VMTCDoor))
		return true;
	else
		return false;
}

bool CDoor::Open(bool bByParent)
{
	typedef bool(*t)(CDoor*, bool);
    t f = (t)0x059A140;
	return f(this, bByParent);
}

bool CDoor::Close(bool bByParent)
{
	typedef bool(*t)(CDoor*, bool);
    t f = (t)0x059A3A0;
	return f(this, bByParent);
}
