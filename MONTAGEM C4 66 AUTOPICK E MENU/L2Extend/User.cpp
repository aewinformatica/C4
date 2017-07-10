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

#include "User.h"
//#include "CPledge.h"
//#include "CPledgeSystem.h"
#include "CSocket.h"

CompileTimeSizeCheck(CEventMatchUser, 8);
CompileTimeSizeCheck(COlympiadUser, 0x60); 

CompileTimeOffsetCheck(COlympiadUser, pUser, 0x58);
CompileTimeOffsetCheck(User, pActiveHTMLFileName, 0x2D58);

User::User()
{
}

User::~User()
{
}

void User::SendQuestList()
{
	typedef void (__thiscall *_SEND_QUEST_LIST) (User *pUser, bool GMPacket);
	_SEND_QUEST_LIST _SendQuestList = (_SEND_QUEST_LIST)0x0081EB20L;
	_SendQuestList(this, false);
}

void User::SendAcquiredSkillToDB(int SkillID, int SkillLevel, bool bMayDown)
{
	typedef void (__thiscall *_SASTDB) (User *pUser, int SkillID, int SkillLevel, bool bMayDown);
	_SASTDB _SendAcquiredSkillToDB = (_SASTDB)0x00801CD0L;
	_SendAcquiredSkillToDB(this, SkillID, SkillLevel, bMayDown);
}

void User::SendDeletedSkillToDB(int SkillID)
{
	typedef void (__thiscall *_SDSTDB) (User *pUser, int SkillID);
	_SDSTDB _SendDeletedSkillToDB = (_SDSTDB)0x00801E40L;
	_SendDeletedSkillToDB(this, SkillID);
}

void User::SetPledge(CPledge *pPledge)
{
	typedef void (__thiscall *_f) (User *pUser, CPledge *pPledge);
	_f __f = (_f)0x00810C50L;
	__f(this, pPledge);
}

bool User::IsInBlockList(WCHAR * pwCharName)
{
	typedef bool (__thiscall *_f) (User *pUser, WCHAR * pwCharName);
	_f __f = (_f)0x0082AEB0L;
	return __f(this, pwCharName);
}

bool User::IsNoblesse()
{
	return (SD->NoblesseType == 1);
}

bool User::IsHero()
{
	return (SD->HeroType == 2);
}

bool User::IsStanding()
{
	return (SD->nStopType > 0);
}

void User::SendUserInfo(bool GMPacket)
{
	typedef void (__thiscall *_SEND_USER_INFO) (User *pUser, bool gmpacket);
	_SEND_USER_INFO _SendUserInfo = (_SEND_USER_INFO)0x00855740L;
	_SendUserInfo(this, false);
}

void User::SendCharInfo(bool GMPacket)
{
	typedef void (__thiscall *_SEND_CHAR_INFO) (User *pUser, bool gmpacket);
	_SEND_CHAR_INFO _SendCharInfo = (_SEND_CHAR_INFO)0x00857AC0L;
	_SendCharInfo(this, GMPacket);
}

bool User::SendCoolTime()
{
	typedef bool(*_sc)(User*);
	_sc sc = (_sc) 0x0082AA70;
	return sc(this);
}

void User::SetKarma(int nKarma)
{
	typedef void (__thiscall * __SetKarma)(User*, int Karma);
	__SetKarma _SetKarma = (__SetKarma)0x00812B10;
	_SetKarma(this, nKarma);
}

bool User::IsNowTrade()
{
	typedef bool (*ISNOWTRADE)(User *pUser);
	ISNOWTRADE xIsNowTrade = (ISNOWTRADE)(0x0080F840L);
	return xIsNowTrade(this);
}

void User::SendUserHPInfo()
{
	typedef void (__thiscall *_USER_SEND_HP_INFO) (User *);
	_USER_SEND_HP_INFO _SendHPInfo = (_USER_SEND_HP_INFO)0x008464A0;
	
	_SendHPInfo(this);
}

