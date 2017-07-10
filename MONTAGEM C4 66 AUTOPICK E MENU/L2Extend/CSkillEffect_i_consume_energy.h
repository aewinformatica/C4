#pragma once

#include "CBaseSkillEffect.h"

class CSkillEffect_i_consume_energy : public CBaseSkillEffect
{
	int nCharge;

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
	CSkillEffect_i_consume_energy(bool bInstallVMT);
	CSkillEffect_i_consume_energy(int arg1) { nCharge = arg1; };
};
