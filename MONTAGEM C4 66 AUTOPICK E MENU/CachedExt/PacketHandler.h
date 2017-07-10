#ifndef _PACKETHANDLER_
#define _PACKETHANDLER_

#include "process.h"
#include "CQuerySocket.h"

class LargeBuffer
{
public:
	char Buffer[16384];
	int nBuffLen;
	int nMemberAmountPos;
public:
	void Clear(){ memset(this, 0, sizeof(LargeBuffer));}
};

class PacketHandler
{
public:
	static void Initialize();
	static bool __cdecl RequestQueryPacket(VOID *pSocket, CHAR *pPacket);
	static bool __cdecl Handle(CQuerySocket *pQuerySocket, unsigned char* packet);
	static bool __cdecl RequestLoadInfectedSkills(CQuerySocket *pSocket, unsigned char *packet);
	static bool __cdecl RequestSaveInfectedSkills(CQuerySocket *pSocket, unsigned char *packet);
};
#endif