#pragma once
#pragma warning(disable: 4244)
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
#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

// Standard Includes
#include "CSocket.h"
#include <windows.h>
#include <map>

// Tools
#include "MemoryTools.h"
#include "Utils.h"

//Classes
#include "CashedFunctions.h"
#include "CLog.h"
#include "CPledge.h"
#include "DBConn.h"
#include "PacketHandler.h"
#include "CInfectedSkillsSystem.h"
#include "CUser.h"
#include "CItem.h"
#include "CObjectSP.h"
#include "CUserDB.h"
#include "CWareHouse.h"
#include "PledgeSystem.h"
