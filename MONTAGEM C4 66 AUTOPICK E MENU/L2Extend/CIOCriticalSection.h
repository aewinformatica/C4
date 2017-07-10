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

#include <windows.h>

class CIOCriticalSection
{
public:

	/* 0000 */  CRITICAL_SECTION cs;
	/* 0028 */  BYTE flag;
	/* 0029 */  BYTE _padding[7];

	void Lock(const WCHAR* wszFile, int nLine)
	{
		typedef void (*FxLock)(void*, const WCHAR*, int);
		FxLock(0x627D10L)(this, wszFile, nLine);
	}

	void Unlock(const WCHAR* wszFile, int nLine)
	{
		typedef void (*FxUnlock)(void*, const WCHAR*, int);
		FxUnlock(0x628010L)(this, wszFile, nLine);
	}

	class AutoLock
	{
	private:

		CIOCriticalSection&  m_cs;
		int                  m_lockCount;
		const WCHAR* const   m_file;
		int const            m_line;

	public:

		AutoLock(const AutoLock& other); // intentionally undefined

		AutoLock(CIOCriticalSection& cs, const WCHAR* file, int line)
			: m_cs(cs), m_lockCount(0), m_file(file), m_line(line)
		{}

		~AutoLock()
		{
			while (m_lockCount > 0)
				this->Unlock();
		}

		void Lock(const WCHAR* file = 0, int line = 0)
		{
			m_cs.Lock(file ? file : m_file, line ? line : m_line);
			m_lockCount++;
		}

		// can be used to unlock before the object goes out of scope
		void Unlock(const WCHAR* file = 0, int line = 0)
		{
			m_cs.Unlock(file ? file : m_file, line ? line : m_line);
			m_lockCount--;
		}
	};
};

#define L2EXTEND_AUTOLOCK_OBJ(name) _autoLock_ ## name

#define L2EXTEND_AUTOLOCK(name, refCS, bLock)                   \
	CIOCriticalSection::AutoLock L2EXTEND_AUTOLOCK_OBJ(name)    \
		(refCS, __FILEW__, __LINE__);                           \
	do if (bLock)                                               \
		L2EXTEND_AUTOLOCK_OBJ(name).Lock(__FILEW__, __LINE__);  \
	while (0)

#define L2EXTEND_LOCK(name)                                     \
	static_cast<CIOCriticalSection::AutoLock&>                  \
	(L2EXTEND_AUTOLOCK_OBJ(name)).Lock(__FILEW__, __LINE__)

#define L2EXTEND_UNLOCK(name)                                   \
	static_cast<CIOCriticalSection::AutoLock&>                  \
	(L2EXTEND_AUTOLOCK_OBJ(name)).Unlock(__FILEW__, __LINE__)
