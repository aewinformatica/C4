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

#include "CParserForAcquire.h"

map<wstring, int> m_ExtendedClasses;
CLexerForAcquire *pAcquireLexer;

extern "C"
{
	CSkillAcquireDB g_SkillAcquireDB;
}

WCHAR * pOcupationsArray[] =
{
	L"fighter",	L"warrior",	L"gladiator", L"warlord", L"knight",
	L"paladin",	L"dark_avenger", L"rogue", L"treasure_hunter",
	L"hawkeye",	L"mage", L"wizard",	L"sorcerer", L"necromancer",
	L"warlock",	L"cleric", L"bishop", L"prophet", L"elven_fighter",
	L"elven_knight", L"temple_knight", L"swordsinger", L"elven_scout",
	L"plains_walker", L"silver_ranger",	L"elven_mage", L"elven_wizard",
	L"spellsinger",	L"elemental_summoner", L"oracle", L"elder",
	L"dark_fighter", L"palus_knight", L"shillien_knight", L"bladedancer", L"assassin",
	L"abyss_walker", L"phantom_ranger", L"dark_mage", L"dark_wizard", L"spellhowler",
	L"phantom_summoner", L"shillien_oracle", L"shillien_elder", L"orc_fighter",
	L"orc_raider", L"destroyer", L"orc_monk", L"tyrant", L"orc_mage", L"orc_shaman",
	L"overlord", L"warcryer", L"dwarven_fighter", L"scavenger", L"bounty_hunter",
	L"artisan", L"warsmith", L"duelist", L"dreadnought", L"phoenix_knight", L"hell_knight",
	L"sagittarius", L"adventurer", L"archmage", L"soultaker", L"arcana_lord", L"cardinal",
	L"hierophant", L"evas_templar", L"sword_muse", L"wind_rider", L"moonlight_sentinel", L"mystic_muse",
	L"elemental_master", L"evas_saint", L"shillien_templar", L"spectral_dancer",L"ghost_hunter",
	L"ghost_sentinel", L"storm_screamer", L"spectral_master", L"shillien_saint",L"titan",
	L"grand_khavatari", L"dominator", L"doomcryer", L"fortune_seeker",L"maestro",
	L"male_kamael_solider", L"female_kamael_solider", L"trooper", L"warder", L"kamael_berserker", 
	L"male_soulbreaker", L"female_soulbreaker", L"arbalester", L"doombringer",L"male_soulhound",
	L"female_soulhound", L"trickster", L"inspector", L"judicator"
};

// constructors
CLexerForAcquire::CLexerForAcquire(bool bTrueInstance)
{
	static bool _init_done = false;
	
	if (! _init_done) 
	{
		_init_done = true;
		LPVOID *org_vmt = (LPVOID*)0x00B01438; // real VMT address
        LPVOID *my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[9], &my_vmt[9], 1);   // yyaction()
	}
}

// ---------------------------------------------------------------------

yywint_t CLexerForAcquire::yyaction(int action)
{
	typedef yywint_t(*t)(CLexerForAcquire*, int); t f = (t)0x902830;
	yywint_t  token = f(this, action);

	if (token == SA_T_STRING) 
	{
		YYSTYPE& yylval = *(YYSTYPE*)yyparserptr->yylvalptr;
		wstring cValue = yylval.id_value;

		// CLog::Add(CLog::blue, "Parsing SkillAcquire... [%ls]->(0x%04X)", yylval.id_value, token);
		
		if (wcsncmp(L"_begin", cValue.c_str()+(cValue.size()-6), 6) == 0) 
		{
			if ( m_ExtendedClasses.find(cValue.substr(0, cValue.size()-6)) != m_ExtendedClasses.end() )
			{
				yylval.int_value = m_ExtendedClasses[cValue.substr(0, cValue.size()-6)];
				token = SA_T_BEGIN;
			}
		} 
			
		if (wcsncmp(L"_end", cValue.c_str()+(cValue.size()-4), 4) == 0) 
		{
			if ( m_ExtendedClasses.find(cValue.substr(0, cValue.size()-4)) != m_ExtendedClasses.end() )
			{
				yylval.int_value = m_ExtendedClasses[cValue.substr(0, cValue.size()-4)];
				token = SA_T_END;
			}
		}

		if (wcsncmp(L"include_", cValue.c_str(), 8) == 0) 
		{
			if ( m_ExtendedClasses.find(cValue.substr(8, cValue.size()-8)) != m_ExtendedClasses.end() )
			{
				yylval.int_value = m_ExtendedClasses[cValue.substr(8, cValue.size()-8)];
				token = SA_T_INCLUDE;
			}
		}
	}

	return token;
}

