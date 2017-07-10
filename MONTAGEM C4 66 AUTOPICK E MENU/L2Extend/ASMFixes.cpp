#include "ASMFixes.h"

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

void ASMFixes::Initialize()
{
	// L2Server Sometimes Crash, When You Shutdown It...
	WriteInstruction(0x63F13D, (INT32)ExitCrash, 0, 0xE9);

	// Error/disconnect on character selection screen caused by invalid packets squence sent by new client.
	// Fix for dc and errors in char selection screen
	WriteInstruction(0x85EAC7, (INT32)LastUsedPacketFix1, 3, 0xE9);

	// gladiator/tyrans fix
	NOPMemory(0x6B8BB6, 0x6B8BBE - 0x6B8BB6);
	WriteInstruction(0x6B8BB6, (INT32)C5_GladiatorTyransFix, 0, 0xE9);
	
	//Attack Range Fix
	WriteInstruction(0x4FFE73, (INT32)RangeHook, 0, 0xE9);
	
	//Backstab
	WriteInstruction(0x7AF6CD, (INT32)BsGotDamageBy, 4, 0xE9);
}

void DoExitApplication()
{
	// Exiting L2Server...
	ExitProcess(1);
}