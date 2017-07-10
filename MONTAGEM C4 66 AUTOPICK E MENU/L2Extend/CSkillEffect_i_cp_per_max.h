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

#include "CBaseSkillEffect.h"

class CSkillEffect_i_cp_per_max : public CBaseSkillEffect
{
	// Parameters
	int nPer;
	

	public:
	
		virtual void CalcSuccess(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction) {};
		virtual void Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance);
		virtual void Unk() {};
		virtual void Tick() {};
		virtual double Unk2() { return 0.0; };
		virtual bool CheckPumpCondition(CObject* pTarget) { return true; };
		virtual void Pump(CObject* pTarget, CSkillInfo* pSkillInfo) {};
		virtual bool Consume(CCreature *pCreature, double param2) { return true; };
		virtual bool CheckResisted() { return false; };

		/* Extended VMT */
		CSkillEffect_i_cp_per_max(bool bInstallVMT);
		CSkillEffect_i_cp_per_max(int arg1) { nPer = arg1; };
};