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

#include <windows.h>
#include <stdio.h>
#include <string>

using namespace std;

class CSPacket
{
	private:

		BYTE * pBuffer;					// Buffer that will be used to store packet data
		WORD   m_length;				// Contains the Total Lenght of the Packet
		WORD   m_position;				// Contains the Actual Position in the Packet Buffer (Index)
		WORD   m_maxlength;				// Stores the max allowed lenght for that packet
		bool   m_IsReference;			// Sets if the Packet is a Reference Or Not !

	public:

		// Constructor
		inline CSPacket()
		{
			pBuffer = NULL;
			m_length = 0;
			m_position = 0;
			m_maxlength = 0;
			m_IsReference = false;
		}

		inline CSPacket(CHAR *pIncommingBuffer, INT32 nPacketLen, INT32 nMaxPacketLen)
		{
			if ( pIncommingBuffer && nPacketLen > 0 && nMaxPacketLen > 0 )
			{
				m_IsReference = true;
				pBuffer = (BYTE *)pIncommingBuffer;
				m_maxlength = nMaxPacketLen;
				m_length = nPacketLen;
				m_position = nPacketLen-1;
			}
			else
			{
				m_IsReference = false;
				pBuffer = new BYTE[8];
				m_length = 8;
				m_position = 8;
				m_maxlength = 8;
			}
		}

		// Destructor
		inline ~CSPacket()
		{
			if ( !m_IsReference && m_length > 0 )
			{
				delete[] pBuffer;
			}
		}

		// Initializer
		void inline set(int nPacketLen)
		{
			if ( m_length == 0 && m_maxlength == 0 )
			{
				pBuffer = new BYTE[nPacketLen];
				memset(pBuffer,0x00,nPacketLen);
				m_maxlength = nPacketLen;
				m_length = 0;
				m_position = 0;
			}
		}

		// Clearer
		void inline clear()
		{
			if ( !m_IsReference && m_maxlength > 0 )
			{
				delete[] pBuffer;
				pBuffer = NULL;
				m_maxlength = 0;
				m_length = 0;
				m_position = 0;
				m_IsReference = false;
			}
		}

		// Current Position
		INT32 GetCurrentPosition() { return m_position; }

		CHAR inline *buffer(bool bMode)
		{ 
			return (CHAR *)pBuffer; 
		}

		CHAR inline *buffer()
		{
			return (CHAR *)pBuffer;
		}
		
		WORD inline size(void) 
		{ 
			return m_length; 
		}
	
		// Writting Routines
		template <typename type> inline void Write(type val)
		{
			// Checking Possible Overflow Before Writting
			if ( (m_length + sizeof(type)) <= m_maxlength )
			{
				*reinterpret_cast<type*>(pBuffer+m_position) = val;
				m_position += sizeof(type);
				m_length = m_position;
			}
		}

		inline void Write(const void *data, int len)
		{
			// Checking Possible Overflow Before Writting
			if ( (m_length + len) <= m_maxlength )
			{
				memcpy(pBuffer+m_position, data, len);
				m_position += len;
				m_length = m_position;
			}
		}

		int Write(CSPacket *inPacket, char type, int startPos)
		{
			switch(type)
			{
				case 'c':
					this->Write(inPacket->GetByte(startPos));
					startPos += 1;
					break;
				case 'h':
					this->Write(inPacket->GetWord(startPos));
					startPos += 2;
					break;
				case 'd':
					this->Write(inPacket->GetDWord(startPos));
					startPos += 4;
					break;
				case 'Q':
				case 'f':
					this->Write(inPacket->GetQWord(startPos));
					startPos += 8;
					break;
				case 'S':
					{
						wstring str = inPacket->GetWString(startPos);
						this->Write(str);
						startPos += (int)(str.length()*2+2);
					}
					break;
				case 'b':
					int count = inPacket->GetWord(startPos);
					this->Write(inPacket->GetBytes(startPos + 2), count);
					startPos += (count + 2);
					break;
			}

			return startPos;
		}

		template <typename type> inline void RewriteAt(type val, int pos)
		{
			// Checking Possible Overflow Before Writting
			if ( (pos + sizeof(type)) <= m_maxlength )
			{
				*reinterpret_cast<type*>(pBuffer+pos) = val;
			}
		}

		inline void RewriteAt(const void *data, int len, int pos)
		{
			// Checking Possible Overflow Before Writting
			if ( (pos + len) <= m_maxlength )
			{
				memcpy(pBuffer+pos, data, len);
			}
		}

		void Write(const char* str)
		{
			Write(str, static_cast<int>(strlen(str)+1));
		}

		void Write(char* str)
		{
			Write(str, static_cast<int>(strlen(str)+1));
		}

		void Write(const WCHAR* str)
		{
			Write(str, static_cast<int>(wcslen(str)*2+2));
		}

		void Write(WCHAR* str)
		{
			Write(str, static_cast<int>(wcslen(str)*2+2));
		}

		template <typename charT>
		void Write(const std::basic_string<charT>& str)
		{
			size_t len = (str.length()+1) * sizeof(charT);
			Write(str.c_str(), static_cast<int>(len));
		}

		template <typename type>
		CSPacket& operator<< (const type& val)
		{
			Write(val);
			return *this;
		}

		// Reading Routines
		string inline GetString(WORD index) 
		{
			if ( index < m_maxlength )
				return reinterpret_cast<CHAR *>(pBuffer)+index;
			else
				return "";
		}
		
		wstring inline GetWString(WORD index) 
		{
			if ( index < m_maxlength )
				return reinterpret_cast<WCHAR *>(reinterpret_cast<char *>(pBuffer)+index); 
			else
				return L"";
		}

		BYTE inline GetByte(WORD index) 
		{
			if ( index < m_maxlength )
				return pBuffer[index]; 
			else
				return 0; 
		}

		BYTE inline *GetBytes(WORD index) 
		{ 
			if ( index < m_maxlength )
				return pBuffer+index; 
			else
				return NULL;
		}

		WORD GetWord(WORD index) 
		{ 
			if ( index < m_maxlength )
				return *((WORD *)(pBuffer + index)); 
			else
				return 0;
		}

		DWORD GetDWord(WORD index) 
		{ 
			if ( index < m_maxlength )
				return *((DWORD *)(pBuffer + index)); 
			else
				return 0; 
		}

		UINT64 GetQWord(WORD index) 
		{ 
			if ( index < m_maxlength )
				return *((UINT64 *)(pBuffer + index)); 
			else
				return 0; 
		}

};
