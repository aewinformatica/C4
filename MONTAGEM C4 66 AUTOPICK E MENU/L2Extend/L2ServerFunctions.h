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

#include <windows.h>
#include "Global.H"
#include "CSPacket.h"
#include "CObjectEx.h"

// n00bish way to hide these functions from intelisense. we use defines so we dont want to see them anyway..
namespace Hidden
{
	extern "C"
	{
		void tls_trace_begin(WCHAR* wszFuncName);
		void tls_trace_end();
		INT32 l2server_shared_guard(WCHAR* wszFuncName);
	};
};

#ifndef USE_SHARED_GUARD
#define USE_SHARED_GUARD 1
#endif

#ifndef USE_SHARED_GUARD_STATIC
#define USE_SHARED_GUARD_STATIC 1
#endif

#if USE_SHARED_GUARD
#	define TLS_TRACE_BEGIN Hidden::tls_trace_begin(__FUNCTIONW__)
#	define TLS_TRACE_END2(return_type) {Hidden::tls_trace_end(); return return_type;}
#	define TLS_TRACE_END Hidden::tls_trace_end()
#	define TLS_TRACE_END_NO_RETURN {Hidden::tls_trace_end();}
#	if USE_SHARED_GUARD_STATIC
#		define L2SERVER_SHARED_GUARD(shared_variable) L2SERVER_SHARED_GUARD0
#	else
#		define L2SERVER_SHARED_GUARD(shared_variable) L2SERVER_SHARED_GUARD1(shared_variable)
#	endif
#else
#	define TLS_TRACE_BEGIN
#	define TLS_TRACE_END
#	define L2SERVER_SHARED_GUARD(shared_variable)
#endif

#define L2SERVER_SHARED_GUARD1(shared_variable) \
	if(shared_variable != 1) { shared_variable |= 1; Hidden::l2server_shared_guard(__FUNCTIONW__); }

#define L2SERVER_SHARED_GUARD0                                          \
{                                                                       \
	typedef INT32 (*FSharedGuard)(const WCHAR* wszFuncName);            \
	static INT32 funcIndex = FSharedGuard(0x401500)(__FUNCTIONW__);     \
};

class L2ServerFunctions
{
	public:

		//static void *GetObjectByName(const wchar_t *cObjectName)
		//{
		//	typedef void *(__fastcall *_GET_OBJECT_BY_NAME) (VOID *, INT64*, const wchar_t *);
		//	_GET_OBJECT_BY_NAME xGetObjectByName = (_GET_OBJECT_BY_NAME)0x00479E20L;
		//	INT64 pUsrAddr[1];
		//	xGetObjectByName((VOID *)0x0E6C70A0, pUsrAddr, cObjectName);
		//	User *pUser = (User *)pUsrAddr[0];
		//	return pUser;
		//}

		//static void *GetObjectDBByName(PWCHAR wcObjectName)
		//{
		//	typedef void *(__fastcall *_GET_OBJECT_BY_NAME) (VOID *ClassObjectDB, PWCHAR pszName);
		//	_GET_OBJECT_BY_NAME xGetObjectByName = (_GET_OBJECT_BY_NAME)0x006FBAC0L;
		//	return xGetObjectByName((VOID *)0x0BC5D810, wcObjectName);
		//}

		static void *GetObject(INT32 nObjectID)
		{
			typedef void *(__fastcall *_GET_OBJECT) (INT32 id);
			_GET_OBJECT xGetObject = (_GET_OBJECT)0x006F4920L;
			return xGetObject(nObjectID);
		}

		static void* GetObjectUserByID(INT32 nID)
		{
			INT64 nAddr = 0;
			typedef void *(__fastcall*_GET_OBJECT)(VOID*, INT64*, INT32);
			_GET_OBJECT xGetObject = (_GET_OBJECT)0x479090;
			xGetObject((VOID*)0xE4E7160, &nAddr, nID);
			return (VOID*)nAddr;
		}

		static void* GetObjectUserByID2(INT32 nID)
		{
			INT64 nAddr = 0;
			typedef void *(__fastcall*_GET_OBJECT)(VOID*, INT64*, INT32);
			_GET_OBJECT xGetObject = (_GET_OBJECT)0x479090;
			xGetObject((VOID*)0xE4471A0, &nAddr, nID);
			return (VOID*)nAddr;
		}

		static void* GetObjectUserByID3(INT32 nID)
		{
			INT64 nAddr = 0;
			typedef void *(__fastcall*_GET_OBJECT)(VOID*, INT64*, INT32);
			_GET_OBJECT xGetObject = (_GET_OBJECT)0x479090;
			xGetObject((VOID*)0xE6C8580, &nAddr, nID);
			return (VOID*)nAddr;
		}

		static CSetItem *GetSetObject(INT32 nSetID)
		{
			typedef CSetItem *(__fastcall *_SET_GET_OBJECT) (VOID *pObjectDB, INT32 nsid);
			_SET_GET_OBJECT xSetGetObject = (_SET_GET_OBJECT)0x006FB0C0L;
			return xSetGetObject((VOID *)0x0BC5D810, nSetID);
		}

		static void BroadcastToNeighbor(INT32 ObjectID, FVector vPos, CSPacket *pPacket)
		{
			typedef void (__fastcall *_BROADCAST_TO_NEIGHBOR) (VOID *UnkArg1, INT32 ObjID, INT32 Dist, FVector Pos, const char *fmt, ...);
			_BROADCAST_TO_NEIGHBOR xBroadcastToNeighbor = (_BROADCAST_TO_NEIGHBOR)0x004AFF20L;
			xBroadcastToNeighbor((VOID *)0x0E427AA8, ObjectID, 0x80000, vPos, "b", pPacket->size(), pPacket->buffer(false));
		}

