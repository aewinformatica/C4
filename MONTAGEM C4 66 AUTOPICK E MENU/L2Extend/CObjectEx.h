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

class CCreature;
class User;
//class CTransformation;
class CSkillMod;
//class HerbalInfo;
//class CursedWeaponInfo;

struct GeneralInfo
{
	CCreature *pLastTalked;
	CCreature *pLastKiller; //WAGNER 2014
	int nSoulCount;
};

struct SummonInfo
{
	int nSummonX;		//Summon frined/chant gate part
	int nSummonY;
	int nSummonZ;
	int nSummonerSID;
};

struct AgathionInfo
{
	INT32 nAgathionID;
};

struct TransformationInfo
{
	time_t nTransTime;
	INT32 nTransID;
	bool  bTransformed;
};

class CObjectEx
{
	public:

		/* Constructor */
		CObjectEx(CCreature *pCreature);

		/* Destructor */
		~CObjectEx();

		CCreature *pCreature;

		User *pUser;

		SummonInfo *pSummonInfo;

		CSkillMod *pSkillMods;

		AgathionInfo *pAgathionInfo;

		TransformationInfo *pTransInfo;

		//HerbalInfo *pHerbalInfo;

		GeneralInfo *pGeneralInfo;

		//CursedWeaponInfo *pCWI;
};