void User::SendUserMPInfo()
{
	typedef void (__thiscall *_USER_SEND_MP_INFO) (User *);
	_USER_SEND_MP_INFO _SendMPInfo = (_USER_SEND_MP_INFO)0x0080ECE0;
	
	_SendMPInfo(this);
}

void User::DespawnSummon()
{
	typedef void(__fastcall *_DS)(User*);
	_DS xDS = (_DS) 0x00812510;
	xDS(this);
}

bool User::TeleportToLocation(int x, int y, int z)
{
	typedef bool (__thiscall *_USER_TELEPORT_TO_LOC) (User *, int, int, int);
	_USER_TELEPORT_TO_LOC _TeleportToLocation = (_USER_TELEPORT_TO_LOC)0x008151E0;

	return _TeleportToLocation(this, x, y, z);
}

void User::TradeCancel()
{
	typedef void (__thiscall *_USER_TRADE_CANCEL) (User *);
	_USER_TRADE_CANCEL _TradeCancel = (_USER_TRADE_CANCEL)0x0080F370;
	
	_TradeCancel(this);
}

bool User::HaveSummon()
{
	typedef bool (__thiscall *_HS) (User *);
	_HS xHS = (_HS)0x00816E80L;
	return xHS(this);
}

void User::SendETCBuffStatus()
{
	typedef void (__fastcall * SendETCBuffStatusS) (User*);
	SendETCBuffStatusS _SendETCBuffStatus = (SendETCBuffStatusS)0x007FFEB0L;
	_SendETCBuffStatus(this);
}

void User::Ride(CPet *pPet)
{
	typedef void(__fastcall *__ODDI)(User*, CPet*);
	__ODDI _ODDI = (__ODDI) 0x00834AD0;
	_ODDI(this, pPet);
}

void User::SendSkillList()
{
	typedef void(__fastcall *_SL)(User*);
	_SL xSL = (_SL) 0x00828500L;
	xSL(this);
}

void User::SendItemList()
{
	typedef void(__fastcall *_SL)(User*);
	_SL xSL = (_SL) 0x00819C40L;
	xSL(this);
}

void User::IconAction(int nID, bool bControl, bool bShift)
{
	typedef void(__fastcall *_IA)(User*,int,bool,bool);
	_IA xIA = (_IA) 0x00837850L;
	xIA(this,nID,bControl,bShift);
}

CPledge* User::GetPledge()
{
	typedef CPledge*(__fastcall *_GET_PLEDGE)(User*);
	_GET_PLEDGE _GetPledge = (_GET_PLEDGE) 0x00410c00;
	return _GetPledge(this);
}


