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

#include "CCreature.h"
#include "CSharedFactory.h"
#include <algorithm>

#define IMAGEBASE 0x400000
#define arg_0  0x08
#define arg_8  0x10
#define arg_10 0x18
#define arg_18 0x20

namespace SharedFactory
{
	const int CSharedData_EquipSlotCount = EquipSlotType::Count;
	const int CSharedData_ExtEquipmentBegin = offsetof(CSharedData, nExtEquipment);
	const int CSharedData_ExtEquipmentEnd = offsetof(CSharedData, nExtEquipment[CSharedData::EXT_SLOTS]);
}

using namespace SharedFactory;

static int g_SlotBitTypeArray[EquipSlotType::Count+1] = {
	0x00000001, 0x00000002, 0x00000004, 0x00000008, //  0.. 3
	0x00000010, 0x00000020, 0x00000040, 0x00000080, //  4.. 7
	0x00000100, 0x00000200, 0x00000400, 0x00000800, //  8..11
	0x00001000, 0x00002000, 0x00004000, 0x00008000, // 12..15
	0x00010000, 0x00020000, 0x00040000, 0x00080000, // 16..19
	0x00100000, 0x00200000, 0x00400000, 0x00800000, // 20..23
	0x01000000, 0x02000000, 0x04000000, 0x08000000, // 24..27
	0x00000000  // (there must be a zero at the end)
};

void CSharedFactory::Initialize()
{
	ExtendCreatureSharedData();
	ExtendEquipmentSlots();
	ExtendPledgeSharedData();
	ReallocateAbnormalTable();
	ReallocateQuests();

	WriteInstruction(0x6BEECC, (INT32)&CSharedFactory::Copy, 0, 0xE8);
}

void CSharedFactory::ExtendCreatureSharedData()
{
	//Extending CSharedData in CSharedFactory
	DWORD NewSize = sizeof(CSharedData);
		//Constructor
	WriteMemoryDWORD(0x4D2EC9 , NewSize);
	WriteMemoryDWORD(0x4D2EF7 , NewSize);
	WriteMemoryDWORD(0x4D2F07 , NewSize);
		//Destructor
	WriteMemoryDWORD(0x4D335C , NewSize);
	WriteMemoryDWORD(0x4D3348 , NewSize);
	WriteMemoryDWORD(0x4D333D , NewSize);
		//Changes in other funcs
	WriteMemoryDWORD(0x4E149E, NewSize);
	WriteMemoryDWORD(0x4E60F5 , NewSize);
	WriteMemoryDWORD(0x611953 , NewSize);
	WriteMemoryDWORD(0x611985 , NewSize);
	WriteMemoryDWORD(0x611AB9 , NewSize);
	WriteMemoryDWORD(0x611C71 , NewSize);
	WriteMemoryDWORD(0x6D8494 , NewSize);
	WriteMemoryDWORD(0x6DB6B3 , NewSize);
	WriteMemoryDWORD(0x7890E7 , NewSize);
	WriteMemoryDWORD(0x78915F , NewSize);
	WriteMemoryDWORD(0x7892D0 , NewSize);
	WriteMemoryDWORD(0x78933D , NewSize);
	WriteMemoryDWORD(0x7893DE , NewSize);
	WriteMemoryDWORD(0x7893F5 , NewSize);
	WriteMemoryDWORD(0x78B14C , NewSize);
	WriteMemoryDWORD(0x78C14E , NewSize);
	WriteMemoryDWORD(0x78C93D , NewSize);
	WriteMemoryDWORD(0x78CA6A , NewSize);
	WriteMemoryDWORD(0x78CA81 , NewSize);
	WriteMemoryDWORD(0x841142 , NewSize);
	WriteMemoryDWORD(0x841B00 , NewSize);
	WriteMemoryDWORD(0x87959A , NewSize);
	WriteMemoryDWORD(0x8A04DF , NewSize);
	WriteMemoryDWORD(0x8A17FD , NewSize);
	WriteMemoryDWORD(0x8A210D , NewSize);
	WriteMemoryDWORD(0x8A29B4 , NewSize);
	WriteMemoryDWORD(0x8A3059 , NewSize);
	WriteMemoryDWORD(0x8B1BDC , NewSize);
	WriteMemoryDWORD(0x8B241A , NewSize);
	WriteMemoryDWORD(0x8B2C47 , NewSize);
	WriteMemoryDWORD(0x8B36CB , NewSize);
	WriteMemoryDWORD(0x8B3EF6 , NewSize);
	WriteMemoryDWORD(0x8B4721 , NewSize);
	WriteMemoryDWORD(0x8B4C8C , NewSize);
	WriteMemoryDWORD(0x8B5566 , NewSize);
	WriteMemoryDWORD(0x8B633D , NewSize);
	WriteMemoryDWORD(0x8B6C45 , NewSize);
	WriteMemoryDWORD(0x8BDFE9 , NewSize);
	WriteMemoryDWORD(0x8C0530 , NewSize);
	// .text:000000000078CA89                 mov     dword ptr [rcx+rax-8B8h], 0FFFFFFFFh
	WriteMemoryQWORD(0x78CA8C, 0x58 - NewSize);
}

