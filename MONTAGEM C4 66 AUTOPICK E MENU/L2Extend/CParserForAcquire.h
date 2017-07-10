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

/* Implementation/Information Credits goes to WFX @ PostPacific */

#pragma once

#include "Global.h"
#include <list>

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

enum TokenForSkillAcquire 
{
	SA_T_BEGIN = 0x10001,
	SA_T_END = 0x10002,
	SA_FISHING_BEGIN = 0X10003,
	SA_FISHING_END = 0X10004,
	SA_PD_WORD = 0x10005,
	SA_T_STRING = 0x10006,
	SA_T_INT = 0x10007,
	SA_T_BOOL = 0x10008, // true, false
	SA_T_DOUBLE = 0x10009,
	SA_SKILL_BEGIN = 0X1000A,
	SA_SKILL_END = 0X1000B,
	SA_SKILL_NAME = 0X1000C,
	SA_GET_LV = 0X1000D,
	SA_ITEM_NEEDED = 0X1000E,
	SA_LV_UP_SP = 0X10010,
	SA_AUTO_GET = 0X10012,
	SA_T_INCLUDE = 0x10013
};

class CLexerForAcquire : public yywflexer
{
	public:
		
		virtual yywint_t yylex() { return 0; };  // fake
		virtual yywint_t yyaction(int action);
		CLexerForAcquire(bool bFakeInstance);
		CLexerForAcquire() {};
};

void InitializeSkillAcquire();

class CSkillAcquireInfo
{
	public:
	
		int i00;
		int i04;
		int i08;
		int i0c;
		int i10;
		int i14;
		int i18;
		int i1c;
}; // sizeof() == 0x20

#define MAX_OCCUPATION_ID 136

class CSkillAcquireDB
{
	public:
		
		// Calling Constructor
		CSkillAcquireDB()
		{
			// * NOT NEEDED IN THAT CASE *
			//typedef void (__thiscall *CSADBC) (CSkillAcquireDB *);
			//CSADBC xConstruct = (CSADBC)0x79D540L;
			//xConstruct(this);
		};
		
		// Calling Destructor
		~CSkillAcquireDB() 
		{
			// * NOT NEEDED IN THAT CASE *
			//typedef void (__thiscall *CSADBD) (CSkillAcquireDB *);
			//CSADBD xDestruct = (CSADBD)0x79D750L;
			//xDestruct(this);
		};

		CSkillAcquireInfo *GetSkillAcquireInfo(int nClass, int nSkillID, int nSkillLevel)
		{
			typedef CSkillAcquireInfo *(__fastcall *GSAI) (CSkillAcquireDB *, int, int, int);
			GSAI xGSAI = (GSAI)0x0079C9A0L;
			return xGSAI(this, nClass, nSkillID, nSkillLevel);
		}

		CSkillAcquireInfo *GetEtcSkillAcquireInfo(int nSkillType, int nSkillID, int nSkillLevel)
		{
			typedef CSkillAcquireInfo *(__fastcall *GSAI) (CSkillAcquireDB *, int, int, int);
			GSAI xGSAI = (GSAI)0x0079CB80L;
			return xGSAI(this, nSkillType, nSkillID, nSkillLevel);
		}

		// Attributes :

		struct SkillAcquireKey
		{
			union {
				int class_id;   // for SkillAcquireInfo (nSkillType == 0)
				int skill_type; // for EtcSkillAcquireInfo (nSkillType != 0)
			};
			int skill_id;
			int skill_level;

			bool operator< (const SkillAcquireKey& other) const
			{
				if (this->class_id < other.class_id) return true;
				if (this->class_id > other.class_id) return false;
				if (this->skill_id < other.skill_id) return true;
				if (this->skill_id > other.skill_id) return false;
				return this->skill_level < other.skill_level;
			}
		};

		// don't know if this is the same as in parser, but if yes, then there
		// are missing members, since this one has some bool at offset 5Ch
		struct SkillAcquireInfo;

		typedef const std::map<SkillAcquireKey, SkillAcquireInfo*> SkillAcquireMap;
		typedef SkillAcquireMap::const_iterator SkillAcquireIterator;

