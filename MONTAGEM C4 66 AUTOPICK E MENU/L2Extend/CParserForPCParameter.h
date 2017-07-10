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

enum TokensForPCParameter 
{
	
};

class CLexerForPCParameter : public yywflexer
{
	public:
	
		virtual yywint_t yylex() { return 0; };  // fake
		virtual yywint_t yyaction(int action);
		CLexerForPCParameter(bool bFakeInstance);
		CLexerForPCParameter() {};
};

//-------------------------------------------------
class CParserForPCParameter : public yywfparser
{
	public:
	
		virtual void yyaction(int action);
		CParserForPCParameter(bool bFakeInstance);
		CParserForPCParameter() {};
};

#define TOTAL_EXTENDED_RACES 4

class CPCParamDB
{
	public:

		/* CONSTRUCTOR */
		CPCParamDB()  
		{
			/* Original DataBlock */
			memset(bUnknown1  , 0x00, sizeof(bUnknown1));

			/* Integer Tables */
			memset(DataArray01, 0x00, sizeof(DataArray01));
			memset(DataArray02, 0x00, sizeof(DataArray02));
			memset(DataArray03, 0x00, sizeof(DataArray03));
			memset(DataArray04, 0x00, sizeof(DataArray04));
			memset(DataArray05, 0x00, sizeof(DataArray05));
			memset(DataArray06, 0x00, sizeof(DataArray06));
			memset(DataArray07, 0x00, sizeof(DataArray07));
			memset(DataArray08, 0x00, sizeof(DataArray08));
			memset(DataArray09, 0x00, sizeof(DataArray09));
			memset(DataArray10, 0x00, sizeof(DataArray10));
			memset(DataArray14, 0x00, sizeof(DataArray14));
			memset(DataArray15, 0x00, sizeof(DataArray15));

			/* Double Tables */
			memset(DataArray11, 0x00, sizeof(DataArray11));
			memset(DataArray12, 0x00, sizeof(DataArray12));
			memset(DataArray13, 0x00, sizeof(DataArray13));
			memset(DataArray16, 0x00, sizeof(DataArray16));
			memset(DataArray17, 0x00, sizeof(DataArray17));
			memset(DataArray18, 0x00, sizeof(DataArray18));
			memset(DataArray19, 0x00, sizeof(DataArray19));
			memset(DataArray20, 0x00, sizeof(DataArray20));
			memset(DataArray21, 0x00, sizeof(DataArray21));
			memset(DataArray22, 0x00, sizeof(DataArray22));
			memset(DataArray23, 0x00, sizeof(DataArray23));
			memset(DataArray24, 0x00, sizeof(DataArray24));
			memset(DataArray25, 0x00, sizeof(DataArray25));

			/* Extended Global Double Tables (Now they are part of the DB !) */
		};

		/* DESTRUCTOR */
		~CPCParamDB() { };
		
		// ORIGINAL BLOCK OF DATA + EXTENDING

		/* Original DataBlock */
		/* 0000 */ BYTE bUnknown1[0x20000];

		// EXTENDED CPCPARAM ARRAYS

		/* Integer Tables */
		/* 1580 */ BYTE DataArray01[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 1730 */ BYTE DataArray02[0x6C    + (TOTAL_EXTENDED_RACES*(0x6C/18))   ];
		/* 179C */ BYTE DataArray03[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 194C */ BYTE DataArray04[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 1AFC */ BYTE DataArray05[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 1CAC */ BYTE DataArray06[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 1E5C */ BYTE DataArray07[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 200C */ BYTE DataArray08[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 21BC */ BYTE DataArray09[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 236C */ BYTE DataArray10[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 251C */ BYTE DataArray14[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		/* 26CC */ BYTE DataArray15[0x1B0   + (TOTAL_EXTENDED_RACES*(0x1B0/18))  ];
		
		///* 287C */ BYTE PADDING1[0x04];

		/* Double Tables */
		/* 2880 */ BYTE DataArray11[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 4380 */ BYTE DataArray12[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 57C0 */ BYTE DataArray13[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray16[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ double DataArray17[0x3FF0  + (TOTAL_EXTENDED_RACES*(0x3FF0/18)) ];
		/* 0000 */ double DataArray18[0x3FF0  + (TOTAL_EXTENDED_RACES*(0x3FF0/18)) ];
		/* 0000 */ BYTE DataArray19[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray20[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray21[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray22[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray23[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray24[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];
		/* 0000 */ BYTE DataArray25[0x20000  + (TOTAL_EXTENDED_RACES*(0x20000/18)) ];

		/* Extended Global Double Tables (Now they are part of the DB !) */

		// Static 0xE1F3430h Instance Address

		// 00745860 void CPCParamDB::Load();

		// Official Re-written Functions
		static VOID SetIntValue(CPCParamDB *pDB, INT32 nSex, INT32 nOccupationID, INT32 nIsMystic, INT32 nTableID, INT32 nIntValue);
		static INT32 GetIntValue(CPCParamDB *pDB, INT32 nSex, INT32 nOccupationID, INT32 nTableID);

		// New Customized Sub System (CPCParamDB Hooks/Extenders)
		static VOID Initialize();
		static VOID HookDatabaseSystem();
		static VOID HookIntegerSystem();
		static VOID HookDoubleSystem();
		static VOID HookRestrictions();
		static VOID ExtendDataArrays();
		static VOID ExtendParser();
		static VOID HookORGSystem();
};

extern "C"
{
	void CParserForPCParameter_LexxerFix_Hook1();
	void CParserForPCParameter_LexxerFix_Hook2();
	void BuilderCMD_SetClass_Class_Hook();
	void BuilderCMD_SetSubJob_Class_Hook();
	void PCParam_Getter_Class_Hook1();
	void PCParam_Getter_Class_Hook2();
	void PCParam_Getter_Class_Hook3();
	void PCParam_Getter_Class_Hook4();
	void PCParam_Getter_Class_Hook5();
	void PCParam_Getter_Class_Hook6();
	void PCParam_Getter_Class_Hook7();
	void CShortCut_DeleteShortcut_Class_Hook();
	void CShortCut_Add_Class_Hook();
	void CSkillEnchantChecker_CheckLearnable_Class_Hook();
	void CSkillEnchantChecker_CheckRequestEnchantSkill_Class_Hook();
	void CSkillEnchantChecker_CheckNpcEnchantSkillSuggestion_Class_Hook();
	void CSkillEnchantChecker_CheckNpcShowEnchantSkillList_Class_Hook();
	void CSkillEffect_i_inform_Class_Hook();
	void ORG_MP_REG_System_Hook();
	void ORG_HP_REG_System_Hook();
	void Fixxing_Offset_Global_Array_Org_HP_CP();
	void Fixxing_Offset_Global_Array_Org_MP();
}