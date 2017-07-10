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

#include "CSkillDB.h"
#include "FeatureRegistry.h"

CompileTimeSizeCheck(CSkillDB::SkillInfoMap, 0x18);
CompileTimeSizeCheck(CSkillDB::SkillInfoMap::value_type, 0x10);

CompileTimeOffsetCheck(CSkillDB, skillInfoMap, 0x00);


void* CSkillDB_ConstructSkillInfoMap(void** rcx)
{
	// L2Server containers use different allocators, and since we're
	// inserting new elements into the map (via operator[]), we must
	// also replace original construction with our own.
	new(rcx) CSkillDB::SkillInfoMap();
	return rcx[1]; // return pMap->_Myhead
}

void CSkillDB_DestroySkillInfoMap(void** rcx)
{
	CSkillDB::SkillInfoMap* pMap = (CSkillDB::SkillInfoMap*)rcx;
	pMap->~map(); // destroy the map
	rcx[1] = 0;   // clear pMap->_Myhead
}

CSkillInfo* CSkillDB_GetSkillInfo(const CSkillDB* rcx, const CSkillKey* rdx)
{
	CSkillDB::SkillInfoIterator it = rcx->skillInfoMap.find(*rdx);
	return it == rcx->skillInfoMap.end() ? 0 : it->second;
}


struct CSkillDB_extension : Feature<CSkillDB_extension>
{
	const char* name() const
	{
		return "CSkillDB extension";
	}

	CSkillDB_extension()
	{
		if (this != &_instance) return;
		FeatureRegistry::addFeature(*this);
	}

	bool initProcessAttach()
	{
		if (SKILL_LEVEL_BITS == 16)
		{
			extendAdd();
			extendGetSkillInfo();
			extendItemSkills();
			extendSkillPchCode();
		}
		return true;
	}

	void extendAdd()
	{
		// CSkillDB construction/destruction
		WriteInstructionCALL(0x95FE54, 0x95FE59, CSkillDB_ConstructSkillInfoMap);
		WriteInstructionCALL(0x79C67B, 0x79C680, CSkillDB_DestroySkillInfoMap);

		// CCubicDB::Add
		// ...

		// CSkillDB::Add
		WriteMemoryBYTES    (0x79C176, "45 0F B7 44 24 0C");        //  movzx   r8d, word ptr [r12+0Ch]
		WriteMemoryBYTES    (0x79C182, "89 54 24 30");              //  mov     [rsp+30h], edx
		WriteMemoryBYTES    (0x79C186, "66 44 89 44 24 32");        //  mov     [rsp+32h], r8w
		WriteInstructionJUMP(0x79C1AE, 0x79C1B4, CSkillKey_cmp_level__79C1AEh);
		WriteInstructionJUMP(0x79C1E3, 0x79C1E9, CSkillKey_cmp_level__79C1E3h);
		WriteInstructionCALLme(0x79C3DC, 0x79C3E1, &CSkillDB::SkillInfoMap::operator []);
	}

