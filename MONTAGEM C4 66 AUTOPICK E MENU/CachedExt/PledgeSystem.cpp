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

#include "PledgeSystem.h"
#include "Global.h"
#include "CashedFunctions.h"
#include "../L2Extend/SharedCached.h"
#include <map>

static std::map<int, CPledgeExt*> m_SubUnits;

DWORD _SendReplyToLoadPledgeExit = 0x004951BC;
DWORD _SendReplyToLoadPledgeExit2 = 0x00495356;

void __declspec(naked) SendReplyToLoadPledgeLanucher()
{
	__asm
	{
		mov edx, [esp+4]
		push edx
		push ecx
		call CPledgeSystem::SendReplyToLoadPledge
		add esp, 0Ch
		jmp _SendReplyToLoadPledgeExit
	}
}

void __declspec(naked) SendReplyToLoadPledgeLanucher2()
{
	__asm
	{
		mov edx, [esp+4]
		push edx
		push ecx
		call CPledgeSystem::SendReplyToLoadPledge
		add esp, 0Ch
		jmp _SendReplyToLoadPledgeExit2
	}
}

void CPledgeSystem::Initialize()
{
	WriteInstruction(0x4951B7, (DWORD)SendReplyToLoadPledgeLanucher, 0, 0xE8); //Reply load by pledge id
	WriteInstruction(0x495351, (DWORD)SendReplyToLoadPledgeLanucher2, 0, 0xE8);	//Reply load by pledge name
}

int nCPledgeSystemRequestUpdateUserSubPledge = 0;
bool __cdecl CPledgeSystem::RequestUpdateUserSubPledge(CQuerySocket *pSocket, unsigned char *packet)
{
	CASHED_SHARED_GUARD(nCPledgeSystemRequestUpdateUserSubPledge);
	TLS_TRACE_BEGIN;

	DBConn *pDBConn = new DBConn;
	int nUserID = 0;
	int nPledgeID = 0;
	int nPledgeType = 0;
	int nRank = 0;

	Disassemble(packet, "dddd", &nUserID, &nPledgeID, &nPledgeType, &nRank);

	if (!pDBConn->Execute(L"UPDATE user_data SET pledge_type = %d, grade = %d WHERE char_id = %d AND pledge_id = %d", nPledgeType, nRank, nUserID, nPledgeID))
	{
		CLog::Add(CLog::red, L"Cannot update pledge type:%d and grade:%d for user:%d pledge:%d", nPledgeType, nRank, nUserID, nPledgeID);
	}
	delete pDBConn;

	TLS_TRACE_END(false);
}

bool __cdecl CPledgeSystem::RequestSavePledgePower(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	int nPledgeID = 0, nRank = 0;
	DWORD Power;
	Disassemble(packet, "ddd", &nPledgeID, &nRank, &Power);
	if(pDBConn->Execute(L"UPDATE pledge_ext SET [%d] = %d WHERE pledge_id = %d", nRank, Power, nPledgeID))
	{
	}
	else
	{
		if(pDBConn->Execute(L"EXEC lin_AddPledgeExt %d", nPledgeID))
			CLog::Add(CLog::blue, L"Pledge[%d] has been added to pledge_ext table", nPledgeID);
	}
	delete pDBConn;

	return false;
}

bool __cdecl CPledgeSystem::RequestCreateExtPledgeInfo(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	int nPledgeID = 0;
	Disassemble(packet, "d", &nPledgeID);
	if(!pDBConn->Execute(L"EXEC lin_AddPledgeExt %d", nPledgeID))
	{
		CLog::Add(CLog::blue, L"Can't save Pledge[%d] to database", nPledgeID);
	}
	delete pDBConn;

	return false;
}

bool __cdecl CPledgeSystem::RequestSetPledgeReputation(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	int nPledgeID = 0, nReputation = 0;
	Disassemble(packet, "dd", &nPledgeID, &nReputation);
	if(pDBConn->Execute(L"UPDATE pledge_ext SET [reputation] = %d WHERE pledge_id = %d", nReputation, nPledgeID))
	{
		CLog::Add(CLog::black, L"Reputation for pledge[%d] has been changed to[%d]", nPledgeID, nReputation);
	}
	else
	{
		delete pDBConn;
		pDBConn = new DBConn;
		if(pDBConn->Execute(L"EXEC lin_AddPledgeExt %d", nPledgeID))
			CLog::Add(CLog::blue, L"Pledge[%d] has been added to database", nPledgeID);
	}
	delete pDBConn;

	return false;
}