void CSharedFactory::ExtendEquipmentSlots()
{
	bool bExtendLocalArrays = true;
	bool bPatchTrade = true;

	// *** EXPERIMENTAL ***
	//return;

	// CCreature::IsEquipped(int)
	WriteInstructionJUMP(0x4DA830, 0x4DA838, &Fix4DA830_CCreature_IsEquipped1);

	// CCreature::ValidateBaseData
	WriteInstructionCALL(0x4DAF8F, 0x4DAF96, &Fix4DAF8F_CCreature_ValidateBaseData);

	// CCreature::IsEquipped(int, SlotType)
	WriteMemoryDWORD    (0x4E126C +2, EquipSlotType::Count);
	WriteInstructionCALL(0x4E1360, 0x4E136B, &Fix4E1360_CCreature_IsEquipped2);

	// various CCreature functions that compute equipment bonuses/penalties
	WriteInstructionCALL(0x4E3213, 0x4E321A, &CSharedData_CheckEquipSlotOffset_ebx);
	WriteInstructionCALL(0x4E3363, 0x4E336A, &CSharedData_CheckEquipSlotOffset_edi);
	WriteInstructionCALL(0x4E3523, 0x4E352A, &CSharedData_CheckEquipSlotOffset_edi);

	// CCreature::DeleteAllItemsInInventory
	WriteInstructionCALL(0x4EAB43, 0x4EAB4A, &CSharedData_CheckEquipSlotOffset_ecx);

	// CCreature::UseItem
	WriteInstructionJUMP(0x4FA03D, 0x4FA043, &Fix4FA03D_CCreature_UseItem);
	WriteMemoryDWORD    (0x4FA0B7 +2, EquipSlotType::Count);

	// CCreature::ValidateAttachedSkills
	WriteInstructionCALL(0x5174B8, 0x5174C0, &Fix5174B8_CCreature_ValidateAttachedSkills);

	// CCreature::EquipItem
	WriteRelativeAddress(0x519915, 3, g_SlotBitTypeArray, 0);
	WriteMemoryBYTE     (0x51991C +2, EquipSlotType::Count);
	WriteRelativeAddress(0x51992D, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteInstructionJUMP(0x519A7C, 0x519A82, &Fix519A7C_CCreature_EquipItem);

	// CCreature::UnequipItem
	WriteMemoryBYTE     (0x51A033 +2, EquipSlotType::Count);
	WriteInstructionJUMP(0x51A197, 0x51A1A2, &Fix51A197_CCreature_UnequipSlot);
	WriteInstructionJUMP(0x51A47F, 0x51A484, &Fix51A47F_CCreature_UnequipItem);

	// CDB::RequestDestroyItem
	WriteRelativeAddress(0x520F89, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x520F90, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);

	// CDB::RequestCrystallizeItem
	WriteRelativeAddress(0x52760B, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x527612, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteMemoryBYTE     (0x527643 +2, EquipSlotType::Count);

	// CDBSocket::ReplyGiveItemToPet
	WriteRelativeAddress(0x54B83E, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x54BBC5, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x54BFB0, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);

	// CDBSocket::LoadItemsPacket
	WriteInstructionCALL(0x571B02, 0x571B09, &CSharedData_CheckEquipSlotOffset_ecx);
	WriteInstructionJUMP(0x571E8C, 0x571E92, &Fix571E8C_CDBSocket_LoadItemsPacket);
	// there seems to be an array of equipped items in CUserSocket
	// loc_571DC0:
	//     rbp = pUser->pSocket
	//     rdx = nSlotType
	//     200h = offset of the array in CUserSocket
	//     eax = pItem->nCharId (which is == pItem->SD->dbid, see sub_62B810)
	// this array is searched for each item being loaded and if present,
	// it is equipped. I have no idea how the array is filled, so until
	// I find out, extended slots probably won't keep items after logout

	// CDBSocket::ReplyLoadPetItems
	WriteInstructionCALL(0x572473, 0x57247A, &CSharedData_CheckEquipSlotOffset_edx);

	// CNPC::EquipItem
	WriteRelativeAddress(0x6BC14F, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x6BC156, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	// .text:00000000006BC1D7                 cmp     dword ptr [rax+rcx*4+128h], 0
	//  doesn't need to be fixed, because (rcx == 'rhand' || rcx == 'chest')

	// CNPC::UnequipItem
	WriteInstructionCALL(0x6C2BB9, 0x6C2BBE, &CItemFactory_FindObjectFix_rdi_rbx_x4);
	WriteMemoryBYTE     (0x6C2BF7 +2, EquipSlotType::Count);

	// NpcSocket::NpcShowBuyPagePacket
	WriteInstructionCALL(0x6E52D2, 0x6E52D9, &CSharedData_CheckEquipSlotOffset_ebx);

	// CPet::DropItem
	WriteRelativeAddress(0x749F71, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x749F78, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteMemoryBYTE     (0x749F9B +2, EquipSlotType::Count);

	// CPet::AutoEquip
	WriteMemoryDWORD    (0x74ADCD +2, EquipSlotType::Count);
	WriteMemoryDWORD    (0x74AE1B +2, EquipSlotType::Count);

	// CPet::SendPetItemList
	WriteRelativeAddress(0x74ED23, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x74EE0F, 3, g_SlotBitTypeArray, 0);
	WriteMemoryBYTE     (0x74EE35 +2, EquipSlotType::Count);
	WriteRelativeAddress(0x74F73E, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x74F757, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x74F8EB, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x74F9AB, 3, g_SlotBitTypeArray, 0);
	WriteMemoryBYTE     (0x74F9D9 +2, EquipSlotType::Count);
	WriteRelativeAddress(0x74FE68, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x74FE76, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);

	// CSkillEffect_p_set_collected::Pump
	WriteInstructionCALL(0x7C4328, 0x7C432F, &Fix7C4328_CSkillEffect_p_set_collected_Pump);

	// CTrade::CheckTradable
	WriteInstructionJUMP(0x7F2EFB, 0x7F2F01, &Fix7F2EFB_CTrade_CheckTradable);

	// User::DropItem
	WriteRelativeAddress(0x80043A, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x800441, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);

	// User::ShowPreview
	// Leaving it here, but it's not finished. There's a local array of items to be
	// tried on (18 slots at [rsp+58h]) which would have to be enlarged to allow...
	// hair accessories, huh? Not worth the effort :)
	//WriteRelativeAddress(0x80A600, 3, g_SlotBitTypeArray, 0);
	//WriteRelativeAddress(0x80A60A, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	//WriteRelativeAddress(0x80A62B, 3, g_SlotBitTypeArray, 0);
	//WriteRelativeAddress(0x80A634, 3, g_SlotBitTypeArray, 0);
	//WriteMemoryBYTE     (0x80A69B +3, EquipSlotType::Count);

	// User::UnequipItem
	WriteInstructionCALL(0x819B03, 0x819B08, &CItemFactory_FindObjectFix_rbx_rdi_x4);

	// User::SendItemList
	WriteRelativeAddress(0x81A04E, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x81A154, 3, g_SlotBitTypeArray, 0);
	WriteMemoryBYTE     (0x81A184 +2, EquipSlotType::Count);
	WriteRelativeAddress(0x81A92C, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x81A93D, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x81AA84, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x81AB3F, 3, g_SlotBitTypeArray, 0);
	WriteMemoryBYTE     (0x81AB65 +2, EquipSlotType::Count);
	WriteRelativeAddress(0x81B033, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x81B044, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);

	// User::OnDieDropItem
	WriteInstructionCALL(0x81C8C2, 0x81C8C9, &CSharedData_CheckEquipSlotOffset_edi);
	WriteInstructionCALL(0x81CA32, 0x81CA39, &CSharedData_CheckEquipSlotOffset_edi);
	WriteInstructionCALL(0x81CDC8, 0x81CDCF, &CSharedData_CheckEquipSlotOffset_edi);
	WriteInstructionCALL(0x81D5D8, 0x81D5DF, &CSharedData_CheckEquipSlotOffset_edi);

	if (bPatchTrade)
	{
		// User::SendPackageSendableList
		WriteRelativeAddress(0x821149, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
		WriteRelativeAddress(0x821231, 3, g_SlotBitTypeArray, 0);
		WriteRelativeAddress(0x821423, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
		WriteInstructionJUMP(0x8212CB, 0x8212D1, &Fix8212CB_User_SendPackageSendableList);
	}

	// User::EquipItem
	WriteMemoryBYTE     (0x8259CF +2, EquipSlotType::Count);
	WriteRelativeAddress(0x8259E4, 3, g_SlotBitTypeArray, 0);
	WriteRelativeAddress(0x8259EB, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteInstructionCALL(0x825BB5, 0x825BBA, &CItemFactory_FindObjectFix_rbp_r12_x4);
	WriteInstructionCALL(0x825BDE, 0x825BE3, &Fix825BDE_User_EquipItem);
	WriteInstructionJUMP(0x825CF0, 0x825CF6, &Fix825CF0_User_EquipItem);

	// User::UnequipItem
	WriteInstructionJUMP(0x826BDB, 0x826BE1, &Fix826BDB_User_UnequipItem);
	WriteMemoryBYTE     (0x826D36 +3, EquipSlotType::Count);

	// User::SendPrivateStoreManageList
	if (bPatchTrade && bExtendLocalArrays && EquipSlotType::Count*4 < 256)
	{
		int nOriginalStackSize = 0;
		ReadMemoryDWORD(0x829555 +1, &nOriginalStackSize);

		int nItemArraySize = ALIGN_OWORD(EquipSlotType::Count*4);
		int nExtendedStackSize = nOriginalStackSize + 0x30 + nItemArraySize*2;
		int nItemIdArrayOffset = nOriginalStackSize + 0x28;
		int nItemTypeArrayOffset = nItemIdArrayOffset + nItemArraySize;

		WriteMemoryDWORD(0x829555 +1, nExtendedStackSize);
		WriteMemoryDWORD(0x82A981 +3, nExtendedStackSize);

		// arg_0 shadow space must stay where it was
		WriteMemoryDWORD(0x82A007 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x82A011 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x82A08E +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x82A4A8 +4, nExtendedStackSize + arg_0);

		WriteMemoryDWORD(0x829717 +4, nItemIdArrayOffset);
		WriteMemoryDWORD(0x829730 +4, nItemIdArrayOffset);
		WriteInstructionCALL(0x829755, 0x82975A, &CItemFactory_FindObjectFix_rbp_rbx_x1);
		WriteMemoryDWORD(0x829770 +3, nItemTypeArrayOffset);
		WriteMemoryDWORD(0x82977C +4, nItemTypeArrayOffset);
		WriteMemoryBYTE (0x8297B7 +3, EquipSlotType::Count*4);

		WriteMemoryDWORD(0x829C91 +3, nItemIdArrayOffset);
		WriteMemoryBYTE (0x829C9D +3, EquipSlotType::Count);

		WriteMemoryDWORD(0x82A334 +3, nItemIdArrayOffset);
		WriteMemoryBYTE (0x82A340 +3, EquipSlotType::Count);
	}

	// User::PrivateStoreListReq
	if (bPatchTrade && bExtendLocalArrays && EquipSlotType::Count*4 < 256)
	{
		int nOriginalStackSize = 0;
		ReadMemoryDWORD(0x82E9D0 +1, &nOriginalStackSize);

		int nItemArraySize = ALIGN_OWORD(EquipSlotType::Count*4);
		int nExtendedStackSize = nOriginalStackSize + 0x30 + nItemArraySize*2;
		int nItemIdArrayOffset = nOriginalStackSize + 0x28;
		int nItemTypeArrayOffset = nItemIdArrayOffset + nItemArraySize;

		WriteMemoryDWORD(0x82E9D0 +1, nExtendedStackSize);
		WriteMemoryDWORD(0x82F6A5 +3, nExtendedStackSize);

		WriteMemoryDWORD(0x82EBDB +4, nItemIdArrayOffset);
		WriteMemoryDWORD(0x82EC00 +4, nItemIdArrayOffset);
		WriteInstructionCALL(0x82EC26, 0x82EC2B, &CItemFactory_FindObjectFix_r14_rbx_x1);
		WriteMemoryDWORD(0x82ED04 +3, nItemTypeArrayOffset);
		WriteMemoryDWORD(0x82ED10 +4, nItemTypeArrayOffset);
		WriteMemoryBYTE (0x82ED4B +3, EquipSlotType::Count*4);

		WriteMemoryDWORD(0x82F004 +3, nItemIdArrayOffset);
		WriteMemoryBYTE (0x82F010 +3, EquipSlotType::Count);
	}

	// User::PrivateStoreBuyListReq
	if (bPatchTrade && bExtendLocalArrays && EquipSlotType::Count*4 < 256)
	{
		int nOriginalStackSize = 0;
		ReadMemoryDWORD(0x82F775 +1, &nOriginalStackSize);

		int nItemArraySize = ALIGN_OWORD(EquipSlotType::Count*4);
		int nExtendedStackSize = nOriginalStackSize + 0x30 + nItemArraySize*2;
		int nItemIdArrayOffset = nOriginalStackSize + 0x28;
		int nItemTypeArrayOffset = nItemIdArrayOffset + nItemArraySize;

		WriteMemoryDWORD(0x82F775 +1, nExtendedStackSize);
		WriteMemoryDWORD(0x830638 +3, nExtendedStackSize);

		// arg_0 shadow space must stay where it was
		WriteMemoryDWORD(0x83019D +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x830242 +4, nExtendedStackSize + arg_0);

		WriteMemoryDWORD(0x82FC07 +4, nItemIdArrayOffset);
		WriteMemoryDWORD(0x82FC98 +4, nItemIdArrayOffset);
		WriteInstructionCALL(0x82FCB4, 0x82FCB9, &Fix82FCB4_User_PrivateStoreBuyListReq);
		WriteMemoryDWORD(0x82FCC6 +3, nItemTypeArrayOffset);
		WriteMemoryDWORD(0x82FCD2 +4, nItemTypeArrayOffset);
		WriteMemoryBYTE (0x82FCDE +3, EquipSlotType::Count*4);

		WriteMemoryDWORD(0x82FDD0 +3, nItemIdArrayOffset);
		WriteMemoryBYTE (0x82FDDC +3, EquipSlotType::Count);
	}

	// User::PrivateStoreBuyBuy
	if (bPatchTrade && bExtendLocalArrays && EquipSlotType::Count*4 < 256)
	{
		int nOriginalStackSize = 0;
		ReadMemoryDWORD(0x83E17A +1, &nOriginalStackSize);

		int nItemArraySize = ALIGN_OWORD(EquipSlotType::Count*4);
		int nExtendedStackSize = nOriginalStackSize + 0x30 + nItemArraySize*2;
		int nItemIdArrayOffset = nOriginalStackSize + 0x28;
		int nItemTypeArrayOffset = nItemIdArrayOffset + nItemArraySize;

		WriteMemoryDWORD(0x83E17A +1, nExtendedStackSize);
		WriteMemoryDWORD(0x83FC05 +3, nExtendedStackSize);

		// arg_0, arg_10 shadow space must stay where it was
		WriteMemoryDWORD(0x83EED8 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F114 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F1E7 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F37D +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F5C1 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F7C5 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F94A +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F969 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F988 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F9A7 +4, nExtendedStackSize + arg_0);
		WriteMemoryDWORD(0x83F7D0 +4, nExtendedStackSize + arg_10);

		WriteMemoryDWORD(0x83E451 +4, nItemIdArrayOffset);
		WriteMemoryDWORD(0x83E473 +4, nItemIdArrayOffset);
		WriteInstructionCALL(0x83E499, 0x83E49E, &CItemFactory_FindObjectFix_r15_rbx_x1);
		WriteMemoryDWORD(0x83E4B4 +3, nItemTypeArrayOffset);
		WriteMemoryDWORD(0x83E4C4 +3, nItemTypeArrayOffset);
		WriteMemoryBYTE (0x83E4FE +3, EquipSlotType::Count*4);

		WriteMemoryDWORD(0x83EB60 +3, nItemIdArrayOffset);
		WriteMemoryBYTE (0x83EB6C +3, EquipSlotType::Count);
	}

	if (bPatchTrade)
	{
		// CUserSocket::SellPacket
		WriteInstructionJUMP(0x87A74F, 0x87A755, &Fix87A74F_CUserSocket_SellPacket);
	}

	// CWarehouseDeposit::RequestEx
	WriteInstructionCALL(0x8A5CE2, 0x8A5CE9, &CSharedData_CheckEquipSlotOffset_edi);
	WriteMemoryDWORD    (0x8A5D00 +3, (int)g_SlotBitTypeArray - IMAGEBASE);
	WriteMemoryBYTE     (0x8A5D0C +3, EquipSlotType::Count);
	WriteInstructionCALL(0x8A5D64, 0x8A5D6B, &Fix8A5D64_CWarehouseDeposit_RequestEx);

	// CWarehouseDeposit::Request
	WriteInstructionCALL(0x8A751F, 0x8A7526, &CSharedData_CheckEquipSlotOffset_edi);
	WriteMemoryDWORD    (0x8A7540 +3, (int)g_SlotBitTypeArray - IMAGEBASE);
	WriteMemoryBYTE     (0x8A754C +3, EquipSlotType::Count);
	WriteInstructionCALL(0x8A75A4, 0x8A75AB, &Fix8A75A4_CWarehouseDeposit_Request);

	// CWarehouseDeposit::SendList
	WriteRelativeAddress(0x8A9DD4, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x8A9EB3, 3, g_SlotBitTypeArray, 0);
	WriteInstructionCALL(0x8A9FC2, 0x8A9FC9, &CSharedData_CheckEquipSlotOffset_ebx);
	WriteRelativeAddress(0x8AA217, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x8AA220, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);

	// CWarehouseDeposit::SendListEx
	WriteRelativeAddress(0x8AA9EF, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
	WriteRelativeAddress(0x8AAACA, 3, g_SlotBitTypeArray, 0);
	WriteInstructionCALL(0x8AAC02, 0x8AAC09, &CSharedData_CheckEquipSlotOffset_ebx);
	WriteRelativeAddress(0x8AADDD, 3, g_SlotBitTypeArray + EquipSlotType::Count, 0);
}

void CSharedFactory::ExtendPledgeSharedData()
{
	//Extending CPledgeSharedData
	DWORD dSize = sizeof(CPledgeSharedData);
	WriteMemoryDWORD(0x762DD9, dSize);
	WriteMemoryDWORD(0x762E07, dSize);
	WriteMemoryDWORD(0x762E17, dSize);
	WriteMemoryDWORD(0x76324D, dSize);
	WriteMemoryDWORD(0x763258, dSize);
	WriteMemoryDWORD(0x76326C, dSize);
	WriteMemoryDWORD(0x78D3CD, dSize);  
	WriteMemoryDWORD(0x78D4FA, dSize); 
	WriteMemoryDWORD(0x78D511, dSize); 
	dSize = dSize - 0x124;
	WriteMemoryDWORD(0x76B73B, dSize); //Clearing new memory size
}

void CSharedFactory::ReallocateAbnormalTable()
{
	const int index = offsetof(CSharedData, AbnormalTable);
	const int count = CSharedData::ABNORMALS;

	//Fix AddAbnormalStatus 
	WriteMemoryDWORD(0x4D96E7, index);
	WriteMemoryBYTE (0x4D9701, count);
	WriteMemoryDWORD(0x4D970C, index);
	WriteMemoryDWORD(0x4D9714, index + 4);

	//Fix DeleteAllAbnormalStatus
	WriteMemoryDWORD(0x4D234F, index);
	WriteMemoryBYTE (0x4D2354, count);

	//Fix DeleteAbnormalStatus
	WriteMemoryDWORD(0x4D95AE, index);
	WriteMemoryBYTE (0x4D95C2, count);
	WriteMemoryDWORD(0x4D95CD, index);

	//Fix InfectedSkillBy
		//AddAbnormal
	WriteMemoryDWORD(0x5065E7, index);
	WriteMemoryBYTE (0x506601, count);
	WriteMemoryDWORD(0x50660D, index);
	WriteMemoryDWORD(0x506615, index + 4);
		//Delete Abnormal
	WriteMemoryDWORD(0x505AD5, index);
	WriteMemoryBYTE (0x505AF0, count);
	WriteMemoryDWORD(0x505AFC, index);

	//AddAbnormal2 - Check Amount of buffs
	//WriteHook(0xE9, 0x5057FB, (DWORD)CheckBuffAmount, 4);

	//Fix SendAbnormalStatus
	WriteMemoryBYTE (0x827D54, count);

	//Fix SpelledInfoChanged 
	WriteMemoryBYTE (0x850F7B, count);

	//Fix CCreature::CCreature() - Delete All Abnormals
	WriteMemoryDWORD(0x4D6C46, index);
	WriteMemoryBYTE (0x4D6C4B, count);

	//Fix CCreature::CCreature(&other) - Delete All Abnormals
	WriteMemoryDWORD(0x4D817F, index);
	WriteMemoryBYTE (0x4D8184, count);

	//Fix CCreature::DispelByCategory
	WriteMemoryDWORD(0x5018A3, index);
	WriteMemoryBYTE (0x5018B6, count);
	WriteMemoryDWORD(0x5018BE, index);

	//Fix CCreature::DispelAll
	WriteMemoryDWORD(0x502555, index);
	WriteMemoryBYTE (0x50256F, count);
	WriteMemoryDWORD(0x502578, index);

	//Fix CCreature::DispelAllByGM
	WriteMemoryDWORD(0x502ECD, index);
	WriteMemoryBYTE (0x502EE0, count);
	WriteMemoryDWORD(0x502EE8, index);

	//Fix CCreature::DispelByName
	WriteMemoryDWORD(0x5039B8, index);
	WriteMemoryBYTE (0x5039CF, count);
	WriteMemoryDWORD(0x5039D8, index);

	//Fix CCreature::DispelBySlot
	WriteMemoryDWORD(0x504553, index);
	WriteMemoryBYTE (0x504566, count);
	WriteMemoryDWORD(0x50456F, index);

	//Fix User::DeleteYongmaAbnormalStatus
	WriteMemoryDWORD(0x831964, index);
	WriteMemoryBYTE (0x831977, count);
	WriteMemoryDWORD(0x831980, index);

	//Fix User::OnChangeSubjobEnd - Delete All Abnormals
	WriteMemoryDWORD(0x854191, index);
	WriteMemoryBYTE (0x854196, count);
}

void CSharedFactory::ReallocateQuests()
{
	const int count = CSharedData::QUESTS;
	const int countMem = count * 16;
	const int countMemSmall = count * 8;
	const int index = offsetof(CSharedData, Quests);
	const int indexEnd = index + countMem;

	// inline bool CSharedCreatureData::SetJournal(int nQuestID , int nJournal)
	// .text:00000000004298D5                 lea     rax, [rdi+1E4h]
	WriteMemoryDWORD(0x4298D8, index);
	// .text:00000000004298DC                 lea     rcx, [rdi+2E4h]
	WriteMemoryDWORD(0x4298DF, indexEnd);

	// inline bool  CSharedCreatureData::SetFlagJournal(int nQuestID , int nFlag) 
	// .text:0000000000429A85                 lea     rdx, [rsi+1E4h]
	WriteMemoryDWORD(0x429A88, index);
	// .text:0000000000429A8C                 lea     rax, [rsi+2E4h]
	WriteMemoryDWORD(0x429A8F, indexEnd);

	// inline bool  CSharedCreatureData::ResetFlagJournal(int nQuestID , int nFlag)
	// .text:0000000000429C45                 lea     rdx, [rsi+1E4h]
	WriteMemoryDWORD(0x429C48, index);
	// .text:0000000000429C4C                 lea     rax, [rsi+2E4h]
	WriteMemoryDWORD(0x429C4F, indexEnd);

	// inline bool CSharedCreatureData::RemoveMemo(int nQuestID )
	// .text:0000000000429DFE                 lea     rax, [rdi+1E4h]
	WriteMemoryDWORD(0x429E01, index);
	// .text:0000000000429E05                 lea     rcx, [rdi+2E4h]
	WriteMemoryDWORD(0x429E08, indexEnd);

	// inline bool  CSharedCreatureData::HaveMemo(int nQuestID)
	// .text:0000000000431C60                 lea     rdx, [rdi+1E4h]
	WriteMemoryDWORD(0x431C63, index);
	// .text:0000000000431C6A                 lea     r8, [rdi+2E4h]
	WriteMemoryDWORD(0x431C6D, indexEnd);

	// inline bool  CSharedCreatureData::SetMemoState(int nQuestID , int nSlot, int nState)
	// .text:0000000000431F27                 lea     rbx, [r13+1E4h]
	WriteMemoryDWORD(0x431F2A, index);
	// .text:0000000000431F31                 lea     rdi, [r13+2E4h]
	WriteMemoryDWORD(0x431F34, indexEnd);

	// bool CSCharacterInfoPacket(CSocket* pSocket, const unsigned char* packet)
	// .text:000000000047B08A                 mov     eax, [rax+22Ch]
	WriteMemoryDWORD(0x47B08C, index + 0x48);
	// .text:000000000047B097                 mov     eax, [rcx+228h]
	WriteMemoryDWORD(0x47B099, index + 0x44);
	// .text:000000000047B0A4                 mov     eax, [rdx+224h]
	WriteMemoryDWORD(0x47B0A6, index + 0x40);
	
	// .text:000000000047B0AE                 mov     eax, [rdi+21Ch]
	WriteMemoryDWORD(0x47B0B0, index + 0x38);
	// .text:000000000047B0B8                 mov     eax, [r8+218h]
	WriteMemoryDWORD(0x47B0BB, index + 0x34);
	// .text:000000000047B0C3                 mov     eax, [r9+214h]
	WriteMemoryDWORD(0x47B0C6, index + 0x30);

	// .text:000000000047B0CE                 mov     eax, [r10+20Ch]
	WriteMemoryDWORD(0x47B0D1, index + 0x28);
	// .text:000000000047B0D9                 mov     eax, [r11+208h]
	WriteMemoryDWORD(0x47B0DC, index + 0x24);
	// .text:000000000047B0E4                 mov     eax, [rbx+204h]
	WriteMemoryDWORD(0x47B0E6, index + 0x20);

	// .text:000000000047B0EE                 mov     eax, [rsi+1FCh]
	WriteMemoryDWORD(0x47B0F0, index + 0x18);
	// .text:000000000047B0F8                 mov     eax, [rbp+1F8h]
	WriteMemoryDWORD(0x47B0FA, index + 0x14);
	// .text:000000000047B102                 mov     eax, [r12+1F4h]
	WriteMemoryDWORD(0x47B106, index + 0x10);

	// .text:000000000047B10E                 mov     eax, [r13+1ECh]
	WriteMemoryDWORD(0x47B111, index + 0x08);
	// .text:000000000047B119                 mov     eax, [r14+1E8h]
	WriteMemoryDWORD(0x47B11C, index + 0x04);
	// .text:000000000047B124                 mov     r9d, [r15+1E4h]
	WriteMemoryDWORD(0x47B127, index + 0x00);

	// void CDB::SaveQuestInfo(User *pUser)
	// .text:0000000000538980                 mov     eax, [rbx+r8+1F0h]
	WriteMemoryDWORD(0x538984, index + 0x0C);
	// .text:000000000053898C                 mov     eax, [rbx+r8+1ECh]
	WriteMemoryDWORD(0x538990, index + 0x08);
	// .text:0000000000538998                 mov     eax, [rbx+r8+1E8h]
	WriteMemoryDWORD(0x53899C, index + 0x04);
	// .text:00000000005389A4                 mov     r9d, [rbx+r8+1E4h]
	WriteMemoryDWORD(0x5389A8, index + 0x00);
	// .text:00000000005389C2                 cmp     rbx, 100h
	WriteMemoryDWORD(0x5389C5, countMem);

	// static bool LoadQuestPacket(CDBSocket *socket, const unsigned char *packet)
	// .text:0000000000552840                 mov     edi, 1F0h
	WriteMemoryDWORD(0x552841, index + 0x0C);
	// .text:0000000000552848                 lea     ebp, [rbx+10h]
	WriteMemoryBYTES(0x552848, 7, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90);
	WriteMemoryDWORD(0x552849, count);

	// .text:0000000000552857                 lea     rax, [rbx+rdx+1F0h]
	WriteMemoryDWORD(0x55285B, index + 0x0C);
	// .text:000000000055285F                 lea     rcx, [rbx+rdx+1ECh]
	WriteMemoryDWORD(0x552863, index + 0x08);
	// .text:0000000000552867                 lea     r9, [rbx+rdx+1E8h]
	WriteMemoryDWORD(0x55286B, index + 0x04);
	// .text:000000000055286F                 lea     r8, [rbx+rdx+1E4h]
	WriteMemoryDWORD(0x552873, index + 0x00);

	// CSharedCreatureData::GetMemoState(int nQuestID, int nSlot) 
	// .text:00000000006D04FF                 lea     rax, [rbx+1E4h]
	WriteMemoryDWORD(0x6D0502, index);
	// .text:00000000006D0506                 lea     rcx, [rbx+2E4h]
	WriteMemoryDWORD(0x6D0509, indexEnd);

	// void User::SendQuestList()
	// quest list
	// .text:000000000081EBF8                 mov     r9d, [rbx+rax+1E4h]
	WriteMemoryDWORD(0x81EBFC, index);
	// .text:000000000081EC00                 mov     r8d, [rbx+rax+1F0h]
	WriteMemoryDWORD(0x81EC04, index+0x0C);
	// .text:000000000081EC0D                 mov     edx, 80h
	WriteMemoryDWORD(0x81EC0E, countMemSmall);				// increase buffer, which is used for assembled packet with list of quests
	// .text:000000000081EC36                 cmp     rbx, 100h
	WriteMemoryDWORD(0x81EC39, countMem);
	// move rest of the list
	// .text:000000000081EC43                 mov     [rsp+0DB8h+var_CC8], r15b
	WriteMemoryDWORD(0x81EC47, 0x70 + countMemSmall);
	// .text:000000000081EC4D                 mov     r8d, 0C7Fh      ; size_t
	WriteMemoryDWORD(0x81EC4F, 0xCFF - countMemSmall);
	// .text:000000000081EC53                 lea     rcx, [rsp+0DB8h+var_CC7]
	WriteMemoryDWORD(0x81EC57, 0x71 + countMemSmall);
	// quest items list
	// .text:000000000081EDAB                 mov     edx, 0C80h
	WriteMemoryDWORD(0x81EDAC, 0xD00-countMemSmall);		// whole original buffer 0xD00 (0xC80 + 0x80)
	// .text:000000000081EDB6                 lea     rcx, [rsp+rax+0DB8h+var_CC8]
	WriteMemoryDWORD(0x81EDBA, 0x70 + countMemSmall);
	// CSocket->Send
	// .text:000000000081F012                 lea     rdx, [rsp+0DB8h+var_CC8]
	WriteMemoryDWORD(0x81F016, 0x70 + countMemSmall);
	// .text:000000000081F059                 lea     rcx, [rsp+0DB8h+var_CC8]
	WriteMemoryDWORD(0x81F05D, 0x70 + countMemSmall);

	// void User::OnChangeSubJobEnd(bool bCreate)
	// .text:0000000000855077                 lea     rax, [rbp+1E4h]
	WriteMemoryDWORD(0x85507A, index);
	// .text:000000000085507E                 lea     rcx, [rbp+2E4h]
	WriteMemoryDWORD(0x855081, indexEnd);
}

void CSharedFactory::Copy(CSharedData *dest, CSharedData *source)
{
	__try
	{
		typedef void (*t)(CSharedData*, CSharedData*);
		t f = (t)0x78C8B0;
		f(dest, source);

		dest->nExp64 = source->nExp64;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CLog::Add(CLog::red, "Error in copy NPC");
	}
}

bool SharedFactory::CCreature_EquipItemExt(CCreature* pCreature, CItem* pItem, int nSlotType)
{
	int nItemIndex = pItem->SD->itemIndex;

	switch (nSlotType)
	{
		case EquipSlotType::hair:
			if (pCreature->SD->EquippedItemIndex(EquipSlotType::hairall) != -1)
			{
				pCreature->SD->EquippedItemIndex(EquipSlotType::hairdeco) = -1;
				pCreature->SD->EquippedItemIndex(EquipSlotType::hairall) = -1;
			}
			pCreature->SD->EquippedItemIndex(EquipSlotType::hair) = nItemIndex;
			return true;

		case EquipSlotType::hairdeco:
			if (pCreature->SD->EquippedItemIndex(EquipSlotType::hairall) != -1)
			{
				pCreature->SD->EquippedItemIndex(EquipSlotType::hair) = -1;
				pCreature->SD->EquippedItemIndex(EquipSlotType::hairall) = -1;
			}
			pCreature->SD->EquippedItemIndex(EquipSlotType::hairdeco) = nItemIndex;
			return true;

		case EquipSlotType::hairall:
			pCreature->SD->EquippedItemIndex(EquipSlotType::hair) = nItemIndex;
			pCreature->SD->EquippedItemIndex(EquipSlotType::hairdeco) = -1;
			pCreature->SD->EquippedItemIndex(EquipSlotType::hairall) = nItemIndex;
			return true;

		case EquipSlotType::rbracelet:
			pCreature->SD->EquippedItemIndex(EquipSlotType::rbracelet) = nItemIndex;
			return true;

		case EquipSlotType::lbracelet:
			pCreature->SD->EquippedItemIndex(EquipSlotType::lbracelet) = nItemIndex;
			return true;
	}

	return false;
}

/*
	CCreature_IsEquippedExt is only called for hair, dress, and extended slots.
	Other C4 slots are handled by the original CCreature::IsEquipped function.

	CCreature::IsEquipped(int, SlotType) treats several slot types in the same
	way. It looks into all slots in a group, and returns the one which contains
	the item in question. For example:

		IsEquipped(indexDoomTunic, slot_legs) can return slot_chest.
*/
int SharedFactory::CCreature_IsEquippedExt(CCreature* pCreature, int nItemIndex, int nSlotType)
{
	switch (nSlotType)
	{
		case EquipSlotType::hair:
		case EquipSlotType::hairdeco:
		case EquipSlotType::hairall:
			if (nItemIndex == pCreature->SD->EquippedItemIndex(EquipSlotType::hair))
				return EquipSlotType::hair;
			if (nItemIndex == pCreature->SD->EquippedItemIndex(EquipSlotType::hairdeco))
				return EquipSlotType::hairdeco;
			if (nItemIndex == pCreature->SD->EquippedItemIndex(EquipSlotType::hairall))
				return EquipSlotType::hairall;
			break;

		case EquipSlotType::alldress:
		case EquipSlotType::rbracelet:
		case EquipSlotType::lbracelet:
			if (nItemIndex == pCreature->SD->EquippedItemIndex(EquipSlotType(nSlotType)))
				return nSlotType;
			break;
	}

	// if the item is not found, return invalid slot type
	return EquipSlotType::Count;
}

bool SharedFactory::CCreature_IsEquippedExtByObjectId(CCreature* pCreature, int nItemObjectId)
{
	for (int nSlot = EquipSlotType::LastC4; (++nSlot) <= EquipSlotType::Last; )
	{
		int nItemIndex = pCreature->SD->EquippedItemIndex(nSlot);
		CSPointer<CItem> spItem = CItem::FindItemSP(nItemIndex);

		if (spItem && spItem->nObjectID == nItemObjectId)
			return true;
	}

	return false;
}

void SharedFactory::CCreature_ValidateAttachedSkillsExt(CCreature* pCreature,
														CSkillKeys* pSkillKeys)
{
	if (!pCreature->IsValidUser())
		return;

	// Add skills from items equipped in extended slots. Only item_skill=[x]
	// field is used, other item skills are not suitable for extended slots.

	for (int nSlot = EquipSlotType::LastC4; (++nSlot) <= EquipSlotType::Last; )
	{
		CItemInfo* pItemInfo = pCreature->GetEquippedItemInfo(nSlot);

		if (pItemInfo == 0)
			continue;
		if (pItemInfo->item_skill_id <= 0)
			continue;
		if (pItemInfo->crystalType > pCreature->allowed_grade)
			continue;

		// this conversion looks dirty, but CSkillKey really *is* there
		pSkillKeys->push_back((const CSkillKey&)pItemInfo->item_skill_id);
		CompileTimeSizeCheck(CSkillKey, 4);
	}

	// Note: this could be a good place for adding augment skills,
	// I'm only not sure how to make the skill unavailable immediately
	// after equipping the weapon (don't know since which update, but
	// it should be disabled for 30s or so).
}

void SharedFactory::User_EquipItemCheckExt(CCreature* pCreature, CItem* pItem, int nSlotType)
{
	switch (nSlotType)
	{
		case EquipSlotType::hair:
		case EquipSlotType::hairdeco:
			if (CItem* pItem = pCreature->GetEquippedItem(EquipSlotType::hairall))
				pCreature->inventory.SetInventoryChanged(pItem, INVENTORY_MODIFY);
			break;

		case EquipSlotType::hairall:
			if (CItem* pItem = pCreature->GetEquippedItem(EquipSlotType::hair))
				pCreature->inventory.SetInventoryChanged(pItem, INVENTORY_MODIFY);
			if (CItem* pItem = pCreature->GetEquippedItem(EquipSlotType::hairdeco))
				pCreature->inventory.SetInventoryChanged(pItem, INVENTORY_MODIFY);
			break;
	}
}
