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

#include "CPledgeSharedData.h"
#include "CSharedData.h"
#include "CSkillKey.h"

class CSharedFactory
{
public:
	static void Initialize();

	static void ExtendCreatureSharedData();
	static void ExtendEquipmentSlots();
	static void ExtendPledgeSharedData();
	static void ReallocateAbnormalTable();
	static void ReallocateQuests();

	static void Copy(CSharedData *dest, CSharedData *source);
};

namespace SharedFactory { extern "C"
{
	typedef std::vector<CSkillKey> CSkillKeys;

	// defined in CSharedFactory.cpp

	extern const int CSharedData_EquipSlotCount;
	extern const int CSharedData_ExtEquipmentBegin;
	extern const int CSharedData_ExtEquipmentEnd;

	bool CCreature_EquipItemExt(CCreature* pCreature, CItem* pItem, int nSlotType);
	int  CCreature_IsEquippedExt(CCreature* pCreature, int nItemIndex, int nSlotType);
	bool CCreature_IsEquippedExtByObjectId(CCreature* pCreature, int nItemObjectId);
	void CCreature_ValidateAttachedSkillsExt(CCreature* pCreature, CSkillKeys* pSkillKeys);
	void User_EquipItemCheckExt(CCreature* pCreature, CItem* pItem, int nSlotType);

	// defined in CSharedFactory.asm

	void CItemFactory_FindObjectFix_rbp_rbx_x1(void);
	void CItemFactory_FindObjectFix_r14_rbx_x1(void);
	void CItemFactory_FindObjectFix_r15_rbx_x1(void);
	void CItemFactory_FindObjectFix_rbp_r12_x4(void);
	void CItemFactory_FindObjectFix_rbx_rdi_x4(void);
	void CItemFactory_FindObjectFix_rdi_rbx_x4(void);

	void CSharedData_CheckEquipSlotOffset_ebx(void);
	void CSharedData_CheckEquipSlotOffset_ecx(void);
	void CSharedData_CheckEquipSlotOffset_edx(void);
	void CSharedData_CheckEquipSlotOffset_edi(void);

	void Fix4DA830_CCreature_IsEquipped1(void);
	void Fix4DAF8F_CCreature_ValidateBaseData(void);
	void Fix4E1360_CCreature_IsEquipped2(void);
	void Fix4FA03D_CCreature_UseItem(void);
	void Fix5174B8_CCreature_ValidateAttachedSkills(void);
	void Fix519A7C_CCreature_EquipItem(void);
	void Fix51A197_CCreature_UnequipSlot(void);
	void Fix51A47F_CCreature_UnequipItem(void);
	void Fix571E8C_CDBSocket_LoadItemsPacket(void);
	void Fix7C4328_CSkillEffect_p_set_collected_Pump(void);
	void Fix7F2EFB_CTrade_CheckTradable(void);
	void Fix8212CB_User_SendPackageSendableList(void);
	void Fix825BDE_User_EquipItem(void);
	void Fix825CF0_User_EquipItem(void);
	void Fix826BDB_User_UnequipItem(void);
	void Fix82FCB4_User_PrivateStoreBuyListReq(void);
	void Fix87A74F_CUserSocket_SellPacket(void);
	void Fix8A5D64_CWarehouseDeposit_RequestEx(void);
	void Fix8A75A4_CWarehouseDeposit_Request(void);
}}
