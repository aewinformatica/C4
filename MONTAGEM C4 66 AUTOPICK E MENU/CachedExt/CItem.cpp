#include "Global.h"

#define DEBUG 0

__declspec(naked)
CItem* CItem::Alloc_442640(size_t)
{
	__asm
	{
		mov     dword ptr [esp+4], size CItem
		mov     edx, 442640h
		jmp     edx
	}
}

__declspec(naked)
CItem* CItem::Alloc_44B290(intptr_t, size_t, size_t , const wchar_t*)
{
	__asm
	{
		mov     dword ptr [esp+4], size CItem
		mov     edx, 44B290h
		jmp     edx
	}
}

CItem* CItem::ConstructBlank(CItem* pItem, int nItemID)
{
	typedef CItem* (__thiscall *FConstructor)(CItem*, int);
	FConstructor(0x442990)(pItem, nItemID);

	pItem->exInfo.locationSlot = 0;
	pItem->exInfo.augmentationId = 0;
	pItem->exInfo.mana = -1;
	pItem->exInfo.nAtkAttrElement = -2;
	pItem->exInfo.nAtkAttrValue = 0;
	pItem->exInfo.nDefAttrFire = 0;
	pItem->exInfo.nDefAttrWater = 0;
	pItem->exInfo.nDefAttrWind = 0;
	pItem->exInfo.nDefAttrEarth = 0;
	pItem->exInfo.nDefAttrHoly = 0;
	pItem->exInfo.nDefAttrUnholy = 0;

	return pItem;
}

__declspec(naked)
CItem* CItem::ConstructCopy(CItem* pItem, int nItemID, int nCharID, int nItemType, int nAmount, int nEnchant, int nDamaged, int nBless, int nIdent, int nWished, int nWarehouse)
{
	CItem*  pNewItem;
	CItem*  pSrcItem;
	void*   _esi;

	__asm
	{
		push    ebp
		mov     ebp, esp
		sub     esp, __LOCAL_SIZE
		mov     [_esi], esi
		mov     [pSrcItem], edi
		mov     [pNewItem], ecx

		// call original constructor
		sub     esp, 40
		lea     esi, [ebp+8]
		lea     edi, [esp]
		mov     ecx, 40 >> 2
		rep movsd
		mov     ecx, [pNewItem]
		mov     edx, 443950h
		call    edx

		// copy exInfo
		mov     edi, [pNewItem]
		lea     edi, [edi+CItem::exInfo]
		mov     esi, [pSrcItem]
		lea     esi, [esi+CItem::exInfo]
		mov     ecx, size CItemEx >> 2
		rep movsd

		// return pItem
		mov     eax, [pNewItem]
		mov     edi, [pSrcItem]
		mov     esi, [_esi]
		mov     esp, ebp
		pop     ebp
		ret     40
	}
}

CItem* CItem::ConstructLoad(CItem* pItem, int nItemID, int nCharID, int nItemType, int nAmount, int nEnchant, int nDamaged, int nBless, int nIdent, int nWished, int nWarehouse)
{
	typedef CItem* (__thiscall *FConstructor)(CItem*, int, int, int, int, int, int, int, int, int, int);
	FConstructor(0x443950)(pItem, nItemID, nCharID, nItemType, nAmount, nEnchant, nDamaged, nBless, nIdent, nWished, nWarehouse);

	pItem->exInfo.locationSlot = -1;
	pItem->exInfo.augmentationId = -1;
	pItem->exInfo.mana = -1;
	pItem->exInfo.nAtkAttrElement = -1;
	pItem->exInfo.nAtkAttrValue = -1;
	pItem->exInfo.nDefAttrFire = -1;
	pItem->exInfo.nDefAttrWater = -1;
	pItem->exInfo.nDefAttrWind = -1;
	pItem->exInfo.nDefAttrEarth = -1;
	pItem->exInfo.nDefAttrHoly = -1;
	pItem->exInfo.nDefAttrUnholy = -1;

	pItem->LoadItemExInfo();

	return pItem;
}

void CItem::Destruct(CItem* pItem, bool bDelete)
{
	// nothing to do, just call the original destructor
	typedef void (__thiscall *FDestructor)(CItem*, bool);
	FDestructor(0x442950)(pItem, bDelete);
}

