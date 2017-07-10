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

#include "CPlayerTracker.h"
#include "User.h"

CPlayerTracker *PlayerTracker;

void CPlayerTracker::Initialize()
{
	PlayerTracker = new CPlayerTracker();
}

CPlayerTracker::CPlayerTracker()
{
	InitializeCriticalSection(&USERDATA_LOCK);
}

CPlayerTracker::~CPlayerTracker()
{
	DeleteCriticalSection(&USERDATA_LOCK);
}

INT32 nAddPlayer = 0;
void CPlayerTracker::AddPlayer(User *pUser)
{
	L2SERVER_SHARED_GUARD(nAddPlayer);
	TLS_TRACE_BEGIN;

	if ( !pUser->IsValidUser() )
	{
		EnterCriticalSection(&PlayerTracker->USERDATA_LOCK);

		PlayerTracker->m_PlayerMapByString[pUser->SD->wszName] = pUser->SD->pObjectEx;
		PlayerTracker->m_PlayerMapByDBID[pUser->SD->nCharId] = pUser->SD->pObjectEx;
		PlayerTracker->m_PlayerMapBySID[pUser->SD->nObjectID] = pUser->SD->pObjectEx;

		LeaveCriticalSection(&PlayerTracker->USERDATA_LOCK);
	}
	TLS_TRACE_END;
}

INT32 nDelPlayer = 0;
void CPlayerTracker::DelPlayer(User *pUser)
{
	L2SERVER_SHARED_GUARD(nDelPlayer);
	TLS_TRACE_BEGIN;

	if ( !pUser->IsValidUser() ) { goto SkipProcess; }

	EnterCriticalSection(&PlayerTracker->USERDATA_LOCK);

	PlayerTracker->m_PlayerMapByString.erase(pUser->SD->wszName);
	PlayerTracker->m_PlayerMapByDBID.erase(pUser->SD->nCharId);
	PlayerTracker->m_PlayerMapBySID.erase(pUser->SD->nObjectID);

	LeaveCriticalSection(&PlayerTracker->USERDATA_LOCK);

	SkipProcess:
	TLS_TRACE_END;
}

INT32 nGetUserByName = 0;
CObjectEx *CPlayerTracker::GetUserByName(wstring sPlayerName)
{
	L2SERVER_SHARED_GUARD(nGetUserByName);
	TLS_TRACE_BEGIN;

	CObjectEx *pObjectEx = NULL;

	EnterCriticalSection(&PlayerTracker->USERDATA_LOCK);

    map<wstring, CObjectEx *, __widestring_lower_case_comparator>::iterator iter = PlayerTracker->m_PlayerMapByString.find(sPlayerName);

	if( iter != PlayerTracker->m_PlayerMapByString.end() ) 
		pObjectEx = (iter->second); 

	LeaveCriticalSection(&PlayerTracker->USERDATA_LOCK);

	TLS_TRACE_END;
	return pObjectEx;
}

INT32 nGetUserByDBID = 0;
CObjectEx *CPlayerTracker::GetUserByDBID(int nDBID)
{
	L2SERVER_SHARED_GUARD(nGetUserByDBID);
	TLS_TRACE_BEGIN;

	CObjectEx *pObjectEx = NULL;

	EnterCriticalSection(&PlayerTracker->USERDATA_LOCK);

    map<int, CObjectEx *>::iterator iter = PlayerTracker->m_PlayerMapByDBID.find(nDBID);

	if( iter != PlayerTracker->m_PlayerMapByDBID.end() ) 
		pObjectEx = (iter->second); 

	LeaveCriticalSection(&PlayerTracker->USERDATA_LOCK);

	TLS_TRACE_END;
	return pObjectEx;
}

INT32 nGetUserBySID = 0;
CObjectEx *CPlayerTracker::GetUserBySID(int nSID)
{
	L2SERVER_SHARED_GUARD(nGetUserBySID);
	TLS_TRACE_BEGIN;

	CObjectEx *pObjectEx = NULL;

	EnterCriticalSection(&PlayerTracker->USERDATA_LOCK);

    map<int, CObjectEx *>::iterator iter = PlayerTracker->m_PlayerMapBySID.find(nSID);

	if( iter != PlayerTracker->m_PlayerMapBySID.end() ) 
		pObjectEx = (iter->second); 

	LeaveCriticalSection(&PlayerTracker->USERDATA_LOCK);

	TLS_TRACE_END;
	return pObjectEx;
}