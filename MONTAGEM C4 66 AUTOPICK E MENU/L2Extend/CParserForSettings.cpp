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

	Coded by Fr3DBr
*/

#include "CParserForSettings.h"

CLexerForSettings *pSettingsLexer;
CParserForSettings *pSettingsParser;

extern "C"
{
	CSettingsDB g_SettingsDB;

	INT64 g_nMinStatTable = offsetof(CSettingsDB, nMinStats);
	INT64 g_nMaxStatTable = offsetof(CSettingsDB, nMaxStats);
	INT64 g_nRecStatTable = offsetof(CSettingsDB, nRecStats);

	OccupationNametoID Occupation2ID[] = 
	{
		// Class Name, Occupation ID, Unknown, RestartPointGroup, Unknown
		{ L"human_fighter", 0, 0, 1, 0 },
		{ L"human_magician", 10, 0, 1024, 0 },
		{ L"elf_fighter", 18, 0, 262144, 0 },
		{ L"elf_magician", 25, 0, 33554432, 0 },
		{ L"darkelf_fighter", 31, 0, -2147483647-1, 0 },
		{ L"darkelf_magician", 38, 0, 0, 64 },
		{ L"orc_fighter", 44, 0, 0, 4096 },
		{ L"orc_shaman", 49, 0, 0, 131072 },
		{ L"dwarf_apprentice", 53, 0, 0, 2097152 },
		{ L"duelist", 88, 0, 0, 0 },
		{ L"dreadnought", 89, 0, 0, 0 },
		{ L"phoenix_knight", 90, 0, 0, 0 },
		{ L"hell_knight", 91, 0, 0, 0 },
		{ L"sagittarius", 92, 0, 0, 0 },
		{ L"adventurer", 93, 0, 0, 0 },
		{ L"archmage", 94, 0, 0, 0 },
		{ L"soultaker", 95, 0, 0, 0 },
		{ L"arcana_lord", 96, 0, 0, 0 },
		{ L"cardinal", 97, 0, 0, 0 },
		{ L"hierophant", 98, 0, 0, 0 },
		{ L"evas_templar", 99, 0, 0, 0 },
		{ L"sword_muse", 100, 0, 0, 0 },
		{ L"wind_rider", 101, 0, 0, 0 },
		{ L"moonlight_sentinel", 102, 0, 0, 0 },
		{ L"mystic_muse", 103, 0, 0, 0 },
		{ L"elemental_master", 104, 0, 0, 0 },
		{ L"evas_saint", 105, 0, 0, 0 },
		{ L"shilien_templar", 106, 0, 0, 0 },
		{ L"spectral_dancer", 107, 0, 0, 0 },
		{ L"ghost_hunter", 108, 0, 0, 0 },
		{ L"ghost_sentinel", 109, 0, 0, 0 },
		{ L"storm_screamer", 110, 0, 0, 0 },
		{ L"spectral_master", 111, 0, 0, 0 },
		{ L"shilien_saint", 112, 0, 0, 0 },
		{ L"titan", 113, 0, 0, 0 },
		{ L"grand_khavatari", 114, 0, 0, 0 },
		{ L"dominator", 115, 0, 0, 0 },
		{ L"doomcryer", 116, 0, 0, 0 },
		{ L"fortune_seeker", 117, 0, 0, 0 },
		{ L"maestro", 118, 0, 0, 0 },
		{ L"male_soldier", 123, 0, 524288, 0 },
		{ L"female_soldier", 124, 0, 1048576, 0 }
	};
}

CLexerForSettings::CLexerForSettings(bool bFakeInstance)
{
    static bool _init_done = false;
    
	if (! _init_done) 
	{
        _init_done = true;
		LPVOID *org_vmt = (LPVOID*)0xABBF18; // real VMT address
        LPVOID* my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[9], &my_vmt[9], 1);   // yyaction()
	}
}

CParserForSettings::CParserForSettings(bool bFakeInstance)
{
    static bool _init_done = false;
    
	if (! _init_done) 
	{
        _init_done = true;
		LPVOID *org_vmt = (LPVOID*)0xAD7808;   // real VMT address
        LPVOID* my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[1], &my_vmt[1], 1);   // yyaction()
	}
}

yywint_t CLexerForSettings::yyaction(int action)
{
	typedef yywint_t(*t)(CLexerForSettings*, int);
	t f = (t)0x8D8DC0;
	yywint_t  token = f(this, action);
	
	if ( token >= 0x10000 )
	{
		//YYSTYPE& yylval = *(YYSTYPE*)yyparserptr->yylvalptr;
		//wstring cValue = this->yytext;
		//CLog::Add(CLog::blue, "Lexing Settings... %ls 0x%04X -> Value : %d - %d", this->yytext, token, yylval.int_value);
	}

	//MessageBoxW( NULL, this->yytext, this->yytext, 0 );

	return token;
}


