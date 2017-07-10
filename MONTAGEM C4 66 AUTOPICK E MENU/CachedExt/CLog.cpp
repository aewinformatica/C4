#include "CLog.h"

void CLog::Add(LogType Type, const wchar_t* format, ...)
{
	va_list va;
	va_start(va, format);
		typedef void (__thiscall *TAddVW) (void*, LogType, const wchar_t*, va_list);
		TAddVW AddVW = (TAddVW)0x00446AC0;
		AddVW((void*)0x8FF138, Type, format, va);
	va_end(va);
}