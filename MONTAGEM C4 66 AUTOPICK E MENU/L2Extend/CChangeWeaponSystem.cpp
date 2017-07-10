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

#include <sstream>
#include <fstream>
#include "CChangeWeaponSystem.h"
#include "CDB.h"
#include "CItem.h"
#include "User.h"

static map<int, CChangeWeaponData *> m_ChangeWeaponData;

void CChangeWeaponSystem::InitializeAfterLoadage()
{
	CChangeWeaponSystem::LoadChangeWeaponData();
}

CChangeWeaponData::CChangeWeaponData()
{
	old_weapon_id = 0;
	new_weapon_id = 0;
}

void CChangeWeaponSystem::LoadChangeWeaponData()
{
	string fileName = "..\\script\\change_weapon_data.txt";

	ifstream file;
	file.open(fileName.c_str());

	if (file)
	{
		CLog::Add(CLog::black, "Loading Change Weapon Data");

		string lineread;
		while(getline(file, lineread))
		{
			stringstream ss(lineread);
			CChangeWeaponData *changeWeaponData = new CChangeWeaponData();

			while (!ss.eof())
			{
				string data;
				ss >> data;		

				if (data.size() == 0)
					break;

				if (data.find("old_weapon_id=") != string::npos)
				{
					changeWeaponData->old_weapon_id = atoi(data.substr(14, data.size() - 14).c_str());
				}
				else if (data.find("new_weapon_id=") != string::npos)
				{
					changeWeaponData->new_weapon_id = atoi(data.substr(14, data.size() - 14).c_str());
				}
				else
				{
					CLog::Add(CLog::red, "Unknown information in change_weapon_data.txt: '%s'", data.c_str());
				}
			}

			m_ChangeWeaponData[changeWeaponData->old_weapon_id] = changeWeaponData;
		}
	}

	file.close();
}

void CChangeWeaponSystem::CheckWeaponId(User* pUser, CItem* pItem, int nItemIndex)
{
	for(map<int, CChangeWeaponData *>::iterator Iter = m_ChangeWeaponData.begin(); Iter!=m_ChangeWeaponData.end(); Iter++)
	{
		CChangeWeaponData *pChangeWeaponData = Iter->second;
		if(pChangeWeaponData)
		{
			if(pChangeWeaponData->old_weapon_id == nItemIndex)
			{
				pUser->UnequipItem(7);
				int ench = pItem->SD->enchant;
				CDB::RequestDestroyItem(pItem, 1, pUser);
				pUser->AddItemToInventory(pChangeWeaponData->new_weapon_id, 1, ench);
			}
		}
	}
}
