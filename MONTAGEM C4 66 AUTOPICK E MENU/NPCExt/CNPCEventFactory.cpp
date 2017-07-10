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

#include "CNPCEventFactory.h"

#define IMAGEBASE 0x400000

VOID CNPCEventFactory::Initialize()
{
	// Initializing the Sub System...
	CScriptAccessible::ExtendDataArrays();
};

VOID CNPCEventFactory::ExtendDataArrays()
{
};

INT32 CNPCEventFactoryCreateCreateAcademyEvent = 0;
NPCEvent* CNPCEventFactory::CreateCreateAcademyEvent(CNPC* pNPC, CSharedData* spTalker, int nReply)
{
	NPC_SHARED_GUARD(CNPCEventFactoryCreateCreateAcademyEvent);
	TLS_TRACE_BEGIN;

	typedef NPCEvent* (__fastcall *__fn)(DWORD);
	__fn _fn = (__fn) 0x0042A930;
	NPCEvent* pNPCEvent = _fn(0x2d0);

	typedef MemoryObject* (__fastcall *__fn1)(NPCEvent*);
	__fn1 _fn1 = (__fn1) 0x00590B80;
	pNPCEvent = (NPCEvent*)_fn1(pNPCEvent);

	pNPCEvent->dw0280 = 0;
	pNPCEvent->dw0024 = 0;
	pNPCEvent->pScriptAccessible = (VOID*)0x0077E200;
	LPVOID *org_vmt = (LPVOID*)0x0067E238; // real VMT address
    LPVOID *my_vmt = *(LPVOID**)pNPCEvent;
	memcpy(&*((LPVOID**)pNPCEvent), &org_vmt, 8);
	pNPCEvent->getparam = (VOID*)0x0067E2D8;
	pNPCEvent->pN = 0;
	pNPCEvent->dw02c8 = 0;

	pNPCEvent->nEventID = 124;
	pNPCEvent->pNPC = pNPC;
	pNPCEvent->pTalker = spTalker;
	pNPCEvent->nReply = nReply;

	TLS_TRACE_END(pNPCEvent);
}
