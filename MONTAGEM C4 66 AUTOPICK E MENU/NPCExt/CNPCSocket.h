#pragma once

#include "Global.h"

#pragma pack( push, 1 )

class CNPCSocket
{
	public:
		static CNPCSocket* I();
		void Send(const char *format, ...);

	private:
		static CNPCSocket *CNPCSocketStatic;
};

#pragma pack( pop )
