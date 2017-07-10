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

#include "CNPC.h"

INT32 CNPCSetAugment = 0;
CNPCSocket *pSocket = (CNPCSocket*)0x328BBB0;
void CNPC::SetAugment(CNPC *pNPC, CSharedData *talker)
{
	NPC_SHARED_GUARD(CNPCSetAugment);
	TLS_TRACE_BEGIN;

	pSocket->Send("chd", 0x7D, 0x01, talker->nObjectID);
	
	TLS_TRACE_END_NO_RETURN;
};

INT32 CNPCDeleteAugment = 0;
void CNPC::DeleteAugment(CNPC *pNPC, CSharedData *talker)
{
	NPC_SHARED_GUARD(CNPCDeleteAugment);
	TLS_TRACE_BEGIN;

	pSocket->Send("chd", 0x7D, 0x02, talker->nObjectID);
	
	TLS_TRACE_END_NO_RETURN;
};

INT32 CNPCShowPledgeSkillList = 0;
void CNPC::ShowPledgeSkillList(CNPC *pNPC, CSharedData *talker)
{
	NPC_SHARED_GUARD(CNPCShowPledgeSkillList);
	TLS_TRACE_BEGIN;

	if(pNPC && talker)
	{
		pSocket->Send("chdd", 0x7D, 0x03, pNPC->pSD->nObjectID, talker->nObjectID);
	}
	else
	{
		CLog::Add(CLog::red, L"[%s][%d] invalid npc or talker", __FUNCTIONW__, __LINE__);
	}
	
	TLS_TRACE_END_NO_RETURN;
};

CNPC* CNPC::Find(unsigned int id)
{
	typedef CNPC* (__fastcall *__f)(DWORD id);
	__f _f = (__f) 0x004CAA50;
	return _f(id);
}

int CNPC::HandleEvent(NPCEvent* pEvent)
{
	typedef int (__fastcall *__f)(CNPC*, NPCEvent* pEvent);
	__f _f = (__f) 0x004DD470;
	return _f(this, pEvent);
}
