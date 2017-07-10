#include "DBConn.h"

DBConn::DBConn()
{
	typedef void (__fastcall *TDBConn) (DBConn*);
	TDBConn _DBConn = (TDBConn)0x00428A80;
	_DBConn(this);
}

DBConn::~DBConn()
{
	typedef void (__fastcall *TDBConn_) (DBConn*);
	TDBConn_ DBConn_ = (TDBConn_)0x00428E00;
	DBConn_(this);
}

bool DBConn::Execute(const wchar_t *cpstmt, ...)
{
	wchar_t buffer[4096];
	memset(buffer,0,sizeof(buffer));
	va_list va;
	va_start(va, cpstmt);
	vswprintf_s(buffer, cpstmt, va);
	va_end(va);
	typedef bool (__cdecl *TExecute) (DBConn*,wchar_t*);
	TExecute Execute_ = (TExecute)0x0042AFF0;
	return Execute_(this,buffer);
}

bool DBConn::Fetch()
{
	typedef bool (__fastcall *TFetch) (DBConn*);
	TFetch _Fetch = (TFetch)0x0042A140;
	return _Fetch(this);
}

void DBConn::BindC(void* pTargetValue, int nBuffLen)
{
	__asm
	{
		push nBuffLen
		push pTargetValue
		mov ecx, this
		mov eax, 42A4E0h
		call eax
	}
}

void DBConn::BindS(void* pTargetValue, int nBuffLen)
{
	__asm
	{
	push nBuffLen
	push pTargetValue
	mov ecx, this
	mov  eax, 42A4E0h
	call eax
	}
}

void DBConn::BindD(void* pTargetValue)
{
	__asm
	{
		push pTargetValue
		mov ecx, this
		mov eax, 42A720h
		call eax
	}
}

void DBConn::BindH(void* pTargetValue)
{
	__asm
	{
		push pTargetValue
		mov ecx, this
		mov eax, 42A7E0h					// this is smallint bind
		call eax
	}
}

void DBConn::BindF(void* pTargetValue)
{
	__asm
	{
		push pTargetValue
		mov ecx, this
		mov eax, 42A8A0h
		call eax
	}
}

void DBConn::BindQ(void* pTargetValue)
{
	__int16 colNum = this->collumnNumber;
	this->collumnNumber++;

	SQLBindCol(this->handle, colNum, SQL_C_SBIGINT, pTargetValue, 8, 0);
}

void DBConn::BindNullable(void* pTargetValue, int nBufferLen)
{
	__asm
	{
		push nBufferLen
		push pTargetValue
		mov ecx, this
		mov  eax, 42AD20h
		call eax
	}
}
