#include "Global.h"
#include "../L2Extend/SharedCached.h"
#include "CAugmentationSystem.h"

void PacketHandler::Initialize()
{
	WriteMemoryDWORD(0x56A960, (INT32)Handle); //overwriting address, our function will be called instead of DummyPacket from cached

	// Protection for Request Query Packet Possible Crash's
	WriteMemoryDWORD(0x501D81, (INT32)PacketHandler::RequestQueryPacket);
}

bool __cdecl PacketHandler::RequestQueryPacket(VOID *pSocket, CHAR *pPacket)
{
	//CLog::Add(CLog::blue, L"Processing Query...");

	__try
	{
		// Functions
		typedef bool (__cdecl *_RQP) (VOID *, CHAR *);
		_RQP xRequestQueryPacket = (_RQP)0x00466880L;

		// Calling Original Function
		xRequestQueryPacket(pSocket, pPacket);
	}
	__except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION)
	{
		CLog::Add(CLog::red, L"[%ls] -> Fatal Error, Verify ! (Query ID 0x%02X)", __FUNCTIONW__, (BYTE)pPacket[0]);
	}

	return false;
}

bool __cdecl PacketHandler::Handle(CQuerySocket *pQuerySocket, unsigned char* packet)
{
	int nOpcode = 0;
	
	BYTE *pPacket = Disassemble(packet, "d", &nOpcode);

	__try
	{
		switch(nOpcode)
		{
			case S_SET_PLEDGE_POWER:
				{
					return CPledgeSystem::RequestSavePledgePower(pQuerySocket, pPacket);
				}
			case S_GET_PLEDGE_INFO:
				{
					return CPledgeSystem::RequestCreateExtPledgeInfo(pQuerySocket, pPacket);
				}
			case S_GET_PLEDGE_REPUTATION:
				{
					return CPledgeSystem::RequestSetPledgeReputation(pQuerySocket, pPacket);
				}
			case S_GET_PLEDGE_SKILL:
				{
					return CPledgeSystem::RequestAcquirePledgeSkill(pQuerySocket, pPacket);
				}
			case S_SET_USER_NEWPLEDGETYPE:
				{
					return CPledgeSystem::RequestReorganizeMember(pQuerySocket, pPacket);
				}
			case S_NEW_SUBPLEDGE_OR_SET_CAPTAIN:
				{
					return CPledgeSystem::RequestCreateSubPledgeOrSetCaptain(pQuerySocket, pPacket);
				}
			case S_DELETE_SUBPLEDGE:
				{
					return CPledgeSystem::RequestDeleteSubPledge(pQuerySocket, pPacket);
				}
			case S_SET_SPONSOR:
				{
					return CPledgeSystem::RequestSetSponsor(pQuerySocket, pPacket);
				}
			case S_SET_APPRENTICE:
				{
					return CPledgeSystem::RequestSetApprentice(pQuerySocket, pPacket);
				}
			case S_SAVE_INFECTED_SKILLS_TO_DB:
				{
					return CInfectedSkillsSystem::RequestSaveToDB(pQuerySocket, pPacket);
				}
			case S_GET_INFECTED_SKILLS:
				{
					return CInfectedSkillsSystem::RequestLoadInfectedSkills(pQuerySocket, pPacket);
				}
			case S_SET_INFECTED_SKILLS:
				{
					return CInfectedSkillsSystem::RequestSaveInfectedSkills(pQuerySocket, pPacket);
				}
			case S_UPDATE_SUBPLEDGE_USER:
				{
					return CPledgeSystem::RequestUpdateUserSubPledge(pQuerySocket, pPacket);
				}
			case S_SET_USER_EXINFO:
				{
					return CPledgeSystem::UpdateExInfo(pQuerySocket, pPacket);
				}
			case S_INCREASE_MEMBER_SUBPLEDGE:
				{
					return CPledgeSystem::IncreaseMemberSubPledge(pQuerySocket, pPacket);
				}
			case S_SAVE_EX_ITEM_INFO:
				{
					return CItem::RequestSaveExItemInfo(pQuerySocket, pPacket);
				}
			default:
				CLog::Add(CLog::red, L"Unknown cached opcode: 0x%02X", nOpcode);
				break;
		}

		return false;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		CLog::Add(CLog::red, L"Fatal Error At : PacketHandler::Handle(0x%02X)", nOpcode);
		return false;
	}
}