//--------------------------------------------------
void CParserForSettings::yyaction(int action)
{
	typedef void(*t)(CParserForSettings*, int);
	t f = (t)0x8EBDF0;
	f(this,action);

	// Bigger Array 00BF9F84 TO 
	// RBX + 2E8

	//YYSTYPE& yylval = *(YYSTYPE*)yylexerptr->yyparserptr->yylvalptr;
	//CLog::Add(CLog::blue, "Parsing Settings... ->>>>>>> %ls 0x%02X - Value : %d", yylval.id_value, action, yylval.int_value);
}

//-----------------------------------------------------------------

VOID CSettingsDB::Initialize()
{
	// Install My Hooks Into The original VMT...
    pSettingsLexer  = new CLexerForSettings(true);
    pSettingsParser = new CParserForSettings(true);

	HookDatabaseSystem();
	ExtendDataArrays();
	FixMethods();
}

VOID CSettingsDB::HookDatabaseSystem()
{
	// Creating DB PTR
	char *pSettingsDB = (char *)&g_SettingsDB;

	// Fixing the Class References
	WriteRelativeAddress(0x47FFB5, 3, pSettingsDB, 0);	// BuilderCMD_SendHome()
	WriteRelativeAddress(0x4B70AB, 3, pSettingsDB, 0);	// CComCli::RequestBBSInit()
	WriteRelativeAddress(0x51C732, 3, pSettingsDB, 0);	// CDB::RequestCreateChar()
	WriteRelativeAddress(0x58A56E, 3, pSettingsDB, 0);	// LoadSelectedCharacterPacket
	WriteRelativeAddress(0x58A720, 3, pSettingsDB, 0);	// LoadSelectedCharacterPacket
	WriteRelativeAddress(0x58A85C, 3, pSettingsDB, 0);	// LoadSelectedCharacterPacket
	WriteRelativeAddress(0x5957F6, 3, pSettingsDB, 0);	// CDBSocketOp::SendHome()
	WriteRelativeAddress(0x5958C3, 3, pSettingsDB, 0);	// CDBSocketOp::SendHome()
	WriteRelativeAddress(0x6430AB, 3, pSettingsDB, 0);	// LoadData
	WriteRelativeAddress(0x70774D, 3, pSettingsDB, 0);	// COlympiadUser::ReadyForMatch()
	WriteRelativeAddress(0x7FCEA0, 3, pSettingsDB, 0);	// sub_7FCE90
	WriteRelativeAddress(0x80D679, 3, pSettingsDB, 0);	// User::TimerExpiredOnPartyMatching()
	WriteRelativeAddress(0x80D712, 3, pSettingsDB, 0);	// User::TimerExpiredOnPartyMatching()
	WriteRelativeAddress(0x8242FE, 3, pSettingsDB, 0);	// User::Restart()
	WriteRelativeAddress(0x824C9F, 3, pSettingsDB, 0);	// User::Restart()
	WriteRelativeAddress(0x84B863, 3, pSettingsDB, 0);	// User::User()
	WriteRelativeAddress(0x88F0D3, 3, pSettingsDB, 0);	// RequestUserCommand()
	WriteRelativeAddress(0x893D80, 3, pSettingsDB, 0);	// sub_893150
	WriteRelativeAddress(0x95F69D, 3, pSettingsDB, 0);	// sub_95F690
	WriteRelativeAddress(0x95F749, 3, pSettingsDB, 0);	// sub_95F740
	WriteRelativeAddress(0x95F769, 3, pSettingsDB, 0);	// sub_95F760
	WriteRelativeAddress(0x95F7A9, 3, pSettingsDB, 0);	// sub_95F7A0
	WriteRelativeAddress(0x95F7D9, 3, pSettingsDB, 0);	// sub_95F7D0
	WriteRelativeAddress(0x9706A9, 3, pSettingsDB, 0);	// sub_9706A0
	WriteRelativeAddress(0x9706C9, 3, pSettingsDB, 0);	// sub_9706C0
	WriteRelativeAddress(0x970709, 3, pSettingsDB, 0);	// sub_970700
	WriteRelativeAddress(0x970739, 3, pSettingsDB, 0);	// sub_970730
	WriteRelativeAddress(0x95F6AD, 0, pSettingsDB, 0);	// sub_95F690
	WriteRelativeAddress(0x9705D9, 0, pSettingsDB, 0);	// sub_9705C0
	WriteRelativeAddress(0x97068D, 0, pSettingsDB, 0);	// sub_9705C0
}