CObject* User::GetSummonOrPet()
{
	typedef CObject *(__fastcall *__gp)(User*);
	__gp _gp = (__gp)0x00812680;
	return _gp(this);
}
/*
INT32 nGetPledgeClass = 0;
int User::GetPledgeClass()
{
	L2SERVER_SHARED_GUARD(nGetPledgeClass);
	TLS_TRACE_BEGIN;

	if(this->IsValidUser())
	{
		int nRank = PLEDGE_RANK::VAGABOND;
		CSharedData *pUSD = this->SD;
		CPledge *pPledge = this->GetPledge();
		if(pPledge->IsValidPledge())
		{
			CMemberData *pData = pPledge->GetMemberDataByDBID(this->nSID);
			CPledgeSharedData *pPSD = pPledge->pSD;
			if(pPSD && pData)
			{
				int nClanLevel = pPSD->nSkillLevel;

				if(pData->nPledgeType == SUBUNIT_ACADEMY || pUSD->NoblesseType || pUSD->HeroType == 2)
				{
					if(pUSD->HeroType == 2)
					{
						nRank = PLEDGE_RANK::MARQUIS;
					}
					else
						if(pUSD->NoblesseType)
						{
							nRank = PLEDGE_RANK::BARON;
							goto Next;
						}
						else
						{
							if(pUSD->nPledgeType == -1 && nClanLevel > 5)
							{
								nRank = PLEDGE_RANK::VASSAL;
								goto Next;
							}
							else
								nRank = PLEDGE_RANK::VAGABOND;
						}
				}
				else
				{
					switch(nClanLevel)
					{
					case 4:
						{
							if(pUSD->nIsPledgeLeader > 0)
								nRank = PLEDGE_RANK::KNIGHT;
							break;
						}
					case 5:
						{
							if(pUSD->nIsPledgeLeader > 0)
								nRank = PLEDGE_RANK::ELDER;
							else
								nRank = PLEDGE_RANK::HEIR;
							break;
						}
					case 6:
						{
							if(pUSD->nIsPledgeLeader)
							{
								nRank = PLEDGE_RANK::BARON;
							}
							else
							{
								if(pUSD->nPledgeType == 100 || pUSD->nPledgeType == 200)
								{
									SubUnitMap::iterator Iter = pPSD->m_SubUnits->find(pUSD->nPledgeType);
									if(Iter->second->nLeaderID == this->nSID)
									{
										nRank = PLEDGE_RANK::ELDER;
									}
									else
									{
										nRank = PLEDGE_RANK::HEIR;
									}
									break;
								}
								else
								{
									if(pUSD->nPledgeType == 0)
									{
										nRank = PLEDGE_RANK::KNIGHT;
									}
								}
							}
							break;
						}
					case 7:
						{							
							switch(pUSD->nPledgeType)
							{
							case 0:
								{
									if(pUSD->nIsPledgeLeader)
									{
										nRank = PLEDGE_RANK::COUNT;
									}
									else
									{
										nRank = PLEDGE_RANK::ELDER;
									}
									break;
								}
							case 100:
							case 200:
								{
									SubUnitMap::iterator Iter = pPSD->m_SubUnits->find(pUSD->nPledgeType);
									if(Iter->second->nLeaderID == this->nSID)
									{
										nRank = PLEDGE_RANK::VISCOUNT;
									}
									else
									{
										nRank = PLEDGE_RANK::KNIGHT;
									}
									break;
								}
							case 1001:
							case 1002:
							case 2001:
							case 2002:
								{
									SubUnitMap::iterator Iter = pPSD->m_SubUnits->find(pUSD->nPledgeType);
									if(Iter->second->nLeaderID == this->nSID)
									{
										nRank = PLEDGE_RANK::BARON;
									}
									else
									{
										nRank = PLEDGE_RANK::HEIR;
									}
									break;
								}
							default:
								{
									nRank = PLEDGE_RANK::VAGABOND;
									break;
								}
							}
							break;
						}
					case 8:
					case 9:
					case 10:
					case 11:
						{
							switch(pUSD->nPledgeType)
							{
							case 0:
								{
									if(pUSD->nIsPledgeLeader)
									{
										nRank = PLEDGE_RANK::MARQUIS;
									}
									else
									{
										nRank = PLEDGE_RANK::BARON;
									}
									break;
								}
							case 100:
							case 200:
								{
									SubUnitMap::iterator Iter = pPSD->m_SubUnits->find(pUSD->nPledgeType);
									if(Iter->second->nLeaderID == this->nSID)
									{
										nRank = PLEDGE_RANK::COUNT;
									}
									else
									{
										nRank = PLEDGE_RANK::ELDER;
									}
									break;
								}
							case 1001:
							case 1002:
							case 2001:
							case 2002:
								{
									SubUnitMap::iterator Iter = pPSD->m_SubUnits->find(pUSD->nPledgeType);
									if(Iter->second->nLeaderID == this->nSID)
									{
										nRank = PLEDGE_RANK::VISCOUNT;
									}
									else
									{
										nRank = PLEDGE_RANK::KNIGHT;
									}
									break;
								}
							default:
								{
									nRank = PLEDGE_RANK::VAGABOND;
									break;
								}
							}
							break;
						}
					//case 9:
					//	{
					//		switch(pUSD->nPledgeType)
					//		{
					//		case 0:
					//			{
					//				if(pUSD->nIsPledgeLeader)
					//				{
					//					nRank = PLEDGE_RANK::DUKE;
					//				}
					//				else
					//				{
					//					nRank = PLEDGE_RANK::VISCOUNT;
					//				}
					//				break;
					//			}
					//		case 100:
					//		case 200:
					//			{
					//				SubUnitMap::iterator Iter = pSD->m_SubUnits->find(pUSD->nPledgeType);
					//				if(Iter->second->nLeaderID == this->nSID)
					//				{
					//					nRank = PLEDGE_RANK::MARQUIS;
					//				}
					//				else
					//				{
					//					nRank = PLEDGE_RANK::BARON;
					//				}
					//				break;
					//			}
					//		case 1001:
					//		case 1002:
					//		case 2001:
					//		case 2002:
					//			{
					//				SubUnitMap::iterator Iter = pSD->m_SubUnits->find(pUSD->nPledgeType);
					//				if(Iter->second->nLeaderID == this->nSID)
					//				{
					//					nRank = PLEDGE_RANK::COUNT;
					//				}
					//				else
					//				{
					//					nRank = PLEDGE_RANK::ELDER;
					//				}
					//				break;
					//			}
					//		default:
					//			{
					//				nRank = PLEDGE_RANK::VAGABOND;
					//				break;
					//			}
					//		}
					//		break;
					//	}
					//case 10:
					//	{
					//		switch(pUSD->nPledgeType)
					//		{
					//		case 0:
					//			{
					//				if(pUSD->nIsPledgeLeader)
					//				{
					//					nRank = PLEDGE_RANK::GRAND_DUKE;
					//				}
					//				else
					//				{
					//					nRank = PLEDGE_RANK::COUNT;
					//				}
					//				break;
					//			}
					//		case 100:
					//		case 200:
					//			{
					//				SubUnitMap::iterator Iter = pSD->m_SubUnits->find(pUSD->nPledgeType);
					//				if(Iter->second->nLeaderID == this->nSID)
					//				{
					//					nRank = PLEDGE_RANK::DUKE;
					//				}
					//				else
					//				{
					//					nRank = PLEDGE_RANK::VISCOUNT;
					//				}
					//				break;
					//			}
					//		case 1001:
					//		case 1002:
					//		case 2001:
					//		case 2002:
					//			{
					//				SubUnitMap::iterator Iter = pSD->m_SubUnits->find(pUSD->nPledgeType);
					//				if(Iter->second->nLeaderID == this->nSID)
					//				{
					//					nRank = PLEDGE_RANK::MARQUIS;
					//				}
					//				else
					//				{
					//					nRank = PLEDGE_RANK::BARON;
					//				}
					//				break;
					//			}
					//		default:
					//			{
					//				nRank = PLEDGE_RANK::VAGABOND;
					//				break;
					//			}
					//		}
					//		break;
					//	}
					default:
						{
							if(pUSD->nPledgeType == 0)
								nRank = PLEDGE_RANK::VASSAL;
							break;
						}
					}
				}
			}
		}

Next:
		TLS_TRACE_END;
		return nRank;
	}

	TLS_TRACE_END;
	return 0;
}*/
void User::UseItem(CItem *pItem)
{
	typedef void (*_USE_ITEM)(User *, CItem *);
	_USE_ITEM xUseItem = (_USE_ITEM)0x0080E160;
	xUseItem(this, pItem);
}

