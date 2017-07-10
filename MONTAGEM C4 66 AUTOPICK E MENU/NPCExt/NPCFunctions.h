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

#pragma once

#include "Global.H"

// n00bish way to hide these functions from intelisense. we use defines so we dont want to see them anyway..
namespace HiddenNPC
{
	extern "C"
	{
		void tls_trace_begin(CHAR* wszFuncName);
		void tls_trace_end();
		INT32 npc_shared_guard(CHAR* wszFuncName);
	};
};

#ifndef USE_SHARED_GUARD
#define USE_SHARED_GUARD 1
#endif

#ifndef USE_SHARED_GUARD_STATIC
#define USE_SHARED_GUARD_STATIC 1
#endif

#if USE_SHARED_GUARD
#	define TLS_TRACE_BEGIN HiddenNPC::tls_trace_begin(__FUNCTION__)
#	define TLS_TRACE_END(return_type) {HiddenNPC::tls_trace_end(); return return_type;}
#	define TLS_TRACE_END_NO_RETURN HiddenNPC::tls_trace_end()
#	if USE_SHARED_GUARD_STATIC
#		define NPC_SHARED_GUARD(shared_variable) NPC_SHARED_GUARD0
#	else
#		define NPC_SHARED_GUARD(shared_variable) NPC_SHARED_GUARD1(shared_variable)
#	endif
#else
#	define TLS_TRACE_BEGIN
#	define TLS_TRACE_END
#	define NPC_SHARED_GUARD(shared_variable)
#endif

#define NPC_SHARED_GUARD1(shared_variable) \
	if(shared_variable != 1) { shared_variable |= 1; HiddenNPC::npc_shared_guard(__FUNCTION__); }

#define NPC_SHARED_GUARD0                                          \
{                                                                       \
	typedef INT32 (*FSharedGuard)(const CHAR* wszFuncName);            \
	static INT32 funcIndex = FSharedGuard(0x41ABD0)(__FUNCTION__);     \
};

class NPCFunctions
{
	public:
};
