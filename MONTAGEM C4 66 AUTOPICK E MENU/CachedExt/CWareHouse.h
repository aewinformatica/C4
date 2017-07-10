#pragma once

#include "CItemSP.h"

class CWareHouse
{
public:
	/* 000 */	char	unk000[0x6D];
	/* 06D */	bool ItNeedsToSave;

	void WriteLock();
	void WriteUnlock();
	void SaveUnsavedItems();
	CItemSP GetItem(int nItemID);
};
