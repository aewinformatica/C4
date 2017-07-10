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

#include "CCursedWeapons.h"
#include "CObjectEx.h"
#include "CPet.h"
#include "CSocket.h"

CRITICAL_SECTION CWSLock;
map<int, CCursedWeapon *> m_CursedWeapons;
CCursedWeapons *CWS;

void CCursedWeapons::Initialize()
{
	// Initializing the Critical Section
	InitializeCriticalSection(&CWSLock);

	// Initializing the Global Object
	CWS = new CCursedWeapons();

	// Loading Weapons
	LoadWeapons();
}

void CCursedWeapons::LoadWeapons()
{
	m_CursedWeapons[8190] = new CCursedWeapon(8190, L"Demonic Sword Zariche", 120, 60);
	m_CursedWeapons[8689] = new CCursedWeapon(8689, L"Akamanah Sword", 120, 60);
}

void CCursedWeapons::SaveWeapons()
{
}

INT32 nCCursedWeapons_DoRedSky = 0;
void CCursedWeapons::DoRedSky(INT32 nDuration, User *pUser)
{
	L2SERVER_SHARED_GUARD(nCCursedWeapons_DoRedSky);
	TLS_TRACE_BEGIN;

	if ( nDuration > 0 )
	{
		// Sending the RedSky to the Entire Server !
		CSPacket Packet; Packet.set(64);
		Packet << (BYTE)0xFE << (INT16)0x40 << nDuration;
		L2ServerFunctions::BroadcastToAllUser(&Packet);
		CWS->nRedSkyDuration = time(NULL)+nDuration;
	}
	else
	{
		// Sending the RedSky (Time Left) to a Specific User (Generally On Login...)
		if ( CWS->nRedSkyDuration > 0 )
		{
			if ( pUser->IsValidUser() && (CWS->nRedSkyDuration-time(NULL)) > 0 )
			{
				CSPacket Packet; Packet.set(64);
				Packet << (BYTE)0xFE << (INT16)0x40 << (CWS->nRedSkyDuration-time(NULL));
				pUser->Socket->Send(&Packet);
			}
		}
	}

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_DoEarthQuake = 0;
void CCursedWeapons::DoEarthQuake(INT32 nDuration, User *pUser)
{
	L2SERVER_SHARED_GUARD(nCCursedWeapons_DoEarthQuake);
	TLS_TRACE_BEGIN;

	if ( nDuration > 0 )	
	{
		// Sending The EarthQuake to the Entire Server
		CSPacket Packet; Packet.set(64);
		Packet << (BYTE)0xC4 << (INT32)0x00 << (INT32)0x00 << (INT32)0x00 << (INT32)100 << nDuration << (INT32)0x00;
		L2ServerFunctions::BroadcastToAllUser(&Packet);
		CWS->nEarthQuakeDuration = time(NULL)+nDuration;
	}
	else
	{
		// Sending the EarthQuake (Time Left) to a Specific User (Generally On Login...)
		if ( CWS->nEarthQuakeDuration > 0 )
		{
			if ( pUser->IsValidUser() && (CWS->nEarthQuakeDuration-time(NULL)) > 0 )
			{
				CSPacket Packet; Packet.set(64);
				Packet << (BYTE)0xC4 << (INT32)0x00 << (INT32)0x00 << (INT32)0x00 << (INT32)100 << (CWS->nEarthQuakeDuration-time(NULL)) << (INT32)0x00;
				pUser->Socket->Send(&Packet);
			}
		}
	}

	TLS_TRACE_END;
}

bool CCursedWeapons::IsWeaponOwner(User *pUser) { if ( pUser->IsValidUser() ) { return pUser->SD->pObjectEx->pCWI->IsOwner(); } else { return false; } }

INT32 nCCursedWeapons_OnLogin = 0;
void CCursedWeapons::OnLogin(User *pUser)
{
	if ( !pUser->IsValidUser() ) { return; }

	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnLogin);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_OnLogout = 0;
void CCursedWeapons::OnLogout(User *pUser)
{
	if ( !pUser->IsValidUser() ) { return; }

	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnLogout);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_OnCreatureDie = 0;
void CCursedWeapons::OnCreatureDie(CCreature *pAttacker, CCreature *pVictim)
{
	if ( !pAttacker->IsValidCreature() || !pVictim->IsValidUser() ) { return; }

	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnCreatureDie);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_OnUserDie = 0;
void CCursedWeapons::OnUserDie(CCreature *pAttacker, User *pVictim)
{
	if ( !pAttacker->IsValidCreature() || !pVictim->IsValidUser() ) { return; }

	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnUserDie);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_OnUserItemPickUp = 0;
void CCursedWeapons::OnUserItemPickUp(User *pUser, CItem *pItem)
{
	if ( !pUser->IsValidUser() || !pItem->IsValidItem() ) { return; }

	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnUserItemPickUp);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_OnPetItemPickUp = 0;
void CCursedWeapons::OnPetItemPickUp(CPet *pPet, CItem *pItem)
{
	if ( !pPet->IsValidPet() || !pItem->IsValidItem() ) { return; }

	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnPetItemPickUp);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

INT32 nCCursedWeapons_OnTimerTick = 0;
void CCursedWeapons::OnTimerTick()
{
	L2SERVER_SHARED_GUARD(nCCursedWeapons_OnTimerTick);
	TLS_TRACE_BEGIN;

	TLS_TRACE_END;
}

bool CCursedWeapons::OnIsEnemy(CCreature *pVictim, CCreature *pAttacker)
{
	return false;
}

INT32 nCCursedWeapons_RequestCursedWeaponLocation = 0;
bool CCursedWeapons::RequestCursedWeaponLocation(CSocket *pSocket, CSPacket *pPacket)
{
	L2SERVER_SHARED_GUARD(nCCursedWeapons_RequestCursedWeaponLocation);
	
	TLS_TRACE_BEGIN;

	EnterCriticalSection(&CWSLock);

	// CLog::Add(CLog::blue, "Requesting Weapon Loc...");

	CSPacket Packet;

	Packet.set(256);

	Packet << (BYTE)0xFE << (INT16)0x46;
	
	Packet << (INT32)m_CursedWeapons.size();
	
	for ( map<int, CCursedWeapon *>::iterator it = m_CursedWeapons.begin() ; it != m_CursedWeapons.end() ; it++ )
	{
		CCursedWeapon *pCursedWeapon = (*it).second;

		if ( pCursedWeapon )
		{
			Packet << pCursedWeapon->nWeaponID << pCursedWeapon->HasOwner();
			Packet << pCursedWeapon->X << pCursedWeapon->Y << pCursedWeapon->Z;
		}
	}

	pSocket->Send(&Packet);

	LeaveCriticalSection(&CWSLock);

	TLS_TRACE_END;

    return false;
}

INT32 nCCursedWeapons_RequestCursedWeaponsList = 0;
bool CCursedWeapons::RequestCursedWeaponsList(CSocket *pSocket, CSPacket *pPacket)
{
	L2SERVER_SHARED_GUARD(nCCursedWeapons_RequestCursedWeaponsList);
	
	TLS_TRACE_BEGIN;

	EnterCriticalSection(&CWSLock);

	CSPacket Packet;

	Packet.set(256);

	// CLog::Add(CLog::blue, "Requesting Weapon List...");

	Packet << (BYTE)0xFE << (INT16)0x45;
	
	Packet << (INT32)m_CursedWeapons.size();
	
	for ( map<int, CCursedWeapon *>::iterator it = m_CursedWeapons.begin() ; it != m_CursedWeapons.end() ; it++ )
	{
		CCursedWeapon *pCursedWeapon = (*it).second;

		if ( pCursedWeapon )
		{
			Packet << pCursedWeapon->nWeaponID;
		}
	}

	pSocket->Send(&Packet);

	LeaveCriticalSection(&CWSLock);

	TLS_TRACE_END;

    return false;
}
