#pragma once

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

#define MAX_PACKET_LEN 0x4000

class User;

#pragma pack( push, 1 )

class CBigBuffer
{
	public:

		void Initialize() 
		{
			pBuffer = new CHAR[MAX_PACKET_LEN];
			memset(this->pBuffer, 0x00, MAX_PACKET_LEN); 
			this->bIsBigPacket = false; 
			this->nBufferLen = 0; 
		}

		bool bIsBigPacket;
		WORD nBufferLen;
		CHAR *pBuffer;
};

class CIOBuffer
{
	public:

		/* 0000 */ BYTE bUnknownBlock[0x2010];
		/* 2010 */ int nWriteCount;
		/* 2014 */ int _dw2014;
		/* 2018 */ int _dw2018;
};

class CSocket
{
	public:

		/* Constructor / Destructor */

		CSocket() { };
		~CSocket() { };

		/* Hooked Functions */

		//void Send(CSPacket *buf);
		//void Send(const char * format, ...);
		//void Close();
		//void SendSystemMessage(int nMessageID);
		//void SendSystemMessage(const char *format, ...);
		//void SendSystemMessage(const wchar_t *wszSender, const wchar_t *wszMessage);
		//void SendSystemMessage_S(int nMessageID, const wchar_t *wszMessage);
		//in_addr GetAddress();
		//void Lock();
		//void Unlock();

		bool IsValidUserSocket()
		{
            if(this)
			{
                __try
				{ 
					if(*(DWORD*)this == 0xA8EE78) return true; 
				}
                __except(EXCEPTION_EXECUTE_HANDLER)
				{ 
					/* Invalid pointer */
					/* Preventing Crash ;) */
				}
            }

			return false;
		}

		void AllocateBuff()
		{
			if ( !this->pBigBuffer ) { this->pBigBuffer = &this->BigBuffer; }
		}

		/* Class Extending Functions */

		static void ExtendClass();
		static CSocket *MemoryAllocation(VOID *pAllocator, INT32 nAllocSize, bool bUnknown, CHAR *pType);

		/* 0000 */ int _dw0000[6];
		/* 0018 */ SOCKET s;
		/* 0020 */ int _dw0020[20];
		/* 0070 */ void *pWSAOverlapped;
		/* 0078 */ int _dw0078[8];
		/* 0098 */ CIOBuffer *pCIOBuffer;
		/* 00A0 */ int _dw00A0[32];
		/* 0120 */ unsigned char *pDecryptKey;
		/* 0128 */ unsigned char *pEncryptKey;
		/* 0130 */ int _dw0130[10];
		/* 0158 */ User *user;
		/* 0160 */ int _dw0160[15];
		/* 0198 */ int nSocketStatus;
		/* 019C */ int _dw019C[4];
		/* 01B0 */ void *pLock;
		/* 01B8 */ int _dw01B8[166];
		/* 0450 */ int nAccountID;
		/* 0454 */ int _dw0454;
		/* 0458 */ int _dw0458;
		/* 045C */ int _dw045C;
		/* 0460 */ int _dw0460;
		/* 0464 */ int _dw0464;
		/* 0468 */ int _dw0468;
		/* 046C */ int _dw046C;

	protected:
	
		CBigBuffer BigBuffer;

	public:
		
		CBigBuffer *pBigBuffer;

		void EnlargeBuffer(BYTE *pBufferData, WORD nLen) 
		{
			if ( this->pBigBuffer )
			{
				this->pBigBuffer->nBufferLen = nLen+2;
				memset(this->pBigBuffer->pBuffer, 0x00, MAX_PACKET_LEN);
				this->pBigBuffer->pBuffer[0] = ((BYTE *)&this->pBigBuffer->nBufferLen)[0];
				this->pBigBuffer->pBuffer[1] = ((BYTE *)&this->pBigBuffer->nBufferLen)[1];
				memcpy(this->pBigBuffer->pBuffer+2, pBufferData, nLen);
				this->pBigBuffer->bIsBigPacket = true;
			}
		}

		void DispatchBuffer() 
		{ 
			if ( this->pBigBuffer ) 
			{
				if ( this->pBigBuffer->bIsBigPacket )
				{
					this->pBigBuffer->bIsBigPacket = false;
				}
			} 
		}

		bool IsBigPacket() 
		{ 
			if ( this->pBigBuffer ) { return this->pBigBuffer->bIsBigPacket; } else { return false; } 
		}
};

#pragma pack( pop )
