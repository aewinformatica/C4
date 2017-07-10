#pragma once

#include "MemoryObject.h"
#include "../L2Extend/SharedCached.h"

#pragma pack( push, 1 )

struct CItemEx
{
	/* 000 */	int locationSlot;
	/* 004 */	int augmentationId;
	/* 008 */	int mana;
	/* 00C */	int nAtkAttrElement;
	/* 010 */	int nAtkAttrValue;
	/* 014 */	int nDefAttrFire;
	/* 018 */	int nDefAttrWater;
	/* 01C */	int nDefAttrWind;
	/* 020 */	int nDefAttrEarth;
	/* 024 */	int nDefAttrHoly;
	/* 028 */	int nDefAttrUnholy;
	/* 02C */
};

class CItem/*	: public MemoryObject*/
{
public:

	/* 000 */ int n000;
	/* 004 */ int n004;
	/* 008 */ int n008;
	/* 00C */ int n00C;
	/* 010 */ int n010;
	/* 014 */	int nTrasactMode;
	/* 018 */	unsigned int nItemID;
	/* 01C */	int nCharID;
	/* 020 */	int nItemType;
	/* 024 */	int nAmount;
	/* 028 */	int nEnchant;
	/* 02C */	int nDamaged;
	/* 030 */	int nBless;
	/* 034 */	int nIdent;
	/* 038 */	int nWished;
	/* 03C */	int nWarehouse;
	/* 040 */	bool unk040;
	/* 041 */	bool unk041;
	/* 042 */	__int8 empty1[2];
	/* 044 */	int unk044;
	/* 048 */	bool unk048;
	/* 049 */	__int8 empty2[3];
	/* 04C */	int unk04c;
	/* 050 */	int unk050;
	/* 054 */	int unk054;

	// --- new part of CItem
	CItemEx exInfo;

	static CItem* __cdecl    Alloc_442640(size_t size = 0x58);
	static CItem* __thiscall Alloc_44B290(intptr_t pool = 0x8CE770, size_t size = 0x58, size_t count = 1, const wchar_t* clsname = L"CItem");

	static CItem* __thiscall ConstructBlank(CItem* pItem, int nItemID);
	static CItem* __thiscall ConstructCopy(CItem* pItem, int nItemID, int nCharID, int nItemType, int nAmount, int nEnchant, int nDamaged, int nBless, int nIdent, int nWished, int nWarehouse);
	static CItem* __thiscall ConstructLoad(CItem* pItem, int nItemID, int nCharID, int nItemType, int nAmount, int nEnchant, int nDamaged, int nBless, int nIdent, int nWished, int nWarehouse);
	static CItem* __thiscall LoadItem(unsigned int nItemID);

	static void __thiscall Destruct(CItem* pItem, bool bDelete);

	void LoadItemExInfo();
	void SaveItemExInfo();

	static bool __cdecl RequestSaveExItemInfo(CQuerySocket *pSocket, unsigned char *packet);
};
#pragma pack( pop )
