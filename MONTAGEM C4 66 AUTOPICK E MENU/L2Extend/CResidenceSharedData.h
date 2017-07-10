#pragma once

#include <windows.h>
#pragma pack( push, 1 )

// name: 
// size: Original 0x268 bytes
class CResidenceSharedData		// this CResidenceSharedData and server CResidenceData is the same! Remember!!!!
{
public:
	/* 0000 */ int _n0000;
	/* 0004 */ int _n0004;
	/* 0008 */ int _n0008;
	/* 000C */ int _n000C;
	/* 0010 */ int _n0010;
	/* 0014 */ int _n0014;
	/* 0018 */ int _n0018;
	/* 001C */ int _n001C;
	/* 0020 */ int _n0020;
	/* 0024 */ int _n0024;
	/* 0028 */ int _n0028;
	/* 002C */ int _n002C;
	/* 0030 */ int _n0030;
	/* 0034 */ int _unk0034;		
	/* 0038 */ int _unk0038;
	/* 003C */ int _unk003C;
	/* 0040 */ int _unk0040;
	/* 0044 */ int _unk0044;
	/* 0048 */ int _unk0048;
	/* 004C */ int _unk004C;
	/* 0050 */ int nResidenceID;
	/* 0054 */ int nPledgeID;
	/* 0058 */ int _unk0058;
	/* 005C */ int _unk005C;
	/* 0060 */ int SiegeTimeLeft; 
	/* 0064 */ int _unk0064;
	/* 0068 */ int nStatus;		// 0 - Off, 1 - in siege(mid vic.), 2 - in siege, 3 - waiting siege, 4 - registering [attack/defence], 5 - registering [next siege date]

public:
	bool IsDefendingPledge(int id);
	bool IsOffendingPledge(int id);
};

#pragma pack( pop )