	void extendGetSkillInfo()
	{
		// This will warn us when the original CSkillDB::GetSkillInfo
		// is called, which must not happen, because it only uses the
		// lower 8 bits of CSkillKey::level.
		DisableFunction(0x79A580, "CSkillDB::GetSkillInfo", 2, __FILE__, __LINE__);

		// CArea::AddSkillInfo
		WriteMemoryBYTES    (0x426F58, "C1 E9 10");                 //  shr     ecx, 10h
		WriteMemoryBYTES    (0x426F5B, "66 89 4C 24 30");           //  mov     [rsp+30h], cx
		WriteInstructionCALL(0x426F70, 0x426F75, CSkillDB_GetSkillInfo1__ax);

		// CBattleCampDB::ReserveBattleCamp
		WriteInstructionCALL(0x441C06, 0x441C0B, CSkillDB_GetSkillInfo1__1);

		// BuilderCmd_setskill
		WriteInstructionCALL(0x44669D, 0x4466A2, CSkillDB_GetSkillInfo1__ax);
		WriteMemoryDWORD    (0x4466C4, 1U << SKILL_LEVEL_BITS);

		// BuilderCmd_buffadd
		WriteInstructionCALL(0x46B07F, 0x46B084, CSkillDB_GetSkillInfo1__ax);

		// CCreature::CubicAction
		WriteInstructionCALL(0x4DF76F, 0x4DF774, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4DF8A8, 0x4DF8AD, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4DFAB5, 0x4DFABA, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4DFB15, 0x4DFB1A, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4DFB75, 0x4DFB7A, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4DFBD5, 0x4DFBDA, CSkillDB_GetSkillInfo1__bx);

		// CCreature::SetMaxMagicLevel
		WriteInstructionCALL(0x4EAE49, 0x4EAE4E, CSkillDB_GetSkillInfo1__rbx_1Ch);

		// CCreature::UseEtcItem
		WriteInstructionCALL(0x4EC228, 0x4EC22D, CSkillDB_GetSkillInfo1i__rdi_38h__item_skill);

		// CCreature::SkillAction
		WriteInstructionCALL(0x4F12CF, 0x4F12D4, CSkillDB_GetSkillInfo1i__r12_38h__item_skill);

		// CCreature::UseItem
		WriteInstructionCALL(0x4FA170, 0x4FA175, CSkillDB_GetSkillInfo1__r11_22h);

		// CCreature::HealCubicAction
		WriteInstructionCALL(0x4FC631, 0x4FC636, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4FC855, 0x4FC85A, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4FCA68, 0x4FCA6D, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4FCCDB, 0x4FCCE0, CSkillDB_GetSkillInfo1__rax_1Ch);
		WriteInstructionCALL(0x4FCE2E, 0x4FCE33, CSkillDB_GetSkillInfo1__bx);
		WriteInstructionCALL(0x4FCF24, 0x4FCF29, CSkillDB_GetSkillInfo1__bx);

		// CCreature::ValidateSkillList
		WriteInstructionCALL(0x509D65, 0x509D6A, CSkillDB_GetSkillInfo1__rbx_1Ch);
		WriteInstructionCALL(0x50A115, 0x50A11A, CSkillDB_GetSkillInfo1__rbx_1Ch);
		WriteMemoryBYTES    (0x50A42E, "42 8B 04 A1");              //  mov     eax, [rcx+r12*4]
		WriteMemoryBYTES    (0x50A432, "89 44 24 30");              //  mov     [rsp+30h], eax
		WriteMemoryBYTES    (0x50A436, "66 66 66 90");              //  nop
		WriteMemoryBYTES    (0x50A43A, "66 66 66 90");              //  nop
		WriteMemoryBYTES    (0x50A43E, "66 66 66 90");              //  nop
		WriteInstructionCALL(0x50A44E, 0x50A453, CSkillDB_GetSkillInfo);

		// CCreature::ValidateAttachedSkills
		WriteMemoryBYTES    (0x517780, "8B 04 99");                 //  mov     eax, [rcx+rbx*4]
		WriteMemoryBYTES    (0x517783, "89 44 24 30");              //  mov     [rsp+30h], eax
		WriteMemoryBYTES    (0x517787, "66 66 66 90");              //  nop
		WriteMemoryBYTES    (0x51778B, "66 66 66 90");              //  nop
		WriteMemoryBYTES    (0x51778F, "66 66 90");                 //  nop
		WriteInstructionCALL(0x51779E, 0x5177A3, CSkillDB_GetSkillInfo);

		// CDBSocket::ReplyLoadAbnormalStatus
		WriteInstructionCALL(0x58CC75, 0x58CC7A, CSkillDB_GetSkillInfo1__rsp_44h);

		// CEventMatchBuilderCommandParser::Parse_useskill
		WriteInstructionCALL(0x5B6A37, 0x5B6A3C, CSkillDB_GetSkillInfo1__ax);

		// CHolyThing::AddPossessingMaster
		WriteInstructionCALL(0x5DD661, 0x5DD666, CSkillDB_GetSkillInfo1__1);

		// CAttackAction::CheckItemSkill
		WriteMemoryBYTES    (0x696B40, "66 8B 40 2A");              //  mov     ax, [rax+2Ah]
		WriteInstructionCALL(0x696B54, 0x696B59, CSkillDB_GetSkillInfo1__ax);
		WriteMemoryBYTES    (0x696C25, "66 8B 40 26");              //  mov     ax, [rax+26h]
		WriteInstructionCALL(0x696C39, 0x696C3E, CSkillDB_GetSkillInfo1__ax);

		// CSkillAction2::OnStart
		WriteInstructionCALL(0x6B370C, 0x6B3711, CSkillDB_GetSkillInfo1__r14_18h);

		// CSkillAction2::OnTick
		WriteMemoryBYTES    (0x6B8D31, "66 8B 40 2E");              //  mov     ax, [rax+2Eh]
		WriteInstructionCALL(0x6B8D4B, 0x6B8D50, CSkillDB_GetSkillInfo1__ax);

		// NpcSocket::NpcGrowSkillSuggestion
		WriteMemoryBYTES    (0x6DABC6, "41 C1 EC 10");              //  shr     r12d, 10h
		WriteMemoryBYTES    (0x6DABCA, "44 0F B7 F9");              //  movzx   r15d, cx
		WriteInstructionCALL(0x6DABE5, 0x6DABEA, CSkillDB_GetSkillInfo1__r15w);

		// COlympiadDefaultSetting::GiveSkill
		WriteMemoryBYTES    (0x70736E, "C1 EF 10");                 //  shr     edi, 10h
		WriteMemoryBYTES    (0x70738B, "0F B7 2B");                 //  movzx   ebp, word ptr [rbx]
		WriteInstructionCALL(0x7073A4, 0x7073A9, CSkillDB_GetSkillInfo1__bp);

		// CShortCut::AddShortCut
		WriteInstructionCALL(0x791D66, 0x791D6B, CSkillDB_GetSkillInfo1__r12w);

		// CSkillAcquireDB::GetSkillAcquireInfo
		WriteInstructionCALL(0x79CB05, 0x79CB0A, CSkillDB_GetSkillInfo1__r13w);

		// CSkillAcquireDB::GetEtcSkillAcquireInfo
		WriteInstructionCALL(0x79CCE4, 0x79CCE9, CSkillDB_GetSkillInfo1__r12w);

		// CSkillEnchantChecker::CheckRequestEnchantSkill
		WriteInstructionCALL(0x79ECEE, 0x79ECF3, CSkillDB_GetSkillInfo1__r12w);

		// CSkillEnchantChecker::CheckNpcEnchantSkillSuggestion
		WriteMemoryBYTES    (0x7A0879, "C1 EB 10");                 //  shr     ebx, 10h
		WriteMemoryBYTES    (0x7A087C, "48 0F B7 F6");              //  movzx   rsi, si
		WriteInstructionCALL(0x7A089F, 0x7A08A4, CSkillDB_GetSkillInfo1__si);

		// User::EnchantItem
		WriteInstructionCALL(0x802650, 0x802655, CSkillDB_GetSkillInfo1i__rdi_38h__item_skill);

		// User::SendCoolTime
		WriteMemoryBYTES    (0x82ABCF, "44 0F B7 6B 1A");           //  movzx   r13d, word ptr [rbx+1Ah]
		WriteInstructionCALL(0x82ABEB, 0x82ABF0, CSkillDB_GetSkillInfo1__r13w);

		// User::SendSkillAcquireList
		WriteInstructionCALL(0x84E7DC, 0x84E7E1, CSkillDB_GetSkillInfo1__rdi_04h);

		// CSocket::ChooseInventoryItem
		WriteInstructionCALL(0x864864, 0x864869, CSkillDB_GetSkillInfo1i__rsi_38h__item_skill);

		// CSocket::RequestAcquireSkill
		WriteInstructionCALL(0x8661D4, 0x8661D9, CSkillDB_GetSkillInfo1__rsp_40h);

		// CParserForArea::yyaction
		WriteInstructionCALL(0x8CB9B7, 0x8CB9BC, CSkillDB_GetSkillInfo1__rsp_38h);
		WriteInstructionCALL(0x8CBCDD, 0x8CBCE2, CSkillDB_GetSkillInfo1__rsp_34h);

		// CParserForSkillEnchant::yyaction
		WriteMemoryBYTES    (0x8F814B, "0F B7 41 04");              //  movzx   eax, word ptr [rcx+4]
 		WriteInstructionCALL(0x8F815F, 0x8F8164, CSkillDB_GetSkillInfo1__ax);
	}

