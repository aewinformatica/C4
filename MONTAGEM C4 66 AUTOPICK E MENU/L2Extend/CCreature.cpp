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

#include "CCreature.h"
#include "CSkillDB.h"
#include "FeatureRegistry.h"

CCreature::CCreature()
{
	CompileTimeSizeCheck(CCreature, 0x14F0);
	CompileTimeSizeCheck(CIOCriticalSection, 0x30);
	CompileTimeSizeCheck(CInventory, 0x68);
	CompileTimeSizeCheck(BuffVector, 0x20);
	CompileTimeSizeCheck(CBuffInfo, 0x18);
	CompileTimeSizeCheck(CubicVector, 0x20);
	CompileTimeSizeCheck(CActiveCubicInfo, 0x30);
}

void CCreature::Lock(WCHAR* file, int line)
{
    typedef void (*t)(CCreature*, WCHAR* , int );
    t f = (t)0x04292F0;
    f(this, file, line);
}

void CCreature::Unlock()
{
    typedef void (*t)(CCreature*);
    t f = (t)0x0429F10;
    f(this);
}

double CCreature::Distance(double x1, double y1, double z1)
{
	double x2 = this->SD->x;
	double y2 = this->SD->y;
	double z2 = this->SD->z;

	return sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
}

bool CCreature::DispelAll(int magic_level, CSkillInfo *pSkillInfo)
{
	typedef bool (*t)(CCreature*, int, CSkillInfo*);
    t f = (t)0x0501DD0;
    return f(this, magic_level, pSkillInfo);
}

bool CCreature::FindBuffByAT(int nAbnormalType, CBuffInfo* pBuffInfo)
{
	L2EXTEND_AUTOLOCK(buff, this->lockBuff, true);

	for (BuffVector::iterator it = this->vBuff.begin(); it != this->vBuff.end(); ++it)
	{
		if (it->pSkillInfo->abnormal_type == nAbnormalType)
		{
			*pBuffInfo = *it;
			return true;
		}
	}
	return false;
}

void CCreature::GetEquippedObjectIdType(int nSlotType, int* pObjectId, int* pObjectType)
{
	int nItemIndex = this->SD->EquippedItemIndex(nSlotType);
	CSPointer<CItem> spItem = CItem::FindItemSP(nItemIndex);

	if (spItem)
	{
		*pObjectId = spItem->nObjectID;
		*pObjectType = spItem->nObjectType;
	}
	else
	{
		*pObjectId = 0;
		*pObjectType = 0;
	}
}

struct CCreature_extension : Feature<CCreature_extension>
{
	const char* name() const
	{
		return "CCreature extension";
	}

	CCreature_extension()
	{
		if (this != &_instance) return;
		FeatureRegistry::addFeature(*this);
	}

	bool initProcessAttach()
	{
		if (SKILL_LEVEL_BITS == 16)
		{
			extendSkillContainers();
		}
		return true;
	}

	void extendSkillContainers()
	{
		// about non-patched places:
		// - CCreature::SaveSkillUsedTime only reads skill_id, not level
		// - calls to CSkillDB::GetSkillInfo are fixed in CSkillDB_extension

		// CCreature::GetSkillUsedTime
		WriteInstructionCALL(0x4F1DE9, 0x4F1DF2, CSkillKey_init__rsp_30h__edi_ebx);
		WriteInstructionCALL(0x4F1E19, 0x4F1E1E, CSkillKey_less);
		WriteInstructionCALL(0x4F1E4D, 0x4F1E52, CSkillKey_less);

		// CCreature::SetSkillUsableTime
		WriteInstructionCALL(0x4F8E04, 0x4F8E15, CSkillKey_init__rsp_C0h__r13_r12);
		WriteInstructionCALL(0x4F8E3C, 0x4F8E41, CSkillKey_less);
		WriteInstructionCALL(0x4F8E73, 0x4F8E78, CSkillKey_less);
		WriteInstructionCALL(0x4F8F24, 0x4F8F35, CSkillKey_init__rsp_C0h__r13_r12);
		WriteInstructionCALL(0x4F8F6F, 0x4F8F74, CSkillKey_less);
		WriteInstructionCALL(0x4F8FE2, 0x4F8FE7, CSkillKey_less);

		// CCreature::SkillReuseMap::_AllocNode
		WriteMemoryBYTES    (0x4EA1E3, "0F B7 4A 02");  //  movzx   ecx, word ptr [rdx+2]
		WriteMemoryBYTES    (0x4EA1E7, "66 89 48 1A");  //  mov     [rax+1Ah], cx

		// CCreature::AttachedSkillList::push_back et al.
		// sub_4EA260
		WriteMemoryBYTES    (0x4EA281, "41 8B 00");     //  mov     eax, [r8]
		WriteMemoryBYTES    (0x4EA284, "89 01");        //  mov     [rcx], eax
		WriteMemoryBYTES    (0x4EA286, "66 66 90");     //  nop
		// sub_4EA440
		WriteMemoryBYTES    (0x4EA4BC, "8B 07");        //  mov     eax, [rdi]
		WriteMemoryBYTES    (0x4EA4BE, "89 01");        //  mov     [rcx], eax
		WriteMemoryBYTES    (0x4EA4C0, "66 66 90");     //  nop
		// sub_4F3A40
		WriteMemoryBYTES    (0x4F3A7D, "45 8B 31");     //  mov     r14d, [r9]
		WriteMemoryBYTES    (0x4F3A80, "45 33 FF");     //  xor     r15d, r15d
		WriteMemoryBYTES    (0x4F3A83, "44 89 70 08");  //  mov     [rax+8], r14d
		WriteMemoryBYTES    (0x4F3A87, "66 66 66 90");  //  nop
		WriteMemoryBYTES    (0x4F3A8B, "66 66 66 90");  //  nop
		WriteMemoryBYTES    (0x4F3F20, "44 89 30");     //  mov     [rax], r14d
		WriteMemoryBYTES    (0x4F3F23, "90");           //  nop
		WriteMemoryBYTES    (0x4F3F24, "66 66 66 90");  //  nop
		WriteMemoryBYTES    (0x4F4090, "45 89 33");     //  mov     [r11], r14d
		WriteMemoryBYTES    (0x4F4093, "90");           //  nop
		WriteMemoryBYTES    (0x4F4094, "66 66 66 90");  //  nop

		// CCreature::AttachSkill
		WriteMemoryBYTES    (0x5000D7, "89 6C 24 30");        //  mov     [rsp+30h], ebp
		WriteMemoryBYTES    (0x5000DB, "66 44 89 74 24 32");  //  mov     [rsp+32h], r14w

		// CCreature::ValidateAttachedSkills
		WriteMemoryBYTES    (0x5176DD, "8B 06");        //  mov     eax, [rsi]
		WriteMemoryBYTES    (0x5176DF, "89 03");        //  mov     [rbx], eax
		WriteMemoryBYTES    (0x5176E1, "66 66 90");     //  nop
	}
};
