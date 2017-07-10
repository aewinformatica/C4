#include "CNPCSocket.h"

CNPCSocket *CNPCSocket::CNPCSocketStatic;

CNPCSocket *CNPCSocket::I()
{
	if (CNPCSocketStatic == NULL)
		CNPCSocketStatic = (CNPCSocket*) 0x328BBB0;
	return CNPCSocketStatic;
}
