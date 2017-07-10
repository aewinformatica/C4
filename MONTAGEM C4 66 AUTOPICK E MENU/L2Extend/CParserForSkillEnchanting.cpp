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

#include "CParserForSkillEnchanting.h"
#include "CAmpedX64.h"
#include "CSocket.h"

static int subst_yyaction = 0;
static map<wstring, int>	t_map; // map of words and their tokens
static int				t_map_reqs = 0;
static bool bFoundSkillEnchant = false;
CLexerForSkillEnchanting *pEnchantLexer;

extern "C"
{
	CSkillEnchantDB g_SkillEnchantDB;
}

class CSocket;

CLexerForSkillEnchanting::CLexerForSkillEnchanting(bool bFakeInstance)
{
	static bool _init_done = false;

	if (! _init_done)
	{
		_init_done = true;
		LPVOID *org_vmt = (LPVOID*)0xACABB8; // real VMT address
		LPVOID* my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[9], &my_vmt[9], 1); // yyaction()
	}
}

CParserForSkillEnchanting::CParserForSkillEnchanting(bool bFakeInstance)
{
	static bool _init_done = false;

	if (! _init_done)
	{
		_init_done = true;
		LPVOID *org_vmt = (LPVOID*)0xAE3258; // real VMT address
		LPVOID* my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[1], &my_vmt[1], 1); // yyaction()
	}
}

