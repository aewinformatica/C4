#include "Global.h"
#include "NpcServer.h"

NpcServer *NpcServer::npcServerStatic;

NpcServer *NpcServer::I()
{
	if (npcServerStatic == NULL)
		npcServerStatic = (NpcServer*) 0x1557EE0;
	return npcServerStatic;
}
