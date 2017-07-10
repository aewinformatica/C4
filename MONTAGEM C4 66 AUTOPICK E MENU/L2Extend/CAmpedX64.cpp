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

#include "CAmpedX64.h"

INT64 nAmpedX64Address = 0;

void CAmpedX64::InitializeAfterLoadage()
{
	// Finding Amped Address
	nAmpedX64Address = GetModuleAddress("AmpeDx64.dll");
	CLog::Add(CLog::blue, "Amped DLL Detected At Address : 0x%08X", nAmpedX64Address);
}

BOOL CAmpedX64::VerifyHTMLBypass(User *pUser, wchar_t *pHTMLFileName, wchar_t *pBypass)
{
	// Functions
	INT64 nFunctionAddress = nAmpedX64Address + 0x2BA0;
	typedef BOOL (__fastcall *_ACB) (User *, wchar_t *, wchar_t *);
	_ACB xVerifyHTMLBypass = (_ACB)nFunctionAddress;
	return xVerifyHTMLBypass(pUser, pHTMLFileName, pBypass);
}