#include "Global.h"
#include "CUser.h"

__declspec(naked) void CUser::SaveMemo()
{
	__asm
	{
		mov		eax, 49E560h
		jmp		eax
	}
}

__declspec(naked) void CUser::SetQuest(__int32 c1)
{
	__asm
	{
		mov		eax, 4A8300h
		jmp		eax
	}
}

__declspec(naked) wchar_t* CUser::GetCharName()
{
	__asm
	{
		mov		eax, 4A00A0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetId()
{
	__asm
	{
		mov		eax, 49D850h
		jmp		eax
	}
}

__declspec(naked) wchar_t* CUser::GetAccountName()
{
	__asm
	{
		mov		eax, 4A0140h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetAccountID()
{
	__asm
	{
		mov		eax, 4A01E0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetPledgeID()
{
	__asm
	{
		mov		eax, 4A0280h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetBuilder()
{
	__asm
	{
		mov		eax, 4A0320h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetGender()
{
	__asm
	{
		mov		eax, 4A03C0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetRace()
{
	__asm
	{
		mov		eax, 4A0460h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetClass()
{
	__asm
	{
		mov		eax, 4A0500h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetWorld()
{
	__asm
	{
		mov		eax, 4A05A0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetX()
{
	__asm
	{
		mov		eax, 4A0640h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetY()
{
	__asm
	{
		mov		eax, 4A06E0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetZ()
{
	__asm
	{
		mov		eax, 4A0780h
		jmp		eax
	}
}

__declspec(naked) double CUser::GetHP()
{
	__asm
	{
		mov		eax, 4A0820h
		jmp		eax
	}
}

__declspec(naked) double CUser::GetMP()
{
	__asm
	{
		mov		eax, 4A08C0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetSP()
{
	__asm
	{
		mov		eax, 4A0A00h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetExp()
{
	__asm
	{
		mov		eax, 4A0AA0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetLevel()
{
	__asm
	{
		mov		eax, 4A0B40h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetAlign()
{
	__asm
	{
		mov		eax, 4A0BE0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetPK()
{
	__asm
	{
		mov		eax, 4A0C80h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetDuel()
{
	__asm
	{
		mov		eax, 4A0D20h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetPKPardon()
{
	__asm
	{
		mov		eax, 4A0DC0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetUnderware()
{
	__asm
	{
		mov		eax, 49EA00h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetRight_ear()
{
	__asm
	{
		mov		eax, 49EAA0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetLeft_ear()
{
	__asm
	{
		mov		eax, 49EB40h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetNeck()
{
	__asm
	{
		mov		eax, 49EBE0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetRight_finger()
{
	__asm
	{
		mov		eax, 49EC80h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetLeft_finger()
{
	__asm
	{
		mov		eax, 49ED20h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetHead()
{
	__asm
	{
		mov		eax, 49EDC0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetRight_hand()
{
	__asm
	{
		mov		eax, 49EE60h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetLeft_hand()
{
	__asm
	{
		mov		eax, 49EF00h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetGloves()
{
	__asm
	{
		mov		eax, 49EFA0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetChest()
{
	__asm
	{
		mov		eax, 49F040h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetLegs()
{
	__asm
	{
		mov		eax, 49F0E0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetFeet()
{
	__asm
	{
		mov		eax, 49F180h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetBack()
{
	__asm
	{
		mov		eax, 49F220h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetBoth_hand()
{
	__asm
	{
		mov		eax, 49F2C0h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetHair()
{
	__asm
	{
		mov		eax, 49F360h
		jmp		eax
	}
}

__declspec(naked) void CUser::WriteLock(const wchar_t* file, int line)
{
	__asm
	{
		mov		eax, 4A16C0h
		jmp		eax
	}
}

__declspec(naked) void CUser::WriteUnlock()
{
	__asm
	{
		mov		eax, 4A1780h
		jmp		eax
	}
}

__declspec(naked) int CUser::GetExpDiff()
{
	__asm
	{
		mov		eax, 4A2B40h
		jmp		eax
	}
}

__int64 CUser::GetExpDiff64()
{
	__int64 result = 0;
	this->WriteLock(L"GetExpDiff64", 1);
	
	if (this->unk560 == 0)
	{
		result = this->GetExp() - this->newExp038;
	}

	this->newExp038 = this->GetExp();
	this->unk038 = (__int32) this->newExp038;
	this->unk560 = 0;

	this->WriteUnlock();

	return result;
}

__declspec(naked) int CUser::GetLevelByExp(int exp)
{
	__asm
	{
		mov		eax, 4A13A0h
		jmp		eax
	}
}

__declspec(naked) void CUser::LoadWarehouseItems(CObjectSP *items, int unk1, int forceLoad)
{
	_asm
	{
		mov		eax, 4A9D30h
		jmp		eax
	}
}

__declspec(naked) bool CUser::Save()
{
	__asm
	{
		mov		eax, 4A77F0h
		jmp		eax
	}
}

__declspec(naked) bool CUser::SaveHennaInfo()
{
	__asm
	{
		mov		eax, 4A3E20h
		jmp		eax
	}
}

__declspec(naked) int CUser::CreateSubJob(int nNewSubJobId, int nNewClass, int nSubClassId, double fHP, double fMP, int nSp, int nExp, int nLevel, int henna1, int henna2, int henna3)
{
	__asm
	{
		mov		eax, 4A4880h
		jmp		eax
	}
}

wchar_t *createSubJob64 = L"EXEC lin_CreateSubJob %d, %d, %d, %d, %f, %f, %d, %I64d, %d, %d, %d, %d";
int CUser::CreateSubJob64(int nNewSubJobId, int nNewClass, int nSubClassId, double fHP, double fMP, int nSp, __int64 nExp, int nLevel, int henna1, int henna2, int henna3)
{
	int result;

	try
	{
		this->WriteLock(__FILEW__, __LINE__);
		DBConn dbc;
		wchar_t sqlCommand[500];

		dbc.BindD(&result);
		
		swprintf(sqlCommand, 500, createSubJob64, this->GetId(), nNewSubJobId, nNewClass, nSubClassId, fHP, fMP, nSp, nExp, nLevel, henna1, henna2, henna3);

		if (dbc.Execute(sqlCommand))
		{
			if (!dbc.Fetch())
			{
				CLog::Add(CLog::red, L"Error creating subjob, charid=%d, newclass=%d", this->GetId(), nNewClass);
			}
		}

		this->unk560 = 1;
		this->WriteUnlock();
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%s][%d] Exception occured !", __FILEW__, __LINE__);
	}

	return result;
}

__declspec(naked) bool CUser::RenewSubJob(int nSubJobId, int nNewClass, int SubClassId, double fHP, double fMP, int nSp, int Exp, int nLevel, int nHenna1, int nHenna2, int nHenna3)
{
	__asm
	{
		mov		eax, 4A4A30h
		jmp		eax
	}
}
wchar_t *renewSubJob64 = L"EXEC lin_RenewSubJob %d, %d, %d, %d, %f, %f, %d, %I64d, %d, %d, %d, %d";
bool CUser::RenewSubJob64(int nSubJobId, int nNewClass, int SubClassId, double fHP, double fMP, int nSp, __int64 Exp, int nLevel, int nHenna1, int nHenna2, int nHenna3)
{
	bool result = false;

	try
	{
		this->WriteLock(__FILEW__, __LINE__);
		DBConn dbc;
		wchar_t sqlCommand[500];
		dbc.BindD(&result);

		swprintf(sqlCommand, 500, renewSubJob64, this->GetId(), nSubJobId, nNewClass, SubClassId, fHP, fMP, nSp, Exp, nLevel, nHenna1, nHenna2, nHenna3);

		if (dbc.Execute(sqlCommand))
		{
			if (dbc.Fetch())
			{
				if (result != 0)
				{
					this->unk560 = 1;
					result = true;
				}
			}
		}
		this->WriteUnlock();
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%s][%d] Exception occured !", __FILEW__, __LINE__);
	}

	return result;
}

__declspec(naked) bool CUser::ChangeSubJob(int nSubJobId, int SubClassId, double *fHP, double *fMP, int *nSp, int *nExp, int *nLevel, int *nHenna1, int *nHenna2, int *nHenna3)
{
	__asm
	{
		mov		eax, 4A4D40h
		jmp		eax
	}
}

wchar_t *changeSubJob64 = L"EXEC lin_ChangeSubJob %d, %d, %d, %f, %f, %d, %I64d, %d, %d, %d, %d";
bool CUser::ChangeSubJob64(int nSubJobId, int SubClassId, double *fHP, double *fMP, int *nSp, __int64 *nExp, int *nLevel, int *nHenna1, int *nHenna2, int *nHenna3)
{
	bool result = false;
	try
	{
		this->WriteLock(__FILEW__, __LINE__);
		DBConn dbc;
		wchar_t sqlCommand[500];

		// hp, mp, sp, exp, level, henna_1, henna_2, henna_3
		dbc.BindF(fHP);
		dbc.BindF(fMP);
		dbc.BindD(nSp);
		dbc.BindQ(nExp);
		dbc.BindD(nLevel);
		dbc.BindD(nHenna1);
		dbc.BindD(nHenna2);
		dbc.BindD(nHenna3);

		swprintf(sqlCommand, 500, changeSubJob64, this->GetId(), nSubJobId, SubClassId, *fHP, *fMP, *nSp, *nExp, *nLevel, *nHenna1, *nHenna2, *nHenna3);
		if (dbc.Execute(sqlCommand))
		{
			if (dbc.Fetch())
			{
				result = true;
			}
		}

		this->unk560 = 1;

		this->WriteUnlock();
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%s][%d] Exception occured !", __FILEW__, __LINE__);
	}

	return result;
}

__declspec(naked) bool CUser::SaveForSubJob(int SubClassId, int nClass, double fHP, double fMP, double fMaxHP, double fMaxMP, double fCP, double fMaxCP, int nSp, int nExp, int nLevel, int nHenna1, int nHenna2, int nHenna3)
{
	__asm
	{
		mov		eax, 490420h
		jmp		eax
	}
}

bool CUser::SaveForSubJob64(int SubClassId, int nClass, double fHP, double fMP, double fMaxHP, double fMaxMP, double fCP, double fMaxCP, int nSp, __int64 nExp, int nLevel, int nHenna1, int nHenna2, int nHenna3)
{
	bool result = false;

	try
	{
		this->subClassId = SubClassId;
		this->nClass = nClass;
		
		this->fHP = fHP;
		this->fMP = fMP;
		this->fMaxHP = fMaxHP;
		this->fMaxMP = fMaxMP;

		this->nSp = nSp;
		this->experience = (unsigned int)nExp;
		this->experienceHi = nExp >> 32;
		this->nLevel = nLevel;
		this->nHenna1 = nHenna1;
		this->nHenna2 = nHenna2;
		this->nHenna3 = nHenna3;

		bool saveResult = this->Save64();
		bool saveHennaResult = this->SaveHennaInfo();

		if (saveResult && saveHennaResult)
			result = true;
	}
	catch(...)
	{
		CLog::Add(CLog::red, L"[%s][%d] Exception occured !", __FILEW__, __LINE__);
	}

	return result;
}

wchar_t *new_user_Save = L"EXEC lin_SaveCharacter %d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%d,%I64d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%d";
bool CUser::Save64()
{
	DBConn dbc;

	__int64 exp = (((__int64)this->experienceHi) << 32) + ((__int64)this->experience);

	bool result = dbc.Execute(new_user_Save, this->subClassId, this->nPledgeId, this->nClass, this->nWorld, this->x, this->y, this->z, this->nIsInVehicle,
		this->fHP, this->fMP, this->fMaxHP, this->fMaxMP, this->nSp, exp, this->nLevel, this->nAlign, this->nPK, this->nDuel, this->nPKPardon,
		this->ST_underware, this->ST_right_ear, this->ST_left_ear, this->ST_neck, this->ST_right_finger, this->ST_left_finger, this->ST_head, this->ST_right_hand,
		this->ST_left_hand, this->ST_gloves, this->ST_chest, this->ST_legs, this->ST_feet, this->ST_back, this->ST_both_hand, this->Face_Index, this->Hair_Shape_Index,
		this->Hair_Color_Index, this->ssq_dawn_round, this->charId, this->subjob0_class, this->subjob1_class, this->subjob2_class, this->subjob3_class,
		this->fCP, this->fMaxCP, this->ST_hair);

	if (!result)
	{
		CLog::Add(CLog::red, L"Character save error.");
	}

	return result;
}

__declspec(naked) void CUser::SetChangedLock()
{
	__asm
	{
		push	0
		push	0
		lea     ecx, [ecx+3Ch]
		mov		eax, 45D000h
		jmp		eax
	}
}

__declspec(naked) void CUser::SetChangedUnlock()
{
	__asm
	{
		lea     ecx, [ecx+3Ch]
		mov		eax, 45D230h
		jmp		eax
	}
}


void CUser::SetChanged(int nPledgeId, int nBuilder, int nGender, int nRace, int nClass, int nWorld, int locX, int locY, int locZ,
							 double fHP, double fMP, double fMaxHP, double fMaxMP, int nSp, __int64 experience, int nLevel, int nAlign, int nPK, int nDuel, int nPKPardon,
							 int ST_underware, int ST_right_ear, int ST_left_ear, int ST_neck, int ST_right_finger, int ST_left_finger, int ST_head, int ST_right_hand,
							 int ST_left_hand, int ST_gloves, int ST_chest, int ST_legs, int ST_feet, int ST_back, int ST_both_hand, int ST_hair, int Face_Index,
							 int Hair_Shape_Index, int Hair_Color_Index, int nIsInVehicle, int subClassId, int subjob0_class, int subjob1_class, int subjob2_class,
							 int subjob3_class, double fCP, double fMaxCP, int ssq_dawn_round, bool locked)
{
	if (!locked)
	{
		this->SetChangedLock();
	}

	this->nPledgeId = nPledgeId;
	this->nBuilder = nBuilder;
	this->nGender = nGender;
	this->nRace = nRace;
	this->nClass = nClass;
	this->nWorld = nWorld;
	this->x = locX;
	this->y = locY;
	this->z = locZ;
	this->fHP = fHP;
	this->fMP = fMP;
	this->fMaxHP = fMaxHP;
	this->fMaxMP = fMaxMP;
	this->nSp = nSp;
	this->experience = (unsigned int)experience;
	this->experienceHi = (unsigned int)(experience >> 32);
	this->nLevel = nLevel;
	this->nAlign = nAlign;
	this->nPK = nPK;
	this->nDuel = nDuel;
	this->nPKPardon = nPKPardon;
	this->ST_underware = ST_underware;
	this->ST_right_ear = ST_right_ear;
	this->ST_left_ear = ST_left_ear;
	this->ST_neck = ST_neck;
	this->ST_right_finger = ST_right_finger;
	this->ST_left_finger = ST_left_finger;
	this->ST_head = ST_head;
	this->ST_right_hand = ST_right_hand;
	this->ST_left_hand = ST_left_hand;
	this->ST_gloves = ST_gloves;
	this->ST_chest = ST_chest;
	this->ST_legs = ST_legs;
	this->ST_feet = ST_feet;
	this->ST_back = ST_back;
	this->ST_both_hand = ST_both_hand;
	this->ST_hair = ST_hair;
	this->Face_Index = Face_Index;
	this->Hair_Shape_Index = Hair_Shape_Index;
	this->Hair_Color_Index = Hair_Color_Index;
	this->nIsInVehicle = nIsInVehicle;
	this->subClassId = subClassId;
	this->subjob0_class = subjob0_class;
	this->subjob1_class = subjob1_class;
	this->subjob2_class = subjob2_class;
	this->subjob3_class = subjob3_class;
	this->fCP = fCP;
	this->fMaxCP = fMaxCP;
	this->ssq_dawn_round = ssq_dawn_round;

	if (!locked)
	{
		this->SetChangedUnlock();
	}
}

// ddddddddffffffddddddddddddddddddddddddddddddddd
bool CUser::SaveCharacterPacket64(CQuerySocket *pSocket, const unsigned char *packet)
{
	int nClassId = 0, var_F0 = 0, nBuilder = 0, nClass = 0, nWorld = 0, locX = 0, locY = 0, locZ = 0;
	double fHP = 0.0, fMP = 0.0, fMaxHP = 0.0, fMaxMP = 0.0, fCP = 0.0, fMaxCP = 0.0;
	int nSp = 0, nLevel = 0, nAlign = 0, nPK = 0, nDuel = 0, nPKPardon = 0, ST_underware = 0, ST_right_ear = 0, ST_left_ear = 0;
	__int64 experience = 0;
	int ST_neck = 0, ST_right_finger = 0, ST_left_finger = 0, ST_head = 0, ST_right_hand = 0, ST_left_hand = 0, ST_gloves = 0, ST_chest = 0, ST_legs = 0, ST_feet = 0;
	int ST_back = 0, ST_both_hand = 0, ST_hair = 0, Face_Index = 0, Hair_Shape_Index = 0, Hair_Color_Index = 0, nIsInVehicle = 0, subClassId = 0, subjob0_class = 0, subjob1_class = 0;
	int subjob2_class = 0, subjob3_class = 0, ssq_dawn_round = 0;

	DisassembleQ((const char*)packet, "ddddddddffffffdQddddddddddddddddddddddddddddddd",
		&nClassId, &var_F0, &nBuilder, &nClass, &nWorld, &locX, &locY, &locZ,
		&fHP, &fMP, &fMaxHP, &fMaxMP, &fCP, &fMaxCP,
		&nSp, &experience, &nLevel, &nAlign, &nPK, &nDuel, &nPKPardon, &ST_underware, &ST_right_ear, &ST_left_ear,
		&ST_neck, &ST_right_finger, &ST_left_finger, &ST_head, &ST_right_hand, &ST_left_hand, &ST_gloves, &ST_chest, &ST_legs, &ST_feet,
		&ST_back, &ST_both_hand, &ST_hair, &Face_Index, &Hair_Shape_Index, &Hair_Color_Index, &nIsInVehicle, &subClassId, &subjob0_class, &subjob1_class,
		&subjob2_class, &subjob3_class, &ssq_dawn_round);

	if (fHP < 0 || fMP < 0 || nPK < 0 || nAlign < 0 || nLevel < 0)
	{
		CLog::Add(CLog::red, L"[%S][%d] Character save error[%d]. [%d][%f][%f][%f][%f][%d][%I64d][%d][%d][%d][%d][%d]",
			__FILEW__, __LINE__, nClassId, var_F0, fHP, fMaxHP, fMP, fMaxMP, nSp, experience, nLevel, nAlign, nPK, nDuel, nPKPardon);
	}
	else
	{
		if (fHP > fMaxHP)
			fHP = fMaxHP;
		if (fMP > fMaxMP)
			fMP = fMaxMP;

		CObjectSP userSP;

		CUserDB::I()->GetUser(&userSP, nClassId, true);

		if (userSP.pObject != NULL)
		{
			CObjectSP itemsSP;
			userSP.GetSafeUser()->LoadWarehouseItems(&itemsSP, 0, 1);
			if (itemsSP.GetSafeWareHouse()->ItNeedsToSave)
			{
				itemsSP.GetSafeWareHouse()->WriteLock();
				itemsSP.GetSafeWareHouse()->SaveUnsavedItems();
				itemsSP.GetSafeWareHouse()->WriteUnlock();
			}

			userSP.GetSafeUser()->WriteLock(__FILEW__, __LINE__);

			int oldLevel = userSP.GetSafeUser()->GetLevel();
			int oldClass = userSP.GetSafeUser()->GetClass();

			userSP.GetSafeUser()->SetChanged(userSP.GetSafeUser()->GetPledgeID(), nBuilder, userSP.GetSafeUser()->GetGender(),
				userSP.GetSafeUser()->GetRace(), nClass, nWorld, locX, locY, locZ, fHP, fMP, fMaxHP, fMaxMP, nSp, experience,
				nLevel, nAlign, nPK, nDuel, nPKPardon, ST_underware, ST_right_ear, ST_left_ear, ST_neck, ST_right_finger, ST_left_finger, ST_head, ST_right_hand,
				ST_left_hand, ST_gloves, ST_chest, ST_legs, ST_feet, ST_back, ST_both_hand, ST_hair, Face_Index, Hair_Shape_Index, Hair_Color_Index, nIsInVehicle,
				subClassId, subjob0_class, subjob1_class, subjob2_class, subjob3_class, fCP, fMaxCP, ssq_dawn_round, true);

			userSP.GetSafeUser()->WriteUnlock();
			userSP.GetSafeUser()->Save64();

			if (oldLevel != nLevel)
			{
				// TODO: save to log
				// from: 469E9E
			}

			if (oldClass != nClass)
			{
				// TODO: save to log
				// from: 46A0EB
			}

			itemsSP.Release();
		}
		else
		{
			CLog::Add(CLog::red, L"Character save error. Cannot find user. id[%d]", nClassId);
		}

		userSP.Release();
	}

	return false;
}

__declspec(naked) CUser* CUser::ThreadSafeTest()
{
	__asm
	{
			mov		eax, 4064F0h
			jmp		eax
	}
}

__declspec(naked) bool CUser::AddUserLog2(int nLogId, int nLogFrom, int nLogTo, unsigned int nUseTime, int nSubjobId)
{
	__asm
	{
			mov		eax, 4A1F00h
			jmp		eax
	}
}
