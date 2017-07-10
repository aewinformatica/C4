#include "Global.h"
#include "CLevel85System.h"

void CLevel85System::Initialize()
{
	CUser test;
	MoveExperience((int)&test.experienceHi - (int)&test);

	WriteMemoryDWORD(0x501C40+1, (INT32)&CLevel85System::NewRequestCreateSubJob);
	WriteMemoryDWORD(0x501C80+1, (INT32)&CLevel85System::NewRequestChangeSubJob);
	WriteMemoryDWORD(0x501CE0+1, (INT32)&CLevel85System::NewRequestSaveCharacterForSubJob);
}

void CLevel85System::InitializeAfterStart()
{
	WriteMemoryDWORD(0x56C3A0 + 0x17*4, (INT32)&CLevel85System::NewRenewSubJob);
}

char *loadSelectedCharacter = "SdSdddddddddddffdddddddddddddddddddddddddddddddddddddddddddffSdddddddddbddddddddffdbdddd";
char *loadCharacterPacket = "SdSddddddddddffdddddddddddddddddddddddddddddddddddddddddddddddddffdddc";

void CLevel85System::MoveExperience(int index)
{
	// 474859                 call    CUser__GetExp - log
	// 4A2D70                 call    CUser__GetExp	- log

	// 4A0AA0 CUser__GetExp
	NOPMemory(0x4A0B20, 6);
	WriteInstruction(0x4A0B20, (INT32)&CLevel85System::FixGetExp, 0, 0xE9);

	// enlargment of CUserDbHelper from 0x740 to 0x748
	// move whole experince from 4D4h to new object offset 740h
	CLevel85System::EnlargeCUserDbHelper(8);

	// CUserDBHelper Init
	NOPMemory(0x49D837, 6);
	WriteInstruction(0x49D837, (INT32)&CLevel85System::ExtendCUserInit, 0, 0xE9);

	// .text:004A69A1                 lea     eax, [esi+4D4h]
	WriteMemoryDWORD(0x4A69A3, 0x740);
	// 4A67F0 CUserDbHelper::BindUserProperty - bind z db do pameti
	// .text:004A69A1                 lea     eax, [esi+4D4h]
	// .text:004A69A7                 push    eax             ; TargetValue
	// .text:004A69A8                 mov     ecx, esi
	// .text:004A69AA                 call    DBConn__Bind_integer ; db-Exp
	// vymenit BindD za BindQ - experience
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset DBConn::BindQ
		push        4A69AAh
		call        WriteInstruction
		add			esp,10h
	}

	//               HMSE
	//               PPPx
	// SdSdddddddddddffddddddddddddddddddddddddddddddddddddddddddffSdddddddddbddddddddffdbdddd
	// SdSdddddddddddffdddddddddddddddddddddddddddddddddddddddddddffSdddddddddbddddddddffdbdddd
	// 473F48                 call    CUser__GetExp
	NOPMemory(0x473F4D, 8);
	WriteInstruction(0x473F4D, (INT32)&CLevel85System::FixLoadSelectedCharacter, 0, 0xE9);
	// .text:00473F62                 lea     ecx, [esp+180h+var_10]
	WriteMemoryDWORD(0x473F65, 0x174);
	// .text:00473F78                 lea     ecx, [esp+188h+var_10]
	WriteMemoryDWORD(0x473F7B, 0x17C);
	// .text:00473F8E                 mov     eax, [esp+188h+arg_D8]
	WriteMemoryDWORD(0x473F91, 0x26C);
	// .text:00473F9C                 lea     ecx, [esp+194h+var_10]
	WriteMemoryDWORD(0x473F9F, 0x188);
	// .text:00473FB0                 lea     ecx, [esp+198h+var_10]
	WriteMemoryDWORD(0x473FB3, 0x18C);
	// .text:00473FC4                 lea     ecx, [esp+19Ch+var_10]
	WriteMemoryDWORD(0x473FC7, 0x190);
	// .text:00473FD8                 lea     ecx, [esp+1A0h+var_10]
	WriteMemoryDWORD(0x473FDB, 0x194);
	// .text:00473FEC                 lea     ecx, [esp+1A4h+var_10]
	WriteMemoryDWORD(0x473FEF, 0x198);
	// .text:00474000                 lea     ecx, [esp+1A8h+var_10]
	WriteMemoryDWORD(0x474003, 0x19C);
	// .text:00474014                 lea     ecx, [esp+1ACh+var_10]
	WriteMemoryDWORD(0x474017, 0x1A0);
	// .text:00474028                 lea     ecx, [esp+1B0h+var_10]
	WriteMemoryDWORD(0x47402B, 0x1A4);
	// .text:0047403C                 lea     ecx, [esp+1B4h+var_10]
	WriteMemoryDWORD(0x47403F, 0x1A8);
	// .text:00474050                 lea     ecx, [esp+1B8h+var_10]
	WriteMemoryDWORD(0x474053, 0x1AC);
	// .text:00474064                 lea     ecx, [esp+1BCh+var_10]
	WriteMemoryDWORD(0x474067, 0x1B0);
	// .text:00474078                 lea     ecx, [esp+1C0h+var_10]
	WriteMemoryDWORD(0x47407B, 0x1B4);
	// .text:0047408C                 lea     ecx, [esp+1C4h+var_10]
	WriteMemoryDWORD(0x47408F, 0x1B8);
	// .text:004740A5                 lea     ecx, [esp+1CCh+arg_524]
	WriteMemoryDWORD(0x4740A8, 0x6FC);
	// .text:004740A0                 push    offset aSdsddddddddddd
	WriteMemoryDWORD(0x4740A1, (INT32)loadSelectedCharacter);	// jedno d navic
	// .text:004740B7                 add     esp, 188h
	WriteMemoryDWORD(0x4740B9, 0x18C);		// posilam o jedno d navic

	// LoadCharacterPacket
	//              HMSE
	//              PPPx
	// SdSddddddddddffddddddddddddddddddddddddddddddddddddddddddddddddffdddc
	// SdSddddddddddffdddddddddddddddddddddddddddddddddddddddddddddddddffdddc
	// 498A35                 call    CUser__GetExp
	NOPMemory(0x498A3A, 8);
	WriteInstruction(0x498A3A, (INT32)&CLevel85System::FixLoadCharacterPacket, 0, 0xE9);
	// .text:00498A7C                 mov     edx, [esp+13Ch+arg_11C]
	WriteMemoryDWORD(0x498A7F, 0x264);
	// .text:00498AC5                 mov     eax, [esp+164h+arg_30]
	WriteMemoryDWORD(0x498AC8, 0x1A0);
	// .text:00498AD1                 push    offset aSdsddddddddddf
	WriteMemoryDWORD(0x498AD2, (INT32) loadCharacterPacket);
	// .text:00498AD9                 lea     edx, [esp+eax+16Ch+arg_6B0]
	WriteMemoryDWORD(0x498ADC, 0x828);
	// .text:00498AE6                 add     esp, 130h
	WriteMemoryDWORD(0x498AE8, 0x134);

	int enlargeSet = 4;
	// CUserDbHelper::MakeNewUserObject
	// 004AF817                 call    CUser__CUser
	NOPMemory(0x4AF62A, 6);
	// .text:004AF786                 mov     eax, [esi+4D4h]
	WriteMemoryDWORD(0x4AF788, 0x740);		// new experience
	WriteInstruction(0x4AF62A, (INT32)&CLevel85System::ExtendMakeNewUserObject, 0, 0xE9);

	// CUser::CUser
	// 4AF028                 call    CUser__Set
	// .text:004AF2D5                 retn    124h
	EnlargeMemoryWORD(0x4AF2D6, enlargeSet);
	NOPMemory(0x4AEF00, 6);
	WriteInstruction(0x4AEF00, (INT32)&CLevel85System::ExtendCUserCUser, 0, 0xE9);

	// 
	// CUser::Set
	// .text:0049DB65                 mov     [edi+15Ch], ecx
	// .text:0049DCE8                 retn    0E0h
	EnlargeMemoryWORD(0x49DCE9, enlargeSet);
	NOPMemory(0x49DCAC, 6);
	WriteInstruction(0x49DCAC, (INT32)&CLevel85System::ExtendCUserSet, 0, 0xE9);

	// CUserDbHelper::ReloadUserInfo - volano CUser::Set
	// 4A6FD0                 mov     eax, [ebx+4D4h] ; experience
	NOPMemory(0x4A6ECD, 7);
	WriteInstruction(0x4A6ECD, (INT32)&CLevel85System::ExtendReloadUserInfo, 0, 0xE9);
	// .text:004A6FD0                 mov     eax, [ebx+4D4h]
	WriteMemoryDWORD(0x4A6FD2, 0x740);
	// .text:004A6FB8                 mov     [esp+10Ch+var_4], 1
	EnlargeMemoryDWORD(0x4A6FBB, enlargeSet);
	
	// it isn't needed, i hope so
	//EnlargeMov3(patch, 0x4A70A1, enlargeSet);
	//EnlargeMov3(patch, 0x4A70B1, enlargeSet);

	// .text:004FFF60                 push    offset SaveCharacterPacket
	WriteMemoryDWORD(0x4FFF61, (INT32)&CUser::SaveCharacterPacket64);

	// CUser::SetChanged
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::SetChanged
		push        469E6Fh
		call        WriteInstruction
		add			esp,10h
	}

	// CUser::Save - new implementation
	// .text:0046971A                 call    CUser__Save
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::Save64
		push        46971Ah
		call        WriteInstruction
		add			esp,10h
	}

	// .text:00469E8F                 call    CUser__Save
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::Save64
		push        469E8Fh
		call        WriteInstruction
		add			esp,10h
	}

	// .text:0047C09B                 call    CUser__Save
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::Save64
		push        47C09Bh
		call        WriteInstruction
		add			esp,10h
	}

	// .text:00480E7A                 call    CUser__Save
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::Save64
		push        480E7Ah
		call        WriteInstruction
		add			esp,10h
	}

	// .text:0048100A                 call    CUser__Save
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::Save64
		push        48100Ah
		call        WriteInstruction
		add			esp,10h
	}

	// .text:004A7B90                 call    CUser__Save	- rewritten in subjob

	// CUser::GetExpDiff
	__asm
	{
		push        0FFFFFFE8h
		push        0
		push        offset CUser::GetExpDiff64
		push        491E52h
		call        WriteInstruction
		add			esp,10h
	}

	//table-0x538FF8
	// 4A13A0 CUser__GetLevelByExp - change it
	// CUser::ModCharExtern
	// .text:004A9F88                 mov     ecx, [edi+15Ch]
	// CUser::ModCharSubJobAbilityAbsolutely
	// .text:004A8BC4                 mov     edx, [esi+15Ch]
	// CUser::ModCharExtern
	// .text:004A88DB                 mov     eax, [esi+15Ch]
	// .text:004A8938                 mov     [esi+15Ch], edi
	// .text:004A89B6                 mov     ecx, [esi+15Ch]
	// .text:004A89D3                 mov     eax, [esi+15Ch]
	// CUser::ModChar3Extern
	// .text:004A8FCB                 mov     eax, [esi+15Ch]
	// .text:004A8FEC                 add     [esi+15Ch], edi
	// .text:004A902C                 mov     eax, [esi+15Ch]
	// .text:004A9078                 mov     edx, [esi+15Ch]
	// .text:004A90B4                 mov     edx, [esi+15Ch]
	// .text:004A90D1                 mov     ecx, [esi+15Ch]
	// CUser::ModCharSubJobAbility
	// 4A9140


	//table-0x528CE8
	// 4630F0 - test that experience
	// 4D8690 - from level makes some kind of experience
}