void User::SetState(INT32 nState)
{
	*(INT32 *)(((BYTE *)this)+0x2958) = nState;
}

bool User::IsMyParty(CCreature *pCreature)
{
	typedef bool (*_MY_PARTY)(User *, CCreature *);
	_MY_PARTY isMyParty = (_MY_PARTY)0x00802DD0;
	return isMyParty(this, pCreature);
}

CParty * User::GetParty()
{
	if(this)
	{
		typedef CParty *(* __GetParty)(User*);
		__GetParty _GetParty = (__GetParty) 0x0046E4D0;
		return _GetParty(this);
	}else
		return NULL;
}

bool User::InCombat()
{
	if(this)
	{
		INT64 dCombat = (INT64)this;
		dCombat += 0xCA5;
		dCombat = *(BYTE*)dCombat;
		return (BYTE)dCombat;
	}
	return 0;
}

int User::CombatTime()
{
	if(this)
	{
		INT64 dCombat = (INT64)this;
		dCombat += 0xCA8;
		dCombat = *(DWORD*)dCombat;
		return dCombat;
	}
	return 0;
}

int User::GetKarma()
{
	return this->SD->nKarma;
}

__int64 User::IncreaseRefCount(char *fileName, int num1, int num2)
{
	typedef __int64 (*t)(User*, char *, int, int);
	t f = (t)0x7FCB70;
	return f(this, fileName, num1, num2);
}

