/*
    This file is part of L2Extend.

    L2Extend is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    L2Extend is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with L2Extend.  If not, see <http://www.gnu.org/licenses/>.

	You May Not Make Commercial Use of any of our content, and any kind
	of newer implementations will be need to be shared and commited.
*/

#pragma once

#include <windows.h>
#include <string>
#include "CCreature.h"
#include "CSharedData.h"

// bits used in User::nAutoSoulshot
#define AUTO_NOVICE_SOULSHOT   (1 <<  0)
#define AUTO_NOVICE_SPIRITSHOT (1 <<  1)
#define AUTO_SOULSHOT_NONE     (1 <<  4)
#define AUTO_SOULSHOT_D        (1 <<  5)
#define AUTO_SOULSHOT_C        (1 <<  6)
#define AUTO_SOULSHOT_B        (1 <<  7)
#define AUTO_SOULSHOT_A        (1 <<  8)
#define AUTO_SOULSHOT_S        (1 <<  9)
#define AUTO_SPIRITSHOT_NONE   (1 << 10)
#define AUTO_SPIRITSHOT_D      (1 << 11)
#define AUTO_SPIRITSHOT_C      (1 << 12)
#define AUTO_SPIRITSHOT_B      (1 << 13)
#define AUTO_SPIRITSHOT_A      (1 << 14)
#define AUTO_SPIRITSHOT_S      (1 << 15)
#define AUTO_BLESSEDSHOT_NONE  (1 << 16)
#define AUTO_BLESSEDSHOT_D     (1 << 17)
#define AUTO_BLESSEDSHOT_C     (1 << 18)
#define AUTO_BLESSEDSHOT_B     (1 << 19)
#define AUTO_BLESSEDSHOT_A     (1 << 20)
#define AUTO_BLESSEDSHOT_S     (1 << 21)
#define AUTO_BEAST_SOULSHOT    (1 << 22)
#define AUTO_BEAST_SPIRITSHOT  (1 << 23)
#define AUTO_BEAST_BLESSEDSHOT (1 << 24)

class CParty;
class CPet;
class CPledge;
class CSocket;

class COlympiadField;

struct CEventMatchUser
{
	/* 0000 */  unsigned nEventMatchId;
	/* 0004 */  char _c04; // could be team number? (0=none)
};

struct COlympiadUser
{
	/* 0000 */  char  cStatus; // if == 1 or 2 => can't use items forbidden in oly
							   // if == 3 then user is observing oly maybe?
	/* 0004 */  int   _unk04[13];
	/* 0038 */  int   nFieldId; // == 0..21
	/* 003C */  int   _unk3C[7];
	/* 0058 */  User* pUser;
	/* total size unknown! */

	void ChangeObserverField(int nFieldId)
	{
		typedef void (*FChangeObserverField)(COlympiadUser*, int);
		FChangeObserverField(0x703E40)(this, nFieldId);
	}

	COlympiadField* GetField()
	{
		typedef COlympiadField* (*FGetField)(COlympiadUser*);
		return FGetField(0x703C00)(this);
	}

	bool WaitingOlympiadObserving()
	{
		typedef bool (*FWaitingOlympiadObserving)(COlympiadUser*);
		return FWaitingOlympiadObserving(0x705B90)(this);
	}
};

class User : public CCreature
{
	public:

		User();
		~User();

		/* 14F0 */ int _dw14F0[342];
		/* 1A48 */ INT64 _qw1A48;	// fishing class or structure have not less then 488h byte used in trade 488h is 1 if user fishing
		/* 1A50 */ int _qw1A50[4];
		/* 1A60 */ bool _b1A60;
		/* 1A61 */ bool _b1A61; //in restart to battle camp most be 0 and hp set maxhp may be accept dialog to restart or battle zone maybe die or not
		/* 1A62 */ bool bDressedInFormalWear;
		/* 1A63 */ bool _b1A63;
		/* 1A64 */ int _dw1A64[17];
		/* 1AA8 */ int nAutoSoulshot; // bit field, see AUTO...SHOT... #defines
		/* 1AAC */ int _dw1AAC[753];
		/* 2670 */ CSocket *Socket;
		/* 2678 */ int nTradeSID;
		/* 267C */ int _dw267C;
		/* 2680 */ int _dw2680[14];

		// right now this is just a guess, I'm yet to check if the object layout
		// matches, but here is probably map<int,X*> that maps pItem->nObjectId
		// to some private-store-related object.
		// used in User::SendPrivateStoreManageList (see loc_829859)
		/* 26B8 */ void* _map26B8_unk00;
		/* 26C0 */ void* _map26B8_Myhead;
		/* 26C8 */ size_t _map26B8_Mysize;

