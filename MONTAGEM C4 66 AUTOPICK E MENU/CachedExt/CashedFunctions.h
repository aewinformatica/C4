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
namespace HiddenCasheD
{
	extern "C"
	{
		void tls_trace_begin(WCHAR* wszFuncName);
		void tls_trace_end();
		INT32 cashed_shared_guard(WCHAR* wszFuncName);
	};
};

#ifndef USE_SHARED_GUARD
#define USE_SHARED_GUARD 1
#endif

#ifndef USE_SHARED_GUARD_STATIC
#define USE_SHARED_GUARD_STATIC 1
#endif

#if USE_SHARED_GUARD
#	define TLS_TRACE_BEGIN HiddenCasheD::tls_trace_begin(__FUNCTIONW__)
#	define TLS_TRACE_END(return_type) {HiddenCasheD::tls_trace_end(); return return_type;}
#	define TLS_TRACE_END_NO_RETURN HiddenCasheD::tls_trace_end()
#	if USE_SHARED_GUARD_STATIC
#		define CASHED_SHARED_GUARD(shared_variable) CASHED_SHARED_GUARD0
#	else
#		define CASHED_SHARED_GUARD(shared_variable) CASHED_SHARED_GUARD1(shared_variable)
#	endif
#else
#	define TLS_TRACE_BEGIN
#	define TLS_TRACE_END
#	define CASHED_SHARED_GUARD(shared_variable)
#endif

#define CASHED_SHARED_GUARD1(shared_variable) \
	if(shared_variable != 1) { shared_variable |= 1; HiddenCasheD::cashed_shared_guard(__FUNCTIONW__); }

#define CASHED_SHARED_GUARD0                                          \
{                                                                       \
	typedef INT32 (*FSharedGuard)(const WCHAR* wszFuncName);            \
	static INT32 funcIndex = FSharedGuard(0x4014B0)(__FUNCTIONW__);     \
};

class CasheDFunctions
{
	public:
};
