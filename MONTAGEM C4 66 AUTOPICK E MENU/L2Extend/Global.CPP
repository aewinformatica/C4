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

#include "Global.h"
#include "IniFile.h"

GlobalVars *pGVars = NULL;
extern "C" int nRevision = -1;
extern "C" int nRev = -1;

void GlobalVars::Initialize()
{
	pGVars = new GlobalVars();
	InitVars();
}

void GlobalVars::InitVars()
{
	// Initializing General Variables
	pGVars->pGeneral = new GeneralVars();
	pGVars->pSubSystems = new SubSystems();

	nRevision = atoi((pGVars->pGeneral->ProtocolVersion = CIniFile::GetValue("PROTOCOL VERSION","GENERAL","L2Extend.ini")).c_str());
	nRev = ((nRevision > 746) ? 0 : 1);
	pGVars->pGeneral->bJoinLeaveMod = CIniFile::GetIntValue("JOIN LEAVE MOD","MODS","L2Extend.ini") == 1 ? true : false;
	pGVars->pGeneral->nDeadlock = CIniFile::GetIntValue("DEADLOCK","GENERAL","L2Extend.ini");
	pGVars->pSubSystems->bDeathPenalty = CIniFile::GetIntValue("ENABLED","DEATH PENALTY","L2Extend.ini") == 1 ? true : false;
	pGVars->pSubSystems->nDeathPenaltySkillID = CIniFile::GetIntValue("SKILLID","DEATH PENALTY","L2Extend.ini");
	pGVars->pSubSystems->bBuffSystem = CIniFile::GetIntValue("ENABLED","ABNORMAL SYSTEM","L2Extend.ini") == 1 ? true : false;
	pGVars->pSubSystems->nBuffSlotSkillID = CIniFile::GetIntValue("SKILLID","ABNORMAL SYSTEM","L2Extend.ini");
	pGVars->pSubSystems->bEnableKamael = CIniFile::GetIntValue("ENABLED","KAMAEL RACE","L2Extend.ini") == 1 ? true : false;
	pGVars->pGeneral->Penaltyfix = CIniFile::GetIntValue("ENABLED","Penalty","L2Extend.ini") == 1 ? true : false;
}

GlobalVars *GlobalVars::GVs()
{
	return pGVars;
}