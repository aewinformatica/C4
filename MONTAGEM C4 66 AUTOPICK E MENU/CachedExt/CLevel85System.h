#pragma once

#include "Global.H"

class CLevel85System
{
public:
	static void Initialize();
	static void InitializeAfterStart();

private:
	static void MoveExperience(int index);
	static void EnlargeCUserDbHelper(int addSize);
	
	static void FixGetExp();
	static void ExtendCUserInit();
	static void FixLoadSelectedCharacter();
	static void FixLoadCharacterPacket();
	static void ExtendMakeNewUserObject();
	static void ExtendCUserCUser();
	static void ExtendCUserSet();
	static void ExtendReloadUserInfo();
	
	static bool NewRequestCreateSubJob(CQuerySocket *pQuerySocket, const char* packet);
	static bool NewRenewSubJob(CQuerySocket *pQuerySocket, const char* packet);
	static bool NewRequestChangeSubJob(CQuerySocket *pQuerySocket, const char* packet);
	static bool NewRequestSaveCharacterForSubJob(CQuerySocket *pQuerySocket, const char* packet);
};
