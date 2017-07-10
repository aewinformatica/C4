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

#include <list>
#include <windows.h>

class CSocket;
class CCreature;
class CSPacket;

enum StatusUpdate_IDs
{
	STATUSUPDATE_LEVEL = 0x01,
    STATUSUPDATE_EXP = 0x02,
    STATUSUPDATE_STR = 0x03,
    STATUSUPDATE_DEX = 0x04,
    STATUSUPDATE_CON = 0x05,
    STATUSUPDATE_INT = 0x06,
    STATUSUPDATE_WIT = 0x07,
    STATUSUPDATE_MEN = 0x08,
    STATUSUPDATE_CUR_HP = 0x09,
    STATUSUPDATE_MAX_HP = 0x0a,
    STATUSUPDATE_CUR_MP = 0x0b,
    STATUSUPDATE_MAX_MP = 0x0c,
    STATUSUPDATE_SP = 0x0d,
    STATUSUPDATE_CUR_LOAD = 0x0e,
    STATUSUPDATE_MAX_LOAD = 0x0f,
    STATUSUPDATE_P_ATK = 0x11,
    STATUSUPDATE_ATK_SPD = 0x12,
    STATUSUPDATE_P_DEF = 0x13,
    STATUSUPDATE_EVASION = 0x14,
    STATUSUPDATE_ACCURACY = 0x15,
    STATUSUPDATE_CRITICAL = 0x16,
    STATUSUPDATE_M_ATK = 0x17,
    STATUSUPDATE_CAST_SPD = 0x18,
    STATUSUPDATE_M_DEF = 0x19,
    STATUSUPDATE_PVP_FLAG = 0x1a,
    STATUSUPDATE_KARMA = 0x1b,
    STATUSUPDATE_CUR_CP = 0x21,
    STATUSUPDATE_MAX_CP = 0x22
};

class CStatusUpdate
{
	public:

		CStatusUpdate(INT32 ObjectID);
		~CStatusUpdate();

		void ResetFields();
		void AddField(INT32 nFieldID, INT32 nFieldValue);
		void ProcessUpdate(CSocket *pSocket, bool nBroadcastToo);
		void ProcessUpdate(CCreature *pCreature);

	private:
		
		INT32 nObjectID;
		CSPacket *pPacket;
		INT32 nTotalFields;
};