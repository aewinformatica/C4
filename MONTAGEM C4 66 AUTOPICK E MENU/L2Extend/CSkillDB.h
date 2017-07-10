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
*/

#pragma once

#include "Global.h"
#include "CSkillInfo.h"

class CSkillDB;
class CSkillInfo;
struct CSkillKey;

extern "C"
{
	void*       CSkillDB_ConstructSkillInfoMap(void** rcx);
	void        CSkillDB_DestroySkillInfoMap(void** rcx);
	CSkillInfo* CSkillDB_GetSkillInfo(const CSkillDB* rcx, const CSkillKey* rdx);
}

class CSkillDB
{
public:

	typedef std::map<CSkillKey, CSkillInfo*>    SkillInfoMap;
	typedef SkillInfoMap::const_iterator        SkillInfoIterator;

	/* 0000 */  const SkillInfoMap              skillInfoMap;
	/* 0018 */  // here is probably map<wstring, pair<int, int> >
				//    sizeof(value_type) == 0x30
				//    used in GetSkillIdLevelByName (sub_79AAD0)
	/* 0030 ... */

	static CSkillDB* instance()
	{
		return (CSkillDB*)0x0E4172C8;
	}

	static int GetSkillIdLevelByName(const wchar_t* wszName, int* pSkillId, int* pLevel)
	{
		typedef int (*FGetSkillIdLevelByName)(CSkillDB*, const WCHAR*, int*, int*);
		return FGetSkillIdLevelByName(0x79AAD0)(instance(), wszName, pSkillId, pLevel);
	}

	static CSkillInfo* GetSkillInfo(const wchar_t* wszName)
	{
		int nSkillId, nLevel;

		if (GetSkillIdLevelByName(wszName, &nSkillId, &nLevel))
			return GetSkillInfo(nSkillId, nLevel);
		else
			return 0;
	}

	static CSkillInfo* GetSkillInfo(int nSkillId, int nLevel)
	{
		return GetSkillInfo(CSkillKey(nSkillId, nLevel));
	}

	static CSkillInfo* GetSkillInfo(CSkillKey sk)
	{
		return CSkillDB_GetSkillInfo(instance(), &sk);
		//typedef CSkillInfo* (*FGetSkillInfo)(CSkillDB*, CSkillKey*);
		//return FGetSkillInfo(0x79A580)(instance(), &sk);
	}
};

extern "C"
{
	// defined in CSkillDB.asm

	void CSkillDB_GetSkillInfo1__1(void);
	void CSkillDB_GetSkillInfo1__ax(void);
	void CSkillDB_GetSkillInfo1__bx(void);
	void CSkillDB_GetSkillInfo1__bp(void);
	void CSkillDB_GetSkillInfo1__si(void);
	void CSkillDB_GetSkillInfo1__r12w(void);
	void CSkillDB_GetSkillInfo1__r13w(void);
	void CSkillDB_GetSkillInfo1__r14w(void);
	void CSkillDB_GetSkillInfo1__r15w(void);

	void CSkillDB_GetSkillInfo1__r11_22h(void);
	void CSkillDB_GetSkillInfo1__r14_18h(void);
	void CSkillDB_GetSkillInfo1__rax_1Ch(void);
	void CSkillDB_GetSkillInfo1__rbx_1Ch(void);
	void CSkillDB_GetSkillInfo1__rdi_04h(void);
	void CSkillDB_GetSkillInfo1__rsp_34h(void);
	void CSkillDB_GetSkillInfo1__rsp_38h(void);
	void CSkillDB_GetSkillInfo1__rsp_40h(void);
	void CSkillDB_GetSkillInfo1__rsp_44h(void);

	void CSkillDB_GetSkillInfo1i__r12_38h__item_skill(void);
	void CSkillDB_GetSkillInfo1i__rdi_38h__item_skill(void);
	void CSkillDB_GetSkillInfo1i__rsi_38h__item_skill(void);

	void CSkillKey_cmp_level__79C1AEh(void);
	void CSkillKey_cmp_level__79C1E3h(void);

	void CSkillKey_init__rsp_30h__edi_ebx(void);
	void CSkillKey_init__rsp_C0h__r13_r12(void);

	bool CSkillKey_less(const CSkillKey*, const CSkillKey*);
}