void CItem::LoadItemExInfo()
{
	DBConn dbc;

	int nLocationSlot = 0;
	int nAugmentationId = 0;
	int nMana = 0;
	int nAtkAttrElement = 0;
	int nAtkAttrValue = 0;
	int nDefAttrFire = 0;
	int nDefAttrWater = 0;
	int nDefAttrWind = 0;
	int nDefAttrEarth = 0;
	int nDefAttrHoly = 0;
	int nDefAttrUnholy = 0;

	dbc.BindD(&nLocationSlot);
	dbc.BindD(&nAugmentationId);
	dbc.BindD(&nMana);
	dbc.BindD(&nAtkAttrElement);
	dbc.BindD(&nAtkAttrValue);
	dbc.BindD(&nDefAttrFire);
	dbc.BindD(&nDefAttrWater);
	dbc.BindD(&nDefAttrWind);
	dbc.BindD(&nDefAttrEarth);
	dbc.BindD(&nDefAttrHoly);
	dbc.BindD(&nDefAttrUnholy);

	if (dbc.Execute(L"EXEC lin_LoadItemExByItemId %d", this->nItemID))
	{
		if (dbc.Fetch())
		{
			this->exInfo.locationSlot = nLocationSlot;
			this->exInfo.augmentationId = nAugmentationId;
			this->exInfo.mana = nMana;
			this->exInfo.nAtkAttrElement = nAtkAttrElement;
			this->exInfo.nAtkAttrValue = nAtkAttrValue;
			this->exInfo.nDefAttrFire = nDefAttrFire;
			this->exInfo.nDefAttrWater = nDefAttrWater;
			this->exInfo.nDefAttrWind = nDefAttrWind;
			this->exInfo.nDefAttrEarth = nDefAttrEarth;
			this->exInfo.nDefAttrHoly = nDefAttrHoly;
			this->exInfo.nDefAttrUnholy = nDefAttrUnholy;
		}
	}
}

void CItem::SaveItemExInfo()
{
	DBConn dbc;

	if (!dbc.Execute(L"EXEC lin_UpdateUserItemEx %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		this->exInfo.locationSlot,
		this->exInfo.augmentationId,
		this->exInfo.mana,
		this->exInfo.nAtkAttrElement,
		this->exInfo.nAtkAttrValue,
		this->exInfo.nDefAttrFire,
		this->exInfo.nDefAttrWater,
		this->exInfo.nDefAttrWind,
		this->exInfo.nDefAttrEarth,
		this->exInfo.nDefAttrHoly,
		this->exInfo.nDefAttrUnholy,
		this->nItemID))
	{
		if(DEBUG)
			CLog::Add(CLog::red, L"Error saving item ex information, itemid=%d", this->nItemID);
	}
}

__declspec(naked) CItem* CItem::LoadItem(unsigned int nItemID)
{
	__asm
	{
		mov		eax, 444190h
		jmp		eax
	}
}

int nCItemRequestSaveExItemInfo = 0;
bool __cdecl CItem::RequestSaveExItemInfo(CQuerySocket *pSocket, unsigned char *packet)
{
	CASHED_SHARED_GUARD(nCItemRequestSaveExItemInfo);
	TLS_TRACE_BEGIN;

	int nUserId = 0;
	int nItemID = 0;
	int nAmount = 0;
	int nType = 0;
	int nContain = 0;

	CWareHouse* pWarehouse = NULL;

	CObjectSP UserSP;
	CObjectSP WarehouseSP;

	packet = Disassemble(packet, "ddd", &nUserId, &nItemID, &nAmount);

	if(CUserDB::I()->GetUser(&UserSP, nUserId, 0))
	{
		CObjectSP::ObjItem((CUser*)UserSP.pObject, &WarehouseSP, 0, 1);
		pWarehouse = (CWareHouse*)WarehouseSP.pObject;
		pWarehouse->WriteLock();
		CItemSP ItemSP = pWarehouse->GetItem(nItemID);
		if(ItemSP.pObject)
		{
			CItem* pItem = (CItem*)ItemSP.pObject;

			for(int i = 0; i < nAmount; i++)
			{
				packet = Disassemble(packet, "dd", &nType, &nContain);
				switch(nType)
				{
				case EIIT_LOCATION_SLOT:
					pItem->exInfo.locationSlot = nContain;
					break;
				case EIIT_AUGMENTATION_ID:
					pItem->exInfo.augmentationId = nContain;
					break;
				case EIIT_MANA:
					pItem->exInfo.mana = nContain;
					break;
				case EIIT_ATK_ATTR_ELEMENT:
					pItem->exInfo.nAtkAttrElement = nContain;
					break;
				case EIIT_ATK_ATTR_VALUE:
					pItem->exInfo.nAtkAttrValue = nContain;
					break;
				case EIIT_DEF_ATTR_FIRE:
					pItem->exInfo.nDefAttrFire = nContain;
					break;
				case EIIT_DEF_ATTR_WATER:
					pItem->exInfo.nDefAttrWater = nContain;
					break;
				case EIIT_DEF_ATTR_WIND:
					pItem->exInfo.nDefAttrWind = nContain;
					break;
				case EIIT_DEF_ATTR_EARTH:
					pItem->exInfo.nDefAttrEarth = nContain;
					break;
				case EIIT_DEF_ATTR_HOLY:
					pItem->exInfo.nDefAttrHoly = nContain;
					break;
				case EIIT_DEF_ATTR_UNHOLY:
					pItem->exInfo.nDefAttrUnholy = nContain;
					break;
				default:
					CLog::Add(CLog::red, L"Unknown parameter type [%d]", nType);
					break;
				}
			}
			pItem->SaveItemExInfo();
		}

		pWarehouse->WriteUnlock();
	}
	else
	{
		CLog::Add(CLog::red,L"[%s][%d] Error... Wrong packet size or amount types", __FUNCTION__, __LINE__);
	}

	TLS_TRACE_END(false);
}