void CLevel85System::EnlargeCUserDbHelper(int addSize)
{
	// 4AD6E0 CUserDb::ReLoadFromDb(int)
	// .text:004AD6F5                 sub     esp, 750h
	EnlargeMemoryDWORD(0x4AD6F7, addSize);
	// .text:004AD702                 mov     [esp+75Ch+var_10], eax
	EnlargeMemoryDWORD(0x4AD705, addSize);
	// .text:004AD70A                 mov     ebp, [esp+760h+arg_4]
	EnlargeMemoryDWORD(0x4AD70D, addSize);
	// .text:004AD713                 mov     edi, [esp+768h+arg_0]
	EnlargeMemoryDWORD(0x4AD716, addSize);
	// .text:004AD73F                 mov     [esp+76Ch+var_4], eax
	EnlargeMemoryDWORD(0x4AD742, addSize);
	// .text:004AD790                 mov     [esp+768h+var_4], 2
	EnlargeMemoryDWORD(0x4AD793, addSize);
	// .text:004AD7A6                 mov     byte ptr [esp+770h+var_4], 3
	EnlargeMemoryDWORD(0x4AD7A9, addSize);
	// .text:004AD7B3                 mov     [esp+768h+var_4], 0
	EnlargeMemoryDWORD(0x4AD7B6, addSize);
	// .text:004AD7CA                 mov     byte ptr [esp+768h+var_4], 2
	EnlargeMemoryDWORD(0x4AD7CD, addSize);
	// .text:004AD7E5                 mov     ecx, [esp+768h+var_C]
	EnlargeMemoryDWORD(0x4AD7E8, addSize);
	// .text:004AD7F7                 mov     ecx, [esp+760h+var_10]
	EnlargeMemoryDWORD(0x4AD7FA, addSize);
	// .text:004AD806                 add     esp, 75Ch
	EnlargeMemoryDWORD(0x4AD808, addSize);

	// 4AFA90 - CUserDb::LoadFromDb(unsigned int)
	// .text:004AFAA5                 sub     esp, 750h
	EnlargeMemoryDWORD(0x4AFAA7, addSize);
	// .text:004AFAB2                 mov     [esp+75Ch+var_10], eax
	EnlargeMemoryDWORD(0x4AFAB5, addSize);
	// .text:004AFABB                 mov     edi, [esp+764h+arg_0]
	EnlargeMemoryDWORD(0x4AFABE, addSize);
	// .text:004AFAE7                 mov     [esp+768h+var_4], eax
	EnlargeMemoryDWORD(0x4AFAEA, addSize);
	// .text:004AFB38                 mov     [esp+764h+var_4], 2
	EnlargeMemoryDWORD(0x4AFB3B, addSize);
	// .text:004AFB48                 mov     eax, [esp+764h+arg_4]
	EnlargeMemoryDWORD(0x4AFB4B, addSize);
	// .text:004AFB55                 mov     byte ptr [esp+76Ch+var_4], 3
	EnlargeMemoryDWORD(0x4AFB58, addSize);
	// .text:004AFB62                 mov     [esp+764h+var_4], 0
	EnlargeMemoryDWORD(0x4AFB65, addSize);
	// .text:004AFB79                 mov     byte ptr [esp+764h+var_4], 2
	EnlargeMemoryDWORD(0x4AFB7C, addSize);
	// .text:004AFB8C                 mov     ecx, [esp+764h+var_C]
	EnlargeMemoryDWORD(0x4AFB8F, addSize);
	// .text:004AFBA5                 mov     ecx, [esp+760h+var_10]
	EnlargeMemoryDWORD(0x4AFBA8, addSize);
	// .text:004AFBB4                 add     esp, 75Ch
	EnlargeMemoryDWORD(0x4AFBB6, addSize);

	// 4AFBC0 - CUserDb::LoadFromDb(WCHAR)
	// .text:004AFBD5                 sub     esp, 750h
	EnlargeMemoryDWORD(0x4AFBD7, addSize);
	// .text:004AFBE2                 mov     [esp+75Ch+var_10], eax
	EnlargeMemoryDWORD(0x4AFBE5, addSize);
	// .text:004AFBEA                 mov     ebp, [esp+760h+arg_4]
	EnlargeMemoryDWORD(0x4AFBED, addSize);
	// .text:004AFBF3                 mov     edi, [esp+768h+arg_0]
	EnlargeMemoryDWORD(0x4AFBF6, addSize);
	// .text:004AFC1F                 mov     [esp+76Ch+var_4], eax
	EnlargeMemoryDWORD(0x4AFC22, addSize);
	// .text:004AFC70                 mov     [esp+768h+var_4], 2
	EnlargeMemoryDWORD(0x4AFC73, addSize);
	// .text:004AFC86                 mov     byte ptr [esp+770h+var_4], 3
	EnlargeMemoryDWORD(0x4AFC89, addSize);
	// .text:004AFC93                 mov     [esp+768h+var_4], 0
	EnlargeMemoryDWORD(0x4AFC96, addSize);
	// .text:004AFCAA                 mov     byte ptr [esp+768h+var_4], 2
	EnlargeMemoryDWORD(0x4AFCAD, addSize);
	// .text:004AFCC5                 mov     ecx, [esp+768h+var_C]
	EnlargeMemoryDWORD(0x4AFCC8, addSize);
	// .text:004AFCD7                 mov     ecx, [esp+760h+var_10]
	EnlargeMemoryDWORD(0x4AFCDA, addSize);
	// .text:004AFCE6                 add     esp, 75Ch
	EnlargeMemoryDWORD(0x4AFCE8, addSize);
}