VOID CSettingsDB::ExtendDataArrays()
{
	// Creating DB PTR
	char *pSettingsDB = (char *)&g_SettingsDB;

	// Patching Initial Stats / Initial Items [Class ID Array]
	WriteRelativeAddress(0x8EA583, 3, &Occupation2ID, 0);
	WriteMemoryBYTE(0x8EA5B3, sizeof(Occupation2ID));
	WriteRelativeAddress(0x8EA613, 3, &Occupation2ID, 0);
	WriteMemoryBYTE(0x8EA643, sizeof(Occupation2ID));

	// Fixxing the Offsets of the Stats Table at the Parser
	WriteMemoryDWORD(0x8EC627, offsetof(CSettingsDB, nMinStats));
	WriteMemoryDWORD(0x8EC640, offsetof(CSettingsDB, nMaxStats));
	WriteMemoryDWORD(0x8EC659, offsetof(CSettingsDB, nRecStats));

	// Fixxing the Offsets of the Stats Table at User::User()
	WriteMemoryDWORD(0x84B86A+3, offsetof(CSettingsDB, nRecStats)+0x04);
	WriteMemoryDWORD(0x84B87E+3, offsetof(CSettingsDB, nRecStats)+0x10);
	WriteMemoryDWORD(0x84B892+3, offsetof(CSettingsDB, nRecStats)+0x08);
	WriteMemoryDWORD(0x84B8A6+3, offsetof(CSettingsDB, nRecStats)+0x00);
	WriteMemoryDWORD(0x84B8BA+3, offsetof(CSettingsDB, nRecStats)+0x14);
	WriteMemoryDWORD(0x84B8CE+3, offsetof(CSettingsDB, nRecStats)+0x0C);

	// Fixxing the Offsets of the Validate Subjob Parameters
	WriteMemoryDWORD(0x851E1B+4, ((INT32)pSettingsDB)+(0x400000 * -1)+(offsetof(CSettingsDB, nRecStats)+0x04));
	WriteMemoryDWORD(0x851E30+4, ((INT32)pSettingsDB)+(0x400000 * -1)+(offsetof(CSettingsDB, nRecStats)+0x10));
	WriteMemoryDWORD(0x851E45+4, ((INT32)pSettingsDB)+(0x400000 * -1)+(offsetof(CSettingsDB, nRecStats)+0x08));
	WriteMemoryDWORD(0x851E5A+4, ((INT32)pSettingsDB)+(0x400000 * -1)+(offsetof(CSettingsDB, nRecStats)+0x00));
	WriteMemoryDWORD(0x851E6F+4, ((INT32)pSettingsDB)+(0x400000 * -1)+(offsetof(CSettingsDB, nRecStats)+0x14));
	WriteMemoryDWORD(0x851E84+4, ((INT32)pSettingsDB)+(0x400000 * -1)+(offsetof(CSettingsDB, nRecStats)+0x0C));

	// Fixxing the Offsets of the Initial Items Creation
	// 0E285F90 - 0E285FB0 - 0E285FB8
	WriteMemoryDWORD(0x51C9F9, ((INT32)pSettingsDB)+(0x400000 * -1)+0x20);
	WriteMemoryDWORD(0x51CA0A, ((INT32)pSettingsDB)+(0x400000 * -1)+0x28);
	WriteMemoryDWORD(0x51CA44, ((INT32)pSettingsDB)+(0x400000 * -1)+0x20);
	WriteMemoryDWORD(0x51CA51, ((INT32)pSettingsDB)+(0x400000 * -1)+0x28);
	WriteMemoryDWORD(0x51CA7D, ((INT32)pSettingsDB)+(0x400000 * -1)+0x20);
}

VOID CSettingsDB::FixMethods()
{
	// Fixxing the Initial Stats when the Player Login ! User::User()
	WriteInstruction(0x84B825, (INT32)CParserForSettings_InitialStatsFix_Hook1, 0, 0xE9);

	// Fixxing the Initial Stats when a Character is Created !
	WriteInstruction(0x85F125, (INT32)CParserForSettings_InitialStatsFix_Hook2, 0, 0xE9);
	WriteInstruction(0x85FA90, (INT32)CParserForSettings_InitialStatsFix_Hook3, 0, 0xE9);

	// Fixxing the Initial Stats when the Player Login ! Validate SubJob Parameters
	WriteInstruction(0x851D8D, (INT32)CParserForSettings_InitialStatsFix_Hook4, 0, 0xE9);
}