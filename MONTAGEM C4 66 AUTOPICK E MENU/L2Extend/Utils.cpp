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

#include "Utils.h"
#include <ctime>
#include <iomanip>
#include <sstream>

__int64 Assemble(char *buf, int bufLen, char *format, ...)
{
	//guard(int Assemble(char *buf, int bufLen, const char *format, ...));

	va_list ap;
	va_start(ap, format);
	__int64 len = VAssemble(buf, bufLen, format, ap);
	va_end(ap);
	return len;

	//unguard;
}

char *StrNChr(char *str, char c, int len)
{
	//guard(const char *StrNChr(const char *str, char c, int len));

	while (len > 0)
	{
		if (*str == c)
			return str;
		str++;
		len--;
	}
	return str;

	//unguard;
}

int WcsNLen(char *str, int len)
{
//	guard(int WcsNLen(const unsigned char *str, int len));

	int i;
	for (i = 0; i < len; i++)
	{
		if (!str[0] && !str[1])
			break;
		str += 2;
	}
	return i;

//	unguard;
}



char *Disassemble(char* packet, char* format, ...)
{
	char* f = format;
	va_list ap;
	int t;
	va_start(ap, format);
	while ((t = *format++))
	{
		switch (t)
		{
		case 'c':
			{
				char* cp = va_arg(ap, char*);
				*cp = *packet++;
			}
			break;
		case 'h':
			{
				short* hp = va_arg(ap, short*);
#ifdef _WIN32
				*hp = ((short *)packet)[0];
#else
				*hp = packet[0] + (packet[1] << 8);
#endif
				packet += 2;
			}
			break;
		case 'd':
			{
				int* dp = va_arg(ap, int*);

#ifdef _WIN32           // CPU specific optimization.
				*dp = ((int *)packet)[0];
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24);
#endif
				packet += 4;
			}
			break;

		case 'f':
			{
				double* dp = va_arg(ap, double*);

#ifdef _WIN32           // CPU specific optimization.
				CopyMemory(dp, packet, 8);
				/*
				int i1 = *(int*)packet;
				int i2 = *(((int*)packet)+1);
				*(((int*)dp)+0) = i2;
				*(((int*)dp)+1) = i1;
				*/
				/*
				*dp = ((double *)packet)[0];
				*/
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24)
					+ (packet[4] << 32) + (packet[5] << 40) + (packet[6] << 48) + (packet[7] << 56)
#endif
				packet += 8;
			}
			break;

		case 's':
			{
				int dstLen = va_arg(ap, int);
				char* dst = va_arg(ap, char*);
				strncpy(dst, (char*)packet, dstLen);
				dst[dstLen - 1] = 0;
				char* end = (char*)StrNChr((char*)packet, '\0', dstLen) + 1;
//		if (end - packet > dstLen) {
//		    log.Add(LOG_ERROR, "too long string in %s", f);
//		}
				packet = end;
			}
			break;
		case 'S':
			{
				int len = va_arg(ap, int) / sizeof(wchar_t);
				len = WcsNLen(packet, len-1);
				wchar_t* dst = va_arg(ap, wchar_t*);
				memcpy(dst, packet, len * sizeof(wchar_t));
				dst[len] = 0;
				packet += (len + 1) * sizeof(wchar_t);
			}
			break;
		case 'Q':
			{
				__int64* dp = va_arg(ap, __int64*);

#ifdef _WIN32           // CPU specific optimization.
				*dp = ((__int64 *)packet)[0];
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24) + 
					(packet[4] << 32) + (packet[5] << 40) + (packet[6] << 48) + (packet[7] << 56);
#endif
				packet += 8;
			}
			break;
		case 'b':
			{
				__int16 size = va_arg(ap, __int16);
				__int64 *mem = va_arg(ap, __int64*);

				CopyMemory(mem, packet, size);
				packet += size;
			}
			break;
#ifdef _DEBUG
		default:
			printf("Disassemble: unknown type %c in %s", t, f);
#endif
		}
	}
	va_end(ap);

	return packet;
}