__declspec(naked) void CLevel85System::FixGetExp()
{
	__asm
	{
		mov     eax, [esi+15Ch]
		mov		edx, [esi+748h]
		mov		esi, 4A0B26h
		jmp		esi
	}
}

__declspec(naked) void CLevel85System::ExtendCUserInit()
{
	__asm
	{
		mov     [esi+73Ch], eax
		// enlarge CUserDbHelper
		mov		[esi+740h], eax
		mov		[esi+744h], eax
		// enlarge CUserDbHelper
		mov		eax,	49D83Dh
		jmp		eax
	}
}

__declspec(naked) void CLevel85System::FixLoadSelectedCharacter()
{
	__asm
	{
		push	edx
		push    eax
		lea     ecx, [esp+170h]
		mov		eax, 473F55h
		jmp		eax
	}
}

__declspec(naked) void CLevel85System::FixLoadCharacterPacket()
{
	__asm
	{
		push	edx
		push    eax
		mov     ecx, esi
		mov		eax, 4A0A00h
		call	eax		// CUser::GetSP
		mov		ecx, 498A42h
		jmp		ecx
	}
}

__declspec(naked) void CLevel85System::ExtendMakeNewUserObject()
{
	__asm
	{
		// new list CUser::CUser
		mov		edx, [esi+744h]
		push	edx
		// new list CUser::CUser
		mov     edx, [esi+578h]
		mov		ecx, 4AF630h
		jmp		ecx
	}
}

