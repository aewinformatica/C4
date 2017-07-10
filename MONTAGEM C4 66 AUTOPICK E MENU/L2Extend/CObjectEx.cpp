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

#include "CObjectEx.h"
//#include "CCursedWeapons.h"
//#include "CHerbSystem.h"
#include "CSkillMod.h"

CObjectEx::CObjectEx(CCreature *pCreature)
{
	this->pCreature = pCreature;
	this->pSkillMods = new CSkillMod(pCreature);
	this->pSummonInfo = new SummonInfo();
	this->pAgathionInfo = new AgathionInfo();
	this->pTransInfo = new TransformationInfo();
	//this->pHerbalInfo = new HerbalInfo();
	this->pGeneralInfo = new GeneralInfo();
//	this->pCWI = new CursedWeaponInfo();

	this->pSummonInfo->nSummonerSID = 0;
	this->pSummonInfo->nSummonX = 0;
	this->pSummonInfo->nSummonY = 0;
	this->pSummonInfo->nSummonZ = 0;

	this->pTransInfo->nTransID = 0;
	this->pTransInfo->nTransTime = 0;
	this->pTransInfo->bTransformed = false;

	this->pAgathionInfo->nAgathionID = 0;
}

CObjectEx::~CObjectEx()
{
	this->pCreature = NULL;
	//delete this->pSkillMods;
	delete this->pSummonInfo;
	delete this->pAgathionInfo;
	delete this->pTransInfo;
	//delete this->pHerbalInfo;
	delete this->pGeneralInfo;
	//delete this->pCWI;
}