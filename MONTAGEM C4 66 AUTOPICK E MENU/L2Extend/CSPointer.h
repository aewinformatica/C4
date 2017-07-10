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
*/

#pragma once

#include "MemoryObject.h"
#include <algorithm>

struct CSPointerBase
{
	MemoryObject* pObject;
	int           nWorkType;
};

template <typename T>
class CSPointer : public CSPointerBase
{
public:

	explicit CSPointer(T* pObject = 0, int nWorkType = 0)
	{
		initialize(pObject, nWorkType);
	}

	CSPointer(const CSPointer<T>& other)
	{
		initialize(other.get(), other.getWorkType());
	}

	template <typename U>
	CSPointer(const CSPointer<U>& other)
	{
		initialize(other.get(), other.getWorkType());
	}

	~CSPointer()
	{
		if (this->pObject)
		{
			this->pObject->Release(__FILE__, __LINE__, this->nWorkType, false);
			this->pObject = 0;
		}
	}

	T* get() const
	{
		return static_cast<T*>(this->pObject);
	}

	int getWorkType() const
	{
		return nWorkType;
	}

	void swap(CSPointer<T>& other)
	{
		std::swap(this->pObject, other.pObject);
		std::swap(this->nWorkType, other.nWorkType);
	}

	CSPointer<T>& operator= (const CSPointer<T>& other)
	{
		swap(CSPointer<T>(other));
		return *this;
	}

	template <typename U>
	CSPointer<T>& operator= (const CSPointer<U>& other)
	{
		swap(CSPointer<T>(other));
		return *this;
	}

	T& operator* () const
	{
		if (get() == 0)
		{
			CLog::Add(CLog::red, "[%s:%d] referencing NULL object", __FILE__, __LINE__);
			CLog::StackTrace(CLog::red);
		}
		return *get();
	}

	T* operator-> () const
	{
		if (get() == 0)
		{
			CLog::Add(CLog::red, "[%s:%d] referencing NULL object", __FILE__, __LINE__);
			CLog::StackTrace(CLog::red);
		}
		return get();
	}

	operator T* () const
	{
		return get();
	}

private:

	void initialize(T* pObject, int nWorkType)
	{
		if (pObject == 0)
		{
			this->pObject = 0;
			this->nWorkType = nWorkType;
		}
		else
		{
			this->pObject = pObject->AddRef(__FILE__, __LINE__, nWorkType);
			this->nWorkType = nWorkType;
		}
	}
};
