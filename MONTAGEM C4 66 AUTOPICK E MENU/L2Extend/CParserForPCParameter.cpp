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

#include "CParserForPCParameter.h"

#define IMAGEBASE 0x400000

CLexerForPCParameter *pPCParameterLexer;
CParserForPCParameter *pPCParameterParser;
map<wstring, int> m_ExtendedRaces;
map<wstring, int> m_ExtendedOccupations;

extern "C"
{
	CPCParamDB g_CPCParamDB;

	INT32 nOccupationIDToType[0x89] =
	{
		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,
		1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,
		0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1,	1,
		1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	0,	0,	0,
		0,	1,	1,	1,	0,	0,	0,	0,	1,	1,	1,	0,	0,	1,	1,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,  0,
		0
	};

	INT32 nOccupationIDToRace[0x89] =
	{
		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	2,	2,
		2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	3,	3,	3,	3,	3,	3,	3,
		3,	3,	4,	4,	4,	4,	4,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
		-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
		-1,	-1,	-1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,
		1,	1,	1,	1,	2,	2,	2,	2,	2,	2,	2,	3,	3,	3,	3,	4,	4,
		-1,  -1,  -1,  -1,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
		5
	};

	INT32 nEnvType[0x89] =
	{
		0,	2,	3,	3,	2,	3,	3,	2,	3,	3,	0,	2,	3,	3,	3,	2,	3,	3,
		0,	2,	3,	3,	2,	3,	3,	0,	2,	3,	3,	2,	3,	0,	2,	3,	3,	2,
		3,	3,	0,	2,	3,	3,	2,	3,	0,	2,	3,	2,	3,	0,	2,	3,	3,	0,
		2,	3,	2,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	3,
		3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,
		3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	0,	0,	0,	0,	0,	0,	2,
		2,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3
	};

	INT32 g_LexxerParserData[(0x12 + TOTAL_EXTENDED_RACES) * 4] =
	{
		// A = Array ID
		// S = Female(1) / Male(0)
		// R = Race
		// M = Fighter(0) / Mage(1)
	
	//  A   S   R   M
		0,	1,	0,	0, // 1 Human Fighter
		1,	0,	0,	0, // 1 Human Fighter
		2,	1,	0,	1, // 1 Human Mystic
		3,	0,	0,	1, // 1 Human Mystic
		4,	1,	1,	0, // 2 Elf Fighter
		5,	0,	1,	0, // 2 Elf Fighter
		6,	1,	1,	1, // 2 Elf Mystic
		7,	0,	1,	1, // 2 Elf Mystic
		8,	1,	2,	0, // 3 Dark Elf Fighter
		9,	0,	2,	0, // 3 Dark Elf Fighter
		10,	1,	2,	1, // 3 Dark Elf Mystic
		11,	0,	2,	1, // 3 Dark Elf Mystic
		12,	1,	3,	0, // 4 Orc Fighter
		13,	0,	3,	0, // 4 Orc Fighter
		14,	1,	3,	1, // 4 Orc Mystic
		15,	0,	3,	1, // 4 Orc Mystic
		16,	1,	4,	0, // 5 Dwarf Fighter
		17,	0,	4,	0, // 5 Dwarf Fighter
		18,	1,	5,	0, // 6 Kamael Fighter
		19,	0,	5,	0  // 6 Kamael Fighter
};
}

//--------------------------------------------

CLexerForPCParameter::CLexerForPCParameter(bool bFakeInstance)
{
    static bool _init_done = false;
    
	if (! _init_done) 
	{
        _init_done = true;
		LPVOID *org_vmt = (LPVOID*)0xAE34A8; // real VMT address
        LPVOID* my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[9], &my_vmt[9], 1);   // yyaction()
	}
}

CParserForPCParameter::CParserForPCParameter(bool bFakeInstance)
{
    static bool _init_done = false;
    
	if (! _init_done) 
	{
        _init_done = true;
		LPVOID *org_vmt = (LPVOID*)0xAFF378;   // real VMT address
        LPVOID* my_vmt = *(LPVOID**)this;
		CopyVMT(&org_vmt[1], &my_vmt[1], 1);   // yyaction()
	}
}

