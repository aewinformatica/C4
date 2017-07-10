#include "CAugmentationSystem.h"

void CAugmentationSystem::Initialize()
{
	WriteInstruction(0x442CB9, (INT32)&CAugmentationSystem::SaveItem1, 0, 0xE9);
	WriteInstruction(0x442D37, (INT32)&CAugmentationSystem::SaveItem2, 0, 0xE9);

	WriteInstruction(0x4B8A3F, (INT32)&CAugmentationSystem::WareHouseSendList, 0, 0xE9);
}

__declspec(naked) void CAugmentationSystem::SaveItem1()
{
	__asm
	{
		mov		ecx, esi
		call	CItem::SaveItemExInfo

		lea		ecx, [esp+10h]
		mov		eax, 428A80h
		call	eax
		mov		eax, 442CC2h
		jmp		eax
	}
}

__declspec(naked) void CAugmentationSystem::SaveItem2()
{
	__asm
	{
		mov		ecx, esi
		call	CItem::SaveItemExInfo

		lea		ecx, [esp+10h]
		mov		eax, 428A80h
		call	eax
		mov		eax, 442D40h
		jmp		eax
	}
}

__declspec(naked) void CAugmentationSystem::WareHouseSendList()
{
	__asm
	{
		push	ecx		// CItem
		mov     eax, 2000h
		sub     eax, ebx
		push    eax		// buflen
		lea     ecx, [esp+ebx+58h]
		push    ecx		// buffer
		
		call	CAugmentationSystem::WareHouseSendListAssemble
		add		esp, 0Ch

		cmp     edi, 39h
		mov     esi, eax
		
		mov		eax, 4B8A9Ch
		jmp		eax
	}
}

int CAugmentationSystem::WareHouseSendListAssemble(char *buffer, int bufLen, CItem *pItem)
{
	return Assemble(buffer, bufLen, "ddddddddddddddddddd",
		pItem->nItemID, pItem->nItemType, pItem->nAmount, pItem->nEnchant, pItem->nDamaged, pItem->nBless,
		pItem->nIdent, pItem->nWished,
		pItem->exInfo.locationSlot, pItem->exInfo.augmentationId, pItem->exInfo.mana, pItem->exInfo.nAtkAttrElement,
		pItem->exInfo.nAtkAttrValue, pItem->exInfo.nDefAttrFire, pItem->exInfo.nDefAttrWater, pItem->exInfo.nDefAttrWind,
		pItem->exInfo.nDefAttrEarth, pItem->exInfo.nDefAttrHoly, pItem->exInfo.nDefAttrUnholy);
}


// .text:004B8790 CWareHouse__SendList
// .text:004B82E0 CWareHouse__SendDepositItemsList
// .text:004919C0 SaveItemsPacket