void InitializeSkillAcquire()
{
	CompileTimeSizeCheck(CSkillAcquireInfo, 0x20);
	CompileTimeOffsetCheck(CSkillAcquireDB, skillAcquireMap, 0x00);
	CompileTimeOffsetCheck(CSkillAcquireDB, by_occupation, 0x30);
	CompileTimeOffsetCheck(CSkillAcquireDB, etcSkillAcquireMap, 0xF10);
	CompileTimeOffsetCheck(CSkillAcquireDB, new_by_occupation, 0xF80);

	// Initializing the Extended Classes Relation
	m_ExtendedClasses[L"male_soldier"]       = 123;
	m_ExtendedClasses[L"female_soldier"]     = 124;
	m_ExtendedClasses[L"trooper"]            = 125;
	m_ExtendedClasses[L"warder"]             = 126;
	m_ExtendedClasses[L"kamael_berserker"]   = 127;
	m_ExtendedClasses[L"male_soulbreaker"]   = 128;
	m_ExtendedClasses[L"female_soulbreaker"] = 129;
	m_ExtendedClasses[L"arbalester"]         = 130;
	m_ExtendedClasses[L"doombringer"]        = 131;
	m_ExtendedClasses[L"male_soulhound"]     = 132;
	m_ExtendedClasses[L"female_soulhound"]   = 133;
	m_ExtendedClasses[L"trickster"]          = 134;
	m_ExtendedClasses[L"inspector"]          = 135;
	m_ExtendedClasses[L"judicator"]          = 136;

	// 0x77 (1 Byte) Max Class ID Identifier L2Server (CMP's)
	
	// install my hooks into the original vmt
    pAcquireLexer = new CLexerForAcquire(true);

	// Fixxing Bugged Log Occupation String Array
	WriteMemoryDWORD(0x79CB15, (((INT32)&pOcupationsArray)-0x79CB15)+4);

	// Fixxing Spam on L2Server [ Skill_name_id ] Invalid
	WriteInstruction(0x865C7B, 0x865CBB, 0, 0xE9);

	char *pDB = (char *)&g_SkillAcquireDB;

	WriteMemoryDWORD(0x79CDED, MAX_OCCUPATION_ID + 1);
	WriteMemoryDWORD(0x79D6FA, MAX_OCCUPATION_ID + 1);
	WriteMemoryDWORD(0x95F77D, MAX_OCCUPATION_ID + 1);
	WriteMemoryDWORD(0x9706DD, MAX_OCCUPATION_ID + 1);
	//WriteMemoryDWORD(0x79D6FF, 0x20); for what?
	//WriteMemoryDWORD(0x95F782, 0x20);
	//WriteMemoryDWORD(0x9706E2, 0x20);

	/* 1st Block */
	WriteRelativeAddress(0x642FEE, 3, pDB, 0);
	WriteRelativeAddress(0x6DAC84, 3, pDB, 0);
	WriteRelativeAddress(0x6DAC9B, 3, pDB, 0);
	WriteRelativeAddress(0x84EB17, 3, pDB, 0);
	WriteRelativeAddress(0x84EB43, 3, pDB, 0);
	WriteRelativeAddress(0x865BF5, 3, pDB, 0);
	WriteRelativeAddress(0x865C10, 3, pDB, 0);
	WriteRelativeAddress(0x86610F, 3, pDB, 0);
	WriteRelativeAddress(0x866137, 3, pDB, 0);
	WriteRelativeAddress(0x907661, 3, pDB, 0);
	WriteRelativeAddress(0x9076E4, 3, pDB, 0);
	WriteRelativeAddress(0x9077DB, 3, pDB, 0);
	WriteRelativeAddress(0x95FF74, 3, pDB, 0);
	WriteRelativeAddress(0x970F50, 3, pDB, 0);

	/* 2nd Block */
	WriteRelativeAddress(0x476166, 3, pDB + 0xF80, 0);
	WriteRelativeAddress(0x595D58, 3, pDB + 0xF80, 0);
	WriteRelativeAddress(0x84E6E2, 3, pDB + 0xF80, 0);
	WriteRelativeAddress(0x907739, 3, pDB + 0xF80, 0);
	WriteRelativeAddress(0x8548DD, 3, pDB + 0xF80, 0);
	WriteRelativeAddress(0x854BC8, 3, pDB + 0xF80, 0);
	WriteRelativeAddress(0x84E6C3, 3, pDB + 0xF40, 0);

	// 0E417340h Database + 0xF80
	// 0E017348h Database + 0xF88
	// 0E017350h Database + 0xF90

	/* AutoLearning Patch's */
	WriteInstruction(0x515472, (INT32)CSkillAcquireLexer_AutoLearnFixHook01, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x51549E, (INT32)CSkillAcquireLexer_AutoLearnFixHook02, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x5154D7, (INT32)CSkillAcquireLexer_AutoLearnFixHook03, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x5155F2, (INT32)CSkillAcquireLexer_AutoLearnFixHook04, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x51561A, (INT32)CSkillAcquireLexer_AutoLearnFixHook05, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x515653, (INT32)CSkillAcquireLexer_AutoLearnFixHook06, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x515CE4, (INT32)CSkillAcquireLexer_AutoLearnFixHook07, 3, 0xE9); // CCreature::LevelUp()                   [Working]
	WriteInstruction(0x515D0D, (INT32)CSkillAcquireLexer_AutoLearnFixHook08, 3, 0xE9); // CCreature::LevelUp()                   [Working]
	WriteInstruction(0x515D42, (INT32)CSkillAcquireLexer_AutoLearnFixHook09, 3, 0xE9); // CCreature::LevelUp()                   [Working]
	WriteInstruction(0x518E82, (INT32)CSkillAcquireLexer_AutoLearnFixHook10, 3, 0xE9); // CCreature::EnterWorld()                [Working]
	WriteInstruction(0x518EAB, (INT32)CSkillAcquireLexer_AutoLearnFixHook11, 3, 0xE9); // CCreature::EnterWorld()                [Working]
	WriteInstruction(0x518EE7, (INT32)CSkillAcquireLexer_AutoLearnFixHook12, 3, 0xE9); // CCreature::EnterWorld()                [Working]
	WriteInstruction(0x5194B2, (INT32)CSkillAcquireLexer_AutoLearnFixHook13, 3, 0xE9); // CCreature::ChangeClass()               [Working]
	WriteInstruction(0x5194DB, (INT32)CSkillAcquireLexer_AutoLearnFixHook14, 3, 0xE9); // CCreature::ChangeClass()               [Working]
	WriteInstruction(0x519510, (INT32)CSkillAcquireLexer_AutoLearnFixHook15, 3, 0xE9); // CCreature::ChangeClass()               [Working]
	WriteInstruction(0x84DD12, (INT32)CSkillAcquireLexer_AutoLearnFixHook16, 3, 0xE9); // User::EnterWorld()                     [Working]
	WriteInstruction(0x84DD3E, (INT32)CSkillAcquireLexer_AutoLearnFixHook17, 3, 0xE9); // User::EnterWorld()                     [Working]
	WriteInstruction(0x84DD77, (INT32)CSkillAcquireLexer_AutoLearnFixHook18, 3, 0xE9); // User::EnterWorld()                     [Working]
	//WriteInstruction(0x852502, (INT32)CSkillAcquireLexer_AutoLearnFixHook19, 3, 0xE9); // User::ValidateSubJobParameters()       [Working]
	WriteInstruction(0x85252B, (INT32)CSkillAcquireLexer_AutoLearnFixHook20, 3, 0xE9); // User::ValidateSubJobParameters()       [Working]
	WriteInstruction(0x852560, (INT32)CSkillAcquireLexer_AutoLearnFixHook21, 3, 0xE9); // User::ValidateSubJobParameters()       [Working]
	WriteInstruction(0x854D32, (INT32)CSkillAcquireLexer_AutoLearnFixHook22, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854D5B, (INT32)CSkillAcquireLexer_AutoLearnFixHook23, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854D90, (INT32)CSkillAcquireLexer_AutoLearnFixHook24, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854DF2, (INT32)CSkillAcquireLexer_AutoLearnFixHook25, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854E1B, (INT32)CSkillAcquireLexer_AutoLearnFixHook26, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854E50, (INT32)CSkillAcquireLexer_AutoLearnFixHook27, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]

	WriteInstruction(0x515483, (INT32)CSkillAcquireLexer_AutoLearnFixHook28, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x5154AB, (INT32)CSkillAcquireLexer_AutoLearnFixHook29, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x515603, (INT32)CSkillAcquireLexer_AutoLearnFixHook30, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x515627, (INT32)CSkillAcquireLexer_AutoLearnFixHook31, 3, 0xE9); // CCreature::LevelDown()                 [Working]
	WriteInstruction(0x515CF6, (INT32)CSkillAcquireLexer_AutoLearnFixHook32, 3, 0xE9); // CCreature::LevelUp()                   [Working]
	WriteInstruction(0x515D1A, (INT32)CSkillAcquireLexer_AutoLearnFixHook33, 3, 0xE9); // CCreature::LevelUp()                   [Working]
	WriteInstruction(0x518E94, (INT32)CSkillAcquireLexer_AutoLearnFixHook34, 3, 0xE9); // CCreature::EnterWorld()                [Working]
	WriteInstruction(0x518EB8, (INT32)CSkillAcquireLexer_AutoLearnFixHook35, 3, 0xE9); // CCreature::EnterWorld()                [Working]
	WriteInstruction(0x5194C4, (INT32)CSkillAcquireLexer_AutoLearnFixHook36, 3, 0xE9); // CCreature::ChangeClass()               [Working]
	WriteInstruction(0x5194E8, (INT32)CSkillAcquireLexer_AutoLearnFixHook37, 3, 0xE9); // CCreature::ChangeClass()               [Working]
	WriteInstruction(0x84DD23, (INT32)CSkillAcquireLexer_AutoLearnFixHook38, 3, 0xE9); // User::EnterWorld()                     [Working]
	WriteInstruction(0x84DD4B, (INT32)CSkillAcquireLexer_AutoLearnFixHook39, 3, 0xE9); // User::EnterWorld()                     [Working]
	WriteInstruction(0x852514, (INT32)CSkillAcquireLexer_AutoLearnFixHook40, 3, 0xE9); // User::ValidateSubJobParameters()       [Working]
	WriteInstruction(0x852538, (INT32)CSkillAcquireLexer_AutoLearnFixHook41, 3, 0xE9); // User::ValidateSubJobParameters()       [Working]
	WriteInstruction(0x854D44, (INT32)CSkillAcquireLexer_AutoLearnFixHook42, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854D68, (INT32)CSkillAcquireLexer_AutoLearnFixHook43, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854E04, (INT32)CSkillAcquireLexer_AutoLearnFixHook44, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]
	WriteInstruction(0x854E28, (INT32)CSkillAcquireLexer_AutoLearnFixHook45, 3, 0xE9); // User::OnChangeSubJobEnd()              [Working]

	/* 3rd Block */
	WriteInstruction(0x79D5D6, (INT32)CSkillAcquireLexer_DatabaseOffsetFix_Hook4, 2, 0xE9); // 20h;77h
	WriteInstruction(0x79D5BF, (INT32)CSkillAcquireLexer_DatabaseOffsetFix_Hook1, 0, 0xE9); // 0xF80
	WriteInstruction(0x906BD9, (INT32)CSkillAcquireLexer_DatabaseOffsetFix_Hook2, 0, 0xE9); // 0xF80
	WriteInstruction(0x79CDE7, (INT32)CSkillAcquireLexer_DatabaseOffsetFix_Hook3, 0, 0xE9); // 0xF90
}

