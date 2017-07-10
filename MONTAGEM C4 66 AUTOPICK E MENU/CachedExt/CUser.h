#pragma once

#include "CQuerySocket.h"

class CWareHouse;
class CObjectSP;

#pragma pack( push, 1 )
struct QuestData
{
	__int32		questId;
	__int32		questState;
	__int32		questJournal;
	__int32		unk4;
};

struct ActionSkill
{
	__int32		ActiveSkills[36][4];
};

// original size - 5A8
class CUser
{
public:
/* 000 */	int VMTUser;
/* 004 */	int nDBID;
/* 008 */	int __unk008;
/* 00c */	int __unk00c;
/* 010 */	int __unk010;
/* 014 */	int __unk014;
/* 018 */	int __unk018;
/* 01c */	int __unk01c;
/* 020 */	int __unk020;
/* 024 */	int __unk024;
/* 028 */	int __unk028;
/* 02c */	int __unk02c;
/* 030 */	int __unk030;
/* 034 */	int __unk034;
/* 038 */	int	unk038;
/* 03C */	int	cs_settings;
/* 040 */	int __unk040;
/* 044 */	int __unk044;
/* 048 */	int __unk048;
/* 04c */	int __unk04c;
/* 050 */	int __unk050;
/* 054 */	int __unk054;
/* 058 */	int __unk058;
/* 05c */	int __unk05c;
/* 060 */	int __unk060;
/* 064 */	wchar_t LName[24];
/* 094 */	wchar_t Name[24];
/* 0C4 */	int charId;
/* 0C8 */	wchar_t Account[24];
/* 0F8 */	int	__unk0F8;
/* 0FC */	int	nPledgeId;
/* 100 */	int nBuilder;
/* 104 */	int nGender;
/* 108 */	int nRace;
/* 10C */	int	nClass;
/* 110 */	int nWorld;
/* 114 */	int x;
/* 118 */	int y;
/* 11C */	int z;
/* 120 */	int nIsInVehicle;
/* 124 */	int unk124;
/* 128 */	double fHP;
/* 130 */	double fMP;
/* 138 */	double fCP;
/* 140 */	double fMaxHP;
/* 148 */	double fMaxMP;
/* 150 */	double fMaxCP;
/* 158 */	int nSp;
/* 15C */	unsigned int	experience;
/* 160 */	int nLevel;
/* 164 */	int unk164;
/* 168 */	int nAlign;
/* 16C */	int nPK;
/* 170 */	int	nDuel;
/* 174 */	int	nPKPardon;
/* 178 */	int ST_underware;
/* 17C */	int ST_right_ear;
/* 180 */	int ST_left_ear;
/* 184 */	int ST_neck;
/* 188 */	int ST_right_finger;
/* 18C */	int ST_left_finger;
/* 190 */	int ST_head;
/* 194 */	int ST_right_hand;
/* 198 */	int ST_left_hand;
/* 19C */	int ST_gloves;
/* 1A0 */	int ST_chest;
/* 1A4 */	int ST_legs;
/* 1A8 */	int ST_feet;
/* 1AC */	int ST_back;
/* 1B0 */	int ST_both_hand;
/* 1B4 */	int ST_hair;
/* 1B8 */	int Hair_Color_Index;
/* 1BC */	int Hair_Shape_Index;
/* 1C0 */	int Face_Index;
/* 1C4 */	char	unk1C4[0x1F4];
/* 3B8 */   int nHenna1;
/* 3BC */	int nHenna2;
/* 3C0 */	int nHenna3;
/* 3C4 */	int subjob0_class;
/* 3C8 */	int subjob1_class;
/* 3CC */	int subjob2_class;
/* 3D0 */	int subjob3_class;
/* 3D4 */	char	unk3D4[0x5C];
/* 430 */	QuestData originalQuests[16];	// 16 * 16= 0x100
/* 530 */	char	unk530[0x2C];
/* 55C */	int	subClassId;
/* 560 */	char	unk560;
/* 561 */	char	unk561[0x3F];
/* 5A0 */	int ssq_dawn_round;
/* 5A4 */	int	unk5A4;
/* 5A8 */	QuestData	quests[26];
/* 748 */	int	experienceHi;
/* 74C */	__int64		newExp038;
/* 754 */	int	PledgeType;
/* 758 */	ActionSkill m_ActionSkill;
/* 75C */

