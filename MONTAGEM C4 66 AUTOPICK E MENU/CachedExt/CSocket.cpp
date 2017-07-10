#include "Global.h"
#pragma comment(lib, "Ws2_32.lib")
/* use it only when it's needed (packet are bigger than 8192)*/
void CSocket::DirectSend(char *packet, int nSize)
{
	char Buff[16384];
	memset(Buff, 0, 16384);
	*(WORD*)Buff = (WORD)nSize;
	memcpy((Buff+2),packet, nSize);
	DWORD BytesSent = 0;
	send(this->s, Buff, nSize, 0);
}

void CSocket::Lock(WCHAR *wszFile, int nLine)
{
	typedef void(__thiscall *lock)(CRITICAL_SECTION*, WCHAR*, int);
	lock _lock = (lock) 0x4422F0;
	_lock(&this->cs_Socket, wszFile, nLine);
}

void CSocket::Unlock()
{
	typedef void(__thiscall *unlock)(CRITICAL_SECTION*, WCHAR*, int);
	unlock _unlock = (unlock) 0x4425E0;
	_unlock(&this->cs_Socket, NULL, NULL);

}

__declspec(naked) void CSocket::Send(const char *format, ...)
{
	__asm
	{
		mov eax, 467370h
		jmp eax
	}
}
