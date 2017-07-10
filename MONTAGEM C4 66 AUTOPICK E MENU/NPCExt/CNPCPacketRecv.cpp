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

#include "CNPCPacketRecv.h"
#include "ScriptAccessible.h"

extern BYTE g_ServerToNPCServerOpcodes[210];

// PACKET HANDLER TABLE
typedef bool (*NPCPACKETHANDLER)(CSocket*, char*, int, int);
static NPCPACKETHANDLER NPCReceivedPackets[256];

void CNPCPacketRecv::Initialize()
{
	// Received Packets Handler
	WriteInstruction(0x5DDFAB, (INT32)NPCReadPackets_Hook, 1, 0xE9);

	// Mapping Packets To The Function Pointer Array
	memset(NPCReceivedPackets, 0, sizeof(NPCReceivedPackets));

	NPCReceivedPackets[0x58] = CreateAcademy;
}

INT32 nNPCReceiveData = 0;
bool CNPCPacketRecv::NPCReceiveData(CSocket *pSocket, CHAR *pPacket, INT16 nPacketLen, BYTE nPacketID)
{
	NPC_SHARED_GUARD(nNPCReceiveData);
	TLS_TRACE_BEGIN;

	bool bPacketResult = false;

	if(nPacketID > 0x57)
	{
		bPacketResult = true;
		NPCReceivedPackets[nPacketID](pSocket, pPacket, nPacketID, nPacketLen);
	}

	if(nPacketID == 0x58)
		bPacketResult = true;	

	TLS_TRACE_END( bPacketResult );
}

bool NPCReceiveData_Wrapper(CSocket *pSocket, CHAR *pPacket, INT16 nPacketLen, BYTE nPacketID)
{
	// Wrapping the Call to the Original Class
	return CNPCPacketRecv::NPCReceiveData(pSocket, pPacket, nPacketLen, nPacketID);
}

bool DefaultPacket(CSocket *pSocket, char *pPacket, int PacketID, int Lenght)
{
	// Allowing Any Packets

	return true;
}
