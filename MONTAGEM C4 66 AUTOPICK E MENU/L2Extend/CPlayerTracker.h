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

class CObjectEx;
/*
// Making sure all the comparisons takes non case sensitive words
struct __widestring_lower_case_comparator
{
   bool operator() (const std::wstring& a, const std::wstring& b) const
   {
      return (wcsicmp (a.c_str ( ), b.c_str ( )) < 0);
   }
};
*/
class CPlayerTracker
{
	public:

		/* Static Initialization */
		static void Initialize();

		/* Static Methods */
		static void AddPlayer(User *pUser);
		static void DelPlayer(User *pUser);
		static CObjectEx *GetUserByName(wstring sPlayerName);
		static CObjectEx *GetUserByDBID(int nDBID);
		static CObjectEx *GetUserBySID(int nSID);

		/* Constructor */
		CPlayerTracker();

		/* Destructor */
		~CPlayerTracker();

		/* Variables */

		CRITICAL_SECTION USERDATA_LOCK;
		map<wstring, CObjectEx *, __widestring_lower_case_comparator> m_PlayerMapByString;
		map<int, CObjectEx *> m_PlayerMapByDBID;
		map<int, CObjectEx *> m_PlayerMapBySID;
};