bool User::ChangeClass(int newClass)
{
	typedef bool (*t)(User*, int);
	t f = (t)0x80E970;
	return f(this, newClass);
}

__int64 User::ExpDown(__int64 exp)
{
	typedef __int64 (*t) (User*, __int64);
	t f = (t) 0x8040F0;
	return f(this, exp);
}

void User::ExpInc(__int64 experience)
{
	typedef void (*t) (User*, __int64);
	t f = (t) 0x7FF470;
	f(this, experience);
}

bool User::DropItem(CItem* itm, int nAmount, FVector vect)
{
	typedef bool (*t)(User*, CItem*, int, FVector);
	t f = (t)0x800350;
	return f(this, itm, nAmount, vect);
}

CPet* User::GetPet()
{
	if(this)
	{
		typedef CPet* (* __GetPet)(User*);
		__GetPet _GetPet = (__GetPet)0x8120B0;
		return _GetPet(this);
	}
	return NULL;
}

void User::EquipItem(User *pUser, CItem *pItem, int bSlot)
{
	typedef void (__fastcall *_EQI) (User *, CItem *, int);
	_EQI xEquipItem = (_EQI)0x008257C0L;
	return xEquipItem(pUser, pItem, bSlot);
}

bool User::AddItemToInventory2(CItem *pItem)
{
	typedef bool (__fastcall *_ADD_ITEM2) (User *, CItem *);
	_ADD_ITEM2 xAddItemToInventory2 = (_ADD_ITEM2)0x007FFD50L;
	return xAddItemToInventory2(this, pItem);
}

void User::SaveInfectedSkills()
{
	if(!this->SD->nIsDuel)
	{
		typedef void (*t) (User*);
		t f = (t) 0x842F60;
		f(this);
	}
}

void User_SaveInfectedSkills(User *pUser)
{	
	if(!pUser->SD->nIsDuel)
	{
		typedef void (*t) (User*);
		t f = (t) 0x842F60;
		f(pUser);
	};
}

void User::PlaySound(const WCHAR* pszFileName, int nCount, int nServerID, int x, int y, int z)
{
	if(this->IsValidUser())
	{
		typedef void (*t) (User*, const WCHAR*, int, int, int, int, int);
		t f = (t) 0x8061B0;
		f(this, pszFileName, nCount, nServerID, x, y, z);
	}
}

void User::PlayVoice(const WCHAR* pszFileName, int nCount, int nServerID, int x, int y, int z, int Delay)
{
	if(this->IsValidUser())
	{
		typedef void (*t) (User*, const WCHAR*, int, int, int, int, int, int);
		t f = (t) 0x806360;
		f(this, pszFileName, nCount, nServerID, x, y, z, Delay);
	}
}

