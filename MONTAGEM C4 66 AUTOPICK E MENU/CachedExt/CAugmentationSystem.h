#pragma once

#include "Global.H"

class CAugmentationSystem
{
public:
	static void Initialize();
private:
	static void SaveItem1();
	static void SaveItem2();
	static void WareHouseSendList();
	static int WareHouseSendListAssemble(char *buffer, int bufLen, CItem *pItem);
public:
};