bool __cdecl CPledgeSystem::RequestAcquirePledgeSkill(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	int nPledgeID = 0, nSkillID = 0, nLevel = 0;
	Disassemble(packet, "ddd", &nPledgeID, &nSkillID, &nLevel);
	
	switch(nLevel)
	{
	case 1:
		{
			pDBConn->Execute(L"INSERT INTO [pledge_skills]([pledge_id],[skill_id],[skill_level]) VALUES (%d, %d, %d)", nPledgeID, nSkillID, nLevel );
			break;
		}
	case 2:
	case 3:
		{
			pDBConn->Execute(L"UPDATE [pledge_skills] SET [skill_level]=%d WHERE [pledge_id]=%d AND [skill_id]=%d", nLevel, nPledgeID, nSkillID);
			break;
		}
	default:
		{
			CLog::Add(CLog::red, L"[%s] Invalid level[%d] pledge[%d]", __FUNCTION__, nLevel, nPledgeID);
			break;
		}
	}

	delete pDBConn;

	return false;
}

int nCPledgeSystemSendReplyToLoadPledge = 0;
void __cdecl CPledgeSystem::SendReplyToLoadPledge(CPledge *pPledge, CSocket *pSocket)
{
	CASHED_SHARED_GUARD(nCPledgeSystemSendReplyToLoadPledge);
	TLS_TRACE_BEGIN;
	DBConn *pDBConn = NULL;

	char Buffer[16384];
	memset(Buffer, 0, 16384);
	int nMemberPos = 0;
	int nBuffLen = 16384;
	int nLen = 0;
	nLen = Assemble(Buffer, nBuffLen, "cSddS", 0x15, pPledge->wszClanName, pPledge->nPledgeID, pPledge->nMasterID, pPledge->wszMasterName);
	nMemberPos = nLen;
	nLen += 4; //Space for member amount;

	//Pledge Ext Info part
	int nReputation = 0;
	DWORD PowerData[10];
	memset(PowerData, 0, 10);
	pDBConn = new DBConn();
	pDBConn->BindD(&nReputation);
	for(int n=1;n<10;n++)
		pDBConn->BindD(&PowerData[n]);
	
	if(pDBConn->Execute(L"EXEC lin_LoadPledgeExt %d", pPledge->nPledgeID))
	{
		pDBConn->Fetch();
	}
	delete pDBConn;
	nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "dddddddddd", nReputation, PowerData[1], PowerData[2], PowerData[3], PowerData[4], PowerData[5], PowerData[6], PowerData[7], PowerData[8], PowerData[9]);

	//Pledge Skills part
	pDBConn = new DBConn;
	std::map <int, int> SkillMap; //<ID, Level>
	int nSkillID, nSkillLevel;
	pDBConn->BindD(&nSkillID);
	pDBConn->BindD(&nSkillLevel);
	if(pDBConn->Execute(L"SELECT [skill_id], [skill_level] FROM pledge_skills WHERE [pledge_id] = %d", pPledge->nPledgeID))
	{
		while(pDBConn->Fetch())
		{
			SkillMap[nSkillID] = nSkillLevel;
		}
	}
	delete pDBConn;
	nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "d", SkillMap.size());
	if(SkillMap.size()>0)
	{
		for(std::map<int, int>::iterator Iter = SkillMap.begin(); Iter!=SkillMap.end();Iter++)
		{
			nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "dd", Iter->first, Iter->second);
		}
	}

	pDBConn = new DBConn;
	SubUnit subUnits[10];
	int subUnitsIndex = 0;

	int nPledgeType = 0;
	wchar_t subPledgeName[25];
	wcscpy(subPledgeName, L"");
	wchar_t leaderName[25];
	wcscpy(leaderName, L"");
	int nLeaderId = 0;
	
	pDBConn->BindS(subPledgeName, 25);
	pDBConn->BindD(&nPledgeType);
	pDBConn->BindS(leaderName, 25);
	pDBConn->BindD(&nLeaderId);

	if (pDBConn->Execute(L"SELECT [name], [pledge_type], isnull(leaderName, ''), isnull(leaderId, 0) FROM [dbo].[pledge_subpledge] WHERE id = %d", pPledge->nPledgeID))
	{
		while(pDBConn->Fetch())
		{
			wcscpy(subUnits[subUnitsIndex].name, subPledgeName);
			subUnits[subUnitsIndex].nPledgeType = nPledgeType;
			wcscpy(subUnits[subUnitsIndex].leaderName, leaderName);
			subUnits[subUnitsIndex].leaderId = nLeaderId;
			subUnitsIndex++;
		}
	}
	delete pDBConn;

	nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "d", subUnitsIndex);
	for (int i = 0; i < subUnitsIndex; i++)
	{
		nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "dSSd", subUnits[i].nPledgeType, subUnits[i].name, subUnits[i].leaderName, subUnits[i].leaderId);
	}

	nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "cccccc", pPledge->n1stRoyalGuard, pPledge->n2stRoyalGuard, pPledge->n1stOrderofKnights, pPledge->n2stOrderofKnights, pPledge->n3stOrderofKnights, pPledge->n4stOrderofKnights);

	//Members Part 
	nPledgeType = 0;
	int nMemberAmount = 0;
	int nDBID = 0;
	wchar_t wszName[25];
	int nLevel = 0;
	int nClass = 0;
	int nGender = 0;
	int nRace = 0;
	int nRank = 0;
	int nSponsorID = 0;
	int nApprenticeID = 0;
	int nJoinLevelToAcademy = 0;
	pDBConn = new DBConn();
	pDBConn->BindS(wszName, 25);
	pDBConn->BindD(&nDBID);
	pDBConn->BindD(&nGender);
	pDBConn->BindD(&nRace);
	pDBConn->BindD(&nClass);
	pDBConn->BindD(&nLevel);
	pDBConn->BindD(&nPledgeType);
	pDBConn->BindD(&nRank);
	pDBConn->BindD(&nSponsorID);
	pDBConn->BindD(&nApprenticeID);
	pDBConn->BindD(&nJoinLevelToAcademy);

	if(pDBConn->Execute(L"SELECT TOP 160 [char_name],[char_id],[gender],[race],[class],[Lev],[pledge_type],[grade],[sponsor_id],[apprentice_id],[joinleveltoacademy] FROM [user_data] WHERE [pledge_id] = %d AND [account_id] > 0", pPledge->nPledgeID))
	{
		while(pDBConn->Fetch())
		{
			nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "dSddddddddd", nDBID, wszName, nLevel, nClass, nGender, nRace, nPledgeType, nRank, nSponsorID, nApprenticeID, nJoinLevelToAcademy);
			nMemberAmount++;
		}
	}
	delete pDBConn;

	Assemble((char*)(Buffer+nMemberPos), 4, "d", nMemberAmount);

	//Pledge Data part 
	nLen += Assemble((char*)(Buffer+nLen), (nBuffLen-nLen), "dddddddddddddddddddcccccc", pPledge->now_war_id, pPledge->root_name_value, pPledge->challenge_time, pPledge->oust_time, pPledge->alliance_id, pPledge->nVar6, pPledge->castle_id, pPledge->agit_id, pPledge->rank, pPledge->status, pPledge->private_flag, pPledge->crest_id, pPledge->is_guilty, pPledge->dismiss_reserved_time, pPledge->skill_level, pPledge->alliance_ousted_time, pPledge->alliance_withdraw_time, pPledge->alliance_dismiss_time, pPledge->emblem_id, pPledge->n1stRoyalGuard, pPledge->n2stRoyalGuard, pPledge->n1stOrderofKnights, pPledge->n2stOrderofKnights, pPledge->n3stOrderofKnights, pPledge->n4stOrderofKnights);

	//Send(pSocket, "b", nLen, Buffer);
	pSocket->Lock(__FILEW__, __LINE__);
	pSocket->DirectSend(Buffer, nLen);
	pSocket->Unlock();

	TLS_TRACE_END_NO_RETURN;
}