yywint_t CLexerForPCParameter::yyaction(int action)
{
	typedef yywint_t(*t)(CLexerForPCParameter*, int);
	t f = (t)0x8F83B0;
	yywint_t  token = f(this, action);
	
	if ( token >= 0x10000 )
	{
		YYSTYPE& yylval = *(YYSTYPE*)yyparserptr->yylvalptr;
		
		if ( token == 0x10003 )
		{
			wstring cValue = yylval.id_value;

			if ( m_ExtendedRaces.find(cValue) != m_ExtendedRaces.end() )
			{
				yylval.int_value = m_ExtendedRaces[cValue];
				token = 0x10001;
			}

			if (wcsncmp(L"hp_table_begin", cValue.c_str()+(cValue.size()-14), 14) == 0) 
			{
				if ( m_ExtendedOccupations.find(cValue.substr(0, cValue.size()-15)) != m_ExtendedOccupations.end() )
				{
					yylval.int_value = m_ExtendedOccupations[cValue.substr(0, cValue.size()-15)];
					token = 0x10009;
				}
			} 
				
			if (wcsncmp(L"hp_table_end", cValue.c_str()+(cValue.size()-12), 12) == 0) 
			{
				if ( m_ExtendedOccupations.find(cValue.substr(0, cValue.size()-13)) != m_ExtendedOccupations.end() )
				{
					yylval.int_value = m_ExtendedOccupations[cValue.substr(0, cValue.size()-13)];
					token = 0x1000A;
				}
			}

			if (wcsncmp(L"mp_table_begin", cValue.c_str()+(cValue.size()-14), 14) == 0) 
			{
				if ( m_ExtendedOccupations.find(cValue.substr(0, cValue.size()-15)) != m_ExtendedOccupations.end() )
				{
					yylval.int_value = m_ExtendedOccupations[cValue.substr(0, cValue.size()-15)];
					token = 0x1000B;
				}
			} 
				
			if (wcsncmp(L"mp_table_end", cValue.c_str()+(cValue.size()-12), 12) == 0) 
			{
				if ( m_ExtendedOccupations.find(cValue.substr(0, cValue.size()-13)) != m_ExtendedOccupations.end() )
				{
					yylval.int_value = m_ExtendedOccupations[cValue.substr(0, cValue.size()-13)];
					token = 0x1000C;
				}
			}

			if (wcsncmp(L"cp_table_begin", cValue.c_str()+(cValue.size()-14), 14) == 0) 
			{
				if ( m_ExtendedOccupations.find(cValue.substr(0, cValue.size()-15)) != m_ExtendedOccupations.end() )
				{
					yylval.int_value = m_ExtendedOccupations[cValue.substr(0, cValue.size()-15)];
					token = 0x1000D;
				}
			} 
				
			if (wcsncmp(L"cp_table_end", cValue.c_str()+(cValue.size()-12), 12) == 0) 
			{
				if ( m_ExtendedOccupations.find(cValue.substr(0, cValue.size()-13)) != m_ExtendedOccupations.end() )
				{
					yylval.int_value = m_ExtendedOccupations[cValue.substr(0, cValue.size()-13)];
					token = 0x1000E;
				}
			}
		}
		
		// CLog::Add(CLog::blue, "Lexing PCParameter... %ls 0x%04X -> Value : %d - %d", this->yytext, token, yylval.int_value);
	}

	return token;
}


//--------------------------------------------------
void CParserForPCParameter::yyaction(int action)
{
	typedef void(*t)(CParserForPCParameter*, int);
	t f = (t)0x8FF770;
	f(this,action);

	// YYSTYPE& yylval = *(YYSTYPE*)yylexerptr->yyparserptr->yylvalptr;
	// CLog::Add(CLog::blue, "Parsing PCParameter... ->>>>>>> 0x%02X - Value : %d - %d", action, yylval.int_value,  yyattribute(7).int_value);
}

//-----------------------------------------------------------------

VOID CPCParamDB::Initialize()
{
	// Install My Hooks Into The original VMT...
    pPCParameterLexer  = new CLexerForPCParameter(true);
    pPCParameterParser = new CParserForPCParameter(true);

	// Initializing the Sub System...
	CPCParamDB::ExtendParser();
	CPCParamDB::ExtendDataArrays();
	CPCParamDB::HookDatabaseSystem();
	CPCParamDB::HookIntegerSystem();
	CPCParamDB::HookDoubleSystem();
	CPCParamDB::HookRestrictions();
	CPCParamDB::HookORGSystem();
}