	void SaveMemo();
	void SetQuest(__int32 c1);
	void WriteLock(const wchar_t* file, int line);
	void WriteUnlock();
	bool Save();
	bool SaveHennaInfo();
	int CreateSubJob(int nNewSubJobId, int nNewClass, int nSubClassId, double fHP, double fMP, int nSp, int nExp, int nLevel, int henna1, int henna2, int henna3);
	int CreateSubJob64(int nNewSubJobId, int nNewClass, int nSubClassId, double fHP, double fMP, int nSp, __int64 nExp, int nLevel, int henna1, int henna2, int henna3);
	bool RenewSubJob(int nSubJobId, int nNewClass, int SubClassId, double fHP, double fMP, int nSp, int Exp, int nLevel, int nHenna1, int nHenna2, int nHenna3);
	bool RenewSubJob64(int nSubJobId, int nNewClass, int SubClassId, double fHP, double fMP, int nSp, __int64 Exp, int nLevel, int nHenna1, int nHenna2, int nHenna3);
	bool ChangeSubJob(int nSubJobId, int SubClassId, double *fHP, double *fMP, int *nSp, int *nExp, int *nLevel, int *nHenna1, int *nHenna2, int *nHenna3);
	bool ChangeSubJob64(int nSubJobId, int SubClassId, double *fHP, double *fMP, int *nSp, __int64 *nExp, int *nLevel, int *nHenna1, int *nHenna2, int *nHenna3);
	bool SaveForSubJob(int SubClassId, int nClass, double fHP, double fMP, double fMaxHP, double fMaxMP, double fCP, double fMaxCP, int nSp, int nExp, int nLevel, int nHenna1, int nHenna2, int nHenna3);
	bool SaveForSubJob64(int SubClassId, int nClass, double fHP, double fMP, double fMaxHP, double fMaxMP, double fCP, double fMaxCP, int nSp, __int64 nExp, int nLevel, int nHenna1, int nHenna2, int nHenna3);

	wchar_t* GetCharName();
	int GetId();
	wchar_t* GetAccountName();
	int GetAccountID();
	int GetPledgeID();
	int GetBuilder();
	int GetGender();
	int GetRace();
	int GetClass();
	int GetWorld();
	int GetX();
	int GetY();
	int GetZ();
	double GetHP();
	double GetMP();
	int GetSP();
	int GetExp();
	int GetLevel();
	int GetAlign();
	int GetPK();
	int GetDuel();
	int GetPKPardon();
	int GetUnderware();
	int GetRight_ear();
	int GetLeft_ear();
	int GetNeck();
	int GetRight_finger();
	int GetLeft_finger();
	int GetHead();
	int GetRight_hand();
	int GetLeft_hand();
	int GetGloves();
	int GetChest();
	int GetLegs();
	int GetFeet();
	int GetBack();
	int GetBoth_hand();
	int GetHair();
	int GetExpDiff();
	__int64 GetExpDiff64();
	int GetLevelByExp(int exp);
	void LoadWarehouseItems(CObjectSP *items, int unk1, int forceLoad);
	CUser* ThreadSafeTest();
	bool AddUserLog2(int nLogId, int nLogFrom, int nLogTo, unsigned int nUseTime, int nSubjobId);

	bool Save64();

	void SetChanged(int nPledgeId, int nBuilder, int nGender, int nRace, int nClass, int nWorld, int locX, int locY, int locZ,
							 double fHP, double fMP, double fMaxHP, double fMaxMP, int nSp, __int64 experience, int nLevel, int nAlign, int nPK, int nDuel, int nPKPardon,
							 int ST_underware, int ST_right_ear, int ST_left_ear, int ST_neck, int ST_right_finger, int ST_left_finger, int ST_head, int ST_right_hand,
							 int ST_left_hand, int ST_gloves, int ST_chest, int ST_legs, int ST_feet, int ST_back, int ST_both_hand, int ST_hair, int Face_Index,
							 int Hair_Shape_Index, int Hair_Color_Index, int nIsInVehicle, int subClassId, int subjob0_class, int subjob1_class, int subjob2_class,
							 int subjob3_class, double fCP, double fMaxCP, int ssq_dawn_round, bool locked);

	static bool SaveCharacterPacket64(CQuerySocket *pSocket, const unsigned char *packet);

private:
	void SetChangedLock();
	void SetChangedUnlock();
};
#pragma pack( pop )