bool __cdecl CPledgeSystem::RequestReorganizeMember(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	wchar_t pledgeMemberName[25];
	int newPledgeType = 0;
	int pledgeId = 0;
	int nGrade = 0;

	Disassemble(packet, "Sddd", sizeof(pledgeMemberName), pledgeMemberName, &newPledgeType, &pledgeId, &nGrade);

	if (!pDBConn->Execute(L"UPDATE user_data SET pledge_type = %d, grade = %d WHERE pledge_id = %d AND char_name = '%ls'", newPledgeType, nGrade, pledgeId, pledgeMemberName))
	{
		CLog::Add(CLog::red, L"For user '%s' and pledgeId[%d] cannot be changed pledgetype.", pledgeMemberName, newPledgeType);
	}

	delete pDBConn;

	return false;
}

bool __cdecl CPledgeSystem::RequestCreateSubPledgeOrSetCaptain(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *DB = new DBConn;
	int result = 0;
	int nUpdate = 0;
	int nUserObj = 0;
	int nNpcObj = 0;
	int nPledgeId = 0;
	int nPledgeType = 0;
	wchar_t subPledgeName[26];
	wchar_t leaderName[26];
	int nleaderId = 0;
	DB->BindD(&result);
	DB->BindD(&nPledgeId);
	DB->BindD(&nPledgeType);
	DB->BindD(&nleaderId);
	DB->BindS(&subPledgeName[26], 26);
	DB->BindS(&leaderName[26], 26);

	Disassemble(packet, "ddddSSd", &nUserObj, &nNpcObj, &nPledgeId, &nPledgeType, sizeof(subPledgeName), subPledgeName, sizeof(leaderName), leaderName, &nleaderId);

	nUpdate = wcscmp(leaderName, L"");
	if (DB->Execute(L"EXEC lin_SubPledge %d, '%ls', %d, '%ls', %d", nPledgeId, subPledgeName, nPledgeType, (!nUpdate ? L"NULL": leaderName), nleaderId))
	{
		if((result = DB->Fetch()))
		{
			if(!nUpdate)
				CLog::Add(CLog::black, L"Captain left. Pledge [%d][%d]", nPledgeId, nPledgeType);
			else
			{
				CLog::Add(CLog::black, L"New SubPledge Created. Pledge [%d][%d]", nPledgeId, nPledgeType);
				pSocket->Send("chddddddS", 0xDA, S_NEW_SUBPLEDGE_OR_SET_CAPTAIN, result, nUserObj, nNpcObj, nPledgeId, nPledgeType, nleaderId, subPledgeName);
			}
		}
	}
	else
	{
		pSocket->Send("chd", 0xDA, S_NEW_SUBPLEDGE_OR_SET_CAPTAIN, 0);
		CLog::Add(CLog::red, L"Subpledge '%s' for pledge [%d] type[%d] cannot be created or captain is not set.", subPledgeName, nPledgeId, nPledgeType);
	}

	delete DB;
	return false;
}