VOID CPCParamDB::ExtendParser()
{
	// Patching the Lexxer Parser Array for the 2 New Elements we Just Added.
	WriteInstruction(0x8FF88A, (INT32)CParserForPCParameter_LexxerFix_Hook1, 0, 0xE9);
	WriteInstruction(0x90068A, (INT32)CParserForPCParameter_LexxerFix_Hook2, 0, 0xE9);

	// Including Newer Parseable Races
	int nTotalOriginalRaces            = 18;
	m_ExtendedRaces[L"FKamaelSoldier"] = nTotalOriginalRaces++;
	m_ExtendedRaces[L"MKamaelSoldier"] = nTotalOriginalRaces++;

	// Including Newer Parseable Occupations
	m_ExtendedOccupations[L"male_soldier"]       = 123;
	m_ExtendedOccupations[L"female_soldier"]     = 124;
	m_ExtendedOccupations[L"trooper"]            = 125;
	m_ExtendedOccupations[L"warder"]             = 126;
	m_ExtendedOccupations[L"kamael_berserker"]   = 127;
	m_ExtendedOccupations[L"male_soulbreaker"]   = 128;
	m_ExtendedOccupations[L"female_soulbreaker"] = 129;
	m_ExtendedOccupations[L"arbalester"]         = 130;
	m_ExtendedOccupations[L"doombringer"]        = 131;
	m_ExtendedOccupations[L"male_soulhound"]     = 132;
	m_ExtendedOccupations[L"female_soulhound"]   = 133;
	m_ExtendedOccupations[L"trickster"]          = 134;
	m_ExtendedOccupations[L"inspector"]          = 135;
	m_ExtendedOccupations[L"judicator"]          = 136;
}

VOID CPCParamDB::ExtendDataArrays()
{
	// BF6390 ClassID to EnvType
	// BF6570 ClassID to Race Table
	// BF6750 ClassID to Fighter/Mystic

	// Patching Extended Arrays
	
	// BF6390
	
	WriteRelativeAddress(0x745585, 3, &nEnvType, 0);

	// BF6750

	WriteMemoryDWORD(0x851DFC, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x851DEA, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x851DD3, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x44DF8F, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x84B812, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x84B7F7, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x84B7DB, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x851E09, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x84B7BE, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x44DE6B, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x7FDB54, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x7FDCC4, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x7FDE34, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x744BC3, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x744D6F, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x744CEF, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x745462, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x7453E6, (INT32)&nOccupationIDToType - IMAGEBASE);
	WriteMemoryDWORD(0x7446A1, (INT32)&nOccupationIDToType - IMAGEBASE);
	
	// BF6570

	WriteMemoryDWORD(0x44DE63, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x44DF85, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x7446A9, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x744BB8, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x744CE0, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x744D60, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x7453D3, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x745453, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x7FDB5C, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x7FDCCC, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x7FDE3C, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x84B7AF, (INT32)&nOccupationIDToRace - IMAGEBASE);
	WriteMemoryDWORD(0x851D66, (INT32)&nOccupationIDToRace - IMAGEBASE);
	
	WriteRelativeAddress(0x745503, 3, &nOccupationIDToRace, 0);
	WriteRelativeAddress(0x745523, 3, &nOccupationIDToRace, 0);
	WriteRelativeAddress(0x745545, 3, &nOccupationIDToRace, 0);
	WriteRelativeAddress(0x745565, 3, &nOccupationIDToRace, 0);
}

