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

enum TokensForSettings 
{
	
};

class CLexerForSettings : public yywflexer
{
	public:
	
		virtual yywint_t yylex() { return 0; };  // fake
		virtual yywint_t yyaction(int action);
		CLexerForSettings(bool bFakeInstance);
		CLexerForSettings() {};
};

//-------------------------------------------------
class CParserForSettings : public yywfparser
{
	public:
	
		virtual void yyaction(int action);
		CParserForSettings(bool bFakeInstance);
		CParserForSettings() {};
};

struct OccupationNametoID
{
	WCHAR *pOccupationName;
	int nOccupationID;
	int b;
	int c;
	int d;
};

#define CS_EXTENDED_CLASSES 14

class CSettingsDB
{
	public:

		CSettingsDB()
		{
			memset(OriginalDataBlock, 0x00, sizeof(OriginalDataBlock));
			memset(&nMinStats, 0x00, sizeof(nMinStats));
			memset(&nMaxStats, 0x00, sizeof(nMaxStats));
			memset(&nRecStats, 0x00, sizeof(nRecStats));
		}

		~CSettingsDB()
		{
		}

		/* Class Structure */
		BYTE  OriginalDataBlock[0x10000];
		INT32 nMinStats[119 + CS_EXTENDED_CLASSES][6];
		INT32 nMaxStats[119 + CS_EXTENDED_CLASSES][6];
		INT32 nRecStats[119 + CS_EXTENDED_CLASSES][6];

		// New Customized Sub System (CPCParamDB Hooks/Extenders)
		static VOID Initialize();
		static VOID HookDatabaseSystem();
		static VOID ExtendDataArrays();
		static VOID FixMethods();
};

extern "C"
{
	void CParserForSettings_InitialStatsFix_Hook1();
	void CParserForSettings_InitialStatsFix_Hook2();
	void CParserForSettings_InitialStatsFix_Hook3();
	void CParserForSettings_InitialStatsFix_Hook4();
}