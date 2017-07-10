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

#include "Global.h"

// YY Parser
#include "yywclex.h"
#include "yywcpars.h"

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#ifndef YYSTYPE
union tagYYSTYPE {
	wchar_t*	id_value;
	int			int_value;
	double		num_value;
	LPVOID		ptr_value;
	long double	lnum_value;
};

#define YYSTYPE union tagYYSTYPE
#endif

#define yyattribute(index) (((YYSTYPE*)yyattributestackptr)[yytop + (index)])

enum TokensForSkillEnchanting
{
	SE_SKILL_NAME = 0x10001,
	SE_ERROR = 0x10002,
	SE_NUMBER = 0x10003,
	SE_ENCHANT_SKILL_BEGIN = 0x10004,
	SE_ENCHANT_SKILL_END = 0x10005,
	SE_ORIGINAL_SKILL = 0x10006,
	SE_ROUTE_ID = 0x10007,
	SE_ENCHANT_ID = 0x10008,
	SE_SKILL_LEVEL = 0x10009,
	SE_EXP = 0x1000A,
	SE_SP = 0x1000B,
	SE_ITEM_NEEDED = 0x1000C,
	SE_PROB_76 = 0x1000D,
	SE_PROB_77 = 0x1000E,
	SE_PROB_78 = 0x1000F,
	SE_PROB_79 = 0x10010,
	SE_PROB_80 = 0x10011,
	SE_PROB_81 = 0x10012,
	SE_PROB_82 = 0x10013,
	SE_PROB_83 = 0x10014,
	SE_PROB_84 = 0x10015,
	SE_PROB_85 = 0x10016
};

class CLexerForSkillEnchanting : public yywflexer
{
public:
	virtual yywint_t yylex() { return 0; };  // fake
	virtual yywint_t yyaction(int action);

	CLexerForSkillEnchanting(bool bFakeInstance);
	CLexerForSkillEnchanting() {};
};

void InitializeSkillEnchanting();
void InitializeSkillEnchantingAfterLoadage();

class  SkillEnchantInfo
{
public:

	/* 0x00 */		int     skill_id;               // case 2
	/* 0x04 */		int     new_enchant_skill_level;        // case 5
	/* 0x08 */		int     org_skill_level;        // case 2
	/* 0x0Ch */		int     enchant_skill_level;    // case 1
	/* 0x10h */		int     route_id;               // case 3 
	/* 0x14h */		int     enchant_id;             // case 4
	/* 0x18h */		int     exp;                    // case 6
	/* 0x1Ch */		int     sp;                             // case 7
	///* 0x20h */		int     dw20;                   // case 8  = 0BAADF00Dh
	/* 0x20h */		std::vector<int> item_need;  
	///* 0x30h */		__int64 i30;                    // = 01C90DC10h => int_1C90DC10 dd 0ABABABABh
	///* 0x38h */		__int64 i38;                    // = 01C90DC10h => int_1C90DC10 dd 0ABABABABh
	///* 0x40h */		__int64 i40;					// case 8
	/* 0x40h */		std::vector<int> item_num_needed;
	///* 0x50h */		__int64 i50;
	///* 0x58h */		__int64 i58;
	/* 0x60h */		int     prob_76;                // case 10
	/* 0x64h */		int     prob_77;                // case 11
	/* 0x68h */		int     prob_78;                // case 12
	/* 0x6Ch */		int     prob_79;
	/* 0x70h */		int     prob_80;
	/* 0x74h */		int     prob_81;
	/* 0x78h */		int     prob_82;
	/* 0x7Ch */		int     prob_83;
	/* 0x80h */		int     prob_84;
	/* 0x84h */		int     prob_85;
};

class CParserForSkillEnchanting : public yywfparser
{
public:
	virtual void yyaction(int action);

//protected:
	/* 0F0 */ INT8 unk001[0xD0];
	/* 1C0 */ SkillEnchantInfo *pSkillEnchantInfo;
	/* 1C8 */

	CParserForSkillEnchanting(bool bFakeInstance);
	CParserForSkillEnchanting() {};
};

class CSkillEnchantDB
{
	public:

		// CSkillEnchantDB map doesn't use CSkillKey (fortunatelly),
		// but rather a pair of ints to store skill id and level
		typedef std::pair<int, int> EnchKey;

		struct EnchKeyLess
		{
			bool operator() (const EnchKey& left, const EnchKey& right) const
			{
				if (left.first < right.first) return true;
				if (left.first > right.first) return false;
				return left.second < right.second;
			}
		};

		typedef const std::map<EnchKey, SkillEnchantInfo*, EnchKeyLess> SkillEnchantMap;
		typedef SkillEnchantMap::const_iterator SkillEnchantIterator;

		CompileTimeSizeCheck(SkillEnchantMap::value_type, 16);

		// Calling Constructor
		CSkillEnchantDB(){};
		
		// Calling Destructor
		~CSkillEnchantDB(){};
	
		/* 0x00  */ void * p00;
		/* 0x08  */ void * p08;
		/* 0x10  */ void * p10;
		/* 0x18  */ void * p18;
		/* 0x20 */	SkillEnchantMap m_SkillEnchantInfo;
		/* 0x28 */	list<int> list_28;
		/* 0x38 */	list<int> list_38;

		static CSkillEnchantDB* Static();

		SkillEnchantInfo* GetSkillEnchantInfo(int nSkillId, int nLevel);
		int GetProbIndex(int nUserLevel);
		bool IsLearnableLevel(int nUserLevel);
		bool CheckNpcEnchantSkillSuggestion(int NpcIndex, int TalkerID, int TalkerSMIndex, int SkillNameID, SkillEnchantInfo *&pEnchantInfo, User *&pUser);
		static bool EnchantSkillInfo(CSocket *pSocket, CSPacket *pPacket);
		static bool RequestEnchantSkill(CSocket *pSocket, CSPacket *pPacket);

		static void EnchantSkillDetailInfo(CSocket *pSocket, CSPacket *pPacket);
		void NpcEnchantSkillSuggestion(int NpcIndex, int TalkerID, int TalkerSMIndex, int SkillNameID);
		static void CSkillEnchantDB_NpcEnchantSkillSuggestion(int NpcIndex, int TalkerID, int TalkerSMIndex, int SkillNameID);
};

extern "C"
{
	void SkillEnchantInfoFix_Hook1();
	void SkillEnchantInfoFix_Hook2();
	void SkillEnchantInfoFix_Hook5();
	void SkillEnchantInfoFix_Hook6();
	void SkillEnchantInfoFix_Hook7();
}
