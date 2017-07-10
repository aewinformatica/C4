#pragma once

#include <windows.h>
#include <map>
#pragma pack( push, 1 )

struct MemberInfo
{
	int nDBID;
	int nObjectID;
};

class CSubUnit
{
public:
	int nPledgeType; //-1/100/200/1001/1002/2001/2002
	int nLeaderID;
	wchar_t wszLeaderName[25];
	wchar_t wszName[25];
};

typedef std::map<int, int> PledgeSkillMap;
typedef std::map<int, CSubUnit*> SubUnitMap;

// name: 
// size: Original 0x268 bytes
class CPledgeSharedData
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
	/* 0024 */ int _n0024; //object
	/* 0028 */ int _n0028;
	/* 002C */ int _n002C; //-1
	/* 0030 */ int _n0030;
	/* 0034 */ int _unk0034;		
	/* 0038 */ int _unk0038;
	/* 003C */ int _unk003C;
	/* 0040 */ int _unk0040;
	/* 0044 */ int _unk0044;
	/* 0048 */ int _unk0048;
	/* 004C */ int _unk004C;
	/* 0050 */ int _unk0050;
	/* 0054 */ WORD _unk0054; //-1
	/* 0056 */ WORD _unk0056;
	/* 0058 */ int _unk0058;
	/* 005C */ int _unk005C;
	/* 0060 */ int _unk0060; 
	/* 0064 */ int nDBID;
	/* 0068 */ WCHAR wszClanName[24];
	/* 0098 */ int nClanleaderDBID;
	/* 009C */ WCHAR wszClanleaderName[26];
	/* 00D0 */ int nChallengeTime;
	/* 00D4 */ int nOustTime;
	/* 00D8 */ int nRootNameValue;
	/* 00DC */ int nActiveLevel;
	/* 00E0 */ int nAllianceID;
	/* 00E4 */ int nSkillLevel;
	/* 00E8 */ int nCrestID;
	/* 00EC */ int nEmblemId;
	/* 00F0 */ int nPrivateFlag;
	/* 00F4 */ int nRank; //Rank
	/* 00F8 */ int nState; //Peace/War/Dissolving - 3
	/* 00FC */ int nIsGuilty;
	/* 0100 */ int nDismissReservedTime;
	/* 0104 */ int nCastleID;
	/* 0108 */ int nAgitID;
	/* 010C */ int _unk010C;
	/* 0110 */ int _unk0110;
	/* 0114 */ int _unk0114;
	/* 0118 */ int nMemberCount; //online member count
	/* 011C */ int nObjectIdCL; 
	/* 0120 */ int _unk0120; // maybe online or not , set -1 if not or another if online 
	/* 0124 */ MemberInfo MemberData[220];
//	/* 0264 */ int _nEndofSharedData; //0x0FFFFFFF
	/* 0804(0624) */ int nReputation;
	/* 0808 */ INT64 PowerData[10];
	/* 0858 */ PledgeSkillMap *m_Skills;
	/* 0860 */ SubUnitMap *m_SubUnits;
	/* 0868 */ int nFortressID;
	/* 086C */ __int8 n1stRoyalGuard;
	/* 086D */ __int8 n2stRoyalGuard;
	/* 086E */ __int8 n1stOrderofKnights;
	/* 086F */ __int8 n2stOrderofKnights;
	/* 0870 */ __int8 n3stOrderofKnights;
	/* 0871 */ __int8 n4stOrderofKnights;
	/* 0872 */ INT32 nTotalMembers;
};

#pragma pack( pop )