void User::PlayMusic(const WCHAR* pszFileName)
{
	if(this->IsValidUser())
	{
		typedef void (*t) (User*, const WCHAR*);
		t f = (t) 0x806360;
		f(this, pszFileName);
	}
}

bool User::CanJoinPledge()
{
	typedef bool(*t)(User*);
	t f = (t) 0x8042C0;
	return f(this);
}

void User::TakeOustedPenalty()
{
	if(this->IsValidUser())
	{
		if(this->SD->nPledgeType == -1 && this->IsSecondClass())
		{
		}
		else
		{
			typedef void(*t)(User*);
			t f = (t) 0x803A90;
			f(this);
		}
	}
}

void User::TakeWithdrawPenalty()
{
	if(this->IsValidUser())
	{
		if(this->SD->nPledgeType == -1 && this->IsSecondClass())
		{
		}
		else
		{
			typedef void(*t)(User*);
			t f = (t) 0x803BE0;
			f(this);
		}
	}
}

INT32 nUserSecondClass = 0;
bool User::IsSecondClass()
{
	bool result = false;

	L2SERVER_SHARED_GUARD(nUserSecondClass);
	TLS_TRACE_BEGIN;
	
	switch(this->SD->nClass)
	{
		case 2:
		case 3:
		case 5:
		case 6:
		case 8:
		case 9:
		case 12:
		case 13:
		case 14:
		case 16:
		case 17:
		case 20:
		case 21:
		case 23:
		case 24:
		case 27:
		case 28:
		case 30:
		case 33:
		case 34:
		case 36:
		case 37:
		case 40:
		case 41:
		case 43:
		case 46:
		case 48:
		case 51:
		case 52:
		case 55:
		case 57:
			result = true;
			break;
		default:
			if(this->SD->nClass > 87)
				result = true;
			break;
	}

	TLS_TRACE_END2(result);
}
/*
INT32 nUserSendPledgeSkillList = 0;
void User::SendPledgeSkillList()
{
	L2SERVER_SHARED_GUARD(nUserSendPledgeSkillList);
	TLS_TRACE_BEGIN;

	CPledge *pPledge = this->GetPledge();

	if(this->IsValidUser() && pPledge->IsValidPledge())
	{
		char packet[0x2000];
		int buflen = 0x2000;
		int nSkillAmount = 0;
		int nSkillLevel = 0;
		int nSize = 0;

		int nLevel = pPledge->pSD->nSkillLevel;

		for(unsigned int n=370; n<392;n++)
		{
			CPledgeSkillInfo *pInfo = CPledgeSystem::GetPledgeSkillInfo(n);
			if(pInfo)
			{
				if(nLevel >= pInfo->nRequiedPledgeLevel)
				{
					int nAcquiredLevel = 0;
					PledgeSkillMap::iterator i = pPledge->pSD->m_Skills->find(pInfo->nID);
					nAcquiredLevel = (i == pPledge->pSD->m_Skills->end()) ? 0: i->second;

					if(nAcquiredLevel < pInfo->nMaxLevel)
					{
						nSize = Assemble(packet+0x2000-buflen, buflen, "ddddd", pInfo->nID, ++nAcquiredLevel, pInfo->nMaxLevel, pInfo->nRequiedReputation, pInfo->nRequiedItemID);
						buflen -= nSize;
						nSkillAmount++;
					}
				}
			}
		}
		this->Socket->Send("cddb", 0x8A, 2, nSkillAmount, sizeof(packet), packet);
	}

	TLS_TRACE_END_NO_RETURN;
}
*/
INT32 nUserActionFailed = 0;
void User::ActionFailed()
{
	L2SERVER_SHARED_GUARD(nUserActionFailed);
	TLS_TRACE_BEGIN;

	this->Socket->Send("c", 0x25);

	TLS_TRACE_END_NO_RETURN;
}

