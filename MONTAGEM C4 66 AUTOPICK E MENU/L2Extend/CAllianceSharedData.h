#pragma once

#include <windows.h>
#include <map>
#pragma pack( push, 1 )

// name: 
// size: Original 0x268 bytes
class CAllianceSharedData
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
	/* 0050 */ int _unk0050;
	/* 0054 */ WORD _unk0054;
	/* 0056 */ WORD _unk0056;
	/* 0058 */ int _unk0058;
	/* 005C */ int _unk005C;
	/* 0060 */ int _unk0060; 
	/* 0064 */ int nDBID;
	/* 0068 */ WCHAR wszAllyName[24];
	/* 0098 */ int nClanleaderDBID;
	/* 009C */ int _unk009C;
	/* 00A0 */ int nCrestID;
	/* 00A4 */ int Amount; // pledges
	/* 00A8 */ int PledgeObjID1;
	/* 00AC */ int PledgeID1;
	/* 00B0 */ int PledgeObjID2;
	/* 00B0 */ int PledgeID2;
	/* 00B8 */ int PledgeObjID3;
	/* 00B0 */ int PledgeID3;
	/* 00C0 */ int PledgeObjID4;
	/* 00B0 */ int PledgeID4;
	/* 00C8 */ int PledgeObjID5;
	/* 00B0 */ int PledgeID5;
	/* 00D0 */ int PledgeObjID6;
	/* 00B0 */ int PledgeID6;
	/* 00D8 */ int PledgeObjID7;
	/* 00B0 */ int PledgeID7;
	/* 00E0 */ int PledgeObjID8;
	/* 00B0 */ int PledgeID8;
	/* 00E8 */ int PledgeObjID9;
	/* 00B0 */ int PledgeID9;
	/* 00F0 */ int PledgeObjID10;
	/* 00B0 */ int PledgeID10;
	/* 00F8 */ int PledgeObjID11;
	/* 00B0 */ int PledgeID11;
	/* 0100 */ int PledgeObjID12;
	/* 0104 */ int PledgeID12;
};

#pragma pack( pop )