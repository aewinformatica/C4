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

#include "CSkillEffect_i_summon_friend.h"
#include "CObjectEx.h"
#include "CSocket.h"

INT32 nCSkillEffect_i_summon_friendInstant = 0;
void CSkillEffect_i_summon_friend::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(nCSkillEffect_i_summon_friendInstant);
	TLS_TRACE_BEGIN;

	User *pUser = (User*)pSkillUser;
	User *pMember = NULL;
	if(pUser->IsValidUser())
		pMember = (User*)L2ServerFunctions::GetObject(pUser->SD->nTargetObjId);
	if(pMember->IsValidUser()) //Checks below can't be done in OP_COND becouse user can do that actions during spell casting
	{
		CParty *pParty = pUser->GetParty();
		if(pParty && pParty == pMember->GetParty())
		{
			if(pMember->SD->nIsAlive)
			{
				if(!pUser->SD->nInBattleField)
				{
					if(!pMember->InCombat())
					{
						if(!pMember->IsNowTrade() && !pMember->SD->nStoreMode)
						{
							CItem *pItem = pMember->GetInventory()->GetFirstItemByID(8615);
							if(pItem)
							{
								CSPacket packet;
								packet.set(1024);
								packet << (BYTE)0xED << (INT32)1842 << (INT32)2 << (INT32)0;
								packet << (wstring)pUser->SD->wszName << (INT32)7;
								double x, y, z;
								int nObjectID;
								pUser->Lock(__FILEW__, __LINE__);
								x = pUser->SD->x;
								y = pUser->SD->y;
								z = pUser->SD->z;
								nObjectID = pUser->nObjectID;
								pUser->Unlock();
								packet << (INT32)x << (INT32)y << (INT32)z;
								packet << (INT32)9000 << (INT32)nObjectID;
								pMember->Lock(__FILEW__, __LINE__);
								pMember->SD->pObjectEx->pSummonInfo->nSummonX = (INT32)x;
								pMember->SD->pObjectEx->pSummonInfo->nSummonY = (INT32)y;
								pMember->SD->pObjectEx->pSummonInfo->nSummonZ = (INT32)z;
								pMember->SD->pObjectEx->pSummonInfo->nSummonerSID = nObjectID;
								pMember->Unlock();
								pMember->Socket->Send("b", packet.size(), packet.buffer(false));
							}else
								pUser->Socket->Send("cdddd", 0x64, 1897, 1, 3, 8615);
						}else
							pUser->Socket->Send("cdddS", 0x64, 1898, 1, 0, pMember->SD->wszName);
					}else
						pUser->Socket->Send("cdddS", 0x64, 1843, 1, 0, pMember->SD->wszName);
				}else
					pUser->Socket->Send("cdddS", 0x64, 1380, 1, 0, pMember->SD->wszName);
			}else
				pUser->Socket->Send("cdddd", 0x64, 1844, 1, 0, pMember->SD->wszName);
		}else
			pUser->Socket->SendSystemMessage(109);
	}
	TLS_TRACE_END;
}