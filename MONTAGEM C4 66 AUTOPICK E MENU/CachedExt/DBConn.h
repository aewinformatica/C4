#ifndef _DBCONN_
#define _DBCONN_

#ifndef _WINDOWS_
#include <windows.h>
#endif

#ifndef _TCHAR_
#include <wchar.h>
#endif

#include <sqlext.h>

class DBConn
{
	/* 000 */ SQLHSTMT handle;
	/* 004 */ __int16 collumnNumber;
	/* 006 */ __int8 unk[0x40A];
	/* 410 */
public:
	DBConn();
	~DBConn();

	void BindC(void* pTargetValue, int nBuffLen);
	void BindS(void* pTargetValue, int nBuffLen);
	void BindNullable(void* pTargetValue, int nBufferLen);
	void BindD(void* pTargetValue);
	void BindH(void* pTargetValue);
	void BindF(void* pTargetValue);
	void BindQ(void* pTargetValue);

	bool Execute(const wchar_t *cpstmt, ...);
	bool Fetch(); 
};

#endif