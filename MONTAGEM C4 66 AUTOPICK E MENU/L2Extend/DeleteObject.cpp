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

#include "CGameEvents.h"

INT32 nOnDeleteObject = 0;
void CGameEvents::OnDeleteObject(unsigned int nSID)
{
	L2SERVER_SHARED_GUARD1(nOnDeleteObject);
	TLS_TRACE_BEGIN;

     __try
	{ 
		// Functions
		typedef void (__fastcall *_DO) (VOID *pObject, unsigned int nSID);
		_DO xDeleteObject = (_DO)0x0062DF60L;
		xDeleteObject((VOID*)0x03E9DFC0, nSID);
		//warn crash error with an empty object of CItem (Meshi and Nicolas)
	}
    __except(EXCEPTION_EXECUTE_HANDLER)
	{ 
		/* Invalid pointer */
		CLog::Add(CLog::red, "found exception in [%ls] line[%d]", __FUNCTIONW__, __LINE__);
	}

	TLS_TRACE_END;
}
