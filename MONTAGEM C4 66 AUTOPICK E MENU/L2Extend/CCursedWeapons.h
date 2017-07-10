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

#include "Global.H"

class CursedWeaponInfo
{
	public:

		/* Constructor & Destructor */
		CursedWeaponInfo()
		{
			nWeaponID = 0;
			bIsVictim = false; bIsKiller = false;
		}

		/* Functions */
		bool IsOwner() { if ( nWeaponID != 0 ) { return true; } else { return false; } }

		/* Variables */
		INT32 nWeaponID;
		bool  bIsVictim;
		bool  bIsKiller;
};

class CCursedWeapon
{
	public:

		/* Constructor & Destructor */
		CCursedWeapon(INT32 WeaponID, wstring ItemName, INT32 MaxUseTime, INT32 MaxDropTime)
		{ 
			// Initializing Variables
			
			nWeaponID    = WeaponID;
			wItemName    = ItemName;
			nMaxUseTime  = MaxUseTime;
			nMaxDropTime = MaxDropTime;

			/* ---------------------------------------------------------------------- */

			nOwnerDBID = 0; nWeaponLV = 0; nWeaponPKs = 0; nOwnerSID = 0;
			X = 0; Y = 0; Z = 0;
		}

		~CCursedWeapon() 
		{ 
		}

		/* Functions */
		VOID  SetOwner(INT32 DBID, INT32 SID) { this->nOwnerDBID = DBID; this->nOwnerSID = SID; }
		INT32 HasOwner() { if ( this->nOwnerDBID != 0 && this->nOwnerSID != 0 ) { return 1; } else { return 0; } }
		bool  WasDropped() { if ( this->nDropTime != 0 ) { return true; } else { return false; } }
		INT32 TimeLeft() { INT32 nTimeLeft = this->nExpireTime-time(NULL); if ( nTimeLeft >= 0 ) { return nTimeLeft; } else { return 0; } }

		/* Variables */

		INT32 nOwnerDBID;
		INT32 nOwnerSID;
		INT32 nDropTime;
		INT32 nExpireTime;

		INT32 nMaxUseTime;
		INT32 nMaxDropTime;

		INT32 nWeaponID; INT32 nWeaponLV; INT32 nWeaponPKs;
		wstring wItemName;
		
		INT32 X; INT32 Y; INT32 Z;
};

class CCursedWeapons
{
	// STATIC DATA
	public:

		// Functions
		static void Initialize();
		static void LoadWeapons();
		static void SaveWeapons();
		static bool IsWeaponOwner(User *pUser);
		static void OnLogin(User *pUser);
		static void OnLogout(User *pUser);
		static void OnCreatureDie(CCreature *pAttacker, CCreature *pVictim);
		static void OnUserDie(CCreature *pAttacker, User *pVictim);
		static void OnUserItemPickUp(User *pUser, CItem *pItem);
		static void OnPetItemPickUp(CPet *pPet, CItem *pItem);
		static void OnTimerTick();
		static bool OnIsEnemy(CCreature *pVictim, CCreature *pAttacker);

		// Server Effects
		static void DoRedSky(INT32 nDuration, User *pUser);
		static void DoEarthQuake(INT32 nDuration, User *pUser);

		// Handled Packets
		static bool RequestCursedWeaponsList(CSocket *pSocket, CSPacket *pPacket);			// 0x2A
		static bool RequestCursedWeaponLocation(CSocket *pSocket, CSPacket *pPacket);		// 0x2B

	// NON STATIC DATA
	public:

		// Constructor & Destructor
		CCursedWeapons()
		{
			nRedSkyDuration = 0;	nEarthQuakeDuration = 0;
		}

		// Variables
		int nRedSkyDuration;
		int nEarthQuakeDuration;
};