VOID CPCParamDB::HookRestrictions()
{
	// Nopping The Occupation Check of L2Server Places
	// BuilderCMD_SetClass
	//.text:000000000044DE53                 movsxd  rbx, eax
	//.text:000000000044DE56                 cmp     ebx, 77h
	WriteInstruction(0x44DE53, (INT32)&BuilderCMD_SetClass_Class_Hook, 1, 0xE9);

	// BuilderCMD_SetSubJob
	//.text:0000000000467BB1                 mov     r12d, eax
	//.text:0000000000467BB4                 cmp     eax, 77h
	WriteInstruction(0x467BB1, (INT32)&BuilderCMD_SetSubJob_Class_Hook, 1, 0xE9);

	//.text:0000000000744688                 ja      short loc_7446D8
	//.text:000000000074468A                 cmp     r9d, 77h
	WriteInstruction(0x744688, (INT32)&PCParam_Getter_Class_Hook1, 1, 0xE9);

	//.text:0000000000744B92                 ja      short loc_744BE5
	//.text:0000000000744B94                 cmp     r8d, 77h
	WriteInstruction(0x744B92, (INT32)&PCParam_Getter_Class_Hook2, 1, 0xE9);

	//.text:0000000000744CC7                 ja      short loc_744D06
	//.text:0000000000744CC9                 cmp     r8d, 77h
	WriteInstruction(0x744CC7, (INT32)&PCParam_Getter_Class_Hook3, 1, 0xE9);

	//.text:0000000000744D47                 ja      short loc_744D86
	//.text:0000000000744D49                 cmp     r8d, 77h
	WriteInstruction(0x744D47, (INT32)&PCParam_Getter_Class_Hook4, 1, 0xE9);

	//.text:00000000007453BA                 ja      short loc_745400
	//.text:00000000007453BC                 cmp     r8d, 77h
	WriteInstruction(0x7453BA, (INT32)&PCParam_Getter_Class_Hook5, 1, 0xE9);

	//.text:000000000074543A                 ja      short loc_745484
	//.text:000000000074543C                 cmp     r8d, 77h
	WriteInstruction(0x74543A, (INT32)&PCParam_Getter_Class_Hook6, 1, 0xE9);

	//.text:0000000000745580                 cmp     edx, 77h
	//.text:0000000000745583                 ja      short loc_745593
	WriteInstruction(0x745580, (INT32)&PCParam_Getter_Class_Hook7, 0, 0xE9);

	// CShortCut::DeleteShortcut()
	//.text:0000000000791986                 cmp     edi, 77h
	//.text:0000000000791989                 ja      loc_791A1A
	WriteInstruction(0x791986, (INT32)&CShortCut_DeleteShortcut_Class_Hook, 4, 0xE9);

	// CShortCut::Add()
	//.text:0000000000791B94                 cmp     r14d, 77h
	//.text:0000000000791B98                 ja      loc_792032
	WriteInstruction(0x791B94, (INT32)&CShortCut_Add_Class_Hook, 5, 0xE9);

	// CSkillEnchantChecker::CheckLearnable()
	//.text:000000000079DF8E                 cmp     ecx, 77h
	//.text:000000000079DF91                 jl      short loc_79DFDB
	WriteInstruction(0x79DF8E, (INT32)&CSkillEnchantChecker_CheckLearnable_Class_Hook, 0, 0xE9);

	// CSkillEnchantChecker::CheckRequestEnchantSkill()
	//.text:000000000079ED5F                 cmp     eax, 77h
	//.text:000000000079ED62                 jge     short loc_79ED98
	WriteInstruction(0x79ED5F, (INT32)&CSkillEnchantChecker_CheckRequestEnchantSkill_Class_Hook, 0, 0xE9);

	// CSkillEnchantChecker::CheckNpcShowEnchantSkillList()
	//.text:00000000007A03A9                 cmp     ecx, 77h
	//.text:00000000007A03AC                 jge     loc_7A043D
	WriteInstruction(0x7A03A9, (INT32)&CSkillEnchantChecker_CheckNpcShowEnchantSkillList_Class_Hook, 4, 0xE9);
		 
	// CSkillEnchantChecker::CheckNpcEnchantSkillSuggestion()
	//.text:00000000007A085B                 cmp     edx, 77h
	//.text:00000000007A085E                 jge     loc_7A0A24
	WriteInstruction(0x7A085B, (INT32)&CSkillEnchantChecker_CheckNpcEnchantSkillSuggestion_Class_Hook, 4, 0xE9);
	
	// CSkillEffect_i_inform()
	//.text:00000000007AB019                 cmp     eax, 77h
	//.text:00000000007AB01C                 jge     short loc_7AB044
	WriteInstruction(0x7AB019, (INT32)&CSkillEffect_i_inform_Class_Hook, 0, 0xE9);
}

