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
#include <time.h>
#include "CQuerySocket.h"

typedef unsigned char *(__cdecl *TDisassemble) (unsigned char* packet, const char* format, ...);
static TDisassemble Disassemble = (TDisassemble)0x0043F450;

typedef int (__cdecl *TAssemble) (char *buf, int bufLen, const char* format, ...);
static TAssemble Assemble = (TAssemble)0x0043F070;

typedef bool (__stdcall *TDummyPacket) (CQuerySocket *pQuerySocket, const unsigned char* packet);
static TDummyPacket DummyPacket = (TDummyPacket)0x0045BFC0;

const char *DisassembleQ(const char* packet, char* format, ...);