	void extendItemSkills()
	{
		// TODO
		// CItemInfo has four CSkillKey members, but these are much
		// less important than all the other stuff, so they can wait
		// for now...
	}

	void extendSkillPchCode()
	{
		// CNPC::OnUseSkillFinished
		WriteMemoryBYTES    (0x6BE9E0, "C1 E7 10");                 //  shl     edi, 10h

		// CNPC::SetDefaultParameters
		WriteMemoryBYTES    (0x6BF200, "C1 ED 10");                 //  shr     ebp, 10h
		WriteMemoryBYTES    (0x6BF23B, "44 0F B7 04 B8");           //  movzx   r8d, word ptr [rax+rdi*4]

		// CNPC::NullSkillAction
		WriteMemoryBYTES    (0x6BF73A, "41 C1 EE 10");              //  shr     r14d, 10h
		WriteMemoryBYTES    (0x6BF73E, "45 0F B7 C5");              //  movzx   r8d, r13w

		// CSkillEnchant::SendEnchantSkillInfo
		WriteMemoryBYTES    (0x79F1BE, "C1 E5 10");                 //  shl     ebp, 10h

		// CSocket::AcquireSkillInfo
		WriteMemoryBYTES    (0x865C44, "C1 E0 10");                 //  shl     eax, 10h

		// CParserForSetting::yyaction
		WriteMemoryBYTES    (0x8EB5A2, "C1 EE 10");                 //  shr     esi, 10h
		WriteMemoryBYTES    (0x8ED24C, "C1 E0 10");                 //  shl     eax, 10h

	}
};
