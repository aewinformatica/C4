#pragma once

#include "..\L2Extend\CPledgeSharedData.h"
#include "..\L2Extend\CSharedData.h"

class CSharedFactory
{
public:
	static void Initialize();
	static void ExtendCreatureSharedData();
	static void ExtendPledgeSharedData();
	static void ReallocateAbnormalTable();
	static void ReallocateQuests();
};