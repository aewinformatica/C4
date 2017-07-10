#include "Global.h"
#include "CInfectedSkillsSystem.h"
#include "CUserDB.h"

void CInfectedSkillsSystem::Initialize()
{
}

bool CInfectedSkillsSystem::RequestLoadInfectedSkills(CQuerySocket *pSocket, unsigned char *packet)
{
	unsigned int nUserID, nServerID;	//User ID = DB ID and Server ID = Game Object ID
	CObjectSP UserSP;
	
	Disassemble(packet, "dd", &nUserID, &nServerID);

	if(CUserDB::I()->GetUser(&UserSP, nUserID, true))
	{
		CUser *pUser = (CUser*)UserSP.pObject;

		int ActiveSkills[36][4]; ZeroMemory(ActiveSkills, sizeof(ActiveSkills));
		DBConn DB;

		for(int i=0; i < 36; ++i)
		{
			DB.BindD(&ActiveSkills[i][0]);
			DB.BindD(&ActiveSkills[i][1]);
			DB.BindD(&ActiveSkills[i][2]);
			DB.BindD(&ActiveSkills[i][3]);
		}

		if( DB.Execute(L"EXEC lin_LoadActiveSkill %d", nUserID) )
		{
			if ( DB.Fetch() )
			{
				// Success
				pSocket->Send("cdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", 
					0x6F, nServerID, 36, ActiveSkills[0][0], ActiveSkills[0][1], ActiveSkills[0][2], ActiveSkills[0][3], ActiveSkills[1][0], ActiveSkills[1][1], ActiveSkills[1][2], ActiveSkills[1][3], ActiveSkills[2][0], ActiveSkills[2][1], ActiveSkills[2][2], ActiveSkills[2][3], 
					ActiveSkills[3][0], ActiveSkills[3][1], ActiveSkills[3][2], ActiveSkills[3][3], ActiveSkills[4][0], ActiveSkills[4][1], ActiveSkills[4][2], ActiveSkills[4][3], ActiveSkills[5][0], ActiveSkills[5][1], ActiveSkills[5][2], ActiveSkills[5][3], 
					ActiveSkills[6][0], ActiveSkills[6][1], ActiveSkills[6][2], ActiveSkills[6][3], ActiveSkills[7][0], ActiveSkills[7][1], ActiveSkills[7][2], ActiveSkills[7][3], ActiveSkills[8][0], ActiveSkills[8][1], ActiveSkills[8][2], ActiveSkills[8][3], 
					ActiveSkills[9][0], ActiveSkills[9][1], ActiveSkills[9][2], ActiveSkills[9][3], ActiveSkills[10][0], ActiveSkills[10][1], ActiveSkills[10][2], ActiveSkills[10][3], ActiveSkills[11][0], ActiveSkills[11][1], ActiveSkills[11][2], ActiveSkills[11][3], 
					ActiveSkills[12][0], ActiveSkills[12][1], ActiveSkills[12][2], ActiveSkills[12][3], ActiveSkills[13][0], ActiveSkills[13][1], ActiveSkills[13][2], ActiveSkills[13][3], ActiveSkills[14][0], ActiveSkills[14][1], ActiveSkills[14][2], ActiveSkills[14][3], 
					ActiveSkills[15][0], ActiveSkills[15][1], ActiveSkills[15][2], ActiveSkills[15][3], ActiveSkills[16][0], ActiveSkills[16][1], ActiveSkills[16][2], ActiveSkills[16][3], ActiveSkills[17][0], ActiveSkills[17][1], ActiveSkills[17][2], ActiveSkills[17][3], 
					ActiveSkills[18][0], ActiveSkills[18][1], ActiveSkills[18][2], ActiveSkills[18][3], ActiveSkills[19][0], ActiveSkills[19][1], ActiveSkills[19][2], ActiveSkills[19][3], ActiveSkills[20][0], ActiveSkills[20][1], ActiveSkills[20][2], ActiveSkills[20][3], 
					ActiveSkills[21][0], ActiveSkills[21][1], ActiveSkills[21][2], ActiveSkills[21][3], ActiveSkills[22][0], ActiveSkills[22][1], ActiveSkills[22][2], ActiveSkills[22][3], ActiveSkills[23][0], ActiveSkills[23][1], ActiveSkills[23][2], ActiveSkills[23][3], 
					ActiveSkills[24][0], ActiveSkills[24][1], ActiveSkills[24][2], ActiveSkills[24][3], ActiveSkills[25][0], ActiveSkills[25][1], ActiveSkills[25][2], ActiveSkills[25][3], ActiveSkills[26][0], ActiveSkills[26][1], ActiveSkills[26][2], ActiveSkills[26][3], 
					ActiveSkills[27][0], ActiveSkills[27][1], ActiveSkills[27][2], ActiveSkills[27][3], ActiveSkills[28][0], ActiveSkills[28][1], ActiveSkills[28][2], ActiveSkills[28][3], ActiveSkills[29][0], ActiveSkills[29][1], ActiveSkills[29][2], ActiveSkills[29][3], 
					ActiveSkills[30][0], ActiveSkills[30][1], ActiveSkills[30][2], ActiveSkills[30][3], ActiveSkills[31][0], ActiveSkills[31][1], ActiveSkills[31][2], ActiveSkills[31][3], ActiveSkills[32][0], ActiveSkills[32][1], ActiveSkills[32][2], ActiveSkills[32][3], 
					ActiveSkills[33][0], ActiveSkills[33][1], ActiveSkills[33][2], ActiveSkills[33][3], ActiveSkills[34][0], ActiveSkills[34][1], ActiveSkills[34][2], ActiveSkills[34][3], ActiveSkills[35][0], ActiveSkills[35][1], ActiveSkills[35][2], ActiveSkills[35][3]
				);

			}
		}
		else
		{
			//Failure
			CLog::Add(CLog::red, L"ERROR IN : EXEC lin_LoadActiveSkill %d", nUserID);
		}
	}

	return false;
}
int nCInfectedSkillsSystemRequestSaveInfectedSkills = 0;
bool CInfectedSkillsSystem::RequestSaveInfectedSkills(CQuerySocket *pSocket, unsigned char *packet)
{
	CASHED_SHARED_GUARD(nCInfectedSkillsSystemRequestSaveInfectedSkills);
	TLS_TRACE_BEGIN;

	bool result = true;
	CObjectSP UserSP;
	unsigned int nUserID, nSkillCount;	//User ID = DB ID
	
	const unsigned char * p = Disassemble(packet, "dd", &nUserID, &nSkillCount);

	if(CUserDB::I()->GetUser(&UserSP, nUserID, true))
	{
		CUser *pUser = (CUser*)UserSP.pObject;
		ZeroMemory(pUser->m_ActionSkill.ActiveSkills, sizeof(pUser->m_ActionSkill.ActiveSkills));
		if(nSkillCount > 36)
			nSkillCount = 36;

		for(unsigned int i=0; i < nSkillCount; ++i)
		{
			p = Disassemble((unsigned char *)p, "dddd", &pUser->m_ActionSkill.ActiveSkills[i][0], &pUser->m_ActionSkill.ActiveSkills[i][1], &pUser->m_ActionSkill.ActiveSkills[i][2], &pUser->m_ActionSkill.ActiveSkills[i][3]);
		}
	}

	TLS_TRACE_END(result);
}

