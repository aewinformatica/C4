#include "CPPFixes.h"
#include "User.h"
#include "CSkillInfo.h"

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

void CPPFixes::Initialize()
{
	WriteInstruction(0x0063CF68, (INT32)MoveErrorLog, 0, 0xE8);	// moving old crash logs
	WriteInstruction(0x00643640, (INT32)SetTime, 0, 0xE8);		// setting server time
}

void CPPFixes::MoveErrorLog(wchar_t *pSrcFile, wchar_t *pDstFile)
{
	wchar_t err_log[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, err_log);
	wcscat_s(err_log, MAX_PATH, L"\\ErrLog\\");
	CreateDirectoryW(err_log, NULL);
	wcscat_s(err_log, MAX_PATH, pDstFile);
	MoveFileW(pSrcFile, err_log);
}

void CPPFixes::SetTime(void *pClass)
{
	typedef void (*_CL2Time__Init)(void *pClass);
	static _CL2Time__Init CL2Time__Init = (_CL2Time__Init)0x00646130;

	typedef void (*_CL2Time__SetTime)(void *pClass, unsigned int nTime);
	static _CL2Time__SetTime CL2Time__SetTime = (_CL2Time__SetTime)0x00646FD0;

	CL2Time__SetTime(pClass, 7 * 60);
	CL2Time__Init(pClass);
}

INT32 nCPPFixesGladiatorTyrantsFix = 0;
void CPPFixes::GladiatorTyrantsFix(User *pUser, CSkillInfo *pSkillInfo)
{
	L2SERVER_SHARED_GUARD(nCPPFixesGladiatorTyrantsFix);
	TLS_TRACE_BEGIN;

		switch(pSkillInfo->skill_id)
		{		
		case 0x105:			// TripleSonicSlash
			if (pUser->nCharges >= 4)
				pUser->nCharges -= 4;
			else
				pUser->nCharges = 0;
			break;
		case 0x5:			// DoubleSonicSlash
			if (pUser->nCharges >= 3)
				pUser->nCharges -= 3;
			else
				pUser->nCharges = 0;
			break;
		case 0x6:			// SonicBlaster
		case 0x11C:			// HurricaneAssault
			if (pUser->nCharges >= 2)
				pUser->nCharges -= 2;
			else
				pUser->nCharges = 0;
			break;
		case 0x36:			// ForceBlaster
			if (pUser->nCharges >= 1)
				pUser->nCharges -= 1;
			else
				pUser->nCharges = 0;
			break;
		default:
			break;
	}

	TLS_TRACE_END_NO_RETURN;
}