		/* 26D0 */ int _dw26D0[74];
		/* 27F8 */ int nAccountID;
		/* 27FC */ WCHAR wAccountName[15];
		/* 281A */ CHAR chAccountName[15];
		/* 2829 */ INT8 _db2829[79];
		/* 2878 */ WCHAR ClanTitle[26];
		/* 28AC */ bool nBlockMsg; //type bool if 1 msg 961 You are now blocking everything - taken from partyjoinpacket
		/* 28AD */ bool _b28AD;
		/* 28AE */ bool _b28AE;
		/* 28AF */ bool _b28AF;
		/* 28B0 */ int nOustTime;
		/* 28B4 */ int _dw28B4;
		/* 28B8 */ int _dw28B8;
		/* 28BC */ int _dw28BC[3];
		/* 28C8 */ bool _b28C8;
		/* 28C8 */ bool _b28C9;
		/* 28C8 */ bool _b28CA;
		/* 28C8 */ bool _b28CB;
		/* 28CC */ int _dw28CC;
		/* 28D0 */ int _dw28D0;
		/* 28D4 */ int _dw28D4;
		/* 28D8 */ int _dw28D8;
		/* 28DC */ int _dw28DC;
		/* 28E0 */ int _dw28E0;
		/* 28E4 */ int _dw28E4;
		/* 28E8 */ int _dw28E8;
		/* 28EC */ int _dw28EC;
		/* 28F0 */ int _dw28F0;
		/* 28F4 */ int _dw28F4;
		/* 28F8 */ int _dw28F8;
		/* 28FC */ int _dw28FC;
		/* 2900 */ int _dw2900;
		/* 2904 */ int _dw2904;
		/* 2908 */ int _dw2908;
		/* 290C */ int _dw290C;
		/* 2910 */ void* pBuy;			// CBuy class
		/* 2918 */ int _dw2918[149];
		/* 2B6C */ int _dw2B6c;
		/* 2B70 */ long nUserChanged; //for locked InterlockedCompareExchange
		/* 2B74 */ int nPledgeCrestId;
		/* 2B78 */ int nPledgeLargeCrestId;
		/* 2B7C */ int nAllianceCrestId;
		/* 2B80 */ int _dw2B80[74];
		/* 2CA8 */ CEventMatchUser eventMatchUser;
		/* 2CB0 */ COlympiadUser   olympiadUser; // total size unknown!
		/* 2D10 */ int _dw2D00[15];
		/* 2D4C */ int _dw2D4C;
		/* 2D50 */ int _dw2D50[2];
		/* 2D58 */ WCHAR *pActiveHTMLFileName;
		/* 2D60 */ int _dw2D60[6];

		void SendQuestList();
		void SendAcquiredSkillToDB(int SkillID, int SkillLevel, bool bMayDown);
		void SendDeletedSkillToDB(int SkillID);
		bool IsNoblesse();
		bool IsHero();
		bool IsStanding();
		void SendUserInfo(bool GMPacket);
		void SendCharInfo(bool GMPacket);
		bool SendCoolTime();
		void SetKarma(int nKarma);
		void SendUserHPInfo();
		void SendUserMPInfo();
		void DespawnSummon();
		bool TeleportToLocation(int x, int y, int z);
		bool IsNowTrade();
		void TradeCancel();
		bool HaveSummon();
		void SendETCBuffStatus();
		void Ride(CPet *pPet);
		void SendSkillList();
		void SendItemList();
		int GetPledgeClass();
		void IconAction(int nID, bool bControl, bool bShift);
		CPledge* GetPledge();
		CObject* GetSummonOrPet();
		void UseItem(CItem *pItem);
		void SetState(INT32 nState);
		bool IsMyParty(CCreature *pCreature);
		CParty *GetParty();
		bool InCombat();
		int CombatTime();
		int GetKarma();
		__int64 IncreaseRefCount(char *fileName, int num1, int num2);
		bool ChangeClass(int newClass);
		void ExpInc(__int64 experience);
		__int64 ExpDown(__int64 exp);
		CPet* GetPet();
		void EquipItem(User *pUser, CItem *pItem, int bSlot); // bSlot 12h mayby User inventory
		bool AddItemToInventory2(CItem *pItem);
		bool CanJoinPledge();

		bool DropItem(CItem* itm, int nAmount, FVector vect);
		void SaveInfectedSkills();
		void PlaySound(const WCHAR* pszFileName, int nCount, int nServerID, int x, int y, int z);
		void PlayVoice(const WCHAR* pszFileName, int nCount, int nServerID, int x, int y, int z, int Delay);
		void PlayMusic(const WCHAR* pszFileName);
		void TakeOustedPenalty();
		void TakeWithdrawPenalty();
		bool IsSecondClass();
		void SetPledge(CPledge *pPledge);
		bool IsInBlockList(WCHAR * pwCharName);

		void SendPledgeSkillList();
		void ActionFailed();
};

extern "C"
{
	// ASM wrappers
	void User_SaveInfectedSkills(User *pUser);
};