__declspec(naked) void CLevel85System::ExtendCUserCUser()
{
	__asm
	{
		// new list CUser::CUser
		mov		eax, [ebp+12Ch]
		push	eax
		// new list CUser::CUser
		mov		eax, [ebp+128h]
		mov		esi, 4AEF06h
		jmp		esi
	}
}

__declspec(naked) void CLevel85System::ExtendCUserSet()
{
	__asm
	{
		mov     [edi+22Ch], eax
		// new params
		mov     eax, [esp+104h]
		mov		[edi+748h], eax
		// new params
		mov		eax, 49DCB2h
		jmp		eax
	}
}

__declspec(naked) void CLevel85System::ExtendReloadUserInfo()
{
	__asm
	{
		// new list of input parameters to CUser::Set
		mov		eax,	[ebx+744h]
		push	eax
		// new list of input parameters to CUser::Set
		mov     eax,	[ebx+578h]
		push    eax
		mov		eax,	4A6ED4h
		jmp		eax
	}
}

bool CLevel85System::NewRequestCreateSubJob(CQuerySocket *pQuerySocket, const char* packet)
{
	try
	{
		int nObjectId = 0;
		int nCharId = 0;
		int bIsGm = 0;
		int nNpcIndex = 0;
		int nUserIndex = 0;
		int nNewSubJobId = 0;
		int nNewClass = 0;
		int nSubClassId = 0;
		double fHP = 0.0;
		double fMP = 0.0;
		int nSp = 0;
		__int64 nExp = 0;
		int nLevel = 0;
		int henna1 = 0;
		int henna2 = 0;
		int henna3 = 0;

		CObjectSP userSP;

		DisassembleQ(packet, "ddddddddffdfdddd",
			&nObjectId,
			&nCharId,
			&bIsGm,
			&nNpcIndex,
			&nUserIndex,
			&nNewSubJobId,
			&nNewClass,
			&nSubClassId,
			&fHP,
			&fMP,
			&nSp,
			&nExp,
			&nLevel,
			&henna1,
			&henna2,
			&henna3);

		CUserDB::I()->GetUser(&userSP, nCharId, true);
		CUser *user = (CUser*)userSP.pObject;

		if (user == NULL)
		{
			pQuerySocket->Send("cdddddd",
				0xCF,
				nObjectId,
				bIsGm,
				nNpcIndex,
				nUserIndex,
				0,
				nNewClass);
			/*
				Threadsafe error
			*/
			return false;
		}
		
		user->ThreadSafeTest();
		int result = user->CreateSubJob64(nNewSubJobId, nNewClass, nSubClassId, fHP, fMP, nSp, nExp, nLevel, henna1, henna2, henna3);

		pQuerySocket->Send("cdddddd",
			0xCF,
			nObjectId,
			bIsGm,
			nNpcIndex,
			nUserIndex,
			result,
			nNewClass);

		if (result == 0)
			return false;

		if (user != NULL)
		{
			// zaznam do logu - 48F40B
			// zaznam do logu - 48F6D7
			user->AddUserLog2(2, user->GetClass(), nNewClass, 0, result);
		}

		userSP.Release();
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%ls] Exception occured !", __FUNCTIONW__);
	}

	return false;
}

