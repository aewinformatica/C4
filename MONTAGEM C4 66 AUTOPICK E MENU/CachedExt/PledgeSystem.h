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

#ifndef _PLEDGESYSTEM_
#define _PLEDGESYSTEM_

#include "Global.H"
#include "process.h"
#include "CQuerySocket.h"

struct SubUnit
{
	int nPledgeType;
	wchar_t name[25];
	wchar_t leaderName[25];
	int leaderId;
};


class CPledgeExt
{
public:
	/* 0000 */ int n1stRoyalGuard;
	/* 0004 */ int n2stRoyalGuard;
	/* 0008 */ int n1stOrderofKnights;
	/* 000C */ int n2stOrderofKnights;
	/* 0010 */ int n3stOrderofKnights;
	/* 0014 */ int n4stOrderofKnights;
};

class CPledgeSystem
{

public:
	static void Initialize();
	static bool __cdecl RequestSavePledgePower(CQuerySocket *pQuerySocket, unsigned char *packet);
	static bool __cdecl RequestCreateExtPledgeInfo(CQuerySocket *pQuerySocket, unsigned char *packet);
	static bool __cdecl RequestSetPledgeReputation(CQuerySocket *pQuerySocket, unsigned char *packet);
	static bool __cdecl RequestAcquirePledgeSkill(CQuerySocket *pQuerySocket, unsigned char *packet);
	static bool __cdecl RequestReorganizeMember(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl RequestCreateSubPledgeOrSetCaptain(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl RequestDeleteSubPledge(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl RequestSetSponsor(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl RequestSetApprentice(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl RequestUpdateUserSubPledge(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl UpdateExInfo(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl IncreaseMemberSubPledge(CQuerySocket *pSocket, unsigned char *packet);

	static void __cdecl SendReplyToLoadPledge(CPledge *pPledge, CSocket *pSocket);
};

#endif