int nCInfectedSkillsSystemRequestSaveToDB = 0;
bool CInfectedSkillsSystem::RequestSaveToDB(CQuerySocket *pSocket, unsigned char *packet)
{
	CASHED_SHARED_GUARD(nCInfectedSkillsSystemRequestSaveToDB);
	TLS_TRACE_BEGIN;

	bool result = true;
	CObjectSP UserSP;
	unsigned int nUserID;	//User ID = DB ID
	
	const unsigned char * p = Disassemble(packet, "d", &nUserID);

	if(CUserDB::I()->GetUser(&UserSP, nUserID, true))
	{
		CUser *pUser = (CUser*)UserSP.pObject;
		int ActiveSkills[36][4];
		memcpy(ActiveSkills, &pUser->m_ActionSkill.ActiveSkills, 576);

		WCHAR *pQuery = L"EXEC lin_UpdateActiveSkill %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d";
		DBConn DB;
		if( !DB.Execute(pQuery,nUserID, ActiveSkills[0][0], ActiveSkills[0][1], ActiveSkills[0][2], ActiveSkills[0][3], ActiveSkills[1][0], ActiveSkills[1][1], ActiveSkills[1][2], ActiveSkills[1][3], ActiveSkills[2][0], ActiveSkills[2][1], ActiveSkills[2][2], ActiveSkills[2][3], 
				ActiveSkills[3][0], ActiveSkills[3][1], ActiveSkills[3][2], ActiveSkills[3][3], ActiveSkills[4][0], ActiveSkills[4][1], ActiveSkills[4][2], ActiveSkills[4][3], ActiveSkills[5][0], ActiveSkills[5][1], ActiveSkills[5][2], ActiveSkills[5][3], 
				ActiveSkills[6][0], ActiveSkills[6][1], ActiveSkills[6][2], ActiveSkills[6][3], ActiveSkills[7][0], ActiveSkills[7][1], ActiveSkills[7][2], ActiveSkills[7][3], ActiveSkills[8][0], ActiveSkills[8][1], ActiveSkills[8][2], ActiveSkills[8][3], 
				ActiveSkills[9][0], ActiveSkills[9][1], ActiveSkills[9][2], ActiveSkills[9][3], ActiveSkills[10][0], ActiveSkills[10][1], ActiveSkills[10][2], ActiveSkills[10][3], ActiveSkills[11][0], ActiveSkills[11][1], ActiveSkills[11][2], ActiveSkills[11][3], 
				ActiveSkills[12][0], ActiveSkills[12][1], ActiveSkills[12][2], ActiveSkills[12][3], ActiveSkills[13][0], ActiveSkills[13][1], ActiveSkills[13][2], ActiveSkills[13][3], ActiveSkills[14][0], ActiveSkills[14][1], ActiveSkills[14][2], ActiveSkills[14][3], 
				ActiveSkills[15][0], ActiveSkills[15][1], ActiveSkills[15][2], ActiveSkills[15][3], ActiveSkills[16][0], ActiveSkills[16][1], ActiveSkills[16][2], ActiveSkills[16][3], ActiveSkills[17][0], ActiveSkills[17][1], ActiveSkills[17][2], ActiveSkills[17][3], 
				ActiveSkills[18][0], ActiveSkills[18][1], ActiveSkills[18][2], ActiveSkills[18][3], ActiveSkills[19][0], ActiveSkills[19][1], ActiveSkills[19][2], ActiveSkills[19][3], ActiveSkills[20][0], ActiveSkills[20][1], ActiveSkills[20][2], ActiveSkills[20][3], 
				ActiveSkills[21][0], ActiveSkills[21][1], ActiveSkills[21][2], ActiveSkills[21][3], ActiveSkills[22][0], ActiveSkills[22][1], ActiveSkills[22][2], ActiveSkills[22][3], ActiveSkills[23][0], ActiveSkills[23][1], ActiveSkills[23][2], ActiveSkills[23][3], 
				ActiveSkills[24][0], ActiveSkills[24][1], ActiveSkills[24][2], ActiveSkills[24][3], ActiveSkills[25][0], ActiveSkills[25][1], ActiveSkills[25][2], ActiveSkills[25][3], ActiveSkills[26][0], ActiveSkills[26][1], ActiveSkills[26][2], ActiveSkills[26][3], 
				ActiveSkills[27][0], ActiveSkills[27][1], ActiveSkills[27][2], ActiveSkills[27][3], ActiveSkills[28][0], ActiveSkills[28][1], ActiveSkills[28][2], ActiveSkills[28][3], ActiveSkills[29][0], ActiveSkills[29][1], ActiveSkills[29][2], ActiveSkills[29][3], 
				ActiveSkills[30][0], ActiveSkills[30][1], ActiveSkills[30][2], ActiveSkills[30][3], ActiveSkills[31][0], ActiveSkills[31][1], ActiveSkills[31][2], ActiveSkills[31][3], ActiveSkills[32][0], ActiveSkills[32][1], ActiveSkills[32][2], ActiveSkills[32][3], 
				ActiveSkills[33][0], ActiveSkills[33][1], ActiveSkills[33][2], ActiveSkills[33][3], ActiveSkills[34][0], ActiveSkills[34][1], ActiveSkills[34][2], ActiveSkills[34][3], ActiveSkills[35][0], ActiveSkills[35][1], ActiveSkills[35][2], ActiveSkills[35][3]
		) )
		{
			//Failure
			CLog::Add(CLog::red, L"ERROR IN : EXEC lin_UpdateActiveSkill %d", nUserID);
		}
		else
		{
			ZeroMemory(pUser->m_ActionSkill.ActiveSkills, sizeof(ActiveSkills));
			result = true;
		}
	}

	TLS_TRACE_END(result);
}