VOID CPCParamDB::HookDatabaseSystem()
{
	// Patching Global References Of :
	char *pDB     = (char *)&g_CPCParamDB;

	/* 1st Block */
	WriteRelativeAddress(0x476C18, 3, pDB, 0);	// BuilderCMD_Ride()
	WriteRelativeAddress(0x476C47, 3, pDB, 0);	// BuilderCMD_Ride()
	WriteRelativeAddress(0x4D8C67, 3, pDB, 0);	// sub_4D8C60
	WriteRelativeAddress(0x4D9277, 3, pDB, 0);	// sub_4D9270
	WriteRelativeAddress(0x4D9297, 3, pDB, 0);	// sub_4D9290
	WriteRelativeAddress(0x4D92B7, 3, pDB, 0);	// sub_4D92B0
	WriteRelativeAddress(0x4D92D7, 3, pDB, 0);	// sub_4D92D0
	WriteRelativeAddress(0x4D92F7, 3, pDB, 0);	// sub_4D92F0
	WriteRelativeAddress(0x4D9317, 3, pDB, 0);	// sub_4D9310
	WriteRelativeAddress(0x4DA4FE, 3, pDB, 0);	// CCreature::HeightDamage()
	WriteRelativeAddress(0x4ED7B6, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend()
	WriteRelativeAddress(0x4ED815, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend()
	WriteRelativeAddress(0x4ED86E, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend()
	WriteRelativeAddress(0x4ED8C7, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend()
	WriteRelativeAddress(0x4ED920, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend()
	WriteRelativeAddress(0x4ED979, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend()
	WriteRelativeAddress(0x4ED9CF, 3, pDB, 0);	// CCreature::EquipedArmorsPDefend() 
	WriteRelativeAddress(0x4EDD85, 3, pDB, 0);	// CCreautre::EquipedArmorsMDefend()
	WriteRelativeAddress(0x4EDDB4, 3, pDB, 0);	// CCreautre::EquipedArmorsMDefend()
	WriteRelativeAddress(0x4EDDE0, 3, pDB, 0);	// CCreautre::EquipedArmorsMDefend()
	WriteRelativeAddress(0x4EDE0C, 3, pDB, 0);	// CCreautre::EquipedArmorsMDefend()
	WriteRelativeAddress(0x4EDE35, 3, pDB, 0);	// CCreautre::EquipedArmorsMDefend()
	WriteRelativeAddress(0x51C6C0, 3, pDB, 0);	// CDB::RequestCreateChar()
	WriteRelativeAddress(0x51C6E1, 3, pDB, 0);	// CDB::RequestCreateChar()
	WriteRelativeAddress(0x51C6FE, 3, pDB, 0);	// CDB::RequestCreateChar()
	WriteRelativeAddress(0x51C717, 3, pDB, 0);	// CDB::RequestCreateChar()
	WriteRelativeAddress(0x642F8B, 3, pDB, 0);	// LoadData()
	WriteRelativeAddress(0x7FCDC0, 3, pDB, 0);	// sub_7FCDB0
	WriteRelativeAddress(0x7FCDE0, 3, pDB, 0);	// sub_7FCDB0
	WriteRelativeAddress(0x7FCE0F, 3, pDB, 0);	// sub_7FCDB0
	WriteRelativeAddress(0x7FDA19, 3, pDB, 0);	// User::RegenBonusByMotionEx()
	WriteRelativeAddress(0x7FDB66, 3, pDB, 0);	// User::ValidateOrgHPRegen()
	WriteRelativeAddress(0x7FDCD6, 3, pDB, 0);	// User::ValidateOrgCPRegen()
	WriteRelativeAddress(0x7FDE46, 3, pDB, 0);	// User::ValidateOrgMPRegen()
	WriteRelativeAddress(0x7FE112, 3, pDB, 0);	// User::ValidateOrgSpeed()
	WriteRelativeAddress(0x7FF55A, 3, pDB, 0);	// User::ExpInc()
	WriteRelativeAddress(0x80BA53, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BA9D, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BAF1, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BB45, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BBF2, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BC3C, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BC90, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80BCE4, 3, pDB, 0);	// User::ValidateStorageSlot()
	WriteRelativeAddress(0x80EA40, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EA75, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EAAD, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EAE2, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EB1A, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EB4F, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EB87, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EBBC, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x80EBDF, 3, pDB, 0);	// User::ChangeClass()
	WriteRelativeAddress(0x81E980, 3, pDB, 0);	// User::Die()
	WriteRelativeAddress(0x835BBA, 3, pDB, 0);	// User::GetOff()
	WriteRelativeAddress(0x835BE9, 3, pDB, 0);	// User::GetOff()
	WriteRelativeAddress(0x845DE5, 3, pDB, 0);	// User::TimerExpired()
	WriteRelativeAddress(0x84B206, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84B9C8, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84B9EE, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BA21, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BA71, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BAA4, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BADC, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BB0F, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BB3F, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BB72, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BBA9, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BBDC, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BC0F, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BC42, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BCE5, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BD14, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BD3C, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BD5B, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BEA4, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BED5, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BF0D, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BF42, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BF7A, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BFAF, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84BFE7, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x84C01C, 3, pDB, 0);	// User::User()
	WriteRelativeAddress(0x8519B2, 3, pDB, 0);	// User::InitSubJob()
	WriteRelativeAddress(0x851D35, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x851F18, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x851F3E, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x851F71, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x851FC1, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x851FF4, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85202C, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85205F, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85208F, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8520C2, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8520F9, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85212C, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85215F, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852192, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852235, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852264, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85228C, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8522AB, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852352, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852384, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8523BC, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8523F1, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852429, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x85245E, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x852496, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8524CB, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x8526D5, 3, pDB, 0);	// User::ValidateSubJobParameters()
	WriteRelativeAddress(0x855AF6, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855B29, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855B60, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855B96, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855BCF, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855C07, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855C40, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x855C76, 3, pDB, 0);	// User::SendUserInfo()
	WriteRelativeAddress(0x857DC3, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857DF6, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857E28, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857E5C, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857E94, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857ECC, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857F02, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x857F38, 3, pDB, 0);	// User::SendCharInfo()
	WriteRelativeAddress(0x87B819, 3, pDB, 0);	// RidePacket()
	WriteRelativeAddress(0x87B848, 3, pDB, 0);	// RidePacket()
	WriteRelativeAddress(0x8FF92A, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FF960, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FF991, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FF9C2, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FF9E3, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFA14, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFAB6, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFAEC, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFB1D, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFB4E, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFB6F, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFBB0, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFC42, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFC78, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFCA9, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFCDA, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFCFB, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFD3C, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x8FFE0D, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x9001A7, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x9002DC, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x90051C, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x9006DF, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x90090B, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900B17, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900B53, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900C93, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900CAF, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900CDC, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900D0C, 3, pDB, 0);	// CParserForCPCParam::YYAction()
	WriteRelativeAddress(0x900D3C, 3, pDB, 0);	// CParserForCPCParam::YYAction()
}

VOID CPCParamDB::HookIntegerSystem()
{
	// GetIntValue
	WriteInstruction(0x4DA505, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x845DEC, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BA78, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BAAB, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BAE3, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BB16, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BB46, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BBB0, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BBE3, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x84BC16, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x851FC8, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x851FFB, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x852033, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x852066, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x852096, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x852100, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x852133, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);
	WriteInstruction(0x852166, (INT32)CPCParamDB::GetIntValue, 0, 0xE8);

	// SetIntValue
	WriteInstruction(0x8FF93E, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FF96F, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FF9A0, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FF9D1, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFA02, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFA33, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFACA, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFAFB, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFB2C, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFB5D, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFB8E, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFBBF, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFC56, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFC87, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFCB8, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFCE9, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFD1A, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x8FFD4B, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x9006FD, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
	WriteInstruction(0x900912, (INT32)CPCParamDB::SetIntValue, 0, 0xE8);
}

VOID CPCParamDB::HookDoubleSystem()
{
	CPCParamDB* pDB = &g_CPCParamDB;
	
	// Fixxing Offsets for the Array DB+2880h [DataArray11] 

	// Fixxing Offsets for the Array DB+4380h [DataArray12]

	// Fixxing Offsets for the Array DB+57C0h [DataArray13]

	// Fixxing Offsets for the Array DB+5E80h [DataArray16]
	WriteMemoryDWORD(0x745642, offsetof(CPCParamDB, DataArray16));	// CPCParamDB::SetRegenMoveModeBonus()
	WriteMemoryDWORD(0x74572A, offsetof(CPCParamDB, DataArray16));	// CPCParamDB::GetRegenMoveModeBonus()

	WriteRelativeAddress(0x745394, 3, &pDB->DataArray17, 0);
	WriteRelativeAddress(0x7454E4, 3, &pDB->DataArray18, 0);

	// Fixxing Offsets for the Array DB+5EA0h [DataArray19]
	WriteMemoryDWORD(0x7451D4, offsetof(CPCParamDB, DataArray19));	// CPCParamDB::SetKarmaIncreaseAmount()
	WriteMemoryDWORD(0x745812, offsetof(CPCParamDB, DataArray19));	// CPCParamDB::GetKarmaIncreaseAmount()

	// Fixxing Offsets for the Global Array 0E1B4370h [DataArray20]
	WriteMemoryDWORD(0x744ABD+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x00);
	WriteMemoryDWORD(0x744ACC+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x20);
	WriteMemoryDWORD(0x744ADE+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x08);
	WriteMemoryDWORD(0x744AF0+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x28);
	WriteMemoryDWORD(0x744B02+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x10);
	WriteMemoryDWORD(0x744B14+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x30);
	WriteMemoryDWORD(0x744B26+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x18);
	WriteMemoryDWORD(0x744B2F+5, (INT32)&pDB->DataArray20 - IMAGEBASE + 0x38);
	WriteMemoryDWORD(0x744BD6+6, (INT32)&pDB->DataArray20 - IMAGEBASE);

	// Fixxing Offsets for the Global Array [DataArray21]
	WriteMemoryDWORD(0x744C5F+5,   (INT32)&pDB->DataArray21 - IMAGEBASE);	// SET
	WriteMemoryDWORD(0x744CF7+6,   (INT32)&pDB->DataArray21 - IMAGEBASE);	// GET

	// Fixxing Offsets for the Global Array [DataArray22]
	WriteMemoryDWORD(0x744C6E+5,   (INT32)&pDB->DataArray22 - IMAGEBASE);	// SET
	WriteMemoryDWORD(0x744D77+6,   (INT32)&pDB->DataArray22 - IMAGEBASE);	// GET
	
	// Fixxing Offsets for the Global Array (0E1DECF0h - 0DDDECF0h) [DataArray23]
	WriteMemoryDWORD(0x745244+5,   (INT32)&pDB->DataArray23 - IMAGEBASE);	// SET
	WriteRelativeAddress(0x74530D, 3, &pDB->DataArray23, 0);					// GET
	
	// Fixxing Offsets for the Global Array (0E1CA5B0h - 0DDCA5B0h) [DataArray24]
	WriteMemoryDWORD(0x745272+5,   (INT32)&pDB->DataArray24 - IMAGEBASE); // SET
	WriteRelativeAddress(0x74532D, 3, &pDB->DataArray24, 0);					// GET

	// Fixxing Offsets for the Global Array (0E1B5E70h - 0DDB5E70h) [DataArray25]
	WriteMemoryDWORD(0x7452A0+5,   (INT32)&pDB->DataArray25 - IMAGEBASE);	// SET
	WriteRelativeAddress(0x74534D, 3, &pDB->DataArray25, 0);					// GET
}

// Re-written Function                RCX          RDX             R8                 R9
INT32 CPCParamDB::GetIntValue(CPCParamDB *pDB, INT32 nSex, INT32 nOccupationID, INT32 nTableID)
{
	INT32 nResult = 0;

	// Calculating the Table Access Offsets :
	int nR8D      = nOccupationIDToRace[nOccupationID];
	int nR11      = nOccupationIDToType[nOccupationID];
	int nRCXInt   = nR11 + (((nSex * 0x1B) + nR8D)*2);
	int nRCXByte  = nR11 + ((nSex * 0x1B) + nR8D);

	switch ( nTableID )
	{
		// 0x12 BASE PHYSICAL ATTACK
		case 0x12: { char *TablePTR = (char *)&pDB->DataArray05;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 1AFC
		// 0x13 BASE CRITICAL
		case 0x13: { char *TablePTR = (char *)&pDB->DataArray08;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 200C
		// 0x14 BASE ATTACK TYPE
		case 0x14: { char *TablePTR = (char *)&pDB->DataArray01;    TablePTR += nRCXInt  * 4;   nResult = *(INT32 *)TablePTR; }	break; // 0560
		// 0x15 BASE ATTACK SPEED
		case 0x15: { char *TablePTR = (char *)&pDB->DataArray07;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 15EC
		// 0x17 BASE MAGICK ATTACK
		case 0x17: { char *TablePTR = (char *)&pDB->DataArray09;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 21BC
		// 0x19 BASE CAN PENETRATE
		case 0x19: { char *TablePTR = (char *)&pDB->DataArray02;	TablePTR += nRCXByte * 2;   nResult = *(BYTE *)TablePTR;  }	break; // 1730
		// 0x1A BASE ATTACK RANGE
		case 0x1A: { char *TablePTR = (char *)&pDB->DataArray03;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 179C
		// 0x1C BASE RAND DAM
		case 0x1C: { char *TablePTR = (char *)&pDB->DataArray04;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 194C
		// 0x21 PC BREATH BONUS
		case 0x21: { char *TablePTR = (char *)&pDB->DataArray14;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 251C
		// 0x22 PC SAFE FALL HEIGHT
		case 0x22: { char *TablePTR = (char *)&pDB->DataArray15;	TablePTR += nRCXInt  * 4;	nResult = *(INT32 *)TablePTR; }	break; // 26CC
	}

	// CLog::Add(CLog::blue, "Requested Parameter... [0x%02X - 0x%02X - 0x%02X]-> %d", nSex, nOccupationID, nTableID, nResult);

	return nResult;
}

//                                 RCX           RDX            R8D                  R9D          STACK 20h      STACK 28h
VOID CPCParamDB::SetIntValue(CPCParamDB *pDB, INT32 nSex, INT32 nOccupationID, INT32 nIsMystic, INT32 nTableID, INT32 nIntValue)
{
	char *TablePTR = NULL;
	bool bFoundTable = false;

	switch ( nTableID )
	{
		// 0x12 BASE PHYSICAL ATTACK
		case 0x12: { TablePTR = (char *)&pDB->DataArray05;	bFoundTable = true; }	break; // 1AFC
		// 0x13 BASE CRITICAL
		case 0x13: { TablePTR = (char *)&pDB->DataArray08;  bFoundTable = true; }	break; // 200C
		// 0x14 BASE ATTACK TYPE		
		case 0x14: { TablePTR = (char *)&pDB->DataArray01;  bFoundTable = true; }	break; // 0560
		// 0x15 BASE ATTACK SPEED
		case 0x15: { TablePTR = (char *)&pDB->DataArray07;	bFoundTable = true; }	break; // 15EC
		// 0x17 BASE MAGICK ATTACK
		case 0x17: { TablePTR = (char *)&pDB->DataArray09;	bFoundTable = true; }	break; // 21BC
		// 0x19 BASE CAN PENETRATE
		case 0x19: { TablePTR = (char *)&pDB->DataArray02;	bFoundTable = true; }	break; // 1730
		// 0x1A BASE ATTACK RANGE
		case 0x1A: { TablePTR = (char *)&pDB->DataArray03;	bFoundTable = true; }	break; // 179C
		// 0x1C BASE RAND DAM
		case 0x1C: { TablePTR = (char *)&pDB->DataArray04;	bFoundTable = true; }	break; // 194C
		// 0x21 PC BREATH BONUS
		case 0x21: { TablePTR = (char *)&pDB->DataArray14;	bFoundTable = true; }	break; // 251C
		// 0x22 PC SAFE FALL HEIGHT
		case 0x22: { TablePTR = (char *)&pDB->DataArray15;	bFoundTable = true; }	break; // 26CC
	}

	if ( bFoundTable )
	{
		// CLog::Add(CLog::blue, "Setting Parameter... [0x%02X - 0x%02X - 0x%02X] -> I:%d M:%d", nSex, nOccupationID, nTableID, nIntValue, nIsMystic);

		int nRCX = 0;
		nRCX = (nSex * 0x1B) + nOccupationID;
		nRCX = nIsMystic + (nRCX * 2);
		TablePTR += (nRCX * 4);
		*(INT32 *)TablePTR = nIntValue;
	}
}

void CPCParamDB::HookORGSystem()
{
	// Increase array size for org_hp and org_mp system
	WriteMemoryBYTE(0x8FFFB9, 9);
	WriteMemoryBYTE(0x8FFE84, 9);

	WriteInstruction(0x8FFFDB, (INT32)ORG_MP_REG_System_Hook, 0, 0xE9);
	WriteInstruction(0x8FFEA6, (INT32)ORG_HP_REG_System_Hook, 0, 0xE9);
	WriteInstruction(0x74477A, (INT32)Fixxing_Offset_Global_Array_Org_HP_CP, 0, 0xE9);
	WriteInstruction(0x744831, (INT32)Fixxing_Offset_Global_Array_Org_MP, 0, 0xE9);
}
