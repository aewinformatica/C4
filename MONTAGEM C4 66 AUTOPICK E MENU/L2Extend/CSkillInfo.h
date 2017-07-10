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

#include "CBaseSkillEffect.h"
#include "CBaseOperateCondition.h"
#include "CSkillAction2.h"
#include "CSkillKey.h"
#include "script/skilldata.h"

class CCreature;
class CBaseSkillEffect;
class CBaseOperateCondition;
class CSkillInfo;

typedef std::vector<CBaseSkillEffect *> CSkillEffectList;
typedef std::vector<CBaseOperateCondition *> CSkillOpCondList;
 
enum SkillOpType
{
        SKILL_OP_TYPE_A1 = 0,
        SKILL_OP_TYPE_A2 = 1,
        SKILL_OP_TYPE_A3 = 2,
        SKILL_OP_TYPE_A4 = 3,
        SKILL_OP_TYPE_P = 4,
        SKILL_OP_TYPE_T = 5,
        SKILL_OP_TYPE_PP = 6
};
 
enum SkillBasePropery
{
        SKILL_BASE_PROP_STR = 1,
        SKILL_BASE_PROP_DEX = 2,
        SKILL_BASE_PROP_CON = 3,
        SKILL_BASE_PROP_INT = 4,
        SKILL_BASE_PROP_MEN = 5,
        SKILL_BASE_PROP_WIT = 6,
        SKILL_BASE_PROP_NONE = 26
};

class CSkillInfo 
{
	public:

	/* 0x0000 */	wchar_t*			skill_name;
	/* 0x0008 */	int					skill_id;
	/* 0x000C */	int					level;
	/* 0x0010 */	int					magic_level;
	/* 0x0014 */	int					is_magic;		// case 8, values: 0,1,2
	/* 0x0018 */	int					has_i_energy_attack;
	/* 0x001C */	SkillOpType			op_type;
	/* 0x0020 */	int					dw20;
	/* 0x0024 */	int					mp_consume2;	// case 13
	/* 0x0028 */	int					dw28;			// case 14
	/* 0x002C */	int					dw2c;
	/* 0x0030 */	std::wstring		item_consume_name;	// case 15, sizeof = 0x28.
	/* 0x0058 */	int					dw58;	// case ???
	/* 0x005C */	int					item_consume_count;	// case 15, item consume?
	/* 0x0060 */	int					cast_range;
	/* 0x0064 */	int					effective_range;
	/* 0x0068 */	int					ary_dw_68[4];		// case 5
	/* 0x0078 */	double				skill_hit_time;
	/* 0x0080 */	double				skill_cool_time;
	/* 0x0088 */	double				skill_hit_cancel_time;
	/* 0x0090 */	double				reuse_delay; // sec*1000
	/* 0x0098 */	CSkillOpCondList	operate_cond_list;
	/* 0x00B8 */	double				lv_bonus_rate; // case 25
	/* 0x00C0 */	int					activate_rate;
	/* 0x00C4 */	SkillBasePropery	basic_property; // case 26
	/* 0x00C8 */	int					abnormal_time;
	/* 0x00CC */	int					abnormal_lv;
	/* 0x00D0 */	int					abnormal_type;
	/* 0x00D4 */	int					abnormal_visual_effect;
	/* 0x00D8 */	int					attribute;		// attr_earth=9 and so on...
	/* 0x00DC */	int					effect_point;
	/* 0x00E0 */	int					debuff;			// (1,2)
	/* 0x00E4 */	int					next_action;
	/* 0x00E8 */	int					next_action_is_fake_death; // bool 
	/* 0x00EC */	int					ride_state;		// bitfield
	/* 0x00F0 */	CBaseSkillEffect*	consume_effect; // not list!
	/* 0x00F8 */	CBaseSkillEffect*	tick_effect;	// not list!
	/* 0x0100 */	CSkillEffectList	pump_effect_list;
	/* 0x0120 */	CSkillEffectList	instant_effect_list;
	/* 0x0140 */	int					target_type;
	/* 0x0144 */	int					affect_scope;	 // affect_scope_stru item1
	/* 0x0148 */	int					dw148;			 // case 43
	/* 0x014C */	int					dw14C;			 // eq -1 if affect_scope==single (0)
	/* 0x0150 */	int					ary_dw150[2];	 // case 40,
	/* 0x0158 */	int					dw158;			 // case 42
	/* 0x015C */	int					affect_limit[2];
	/* 0x0164 */	int					dw164;

	// EXTENDED MEMBERS

	std::wstring        trigger_skill_name;
	CSkillInfo*         trigger_skill_info;
	int                 trigger_type;
	double              trigger_rate;

	// EXTENDED FUNCTIONS

	CSkillInfo* Construct();
	       void Destroy();
	static void extendClass();

	// THUNK FUNCTIONS

	void ActivateSkill(CCreature* pCaster, CObject* pTarget, double fDistance, CSkillAction2* pAction)
	{
		typedef void (*FActivateSkill)(CSkillInfo*, CCreature*, CObject*, double, CSkillAction2*);
		FActivateSkill(0x799000)(this, pCaster, pTarget, fDistance, pAction);
	}

	void AddInstantEffect(CBaseSkillEffect *pSkillEffect)
	{
		typedef void (*FPUSHBACK)(CSkillEffectList*, CBaseSkillEffect**);
		FPUSHBACK(0x7A1D60)(&this->instant_effect_list, &pSkillEffect);
	}

	void AddOperateCondition(CBaseOperateCondition *pOpCond)
	{
		typedef void (*FPUSHBACK)(CSkillOpCondList*, CBaseOperateCondition**);
		FPUSHBACK(0x9068A0)(&this->operate_cond_list, &pOpCond);
	}

	void AddPumpEffect(CBaseSkillEffect *pSkillEffect)
	{
		typedef void (*FPUSHBACK)(CSkillEffectList*, CBaseSkillEffect**);
		FPUSHBACK(0x7A1D60)(&this->pump_effect_list, &pSkillEffect);
	}
};
