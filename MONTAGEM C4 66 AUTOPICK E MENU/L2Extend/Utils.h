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
#include <cstdarg>
#include <string>
#include <vector>

using namespace std;

__int64 Assemble(char *buf, int bufLen, char *format, ...);
char *StrNChr(char *str, char c, int len);
int WcsNLen(char *str, int len);
char *Disassemble(char* packet, char* format, ...);
void DisassembleVA(const char* format, va_list sourceva, ...);
__int64 VAssemble(char* buf, int bufLen, char* format, va_list ap);
unsigned short GETPACKETLENGHT(char *pPacket);
string GetServerTime();
string U2A(wstring str);
wstring A2U(string str);
bool CopyVMT(LPVOID *dst, LPVOID *src, size_t num);
vector <string> Split( string _separator, string _string );
vector <wstring> Split( wstring _separator, wstring _string );
void trim( std::wstring& s );
void trim( std::string& s );


/*
	To check that your data types have exactly the desired size, use the
	CompileTimeSizeCheck macro. You can place it in a static function
	that's never called, because the macro doesn't actually do anything.

		static void CompileTimeChecks()
		{
			CompileTimeSizeCheck(MyFiftyByteStruct, 50);
		}

	If the actual size doesn't match the desired value, the compiler will
	complain about undefined base class TypeSizeCheck - don't be confused,
	it's just a trick. The name of the broken type, it's size, and the
	desired size, will also appear in the message as template parameters.
*/

// intentionally undefined to catch 'sizeof' errors
template <typename Type, int Size, int RequiredSize>
struct TypeSizeCheck;

// specialization for correct 'sizeof' == desired size combinations
template <typename Type, int Size>
struct TypeSizeCheck<Type, Size, Size>
{};

#define UniqueSizeCheckName2(c) TypeSizeCheck__##c
#define UniqueSizeCheckName1(c) UniqueSizeCheckName2(c)
#define UniqueSizeCheckName     UniqueSizeCheckName1(__COUNTER__)

#define CompileTimeSizeCheck(Type, Size) \
	struct UniqueSizeCheckName : TypeSizeCheck<Type, sizeof(Type), Size> \
	{} // semicolon required after expansion


/*
	Similar to the above, CompileTimeOffsetCheck validates that
	offsetof(Type, Member) has the desired value. The macro expands to
	a class definition which, if the Member's offset in Type is wrong,
	fails to compile. Example:

		CompileTimeOffsetCheck(CParserForSkill, lexer, 0x150);
*/

// intentionally undefined to catch 'offsetof' errors
template <typename Type, typename Member, int Offset, int RequiredOffset>
struct MemberOffsetCheck;

// specialization for correct 'offsetof' == desired offset combinations
template <typename Type, typename Member, int Offset>
struct MemberOffsetCheck<Type, Member, Offset, Offset>
{};

#define CompileTimeOffsetCheck(Type, Member, Offset) \
	typedef size_t Type##__##Member##__; /* member name in error message */ \
	struct Type##__##Member##__OffsetCheck : \
	MemberOffsetCheck<Type, Type##__##Member##__, offsetof(Type, Member), Offset> \
	{} // semicolon required after expansion

// Making sure all the comparisons takes non case sensitive words for string in map CPlayerTracker, CPledge and so on.
struct __widestring_lower_case_comparator
{
   bool operator() (const std::wstring& a, const std::wstring& b) const
   {
      return (_wcsicmp (a.c_str ( ), b.c_str ( )) < 0);
   }
};