		static void BroadcastToNeighborDist(INT32 ObjectID, FVector vPos, int Distance, CSPacket *pPacket)
		{
			typedef void (__fastcall *_BROADCAST_TO_NEIGHBOR_DIST) (VOID *UnkArg1, INT32 ObjID, INT32 Dist, FVector Pos, int Dist2, const char *fmt, ...);
			_BROADCAST_TO_NEIGHBOR_DIST xBroadcastToNeighborDist = (_BROADCAST_TO_NEIGHBOR_DIST)0x00403DE0L;
			xBroadcastToNeighborDist((VOID *)0x0E427AA8, ObjectID, 0x80000, vPos, Distance, "b", pPacket->size(), pPacket->buffer(false));
		}

		static void BroadcastToNeighborExceptSelf(INT32 ObjectID, FVector vPos, CSPacket *pPacket)
		{
			typedef void (__fastcall *_BROADCAST_TO_NEIGHBOR_EXCEPT_SELF) (VOID *UnkArg1, INT32 ObjID, INT32 Dist, FVector Pos, const char *fmt, ...);
			_BROADCAST_TO_NEIGHBOR_EXCEPT_SELF xBroadcastToNeighborExceptSelf = (_BROADCAST_TO_NEIGHBOR_EXCEPT_SELF)0x004E8CB0L;
			xBroadcastToNeighborExceptSelf((VOID *)0x0E427AA8, ObjectID, 0x80000, vPos, "b", pPacket->size(), pPacket->buffer(false));
		}

		static void BroadcastToAllUser(CSPacket *pPacket)
		{
			typedef void (__fastcall *_BROADCAST_TO_ALL_USER) (const char * format, ...);
			_BROADCAST_TO_ALL_USER BroadcastToAllUser = (_BROADCAST_TO_ALL_USER)0x00822F40;
			BroadcastToAllUser("b", pPacket->size(), pPacket->buffer(false));
		}

		static void BroadcastSendSystemMessageToAll(const WCHAR* format, ...)
		{
			typedef void (__fastcall *_BROADCAST_TO_ALL_USER) (const char * format, ...);
			_BROADCAST_TO_ALL_USER xBroadcastToAllUser = (_BROADCAST_TO_ALL_USER)0x00822F40;

			static const size_t MSGLEN = 1000;
			WCHAR msg[MSGLEN+1];

			va_list args;
			va_start(args, format);
			_snwprintf(msg, MSGLEN, format, args);
			msg[MSGLEN] = L'\0';
			va_end(args);

			xBroadcastToAllUser("cdddSdS", 0x64, 614, 2, 0, L"SVR", 0, msg);
		}

		static CObject* AddNewObject(int nObjectSize, WCHAR* wszObjectClassName, int ItemTypeClass)
		{
			typedef CObject* (__fastcall *__f)(VOID*, DWORD, BYTE, WCHAR*);
			__f _f = (__f) 0x00670140;
			CObject* pObject = _f((VOID*)0x01557E00, nObjectSize, 1, wszObjectClassName);

			INT64 *Addr2 = (INT64*)0x06FD2320;
			int *Addr3 = (int*)(0x07052320);
			InterlockedIncrement(&((long*)0x06F92320)[ItemTypeClass]);
			Addr2[ItemTypeClass] = *wszObjectClassName;
			Addr3[ItemTypeClass] = nObjectSize;

			return pObject;
		}

		static void InsertByName(const wstring id, void* p, char *caller=NULL, int line=-1)
		{
			typedef void (__fastcall *__f)(VOID*, wstring, void*, char*, int);
			__f _f = (__f) 0x0058FEB0;
			_f((VOID*)0x0E2853E0, id, p, caller, line);
		}

		static void InsertByID(int id, void* p, char *caller=NULL, int line=-1)
		{
			typedef void (__fastcall *__f)(VOID*, int, void*, char*, int);
			__f _f = (__f) 0x00588C00;
			_f((VOID*)0x0E285350, id, p, caller, line);
		}

		static void RegObject(VOID* pObject, wchar_t* object_name)
		{
			typedef void (__fastcall *_f) (VOID*, VOID*, wchar_t*);
			_f xf = (_f)0x006FC400L;
			xf((VOID*)0x0BC5D810, pObject, object_name);
		}
		
		static bool IsWaitingReply(VOID* pN, VOID* pObject1, VOID* pObject2, INT32 timer)
		{
			typedef bool (__fastcall *_f) (VOID*, VOID*, VOID*, INT32);
			_f xf = (_f)0x0085C9F0L;
			return xf(pN, pObject1, pObject2, timer);
		}

		static void* FindUserByReply(void *pUser)
		{
			INT64 nAddr = 0;
			typedef void* (__fastcall *_f) (INT64*, VOID*);
			_f xf = (_f)0x0085B740L;
			xf(&nAddr, pUser);
			return (VOID*)nAddr;
		}

		static void DeleteUserFromReply(void *pUser)
		{
			typedef void (__fastcall *_f) (VOID*);
			_f xf = (_f)0x0085CD30L;
			xf(pUser);
		}

		static bool CheckClassObject(int* nID)
		{
			typedef bool (__fastcall *_f) (int*);
			_f xf = (_f)0x007F06D0L;
			return xf(nID);
		}

		static void* GetClassObject(int* nID)
		{
			typedef void* (__fastcall *_f) (int*);
			_f xf = (_f)0x007F07F0L;
			return xf(nID);
		}

		static void* malloc(size_t n);
		static void  free(void* p);

		static void* operator_new(size_t n);
		static void  operator_delete(void* p);
};