yywint_t CLexerForSkillEnchanting::yyaction(int action)
{
	typedef yywint_t(*t)(CLexerForSkillEnchanting*, int); t f = (t)0x8DCA30;
	yywint_t  token = f(this, action);
	
	if (token == SE_ERROR) 
	{
		YYSTYPE& yylval = *(YYSTYPE*)yyparserptr->yylvalptr;
		wstring cString = yylval.id_value;

		if ( wcsncmp(L"prob_79", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_79;
		}
		else if ( wcsncmp(L"prob_80", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_80;
		}
		else if ( wcsncmp(L"prob_81", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_81;
		}
		else if ( wcsncmp(L"prob_82", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_82;
		}
		else if ( wcsncmp(L"prob_83", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_83;
		}
		else if ( wcsncmp(L"prob_84", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_84;
		}
		else if ( wcsncmp(L"prob_85", cString.c_str(), cString.size()) == 0 )
		{
			token = SE_PROB_76;
			subst_yyaction = SE_PROB_85;
		}
	}

	return token;
}



//--------------------------------------------------
void CParserForSkillEnchanting::yyaction(int action)
{
	typedef void(*t)(CParserForSkillEnchanting*, int);
	t f = (t)0x8F7FB0;

	#define CHECK_SUBST_AND_FALLBACK { if (!subst_yyaction) { f(this,action); return; } }

	switch(action)
	{
		//case 0x00: new [] == 0x70 for 10004h
		//case 0x01: 
		//case 0x02: get skill ID & Level for 10001h
		//case 0x03: set param number for 10007h & 10003h
		//case 0x04: set param number for 10008h & 10003h
		//case 0x05: set param number for 10009h & 10003h
		//case 0x06: set param number for 1000Ah & 10003h
		//case 0x07: set param number for 1000Bh & 10003h
		//case 0x08: get param for 1000Ch
		//case 0x09: empty
		//case 0x0A: set param number for 1000Dh & 10003h
		//case 0x0B: set param number for 1000Eh & 10003h
		//case 0x0C: set param number for 1000Fh & 10003h
		//case 0x0e: empty
		//case 0x0f: set param number for 10001h & 10003h after 1000Ch
		case 0x0A: 
			{
				CHECK_SUBST_AND_FALLBACK;

				int  arg1 = yyattribute(0).int_value;

				switch(subst_yyaction)
				{
					case SE_PROB_79:
						pSkillEnchantInfo->prob_79 = arg1;
						break;

					case SE_PROB_80:
						pSkillEnchantInfo->prob_80 = arg1;
						break;

					case SE_PROB_81:
						pSkillEnchantInfo->prob_81 = arg1;
						break;

					case SE_PROB_82:
						pSkillEnchantInfo->prob_82 = arg1;
						break;

					case SE_PROB_83:
						pSkillEnchantInfo->prob_83 = arg1;
						break;

					case SE_PROB_84:
						pSkillEnchantInfo->prob_84 = arg1;
						break;

					case SE_PROB_85:
						pSkillEnchantInfo->prob_85 = arg1;
						break;
				}

				subst_yyaction = 0;
			}
			break;


		default:
			f(this,action);
			break;
	}
}

SkillEnchantInfo* CSkillEnchantDB::GetSkillEnchantInfo(int nSkillId, int nLevel)
{
	typedef SkillEnchantInfo* (__fastcall *__gsei)(CSkillEnchantDB*, int, int);
	__gsei _gsei = (__gsei) 0x0079E7A0;
	return _gsei(this, nSkillId, nLevel);
}

int CSkillEnchantDB::GetProbIndex(int nUserLevel)
{
	typedef int (__fastcall *_GET_PROB_INDEX) (int nUserLevel);
	_GET_PROB_INDEX xGetProbIndex = (_GET_PROB_INDEX)0x0079DB10L;
	return xGetProbIndex(nUserLevel);
}

bool CSkillEnchantDB::IsLearnableLevel(int nUserLevel)
{
	typedef bool (__fastcall *_IS_LEARNABLE_LEVEL) (int nUserLevel);
	_IS_LEARNABLE_LEVEL xIsLearnableLevel = (_IS_LEARNABLE_LEVEL)0x0079DA30L;
	return xIsLearnableLevel(nUserLevel);
}

bool CSkillEnchantDB::CheckNpcEnchantSkillSuggestion(int NpcIndex, int TalkerID, int TalkerSMIndex, int SkillNameID, SkillEnchantInfo *&pEnchantInfo, User *&pUser)
{
	typedef bool (__fastcall *CNESS) (int, int, int, int, SkillEnchantInfo*&, User*&);
	CNESS xCheckNpcEnchantSkillSuggestion = (CNESS)0x007A06C0L;
	return xCheckNpcEnchantSkillSuggestion(NpcIndex, TalkerID, TalkerSMIndex, SkillNameID, pEnchantInfo, pUser);
}

CSkillEnchantDB *CSkillEnchantDB::Static()
{
	return	(CSkillEnchantDB*) &g_SkillEnchantDB;
}

INT32 nCSkillEnchantDBNpcEnchantSkillSuggestion = 0;
void CSkillEnchantDB::NpcEnchantSkillSuggestion(int NpcIndex, int TalkerID, int TalkerSMIndex, int SkillNameID)
{
	SkillEnchantInfo *pEnchantInfo = NULL;
	SkillEnchantInfo *pSEI = NULL;
	User* pUser = NULL;
	char pBuf[0x2000];
	char *f = pBuf;
	PINT32 prob = NULL;
	INT32 nBufLen = 0x2000;
	INT32 SkillCount = 0;
	CSkillKey cSkillKey(SkillNameID);

	L2SERVER_SHARED_GUARD1(nCSkillEnchantDBNpcEnchantSkillSuggestion);
	TLS_TRACE_BEGIN;

	__try
	{
		if(this->CheckNpcEnchantSkillSuggestion(NpcIndex, TalkerID, TalkerSMIndex, SkillNameID, pEnchantInfo, pUser))
		{
			if(pUser->IsValidUser())
			{
				if(pEnchantInfo)
				{
					if(this->IsLearnableLevel(pUser->SD->nLevel))
					{
						for(SkillEnchantIterator Iter=this->m_SkillEnchantInfo.begin(); Iter!=this->m_SkillEnchantInfo.end(); ++Iter)
						{
							pSEI = Iter->second;
							if(pSEI->skill_id == cSkillKey.skill_id)
							{
							
								if(cSkillKey.level == pSEI->enchant_skill_level)
								{
									prob = &pSEI->prob_76 + this->GetProbIndex(pUser->SD->nLevel);
									Assemble(f, nBufLen, "ddddfdddd", pSEI->skill_id, pSEI->new_enchant_skill_level, *prob, pSEI->sp, (INT64)pSEI->exp, 0, 0, 0, 0);
									f += 40;
									nBufLen -= 40;
									SkillCount++;
								}
							}
						}
						pUser->Socket->Send("chddb", 0x0FE, 0x18, 0, SkillCount, SkillCount*40, pBuf);
					}
					else
						CLog::Add(CLog::red, "[%s][%d] invalid user(%s) level(%d)", __FUNCTION__, __LINE__, pUser->SD->wszName, pUser->SD->nLevel);
				}
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CLog::Add(CLog::red, "[%s][%d] Critical error in NpcEnchantSkillSuggestion", __FUNCTION__, __LINE__);
	}
	TLS_TRACE_END;
}

void CSkillEnchantDB_NpcEnchantSkillSuggestion(int NpcIndex, int TalkerID, int TalkerSMIndex, int SkillNameID)
{
	CSkillEnchantDB::Static()->NpcEnchantSkillSuggestion(NpcIndex, TalkerID, TalkerSMIndex, SkillNameID);
}

INT32 nCSkillEnchantDBEnchantSkillDetailInfo = 0;
void CSkillEnchantDB::EnchantSkillDetailInfo(CSocket *pSocket, CSPacket *pPacket)
{
	bool result = 0;
	int *prob = NULL;
	int len = 0;

	L2SERVER_SHARED_GUARD1(nCSkillEnchantDBEnchantSkillDetailInfo);
	TLS_TRACE_BEGIN;

	WORD	nExPacket = pPacket->GetWord(len); len += 2;
	DWORD	nTypeEnchant = pPacket->GetDWord(len); len += 4;
	DWORD	nSkillID = pPacket->GetDWord(len); len += 4;
	DWORD	nLevel = pPacket->GetDWord(len);

	__try
	{
		if(CSkillEnchantDB::Static())
		{
			for(SkillEnchantIterator Iter=CSkillEnchantDB::Static()->m_SkillEnchantInfo.begin(); Iter!=CSkillEnchantDB::Static()->m_SkillEnchantInfo.end(); ++Iter)
			{
				SkillEnchantInfo *pSEI = Iter->second;
				if(pSEI->skill_id == nSkillID)
				{
					if(pSEI->new_enchant_skill_level == nLevel)
					{
						vector <int>::iterator Count = pSEI->item_num_needed.begin();
						vector <int>::iterator Item = pSEI->item_need.begin();
						prob = &pSEI->prob_76 + CSkillEnchantDB::Static()->GetProbIndex(pSocket->user->SD->nLevel);
						pSocket->Send("chddddfddddd", 0x0FE, 0x5e, pSEI->skill_id, pSEI->new_enchant_skill_level, *prob, pSEI->sp, (INT64)pSEI->exp, 6221, (pSEI->item_num_needed.size() ? *Count : 0), 6220, (pSEI->item_need.size() ? *Item : 0), 6223);
						result = true;
					}
				}
			}
			if(!result)
				CLog::Add(CLog::red, "[%s][%d] Can't find skill info. SkillId[%d] Level[%d]", __FUNCTION__, __LINE__, nSkillID, nLevel);
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CLog::Add(CLog::red, "[%s][%d] Critical error in EnchantSkillDetailInfo", __FUNCTION__, __LINE__);
	}

	TLS_TRACE_END;
}

bool CSkillEnchantDB::EnchantSkillInfo(CSocket *pSocket, CSPacket *pPacket)
{
	DWORD	nEnchantType = pPacket->GetDWord(2);
	DWORD	nSkillID = pPacket->GetDWord(6);
	DWORD	nSkillLevel = pPacket->GetDWord(10);

	User* pUser = pSocket->user;
	if(pUser->IsValidUser())
	{
		pUser->SD->nEnchantType = nEnchantType;

		typedef bool (*t)(User*, CSocket*, int, int);
		t f = (t)0x79EEC0;
		return f(pUser, pSocket, nSkillID, nSkillLevel);
	}	

	return false;
}

bool CSkillEnchantDB::RequestEnchantSkill(CSocket *pSocket, CSPacket *pPacket)
{
	DWORD	nSkillID = pPacket->GetDWord(2);
	DWORD	nSkillLevel = pPacket->GetDWord(6);

	User* pUser = pSocket->user;
	if(pUser->IsValidUser())
	{
		typedef bool (*t)(User*, CSocket*, int, int);
		t f = (t)0x79F320;
		return f(pUser, pSocket, nSkillID, nSkillLevel);
	}
	return false;
}
//-----------------------------------------------------------------

void InitializeSkillEnchanting()
{
	// .text:00000000008F7FE9                 mov     ecx, 70h        ; jumptable 008F7FE7 case 0
	WriteMemoryDWORD(0x8F7FEA, sizeof(SkillEnchantInfo));

	WriteInstruction(0x79F194, (INT32)SkillEnchantInfoFix_Hook1, 0, 0xE9);
	WriteInstruction(0x7A0922, (INT32)SkillEnchantInfoFix_Hook2, 0, 0xE9);
	WriteInstruction(0x846B1A, (INT32)SkillEnchantInfoFix_Hook5, 0x32, 0xE9);
	WriteInstruction(0x846B96, (INT32)SkillEnchantInfoFix_Hook6, 0x24, 0xE9);
	WriteInstruction(0x846A1F, (INT32)SkillEnchantInfoFix_Hook7, 0x13, 0xE9);

	// new function for enchant skill info
	WriteInstruction(0x6CEE55, (INT32)&CSkillEnchantDB_NpcEnchantSkillSuggestion, 0, 0xE8);

	// install my hooks into the original vmt
    static CLexerForSkillEnchanting  *lexer  = NULL;
    lexer = new CLexerForSkillEnchanting(true);
    static CParserForSkillEnchanting *parser = NULL;
    parser = new CParserForSkillEnchanting(true);

	CSkillEnchantDB* pDB = &g_SkillEnchantDB;

	WriteRelativeAddress(0x64300F, 3, pDB, 0);
	WriteRelativeAddress(0x79EC5A, 3, pDB, 0);
	WriteRelativeAddress(0x79F199, 3, pDB, 0);
	WriteRelativeAddress(0x7A0927, 3, pDB, 0);
	WriteRelativeAddress(0x8469F6, 3, pDB, 0);
	WriteRelativeAddress(0x846F06, 3, pDB, 0);
	WriteRelativeAddress(0x8471C9, 3, pDB, 0);
	WriteRelativeAddress(0x8F8043, 3, pDB, 0);
	WriteRelativeAddress(0x960049, 3, pDB, 0);
	WriteRelativeAddress(0x960069, 3, pDB, 0);
	WriteRelativeAddress(0x970F60, 3, pDB, 0);

	//WriteInstruction(0x79F1A0, (INT32)&CSkillEnchantDB::GetSkillEnchantInfoExt, 0, 0xE8);
	//WriteInstruction(0x7A092E, (INT32)&CSkillEnchantDB::GetSkillEnchantInfoExt, 0, 0xE8);
}

void InitializeSkillEnchantingAfterLoadage()
{
	INT64 nAmpedX64Address = GetModuleAddress("AmpeDx64.dll");
	WriteMemoryBYTES(nAmpedX64Address + 0xECF6, 9, 0x48, 0xc7, 0xc0, 1, 0, 0, 0, 0x90, 0x90);  // inject Amped
	WriteMemoryBYTES(nAmpedX64Address + 0xAFA1, 6, 0x8B, 0x73, 0x06, 0x8B, 0x5B, 0x0A);
}