		CompileTimeSizeCheck(SkillAcquireMap, 0x18);
		CompileTimeSizeCheck(SkillAcquireMap::value_type, 0x18);

		/* 0000 */  SkillAcquireMap skillAcquireMap; // used in GetSkillAcquireInfo
		/* 0018 */  list<int> list_018;											// dunno what is it
		/* 0030 */  CSkillAcquireInfo by_occupation[0x77];						// sizeof = 0x20 * 0x77
		/* 0F10 */  SkillAcquireMap etcSkillAcquireMap; // used in GetEtcSkillAcquireInfo
		/* 0F28 */  list<int> list_0F28;										// dunno what is it
		/* 0F40 */  CSkillAcquireInfo ary_0F40[2];								// sizeof = 0x20 *2
		/* 0F80 */  CSkillAcquireInfo new_by_occupation[MAX_OCCUPATION_ID +1];	// sizeof = 0x20 * 0x77
};

extern "C"
{
	void CSkillAcquireLexer_DatabaseOffsetFix_Hook1();
	void CSkillAcquireLexer_DatabaseOffsetFix_Hook2();
	void CSkillAcquireLexer_DatabaseOffsetFix_Hook3();
	void CSkillAcquireLexer_DatabaseOffsetFix_Hook4();

	// Auto Learning
	void CSkillAcquireLexer_AutoLearnFixHook01();	void CSkillAcquireLexer_AutoLearnFixHook02();	void CSkillAcquireLexer_AutoLearnFixHook03();
	void CSkillAcquireLexer_AutoLearnFixHook04();	void CSkillAcquireLexer_AutoLearnFixHook05();	void CSkillAcquireLexer_AutoLearnFixHook06();
	void CSkillAcquireLexer_AutoLearnFixHook07();	void CSkillAcquireLexer_AutoLearnFixHook08();	void CSkillAcquireLexer_AutoLearnFixHook09();
	void CSkillAcquireLexer_AutoLearnFixHook10();
	void CSkillAcquireLexer_AutoLearnFixHook11();	void CSkillAcquireLexer_AutoLearnFixHook12();	void CSkillAcquireLexer_AutoLearnFixHook13();
	void CSkillAcquireLexer_AutoLearnFixHook14();	void CSkillAcquireLexer_AutoLearnFixHook15();	void CSkillAcquireLexer_AutoLearnFixHook16();
	void CSkillAcquireLexer_AutoLearnFixHook17();	void CSkillAcquireLexer_AutoLearnFixHook18();	void CSkillAcquireLexer_AutoLearnFixHook19();
	void CSkillAcquireLexer_AutoLearnFixHook20();
	void CSkillAcquireLexer_AutoLearnFixHook21();	void CSkillAcquireLexer_AutoLearnFixHook22();	void CSkillAcquireLexer_AutoLearnFixHook23();
	void CSkillAcquireLexer_AutoLearnFixHook24();	void CSkillAcquireLexer_AutoLearnFixHook25();	void CSkillAcquireLexer_AutoLearnFixHook26();
	void CSkillAcquireLexer_AutoLearnFixHook27();	void CSkillAcquireLexer_AutoLearnFixHook28();	void CSkillAcquireLexer_AutoLearnFixHook29();
	void CSkillAcquireLexer_AutoLearnFixHook30();
	void CSkillAcquireLexer_AutoLearnFixHook31();	void CSkillAcquireLexer_AutoLearnFixHook32();	void CSkillAcquireLexer_AutoLearnFixHook33();
	void CSkillAcquireLexer_AutoLearnFixHook34();	void CSkillAcquireLexer_AutoLearnFixHook35();	void CSkillAcquireLexer_AutoLearnFixHook36();
	void CSkillAcquireLexer_AutoLearnFixHook37();	void CSkillAcquireLexer_AutoLearnFixHook38();	void CSkillAcquireLexer_AutoLearnFixHook39();
	void CSkillAcquireLexer_AutoLearnFixHook40();
	void CSkillAcquireLexer_AutoLearnFixHook41();	void CSkillAcquireLexer_AutoLearnFixHook42();	void CSkillAcquireLexer_AutoLearnFixHook43();
	void CSkillAcquireLexer_AutoLearnFixHook44();	void CSkillAcquireLexer_AutoLearnFixHook45();
}