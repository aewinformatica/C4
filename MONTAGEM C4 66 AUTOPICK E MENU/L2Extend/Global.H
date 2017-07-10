#pragma warning(disable: 4018)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#pragma warning(disable: 4800)
#pragma warning(disable: 4065)
#pragma comment(lib, "Ws2_32.lib")
#pragma once

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

#define _AMD64_

// Uncomment to enable ct2.2 login. Be aware that ct2.2 is not supported, and will not be supported for some time!
//#define _CT2_2_

#ifdef _CT2_2_
	#define CHRONICLE "CT2.2"
#else
	#define CHRONICLE "CT1.5"
#endif
#define BUILDVERSION "1.01"
#define BUILDDATE "20081214"

#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

// Standard Includes
#include <cmath>
#include <cstdarg>
#include <ctime>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <windows.h>

// Namespaces
using namespace std;

// L2Server Classes
class MemoryObject;
class CIOObject;
class CObject;
// ----------------
class CCreature;
class CInventory;
class CItem;
class CNPC;
class CParty;
class CPet;
class CPledge;
class CSetItem;
class CSharedData;
class CSharedItemData;
class CSkillInfo;
class CSocket;
class User;

#include "Structures.h"
#include "Enumerations.h"

// Tools
#include "CLog.h"
#include "L2ServerFunctions.h"
#include "MemoryTools.h"
#include "Utils.h"
#include "FeatureRegistry.h"

struct L2ServerObject
{
	void* operator new(size_t nSize)
	{
		return L2ServerFunctions::operator_new(nSize);
	}

	void operator delete(void* pObject)
	{
		L2ServerFunctions::operator_delete(pObject);
	}
};

// Global Variables Class

class SubSystems
{
	public:
		
		bool bDeathPenalty;
		INT32 nDeathPenaltySkillID;
		bool bBuffSystem;
		INT32 nBuffSlotSkillID;
		bool bEnableKamael;
		INT32 nAutoPickUp; //WAGNER 2014
};

class GeneralVars
{
	public:
		INT32 nDeadlock;
		bool bJoinLeaveMod;
		bool Penaltyfix;
		string ProtocolVersion;
};

class GlobalVars
{
	public:

		// Static Methods
		static void Initialize();
		static void InitVars();
		static GlobalVars *GVs();

		// Variables
		GeneralVars *pGeneral;
		SubSystems *pSubSystems;
};

static const char *PenaltyNames[16] = 
{
	"PLEDGE_WAR_TIMEOUT",
	"PLEDGE_OUST_PENALTY_TIMEOUT",
	"PLEDGE_WITHDRAW_PENALTY_TIMEOUT",
	"PLEDGE_OUSTED_PENALTY_TIMEOUT",
	"PLEDGE_RECHALLENGE_PENALTY_TIMEOUT",
	"PLEDGE_RECHALLENGE_DESPITE_REJECTION_PENALTY_TIMEOUT",
	"PLEDGE_DISMISS_TIMEOUT",
	"PLEDGE_DISMISS_PENALTY_TIMEOUT",
	"CASTLE_ANNOUNCE_TIME",
	"CASTLE_STANDBY_TIME",
	"ALLIANCE_OUST_PENALTY_TIMEOUT",
	"ALLIANCE_WITHDRAW_PENALTY_TIMEOUT",
	"ALLIANCE_OUSTED_PENALTY_TIMEOUT",
	"ALLIANCE_DISMISS_PENALTY_TIMEOUT",
	"ALLIANCE_RECHALLENGE_PENALTY_TIMEOUT",
	"ALLIANCE_RECHALLENGE_DESPITE_REJECTION_PENALTY_TIMEOUT"
};

static const DWORD penaltyTable[16] =
{
	0xBF6F08, // PLEDGE_WAR_TIMEOUT (1)
	0xBF6F0C, // PLEDGE_OUST_PENALTY_TIMEOUT (2)
	0xBF6F10, // PLEDGE_WITHDRAW_PENALTY_TIMEOUT (3)
	0xBF6F14, // PLEDGE_OUSTED_PENALTY_TIMEOUT (4)
	0xBF6F18, // PLEDGE_RECHALLENGE_PENALTY_TIMEOUT (5)
	0xBF6F1C, // PLEDGE_RECHALLENGE_DESPITE_REJECTION_PENALTY_TIMEOUT (6)
	0xBF6F20, // PLEDGE_DISMISS_TIMEOUT (7)
	0xBF6F24, // PLEDGE_DISMISS_PENALTY_TIMEOUT (8)
	0xBF6F44, // CASTLE_ANNOUNCE_TIME (9)
	0xBF6F48, // CASTLE_STANDBY_TIME (10)
	0xBF6F2C, // ALLIANCE_OUST_PENALTY_TIMEOUT (12)
	0xBF6F30, // ALLIANCE_WITHDRAW_PENALTY_TIMEOUT (13)
	0xBF6F34, // ALLIANCE_OUSTED_PENALTY_TIMEOUT (14)
	0xBF6F38, // ALLIANCE_DISMISS_PENALTY_TIMEOUT (15)
	0xBF6F3C, // ALLIANCE_RECHALLENGE_PENALTY_TIMEOUT (16)
	0xBF6F40  // ALLIANCE_RECHALLENGE_DESPITE_REJECTION_PENALTY_TIMEOUT (17)
};