bool CLevel85System::NewRenewSubJob(CQuerySocket *pQuerySocket, const char* packet)
{
	try
	{
		int nObjectID = 0;
		int nCharId = 0;
		int bByBuilder = 0;
		int nNpcIndex = 0;
		int nUserIndex = 0;
		int nSubJobId = 0;
		int nNewClass = 0;
		int SubClassId = 0;
		double fHP = 0.0;
		double fMP = 0.0;
		int nSp = 0;
		__int64 newExp = 0;
		int nLevel = 0;
		int nHenna1 = 0;
		int nHenna2 = 0;
		int nHenna3 = 0;
		CObjectSP userSP;

		DisassembleQ(packet, "ddddddddffdQdddd",
				&nObjectID,
				&nCharId,
				&bByBuilder,
				&nNpcIndex,
				&nUserIndex,
				&nSubJobId,
				&nNewClass,
				&SubClassId,
				&fHP,
				&fMP,
				&nSp,
				&newExp,
				&nLevel,
				&nHenna1,
				&nHenna2,
				&nHenna3);

		CUserDB::I()->GetUser(&userSP, nCharId, true);
		CUser *user = (CUser*)userSP.pObject;

		if (user == NULL)
		{
			pQuerySocket->Send("chddddddd",
				0xD6,
				0x14,
				nObjectID,
				bByBuilder,
				nNpcIndex,
				nUserIndex,
				nSubJobId,
				nNewClass,
				0);
			return false;
		}

		bool result = user->RenewSubJob64(nSubJobId, nNewClass, SubClassId, fHP, fMP, nSp, newExp, nLevel, nHenna1, nHenna2, nHenna3);

		pQuerySocket->Send("chddddddd",
			0xD6,
			0x14,
			nObjectID,
			bByBuilder,
			nNpcIndex,
			nUserIndex,
			nSubJobId,
			nNewClass,
			result);
		
		if (result && user != NULL)
		{
			// zaznam do logu - 460A59
		}

		userSP.Release();
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%ls] Exception occured !", __FUNCTIONW__);
	}

	return false;
}