void DisassembleVA(const char* format, va_list sourceva, ...)
{
	const char* f = format;
	va_list ap;
	int t;
	va_start(ap, format);
	while ((t = *format++))
	{
		switch (t)
		{
		case 'c':
			{
				char* cp = va_arg(ap, char*);
				*cp = va_arg(sourceva, char);
			}
			break;
		case 'h':
			{
				short* hp = va_arg(ap, short*);
				*hp = va_arg(sourceva, short);
			}
			break;
		case 'd':
			{
				int* dp = va_arg(ap, int*);
				*dp = va_arg(sourceva, int);
			}
			break;

		case 'f':
			{
				double* dp = va_arg(ap, double*);
				*dp = va_arg(sourceva, double);
			}
			break;

		case 's':
			{
				va_arg(ap, char*) = va_arg(sourceva, char*);
			}
			break;
		case 'S':
			{
				va_arg(ap, char*) = va_arg(sourceva, char*);
			}
			break;
		}
	}
	va_end(ap);
}

__int64 VAssemble(char* buf, int bufLen, char* format, va_list ap)
{
	//guard(int VAssemble(char* buf, int bufLen, const char* format, va_list ap));

	char* f = format;
	char* start = buf;
	char* end = buf + bufLen;
	int t;
	char* p;
	size_t len;
	int i;

	double d;

	while ((t = *format++))
	{
		switch (t)
		{
		case 's':
			p = va_arg(ap, char*);
			if (p)
			{
				len = strlen(p);
				if (buf + len + 1 > end)
				{
					goto overflow;
				}
				strcpy(buf, p);
				buf += len + 1;
			}
			else
			{
				// p is null. Is it correct?
				if (buf + 1 > end)
				{
					goto overflow;
				}
				*buf++ = 0;
			}
			break;
		case 'S': 
			{
				wchar_t* p = va_arg(ap, wchar_t*);
				if (p)
				{
					len = (wcslen(p) + 1)* sizeof(wchar_t);
					if (buf + len > end)
					{
						goto overflow;
					}
					memcpy(buf, p, len);
					buf += len;
				}
				else
				{
					// p is null. Is it correct?
					if (buf + 2 > end)
					{
						goto overflow;
					}
					*buf++ = 0;
					*buf++ = 0;
				}
			}
			break;
		case 'b':	    // blind copy
			len = va_arg(ap, int);
			p = va_arg(ap, char*);
			if (buf + len > end)
			{
				goto overflow;
			}
			memcpy(buf, p, len);
			buf += len;
			break;
		case 'c':
			i = va_arg(ap, int);
			if (buf + 1 > end)
			{
				goto overflow;
			}
			*buf++ = i;
			break;
		case 'h':
			i = va_arg(ap, int);
			if (buf + 2 > end)
			{
				goto overflow;
			}
#ifdef _WIN32
			*((short *)buf) = i;
			buf += 2;
#else
			*buf++ = i;
			*buf++ = i >> 8;
#endif
			break;
		case 'd':
			i = va_arg(ap, int);
			if (buf + 4 > end)
			{
				goto overflow;
			}
#ifdef _WIN32
			*((int *)buf) = i;
			buf += 4;
#else
			*buf++ = i;
			*buf++ = i >> 8;
			*buf++ = i >> 16;
			*buf++ = i >> 24;
#endif
			break;

		case 'f':
			d = va_arg(ap, double);
			if (buf + 8 > end)
			{
				goto overflow;
			}
#ifdef _WIN32
			CopyMemory(buf, &d, 8);
			/*
			*(((int*)buf)+0) = *(((int*)&d)+0);
			*(((int*)buf)+1) = *(((int*)&d)+1);
			*/
			/*
			*((double *)buf) = d;
			*/
			buf += 8;
#else
			*buf++ = d;
			*buf++ = d >> 8;
			*buf++ = d >> 16;
			*buf++ = d >> 24;
			*buf++ = d >> 32;
			*buf++ = d >> 40;
			*buf++ = d >> 48;
			*buf++ = d >> 56;
#endif
			break;
		}
	}
	return (buf - start);
overflow:
#ifdef _DEBUG
	printf("Buffer overflow in Assemble");
#endif
	return 0;

	//unguard;
}

