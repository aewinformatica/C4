#pragma once
#include <Winsock2.h>

class CSocket
{
public:
	/*0x00*/ BYTE nUnkn1[0x14];
	/*0x14*/ SOCKET s;
	/*0x18*/ BYTE nUnkn2[0xBC];
	/*0xD4*/ CRITICAL_SECTION cs_Socket;
public:
	void Lock(WCHAR *wszFile, int nLine);
	void Unlock();
	void DirectSend(char *packet, int nSize);
	void Send(const char *format, ...);
};