bool CLevel85System::NewRequestChangeSubJob(CQuerySocket *pQuerySocket, const char* packet)
{
	try
	{
		int nObjectID = 0;
		int nCharId = 0;
		int bByBuilder = 0;
		int nNpcIndex = 0;
		int nUserIndex = 0;
		int nSubJobId = 0;
		int SubClassId = 0;
		double fHP = 0.0;
		double fMP = 0.0;
		int nSp = 0;
		__int64 newExp = 0;
		int nLevel = 0;
		int nHenna1 = 0;
		int nHenna2 = 0;
		int nHenna3 = 0;

		CObjectSP userSP;

		DisassembleQ(packet, "dddddddffdQdddd",
			&nObjectID,
			&nCharId,
			&bByBuilder,
			&nNpcIndex,
			&nUserIndex,
			&nSubJobId,
			&SubClassId,
			&fHP,
			&fMP,
			&nSp,
			&newExp,
			&nLevel,
			&nHenna1,
			&nHenna2,
			&nHenna3);

		CUserDB::I()->GetUser(&userSP, nCharId, true);
		CUser *user = (CUser*)userSP.pObject;

		if (user == NULL)
		{
			pQuerySocket->Send("cddddddffdfdddd",
				0xD1,
				nObjectID,
				bByBuilder,
				nNpcIndex,
				nUserIndex,
				nSubJobId,
				0,
				fHP,
				fMP,
				nSp,
				newExp,
				nLevel,
				nHenna1,
				nHenna2,
				nHenna3);
		}
		else
		{
			bool result = user->ChangeSubJob64(nSubJobId, SubClassId, &fHP, &fMP, &nSp, &newExp, &nLevel, &nHenna1, &nHenna2, &nHenna3);
			user->ThreadSafeTest();

			// zaznam do logu - 4900CE

			pQuerySocket->Send("cddddddffdfdddd",
				0xD1,
				nObjectID,
				bByBuilder,
				nNpcIndex,
				nUserIndex,
				nSubJobId,
				result,
				fHP,
				fMP,
				nSp,
				newExp,
				nLevel,
				nHenna1,
				nHenna2,
				nHenna3);

			userSP.Release();
		}
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%ls] Exception occured !", __FUNCTIONW__);
	}

	return false;
}

