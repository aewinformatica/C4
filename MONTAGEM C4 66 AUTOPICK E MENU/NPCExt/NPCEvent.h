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
#pragma once

#include "Global.h"
#include "MemoryObject.h"
#include "CNPC.h"

class NPCEvent;
class CNPC;
class CSharedData;

#pragma pack( push, 1 )

class NPCEvent : public MemoryObject
{
	public:

		/* 0x018 */  VOID *getparam;
		/* 0x020 */  int nEventID;
		/* 0x024 */  int dw0024;
		/* 0x028 */  CSharedData* pTalker;
		/* 0x030 */  int dw002C[29];
		/* 0x0A4 */  int nReply;
		/* 0x0A8 */  int dw00A8[116];
		/* 0x278 */  VOID* pScriptAccessible;
		/* 0x280 */  int dw0280;
		/* 0x284 */  int dw0284;
		/* 0x288 */  VOID *pN;
		/* 0x290 */  int dw0290[12];
		/* 0x2c0 */  CNPC *pNPC;
		/* 0x2c8 */  int dw02c8;
		/* 0x2cc */  int dw02cc;
		/* 0x2d0 */

		NPCEvent(){CompileTimeSizeCheck(NPCEvent, 0x2D0);};
		virtual	~NPCEvent(){};
};

#pragma pack( pop )