bool __cdecl CPledgeSystem::RequestDeleteSubPledge(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	int nPledgeId = 0;

	Disassemble(packet, "d", &nPledgeId);

	if (!pDBConn->Execute(L"DELETE FROM [pledge_subpledge] WHERE id = %d", nPledgeId))
	{
		CLog::Add(CLog::red, L"Subpledges for pledge [%d] cannot be deleted.", nPledgeId);
	}

	delete pDBConn;

	return false;
}

bool __cdecl CPledgeSystem::RequestSetSponsor(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *DB = new DBConn;
	int nObjUser = 0;
	int nDBID = 0;
	int nObjSponsor = 0;
	int nSponsorId = 0;

	Disassemble(packet, "dddd", &nObjUser, &nDBID, &nObjSponsor, &nSponsorId);

	if (DB->Execute(L"UPDATE user_data SET sponsor_id=%d WHERE char_id=%d", nSponsorId, nDBID))
	{
		pSocket->Send("chddd", 0xDA, S_SET_SPONSOR, 1, nObjUser, nObjSponsor);
	}
	else
	{
		CLog::Add(CLog::red, L"Cannot set sponsor:%d for user:%d", nSponsorId, nDBID);
	}
	delete DB;

	return false;
}

bool __cdecl CPledgeSystem::RequestSetApprentice(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *DB = new DBConn;
	int nObjUser = 0;
	int nDBID = 0;
	int nObjApprentice = 0;
	int nApprenticeID = 0;

	Disassemble(packet, "dddd", &nObjUser, &nDBID, &nObjApprentice, &nApprenticeID);

	if (DB->Execute(L"UPDATE user_data SET apprentice_id=%d WHERE char_id=%d", nApprenticeID, nDBID))
	{
		pSocket->Send("chddd", 0xDA, S_SET_APPRENTICE, 1, nObjUser, nObjApprentice);
	}
	else
	{
		CLog::Add(CLog::red, L"Cannot set apprentice:%d for user:%d", nApprenticeID, nDBID);
	}
	delete DB;

	return false;
}

