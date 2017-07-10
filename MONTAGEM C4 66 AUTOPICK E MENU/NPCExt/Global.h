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

#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

// Standard Includes
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <process.h>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

// Namespaces
using namespace std;

//Shared Factory
#include "CSharedFactory.h"

// Tools
#include "MemoryTools.h"
#include "../L2Extend/Utils.h"

// Classes

#include "CLog.h"
#include "CParserForResidence.h"
#include "CStaticObject.h"
#include "ScriptAccessible.h"
#include "CNPC.h"

#include "NPCFunctions.h"
#include "CNPCSocket.h"
#include "CNPCPacketRecv.h"