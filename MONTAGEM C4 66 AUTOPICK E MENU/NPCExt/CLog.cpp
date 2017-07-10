#include "CLog.h"

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

static void* g_CLog = (void*)0x0638C7D0;

void CLog::Add(LogType type, const char* format, ...)
{
	typedef void (*CLogAddV_t)(void*, int, const char*, va_list);
	CLogAddV_t pfCLogAddV = (CLogAddV_t)0x4AA950;
	va_list args;
	va_start(args, format);
	pfCLogAddV(g_CLog, type, format, args);
	va_end(args);
}

void CLog::Add(LogType type, const wchar_t* format, ...)
{
	typedef void (*CLogAddVW_t)(void*, int, const wchar_t*, va_list);
	CLogAddVW_t pfCLogAddVW = (CLogAddVW_t)0x4AAAE0;
	va_list args;
	va_start(args, format);
	pfCLogAddVW(g_CLog, type, format, args);
	va_end(args);
}