unsigned short GETPACKETLENGHT(char *pPacket)
{
 	BYTE *temp = (BYTE*)pPacket;
 	temp-=2;
 	WORD packetlen = *temp  << 8;
 	temp--;
 	packetlen += *temp;
 	return packetlen-3;  //1=BYTE packetno + 2=WORD packetlen
}

string GetServerTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	time( &rawtime );
	timeinfo = localtime ( &rawtime );
	stringstream ss;
	ss << setw(2) << setfill('0') << timeinfo->tm_hour;
	ss << ":" << setw(2) << setfill('0') << timeinfo->tm_min;
	ss << ":" << setw(2) << setfill('0') << timeinfo->tm_sec;
	return ss.str();
}

string U2A(wstring str)
{
	string ascii;

	for ( int i = 0 ; i < str.size() ; i++ )
		ascii += (CHAR)str.c_str()[i];

	return ascii;
}

wstring A2U(string str)
{
	wstring unicode;

	for ( int i = 0 ; i < str.size() ; i++ )
		unicode += str.c_str()[i];

	return unicode;
}

bool CopyVMT(LPVOID *dst, LPVOID *src, size_t num)
{
	DWORD oldProtect = NULL;
	size_t size = num * sizeof(LPVOID);

	if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect)!=0)
	{
		memcpy_s(dst, size, src, size);
		VirtualProtect(dst, size, oldProtect, &oldProtect);
		return true;
	}
	else
	{
		MessageBox(NULL, "CopyVMT() failed!", "(Error) L2Server_addon", MB_OK);
		return false;
	}
}

std::vector <std::string> Split( std::string _separator, std::string _string )
{

        std::vector <std::string> array;

        size_t position;
        
        // we will find the position of first of the separators
        position = _string.find_first_of( _separator );
        
        // We will loop true this until there are no separators left
        // in _string
        while ( position != _string.npos )
        {
        
                // This thing here checks that we dont push empty strings
                // to the array
                if ( position != 0 )
                        array.push_back( _string.substr( 0, position ) );

                // When the cutted part is pushed into the array we
                // remove it and the separator from the _string
                _string.erase( 0, position + _separator.length() );

                // And the we look for a new place for the _separator
                position = _string.find_first_of( _separator );
        }

        // We will push the rest of the stuff in to the array
        if ( _string.empty() == false )
                array.push_back( _string );

        // Then we'll just return the array
        return array;
}

std::vector <std::wstring> Split( std::wstring _separator, std::wstring _wstring )
{

        std::vector <std::wstring> array;

        size_t position;
        
        // we will find the position of first of the separators
        position = _wstring.find_first_of( _separator );
        
        // We will loop true this until there are no separators left
        // in _string
        while ( position != _wstring.npos )
        {
        
                // This thing here checks that we dont push empty strings
                // to the array
                if ( position != 0 )
                        array.push_back( _wstring.substr( 0, position ) );

                // When the cutted part is pushed into the array we
                // remove it and the separator from the _string
                _wstring.erase( 0, position + _separator.length() );

                // And the we look for a new place for the _separator
                position = _wstring.find_first_of( _separator );
        }

        // We will push the rest of the stuff in to the array
        if ( _wstring.empty() == false )
                array.push_back( _wstring );

        // Then we'll just return the array
        return array;
}

void trim( std::wstring& s )
{
	static const wchar_t whitespace[] = L" \n\t\v\r\f";
	s.erase( 0, s.find_first_not_of(whitespace) );
	s.erase( s.find_last_not_of(whitespace) + 1U );
}

void trim( std::string& s )
{
	size_t index;
	static const char whitespace[] = " \n\t\v\r\f";
	while((index = (s.find_first_of(whitespace))) != string::npos)
		s.erase(index,1);
}