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

#include "Global.h"

class CObject;
class CCreature;
class CCubicInfo;
class CSkillInfo;
class CSkillAction2;

class CBaseSkillEffect : public L2ServerObject
{
protected:

	__int64 i08;

public:

	enum ModifierType { modify_per = 0, modify_diff = 1 };

	/* 00h */  virtual void CalcSuccess(CCreature* pCaster, CObject* pTarget, CSkillInfo* pSkillInfo, CSkillAction2* pAction) { return; }
	/* 08h */  virtual void Instant(CCreature* pCaster, CObject* pTarget, CSkillInfo* pSkillInfo, CSkillAction2* pAction, double fDistance) { return; }
	/* 10h */  virtual void CubicInstant(CCreature* pCaster, CObject* pTarget, CSkillInfo* pSkillInfo, CCubicInfo* pCubicInfo) { return; }
	/* 18h */  virtual void Tick(CObject* pTarget, double xmm2, int r9d) { return; }
	/* 20h */  virtual double UnkParam() { return 0.0; }
	/* 28h */  virtual bool CheckPumpCondition(CObject* pTarget) { return true; }
	/* 30h */  virtual void Pump(CObject* pTarget, CSkillInfo* pSkillInfo) { return; }
	/* 38h */  virtual bool Consume(CObject* pTarget, double xmm2) { return true; }
	/* 40h */  virtual bool CheckResisted(int edx, double xmm2, int r9d, ...); // in CBaseSkillEffect.asm
};
