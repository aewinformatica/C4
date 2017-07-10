#include "CSkillEffect_i_consume_energy.h"
#include "CStatusUpdate.h"
#include "User.h"



int CSkillEffect_i_consume_energyInstant = 0;
void CSkillEffect_i_consume_energy::Instant(CCreature *pSkillUser, CObject *pTarget, CSkillInfo *pSkillInfo, CSkillAction2 *pAction, double distance)
{
	L2SERVER_SHARED_GUARD(CSkillEffect_i_consume_energyInstant);
	TLS_TRACE_BEGIN;
	if(pSkillUser->IsValidUser())
	{
		User *pUser = (User *)pSkillUser;

		if(pUser->nCharges < nCharge)
		{
			
		}
		else
		{
			pUser->nCharges -= nCharge;
		}
	}
	TLS_TRACE_END;
}
