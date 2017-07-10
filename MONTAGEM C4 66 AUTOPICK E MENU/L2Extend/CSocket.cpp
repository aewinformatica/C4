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

#include <winsock2.h>
#include "CSocket.h"
#include "CLog.h"
#include "L2ServerFunctions.h"
#include "CAmpedX64.h"
#include "CAmpedX64.h"

void CSocket::ExtendClass()
{
	INT64 nAmpedAddr = GetModuleAddress("AmpeDx64.dll");
	
	// Extending Class Capacity Size
	WriteMemoryDWORD(0x89036B, sizeof(CSocket));
	WriteMemoryDWORD(0x8903A7, sizeof(CSocket));

	if ( nAmpedAddr > 0 )
	{
		// Extending Class Size
		WriteMemoryDWORD(nAmpedAddr+0xE124, sizeof(CSocket));

		// Extending Class Allocation
		WriteInstruction(nAmpedAddr+0xE0E7, (INT32)CSocket::MemoryAllocation, 0, 0xE8);
	}
}

CSocket *CSocket::MemoryAllocation(VOID *pAllocator, INT32 nAllocSize, bool bUnknown, CHAR *pType)
{
	typedef VOID *(__fastcall *_ML) (VOID *, INT32, bool, CHAR *);
	_ML xMalloc = (_ML)0x00670140L;

	CSocket *pSocketNew = (CSocket *)xMalloc(pAllocator, nAllocSize, bUnknown, pType);
	
	// CLog::Add(CLog::blue, "Allocating Memory...");
	memset(pSocketNew, 0x00, nAllocSize);

	if ( pSocketNew )
	{
		// CLog::Add(CLog::blue, "Initializing Buffers...");

		// Allocating the Buffer
		pSocketNew->AllocateBuff();

		// Initializing The Extended Send Buffer
		pSocketNew->pBigBuffer->Initialize();
	}

	return pSocketNew;
}

INT32 nSend1 = 0;
void CSocket::Send(CSPacket *buf)
{
	L2SERVER_SHARED_GUARD(nSend1);
	TLS_TRACE_BEGIN;

	// Performing Custom Send
	if ( buf->size() <= 0x1FFE )
	{
		this->Send("b", buf->size(), buf->buffer(false));
	}
	else
	{
		if ( buf->size() <= (MAX_PACKET_LEN-2) )
		{
			// Enlarging the Output Buffer and Sending a Dummy Packet !
			this->EnlargeBuffer((BYTE *)buf->buffer(), buf->size());
			this->Send("cd", 0x70, buf->size());
		}
		else
		{
			CLog::Add(CLog::red, "CBigBuffer::Overflow %d > %d, Please Verify !!!", buf->size(), MAX_PACKET_LEN);
		}
	}

	TLS_TRACE_END;
}

void CSocket::Send(const char * format, ...)
{
	// Performing Normal Send
	typedef void (__fastcall *_SENDV) (CSocket * pSocket, const char * format, ...); _SENDV SendV = (_SENDV)0x007D5D40;
	va_list vl;	va_start(vl, format);	SendV(this, format, vl);	va_end(vl);
}

void CSocket::SendSystemMessage(const char *format, ...)
{
	CHAR  BUF1[256];
	WCHAR BUF2[512];

	memset(BUF1, 0x00, 256);
	memset(BUF2, 0x00, 512);

	va_list args;
	va_start(args, format);
	vsprintf(BUF1,format,args);
	va_end(args);

	MultiByteToWideChar(CP_ACP, 0, BUF1, -1, BUF2, 256);

	Send("cdddSdS", 0x64, 614, 2, 0, L"SVR", 0, BUF2);
}

void CSocket::Close()
{
	typedef void (__thiscall *_CLOSE) (void * pIOSocket);
	_CLOSE _Close = (_CLOSE)0x0061E540;
	this->nSocketStatus = 2;
	_Close(this);
}

void CSocket::SendSystemMessage(int nMessageID)
{
	typedef void (__thiscall *_SSM) (CSocket *, int);
	_SSM xSendSystemMessage = (_SSM)0x00410920;

	xSendSystemMessage(this, nMessageID);
}

void CSocket::SendSystemMessage(const wchar_t *wszSender, const wchar_t *wszMessage)
{
	typedef void (*__SSM)(CSocket *, const wchar_t *, const wchar_t *);
	__SSM _SSM = (__SSM)0x0086C340;

	_SSM(this, wszSender, wszMessage);
}

void CSocket::SendSystemMessage_S(int nMessageID, const wchar_t *wszMessage)
{
	typedef void (*__SSMS)(CSocket *, int, const wchar_t *);
	__SSMS _SSMS = (__SSMS)0x00439950;

	_SSMS(this, nMessageID, wszMessage);
}
/*
in_addr CSocket::GetAddress()
{
	typedef void (*_Get_Address)(CSocket *);
	_Get_Address xGetAddress = (_Get_Address)0x007D53B0;
	xGetAddress(this);
}
*/
INT32 nCSocket_Lock = 0;
void CSocket::Lock()
{
	L2SERVER_SHARED_GUARD(nCSocket_Lock);
	TLS_TRACE_BEGIN;

	typedef void (__fastcall *_LOCK) (void *, wchar_t *, int); _LOCK xLock = (_LOCK)0x00627D10L;
	xLock(&this->pLock, L"CSocket.cpp", __LINE__);

	TLS_TRACE_END;
}

INT32 nCSocket_Unlock = 0;
void CSocket::Unlock()
{
	L2SERVER_SHARED_GUARD(nCSocket_Unlock);
	TLS_TRACE_BEGIN;

	typedef void (__fastcall *_UNLOCK) (void *, wchar_t *, int); _UNLOCK xUnlock = (_UNLOCK)0x00628010L;

	xUnlock(&this->pLock, L"CSocket.cpp", __LINE__);

	TLS_TRACE_END;
}