// 490420 - RequestSaveCharacterForSubJob
bool CLevel85System::NewRequestSaveCharacterForSubJob(CQuerySocket *pQuerySocket, const char* packet)
{
	try
	{
		int nCharId = 0;
		int SubClassId = 0;
		int nClass = 0;
		double fHP = 0.0;
		double fMP = 0.0;
		double fMaxHP = 0.0;
		double fMaxMP = 0.0;
		double fCP = 0.0;
		double fMaxCP = 0.0;
		int nSp = 0;
		__int64 newExp = 0;
		int nLevel = 0;
		int nHenna1 = 0;
		int nHenna2 = 0;
		int nHenna3 = 0;
		CObjectSP userSP;

		DisassembleQ(packet, "dddffffffdQdddd",
			&nCharId,
			&SubClassId,
			&nClass,
			&fHP,
			&fMP,
			&fMaxHP,
			&fMaxMP,
			&fCP,
			&fMaxCP,
			&nSp,
			&newExp,
			&nLevel,
			&nHenna1,
			&nHenna2,
			&nHenna3);

		CUserDB::I()->GetUser(&userSP, nCharId, true);
		CUser *user = (CUser*)userSP.pObject;

		if (user == NULL)
		{
			// show in log
			return false;
		}

		user->WriteLock(__FUNCTIONW__, __LINE__);

		if (user != NULL)
		{
			if (!user->SaveForSubJob64(SubClassId, nClass, fHP, fMP, fMaxHP, fMaxMP, fCP, fMaxCP, nSp, newExp, nLevel, nHenna1, nHenna2, nHenna3))
			{
				// show error in log
			}
		}
		user->WriteUnlock();
		
		userSP.Release();
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%ls] Exception occured !", __FUNCTIONW__);
	}

	return false;
}
