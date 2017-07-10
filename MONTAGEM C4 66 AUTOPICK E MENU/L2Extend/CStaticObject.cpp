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

#include "CStaticObject.h"

extern "C"
{
	CStaticObject g_StaticObject;
};

BYTE CStaticObject::pIndex[INDEXDOOR] = {0};
INT64 CStaticObject::pIndex2[INDEXDOOR] = {0};
INT64 CStaticObject::pStatic[INDEXDOOR] = {0};
//INT64 CStaticObject::pStaticObj[INDEXDOOR*5] = {0};

void CStaticObject::InitializeStaticObject()
{
	//FindObjectSize();

	//enlarge array
	WriteMemoryDWORD(0xBF7210, INDEXDOOR);
	WriteMemoryDWORD(0x7E08CE, INDEXDOOR);
	WriteMemoryDWORD(0x7DF718, INDEXDOOR);
	WriteMemoryDWORD(0x7DFAEA, INDEXDOOR);
	WriteMemoryDWORD(0x960528, sizeof(CStaticObject::pIndex));
	WriteMemoryDWORD(0x960514, sizeof(CStaticObject::pStatic));
	WriteMemoryDWORD(0x9604F9, sizeof(CStaticObject::pIndex2));

	//new addr for index array
	WriteInstruction(0x96051D, (INT32) &CStaticObject::Code_96051D, 2, 0xE9);
	WriteInstruction(0x7DF72A, (INT32) &CStaticObject::Code_7DF72A, 3, 0xE9);
	WriteInstruction(0x7DFC1B, (INT32) &CStaticObject::Code_7DFC1B, 3, 0xE9);
	WriteInstruction(0x7DFC30, (INT32) &CStaticObject::Code_7DFC30, 2, 0xE9);

	////new addr for static array
	WriteInstruction(0x960509, (INT32) &CStaticObject::Code_960509, 2, 0xE9);
	WriteInstruction(0x7DF74C, (INT32) &CStaticObject::Code_7DF74C, 3, 0xE9);
	WriteInstruction(0x7E09A4, (INT32) &CStaticObject::Code_7E09A4, 3, 0xE9);
	WriteInstruction(0x7DFB2E, (INT32) &CStaticObject::Code_7DFB2E, 3, 0xE9);

	////new addr for index2 void array

	WriteInstruction(0x9604EE, (INT32) &CStaticObject::Code_9604EE, 2, 0xE9);
	WriteInstruction(0x7E096B, (INT32) &CStaticObject::Code_7E096B, 3, 0xE9);
	WriteInstruction(0x7DF73E, (INT32) &CStaticObject::Code_7DF73E, 3, 0xE9);
	WriteInstruction(0x7DFB1C, (INT32) &CStaticObject::Code_7DFB1C, 4, 0xE9);

	////new buffer
	//memset(g_StaticObject.pStaticObj, 0, 0xEA60);
	//WriteRelativeAddress(0x960498, 3, &g_StaticObject.pStaticObj+0x3F8, 0);
	//WriteRelativeAddress(0x9604FD, 3, &g_StaticObject.pStaticObj, 0);
	//WriteRelativeAddress(0x7E15F3, 3, &g_StaticObject.pStaticObj, 0);
	//WriteRelativeAddress(0x7E0F55, 3, &g_StaticObject.pStaticObj, 0);
	//WriteRelativeAddress(0x7E0DBC, 3, &g_StaticObject.pStaticObj, 0);
	//WriteRelativeAddress(0x971217, 3, &g_StaticObject.pStaticObj+8, 0);
	//WriteRelativeAddress(0x624C51, 3, &g_StaticObject.pStaticObj+8, 0);
	//WriteRelativeAddress(0x624C5B, 3, &g_StaticObject.pStaticObj, 0);

	//WriteMemoryDWORD(0x9604AB, INDEXDOOR*4);
	//WriteMemoryDWORD(0x7E13DA, INDEXDOOR);

	//WriteMemoryDWORD(0x40357B, 0x3e8*4);
	//WriteMemoryDWORD(0xBF7218, 0xBB8*4);
}

//void FindObjectSize()
//{
//	CHAR Addr[256];
//	DWORD byteread;
//	INT32 nValue32;
//	const INT32 nAddress = 0x401000;
//	INT32 nPoint;
//	INT32 nLen;
//	HANDLE hReport = CreateFileA("ArrayObject4.txt", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
//
//	for(INT32 i=0; i < (0x973000 - nAddress); i++)
//	{
//		ReadMemoryDWORD(nAddress+i, &nValue32);
//		switch(nValue32)
//		{
//		case 0x042C1DE0:
//			ReadMemoryDWORD(nAddress+i, &nValue32);
//			SetFilePointer(hReport,0,NULL,FILE_END);
//			nPoint = (INT32)nAddress+i;
//			nLen = sprintf(Addr, "\tWriteRelativeAddress(0x%x, 0, &g_StaticObject.pObj-0x400000, 0);\r\n", nPoint);				
//			WriteFile(hReport,Addr,nLen,&byteread,NULL);
//			break;
//		default:
//			break;
//		}
//	}
//	CloseHandle(hReport);
//}
