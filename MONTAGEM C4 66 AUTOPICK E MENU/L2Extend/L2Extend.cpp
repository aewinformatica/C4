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

#include "L2Extend.h"
#include "FeatureRegistry.h"

// Common Clases
#include "CPPFixes.h"
#include "ASMFixes.h"
#include "HEXHooks.h"

// L2Server Classes
#include "CSetItem.h"
#include "CSharedFactory.h"

// Networking
//#include "CPacketRecv.h"
//#include "CPacketSent.h"
//#include "CPacketRecvCDB.h"
//#include "CPacketRecvNpc.h"

// Encryption
//#include "CDataEncryption.h"

// Game Systems
//#include "CCursedWeapons.h"
#include "CGameEvents.h"
//#include "CIconActions.h"
#include "CPlayerTracker.h"
#include "CObjectEx.h"
//#include "CHeroSystem.h"
//#include "CTimerSystem.h"
//#include "CUserTimerSystem.h"
//#include "CPledgeSystem.h"
//#include "CCharactersSystem.h"
//#include "CAntiExploits.h"
//#include "CDuelSystem.h"
//#include "CSetEffectsSystem.h"
#include "AVESystem.h"
//#include "CSetEffectsSystem.h"
//#include "CNPCShopSystem.h"
//#include "CTransform.h"
//#include "CachedListener.h"
//#include "CFortress.h"
//#include "CBuilderCMDSystem.h"
//#include "CDeathPenalty.h"
//#include "CBuffSystem.h"
//#include "CHerbSystem.h"
#include "CStatusUpdate.h"
//#include "CQuestSystem.h"
//#include "CBypassSystem.h"
#include "CAmpedX64.h"
//#include "CLevel85System.h"
//#include "CSoulSystem.h"
//#include "CAugmentationSystem.h"
#include "CDestroyItem.h"
//#include "CChangeWeaponSystem.h"
//#include "COlympiadSystem.h"
#include "CStaticObject.h"
#include "CParserForResidence.h" 

// Sub Systems
//#include "CWSASystem.h"

// Parsers
#include "CParserForSkill.h"
#include "CParserForAcquire.h"
#include "CParserForPCParameter.h"
#include "CParserForSettings.h"
#include "CParserForSkillEnchanting.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			Initialize();
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
    
	return TRUE;
}

void Initialize()
{
	// Checking the Size of the Classes to make sure everything is Correct...
//	CompileTimeSizeCheck(BuffVector, 0x20);
//	CompileTimeSizeCheck(CCreature, 0x14F0);
//	CompileTimeSizeCheck(CIOCriticalSection, 0x30);
//	CompileTimeSizeCheck(CInventory, 0x68);
//	CompileTimeSizeCheck(CSetItem, 0x210);
//	CompileTimeSizeCheck(RWLock, 0x38);

	// Initializing Sub Systems
	//CWSASystem::Initialize();

	// Global Variables
	GlobalVars::Initialize();

	// Initializing the Player Tracker
	CPlayerTracker::Initialize();

	// Initializing Static Object
	CStaticObject::InitializeStaticObject();

	// Initializing Agit //FUNDAMENTAL PRA O NPCSERVER NAO DAR ERRO
	InitializeAgit();

	// Initializing Packet Encryption
	//CDataEncryption::Initialize();

	// Initializing the Characters System
	//CCharactersSystem::Initialize();

	// Initializing Game Events
	CGameEvents::Initialize();

	// Initializing Icon Actions
	//CIconActions::Initialize();

	// Initializing Network Handlers
	//CPacketRecv::Initialize();
	//CPacketSent::Initialize();
	//CPacketRecvNpc::Initialize();

	// Initializing Sub Modules
	CPPFixes::Initialize();
	ASMFixes::Initialize();
	HEXHooks::Initialize();

	// Skills System
	InitializeAVEs();
	InitializeSkillEffects();
	InitializeSkillAcquire();
	InitializeSkillEnchanting();

	// Set Effects System
	//CSetEffectsSystem::Initialize();
	
	// Initializing the Hero System
	//CHeroSystem::Initialize();

	// Initializing The Anti Exploit System
	//CAntiExploits::Initialize();

	// Initializing Shop System
	//CNPCShopSystem::Initialize();

	// Initializing PC Parameter System
	CPCParamDB::Initialize();

	// Initializing Settings System
	CSettingsDB::Initialize();

	// Initializing the Timers
	//CTimerSystem::Initialize();
	//CUserTimerSystem::Initialize();
	
	// Initializing Pledge System
	//CPledgeSystem::Initialize();

	//Shared Factory
	CSharedFactory::Initialize();

	// Builder CMD System
	//CBuilderCMDSystem::LoadCMDs();

	// Abnormal Extension System
	//CBuffSystem::Initialize();

	// Cached Listener
	//CachedListener::Initialize();

	// Quest System - fix for setquest and delquest
	//CQuestSystem::Initialize();

	// HTML Bypass System
	//CBypassSystem::Initialize();

	// Cursed Weapon System
	//CCursedWeapons::Initialize();

	// Level 85 system
	//CLevel85System::Initialize();

	// Soul system
	//CSoulSystem::Initialize();

	// Augmentation system
	//CAugmentationSystem::Initialize();

	// DestroyItem system
	CDestroyItem::Initialize();

	// COlympiad System
	//COlympiadSystem::Initialize();



	// call initProcessAttach() method of self-initializing systems
	FeatureRegistry::initFeatures(FeatureRegistry::stProcessAttach);
}
