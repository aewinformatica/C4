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

#include "CStatusUpdate.h"
#include "CSocket.h"

CStatusUpdate::CStatusUpdate(INT32 ObjectID)
{
	nObjectID = ObjectID;
	nTotalFields = 0;

	pPacket = new CSPacket();
	
	pPacket->set(64);

	pPacket->Write((BYTE)0x0E);
	pPacket->Write(nObjectID);
	pPacket->Write(nTotalFields);
}

CStatusUpdate::~CStatusUpdate()
{
	delete pPacket;
}

void CStatusUpdate::ProcessUpdate(CSocket *pSocket, bool nBroadcastToo)
{
	if ( nTotalFields > 0 )
	{
		// Rewritting the Total of Fields We Are Updating
		pPacket->RewriteAt(nTotalFields, 0x05);
	
		// Sending the Packet to Ourselves
		pSocket->Send(pPacket);
	
		if ( nBroadcastToo )
		{
			// Checking the Current Player Position And Send To Everyone Around It Except Self
			FVector vPos = { pSocket->user->SD->x, pSocket->user->SD->y, pSocket->user->SD->z };
			L2ServerFunctions::BroadcastToNeighborExceptSelf(nObjectID, vPos, pPacket);
		}
	}
}

void CStatusUpdate::ProcessUpdate(CCreature *pCreature)
{
	if ( nTotalFields > 0 )
	{
		// Rewritting the Total of Fields We Are Updating
		pPacket->RewriteAt(nTotalFields, 0x05);

		// Checking the Current Creature Position And Send To Everyone Around It Except Self
		FVector vPos = { pCreature->SD->x, pCreature->SD->y, pCreature->SD->z };
		L2ServerFunctions::BroadcastToNeighborExceptSelf(nObjectID, vPos, pPacket);
	}
}

void CStatusUpdate::AddField(INT32 FieldID, INT32 FieldValue)
{
	pPacket->Write(FieldID);
	pPacket->Write(FieldValue);
	nTotalFields++;
}

void CStatusUpdate::ResetFields()
{
	nTotalFields = 0;

	pPacket->clear();

	pPacket->Write((BYTE)0x0E);
	pPacket->Write(nObjectID);
	pPacket->Write(nTotalFields);
}