bool __cdecl CPledgeSystem::UpdateExInfo(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *pDBConn = new DBConn;
	int nUserID = 0;
	int nTitleColor = 0;
	int nJoinLevelAcademy = 0;

	Disassemble(packet, "ddd", &nUserID, &nTitleColor, &nJoinLevelAcademy);

	if (!pDBConn->Execute(L"UPDATE user_data SET joinleveltoacademy=%d WHERE char_id=%d", nJoinLevelAcademy, nUserID))
	{
		CLog::Add(CLog::red, L"Cannot update joinleveltoacademy:%d for user:%d", nJoinLevelAcademy, nUserID);
	}
	delete pDBConn;

	return false;
}

bool __cdecl CPledgeSystem::IncreaseMemberSubPledge(CQuerySocket *pSocket, unsigned char *packet)
{
	DBConn *DB = new DBConn;
	int result = 0;
	int nType = 0;
	int nPledgeObject = 0;
	int nMembers = 0;
	int nPledgeID = 0;
	int nTypeSubPledge = 0;
	DB->BindD(&result);
	DB->BindD(&nPledgeObject);
	DB->BindD(&nMembers);
	DB->BindD(&nPledgeID);
	DB->BindD(&nTypeSubPledge);

	Disassemble(packet, "dddd", &nPledgeObject, &nMembers, &nPledgeID, &nTypeSubPledge);

	
	switch(nTypeSubPledge)
	{
		case 100:
			nType = 1;
			break;
		case 200:
			nType = 2;
			break;
		case 1001:
			nType = 1;
			break;
		case 1002:
			nType = 2;
			break;
		case 2001:
			nType = 3;
			break;
		case 2002:
			nType = 4;
			break;
	}

	if(nTypeSubPledge < 1000)
	{
		if (DB->Execute(L"UPDATE [dbo].[Pledge] SET RoyalGuards%d =  %d WHERE pledge_id = %d", nType , nMembers, nPledgeID))
		{
			CLog::Add(CLog::black, L"New SubPledge Members Updated. Pledge [%d][%d]", nPledgeID, nTypeSubPledge);
			pSocket->Send("chddddd", 0xDA, S_INCREASE_MEMBER_SUBPLEDGE, result, nPledgeObject, nPledgeID, nTypeSubPledge, nMembers);	
		}
		else
		{
			pSocket->Send("chd", 0xDA, S_INCREASE_MEMBER_SUBPLEDGE, 0);
			CLog::Add(CLog::red, L"Subpledge type[%d] of Pledge [%d] update members fails.", nTypeSubPledge, nPledgeID);
		}
	}
	else
	{
		if (DB->Execute(L"UPDATE [dbo].[Pledge] SET OrderOfKnights%d =  %d WHERE pledge_id = %d", nType , nMembers, nPledgeID))
		{
			CLog::Add(CLog::black, L"New SubPledge Members Updated. Pledge [%d][%d]", nPledgeID, nTypeSubPledge);
			pSocket->Send("chddddd", 0xDA, S_INCREASE_MEMBER_SUBPLEDGE, result, nPledgeObject, nPledgeID, nTypeSubPledge, nMembers);	
		}
		else
		{
			pSocket->Send("chd", 0xDA, S_INCREASE_MEMBER_SUBPLEDGE, 0);
			CLog::Add(CLog::red, L"Subpledge type[%d] of Pledge [%d] update members fails.", nTypeSubPledge, nPledgeID);
		}
	}


	delete DB;
	return false;
}