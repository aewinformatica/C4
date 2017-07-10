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

/* Implementation/Information Credits goes to WFX @ PostPacific */

#include "CParserForSkill.h"
#include "CSkillDB.h"
#include "CSkillInfo.h"
#include "PchFile.h"
#include <fstream>

// Skill Effects
#include "CSkillEffect_i_transform.h"
#include "CSkillEffect_i_summon_friend.h"
#include "CSkillEffect_i_rush.h"
#include "CSkillEffect_i_augment.h"
#include "CSkillEffect_i_erase.h"
#include "CSkillEffect_i_target_cancel_chance.h"
#include "CSkillEffect_i_remove_death_penalty.h"
#include "CSkillEffect_i_summon_agathion.h"
#include "CSkillEffect_i_death.h"
#include "CSkillEffect_i_mana_burn.h"
#include "CSkillEffect_i_target_me_chance.h"
#include "CSkillEffect_i_change_weapon.h"
#include "CSkillEffect_i_consume_souls.h"
#include "CSkillEffect_i_life_to_soul.h"
#include "CSkillEffect_i_soul_gathering.h"
#include "CSkillEffect_i_transfer_soul.h"
#include "CSkillEffect_p_block_icon_action.h"
#include "CSkillEffect_p_disarm.h"
#include "CSkillEffect_p_modify_by_weapon.h"
#include "CSkillEffect_p_modify_by_weapon_hp.h"
#include "CSkillEffect_p_charm_of_courage.h"
#include "CSkillEffect_i_cp_per_max.h"
#include "CSkillEffect_i_consume_energy.h"
#include "CSkillEffect_i_blink.h"
#include "CSkillEffect_i_shadow_step.h"
#include "CSkillEffect_i_acquire_skill.h"

// Operate Conditions
#include "COPCondition_can_summon_friend.h"
#include "COPCondition_remain_mp_per.h"
#include "COPCondition_remain_cp_per.h"
#include "COPCondition_has_souls.h"
#include "COPCondition_check_cast_range.h"
#include "COPCondition_have_abnormal.h"
#include "COPCondition_have_abnormal_level.h"
#include "COPCondition_target_class.h"
#include "COPCondition_target_not_class.h"
#include "COPCondition_on_siege.h"
#include "COPCondition_target_not_boss.h"
#include "COPCondition_have_abnormal_block_cast.h"

static bool bFoundSkill = false;
static bool bPrintActions = false;

//--------------------------------------------

CLexerForSkill::CLexerForSkill(bool bFakeInstance)
{
        static bool _init_done = false;
        if (! _init_done) {
            _init_done = true;
			LPVOID *org_vmt = (LPVOID*)0x00ABDF18; // real VMT address
            LPVOID* my_vmt = *(LPVOID**)this;
			CopyVMT(&org_vmt[9], &my_vmt[9], 1); // yyaction()
		}
}

CParserForSkill::CParserForSkill(bool bFakeInstance)
{
	    static bool _init_done = false;
        if (! _init_done) {
            _init_done = true;
			LPVOID *org_vmt = (LPVOID*)0xAE2538; // real VMT address
            LPVOID* my_vmt = *(LPVOID**)this;
			CopyVMT(&org_vmt[1], &my_vmt[1], 1); // yyaction()
		}
}

typedef std::map<std::wstring, int> AbnormalTypesMap;

static int subst_yyaction = 0;
static map<wstring, int>	t_map; // map of words and their tokens
static int				t_map_reqs = 0;
static CSkillExtTokenMap g_extTokenMap;
static std::vector<CSkillInfo*> g_triggerSkills;
static AbnormalTypesMap g_abnormalTypes;

extern "C"
{
	int CParserForSkill_FindAbnormalType(CParserForSkill* parser, const char* effect, const wchar_t* slotname)
	{
		AbnormalTypesMap::const_iterator it = g_abnormalTypes.find(slotname);
		if (it != g_abnormalTypes.end())
			return it->second;

		CLog::Add(CLog::red, "[%ls] unknown abnormal type '%ls' in effect {%s}",
			parser->pSkillInfo->skill_name, slotname, effect);
		return -1;
	}

	// in CParserForSkill.asm
	void CSkillEffect_i_abnormal_time_change__ctor(void);
	void CSkillEffect_i_dispel_by_slot__ctor(void);
	void CSkillEffect_i_dispel_by_slot_probability__ctor(void);
}

static int CParserForSkill_create(CParserForSkill* pParser)
{
	PchFile manual_pch;

	CLog::Add(CLog::black, "  loading manual_pch.txt"); // intentionally indented
	manual_pch.LoadUnicode("../Script/manual_pch.txt");

	for (PchFile::map_iterator it = manual_pch.map.begin(); it != manual_pch.map.end(); ++it)
	{
		// abnormal types have a prefix in manual_pch.txt, but not in skilldata.txt
		if (it->first.find(L"ab_") == 0)
			g_abnormalTypes[it->first.substr(3)] = it->second;
	}

	CLog::Add(CLog::black, "  %d abnormal types found", g_abnormalTypes.size());

	// In the original C4 skill parser, abnormal types 'none' and 'gara'
	// both have code 135 (see loc_8F0AEC). But manual_pch.txt usually
	// defines [ab_none] = -1, and L2ScriptMaker's PCH generator has this
	// value hardcoded, so even if you change it, you'll still get -1 in
	// skill_pch2.txt. That's why we hardcode skill parser's value here.
	g_abnormalTypes[L"none"] = manual_pch.Get(L"gara", 135);

	// call original function
	typedef int (*Fyycreate)(CParserForSkill*);
	return Fyycreate(0x8ED570)(pParser);
}

static void CParserForSkill_destructor(CParserForSkill *pParser)
{
	typedef void (*t)(CParserForSkill *p);
	t f = (t)0x08EDC50;
	f(pParser);

	// pSkillInfo->trigger_skill_info cannot be setup at the time
	// the passive skill is defined, because the triggered skill's
	// definition might come later. We'll find the skills now.

	for (size_t i = 0; i < g_triggerSkills.size(); ++i)
	{
		CSkillInfo* pPassiveInfo = g_triggerSkills[i];
		CSkillInfo* pActiveInfo = 0;

		if (pPassiveInfo->trigger_skill_name != L"none")
		{
			pActiveInfo = CSkillDB::GetSkillInfo(pPassiveInfo->trigger_skill_name.c_str());
		}

		pPassiveInfo->trigger_skill_info = pActiveInfo;
	}
	g_triggerSkills.clear();

	// dump found tokens
	if (t_map_reqs > 0)
	{
		int tok_cnt = 0;
		//--- Write the count and the word.
		wofstream tout(L"skillparser.txt", ios_base::out);
		map<wstring, int>::const_iterator iter;
		for (iter=t_map.begin(); iter != t_map.end(); ++iter) {
			tout << iter->second << L" " << iter->first << L"\n";
			++tok_cnt;
		}
		tout.close();
		CLog::Add(CLog::blue, "Flushed skilldata token map(t_map_reqs %d)(tok_cnt %d)", t_map_reqs, tok_cnt);
	}
}

yywint_t CLexerForSkill::yyaction(int action)
{
	typedef yywint_t(*t)(CLexerForSkill*, int);
	t f = (t)0x08D95E0;
	yywint_t  token = f(this, action);
	
	if (token == T_ID) 
	{
		YYSTYPE& yylval = *(YYSTYPE*)yyparserptr->yylvalptr;
		
		// CLog::Add(CLog::blue, "%ls -> pSkillInfo = %p", yylval.id_value, ((CParserForSkill *)yyparserptr)->pSkillInfo);

		CLexerForSkill::TokenType nSubstToken;
		CParserForSkill::SubstActionType nSubstAction;

		if (g_extTokenMap.find(yylval.id_value, &nSubstToken, &nSubstAction))
		{
			token = nSubstToken;
			subst_yyaction = nSubstAction;
		}
	}
	else if (token == i_death)
	{
		CParserForSkill* pParser = static_cast<CParserForSkill*>(yyparserptr);
		CLog::Add(CLog::red, "[%ls] {i_death;a} is deprecated, use {i_death2;a;b} instead",
			pParser->pSkillInfo->skill_name);
	}

	/* DONT REMOVE THIS EVEN IF ITS COMMENTED !!!! */
	// Uncomment to find a skill action id for parser ! :)
	//wstring cSkillName = L"i_p_attack_over_hit";
	//if ( wcsncmp(cSkillName.c_str(), this->yytext, cSkillName.size()) == 0 )
	//{
	//	CLog::Add(CLog::blue, "Found the String on SkillData... Looking Up the Action ID !");
	//	bFoundSkill = true;
	//}

	return token;

/* DONT REMOVE THIS EVEN IF ITS COMMENTED !!!!
	typedef yywint_t(*t)(CLexerForSkill*, int);
	t f = (t)0x08D95E0;
	yywint_t  token = f(this, action);

	switch(action) {
		case 401: // T_ID
		case 402: // T_ID
		case 403: // T_NUM
		case 404: // pass token
		case 405: // PD_WORD
		case 406: // T_ID
		case 409: // inv char
		case 3:
		case 4:
		case 407: // eat token
			break;
		default:
			// log it
			if (this->yytext[0] != '/') {
				wstring s(this->yytext, this->yyleng);
				t_map[s] = token;
				++t_map_reqs;
			}
			;
	}
	return token;
*/
}



//--------------------------------------------------
void CParserForSkill::yyaction(int action)
{
	///* DONT REMOVE THIS EVEN IF ITS COMMENTED !!!! */
	// Uncomment to find a skill action id for parser ! :)
	//if ( bFoundSkill )
	//{
	//	CLog::Add(CLog::blue, "And the Action ID is : %d !!!", action);
	//	bFoundSkill = false;
	//	Sleep(10000);
	//}

	if (bPrintActions)
	{
		CLog::Add(CLog::black, "  action=%-4d subst=%d", action, subst_yyaction);
	}

	if (ExtendedAction(action, subst_yyaction))
	{
		// extended action was performed, clear it
		subst_yyaction = 0;
	}
	else if (action == ABNORMAL_TYPE)
	{
		// search extended abnormal types
		const wchar_t* arg1 = yyattribute(0).id_value;
		AbnormalTypesMap::const_iterator it = g_abnormalTypes.find(arg1);

		if (it != g_abnormalTypes.end())
		{
			this->pSkillInfo->abnormal_type = it->second;
		}
		else
		{
			this->pSkillInfo->abnormal_type = -1;
			CLog::Add(CLog::red, "[%ls] unknown abnormal_type=%ls",
				this->pSkillInfo->skill_name, arg1);
		}
	}
	else
	{
		// no extended action, call the original one
		typedef void(*Fyyaction)(CParserForSkill*, int);
		Fyyaction(0x08EF6F0)(this, action);

		if (bPrintActions && action == SKILL_NAME)
		{
			CLog::Add(CLog::black, "skill_name=[%ls]", this->pSkillInfo->skill_name);
		}
	}
}

bool CParserForSkill::ExtendedAction(int nAction, int nSubstAction)
{
	#define DEFAULT_SUBST_ACTION \
		default: \
			CLog::Add(CLog::red, "[%ls] invalid subst_action %d for action %d", \
				this->pSkillInfo->skill_name, nSubstAction, nAction); \
			break

	#define MODIFY(Action, ModType) (((Action) << 1) | ((ModType) & 1))
	#define DIFF(Action) MODIFY((Action), CBaseSkillEffect::modify_diff)
	#define PER(Action) MODIFY((Action), CBaseSkillEffect::modify_per)

	CompileTimeSizeCheck(YYSTYPE, 8);

	if (nSubstAction == 0)
	{
		return false;
	}

	// Every action in this switch is assumed to be substituted with
	// an extended action. That means the return value will be true if
	// nAction is found, even if nSubstAction isn't found in the inner
	// switch - which should not happen, and will be reported.

	switch(nAction)
	{
		default: return false;

		case SKILL_NAME: // skill_name=[<wstring>]
			{
				const wchar_t* arg1 = yyattribute(0).id_value;

				switch (nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case TRIGGER_SKILL:
						this->pSkillInfo->trigger_skill_name = arg1;
						g_triggerSkills.push_back(this->pSkillInfo);
						break;
				}
			}
			break;

		case OPERATE_TYPE: // operate_type=<wstring>
			{
				const wchar_t* arg1 = yyattribute(0).id_value;

				switch (nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case TRIGGER_TYPE:
						if (wcscmp(arg1, L"counter") == 0)
							this->pSkillInfo->trigger_type |= Script::trigger_type::counter;
						else if (wcscmp(arg1, L"chance") == 0)
							this->pSkillInfo->trigger_type |= Script::trigger_type::chance;
						else if (wcscmp(arg1, L"physical_attack") == 0)
							this->pSkillInfo->trigger_type |= Script::trigger_type::physical_attack;
						else if (wcscmp(arg1, L"critical_attack") == 0)
							this->pSkillInfo->trigger_type |= Script::trigger_type::critical_attack;
						else if (wcscmp(arg1, L"magical_attack") == 0)
							this->pSkillInfo->trigger_type |= Script::trigger_type::magical_attack;
						else
							CLog::Add(CLog::red, "[%ls] invalid trigger_type=%ls",
								this->pSkillInfo->skill_name, arg1);
						break;
				}
			}
			break;

		case REUSE_DELAY: // reuse_delay=<double>
			{
				double arg1 = yyattribute(0).num_value;

				switch (nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case TRIGGER_RATE:
						this->pSkillInfo->trigger_rate = arg1;
						break;
				}
			}
			break;

		case OP_REMAIN_HP_PER: // operate_cond={{remain_hp_per;<!-- arg1 int -->}}
			{
				int  arg1 = yyattribute(0).int_value;

				switch(nSubstAction)
				{
					DEFAULT_SUBST_ACTION;

					case OP_REMAIN_MP_PER:
						this->pSkillInfo->AddOperateCondition(new COPCondition_remain_mp_per(arg1));
						break;

					case OP_REMAIN_CP_PER:
						this->pSkillInfo->AddOperateCondition(new COPCondition_remain_cp_per(arg1));
						break;	
				}
			}
			break;

		case OP_CHECK_LEVEL: // operate_cond={{check_level;<arg1 int>, <arg2 int>}}
			{
				int  arg1 = yyattribute(-2).int_value;
				int  arg2 = yyattribute(0).int_value;

				switch(nSubstAction)
					{
					DEFAULT_SUBST_ACTION;
				
					case OP_HAVE_ABNORMAL_LEVEL:
						this->pSkillInfo->AddOperateCondition(new COPCondition_have_abnormal_level(arg1,arg2));
						break;
						
					}
			}
			break;

		case OP_ENERGY_SAVED: // operate_cond={{energy_saved;<!-- arg1 int -->}}
			{
				int  arg1 = yyattribute(0).int_value;

				switch(nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case OP_HAS_SOULS:
						this->pSkillInfo->AddOperateCondition(new COPCondition_has_souls(arg1));
						break;
					case OP_CHECK_CAST_RANGE:
						this->pSkillInfo->AddOperateCondition(new COPCondition_check_cast_range(arg1));
						break;
					case OP_HAVE_ABNORMAL:
						this->pSkillInfo->AddOperateCondition(new COPCondition_have_abnormal(arg1));
						break;
					case OP_TARGET_CLASS:
						this->pSkillInfo->AddOperateCondition(new COPCondition_target_class(arg1));
						break;
					case OP_TARGET_NOT_CLASS:
						this->pSkillInfo->AddOperateCondition(new COPCondition_target_not_class(arg1));
						break;
					case OP_HAVE_ABNORMAL_BLOCK_CAST:
						this->pSkillInfo->AddOperateCondition(new COPCondition_have_abnormal_block_cast(arg1));
						break;
				}
			}
			break;

		case OP_CAN_SUMMON: // operate_cond={{can_summon}}
			{
				switch(nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case OP_CAN_SUMMON_FRIEND:
						this->pSkillInfo->AddOperateCondition(new COPCondition_can_summon_friend());
						break;
					case OP_ON_SIEGE:
						this->pSkillInfo->AddOperateCondition(new COPCondition_on_siege());
						break;
					case OP_TARGET_NOT_BOSS:
						this->pSkillInfo->AddOperateCondition(new COPCondition_target_not_boss());
						break;
				}
			}
			break;

		case I_HP_DRAIN: // {i_hp_drain;<double>;<double>}
			{
				double arg1 = yyattribute(-2).num_value;
				double arg2 = yyattribute(-0).num_value;

				switch (nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case I_DEATH2:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_death(arg1, arg2));
						break;
					case I_BLINK:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_blink(arg1, arg2));
						break;
				}
			}
			break;

		case I_MP_BY_LEVEL: // i_mp_by_level <!-- arg1 int -->
			{
				int  arg1 = yyattribute(0).int_value;

				switch(nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case I_TRANSFORM:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_transform(arg1));
						break;
					case I_SUMMON_FRIEND:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_summon_friend(arg1));
						break;
					case I_RUSH:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_rush(arg1));
						break;
					case I_ERASE:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_erase(arg1));
						break;
					case I_TARGET_CANCEL_CHANCE:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_target_cancel_chance(arg1));
						break;
					case I_REMOVE_DEATH_PENALTY:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_remove_death_penalty(arg1));
						break;
					case I_SUMMON_AGATHION:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_summon_agathion(arg1));
						break;
					case I_TARGET_ME_CHANCE:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_target_me_chance(arg1));
						break;
					case I_AUGMENT:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_augment(arg1));
						break;
					case I_CHANGE_WEAPON:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_change_weapon(arg1));
						break;
					case I_CONSUME_SOULS:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_consume_souls(arg1));
						break;
					case I_LIFE_TO_SOUL:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_life_to_soul(arg1));
						break;
					case I_SOUL_GATHERING:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_soul_gathering(arg1));
						break;
					case I_TRANSFER_SOUL:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_transfer_soul(arg1));
						break;
					case I_CONSUME_ENERGY:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_consume_energy(arg1));
						break;
					case I_CP_PER_MAX:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_cp_per_max(arg1));
						break;
					case I_SHADOW_STEP:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_shadow_step(arg1));
						break;
					case I_ACQUIRE_SKILL:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_acquire_skill(arg1));
						break;
				}
			}
			break;

		case I_RUN_AWAY: // i_run_away
			{
				int  arg1 = yyattribute(-1).int_value;
				int  arg2 = yyattribute(0).int_value;

				switch(nSubstAction)
				{
					DEFAULT_SUBST_ACTION;
					case I_MANA_BURN:
						this->pSkillInfo->AddInstantEffect(new CSkillEffect_i_mana_burn(arg1,arg2));
						break;
				}
			}
			break;

		case P_BLOCK_ACT: // p_block_act
			{
				switch(nSubstAction)
				{	
					DEFAULT_SUBST_ACTION;
					case P_BLOCK_ICON_ACTION:
						this->pSkillInfo->AddPumpEffect(new CSkillEffect_p_block_icon_action(0));
						break;
					case P_DISARM:
						this->pSkillInfo->AddPumpEffect(new CSkillEffect_p_disarm(0));
						break;
					case P_CHARM_OF_COURAGE:
						this->pSkillInfo->AddPumpEffect(new CSkillEffect_p_charm_of_courage());
						break;
				}
			}
			break;

		case P_ATTACK_SPEED_BY_WEAPON:
			{
				bool *pWTFlags = this->wpn_type;
				double fParam = yyattribute(-2).num_value;
				int nModType = yyattribute(0).int_value;

				switch (MODIFY(nSubstAction, nModType))
				{
					DEFAULT_SUBST_ACTION;

					case DIFF(P_CRITICAL_DAMAGE_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::critical_damage_diff,
							nModType));
						break;

					case PER(P_CRITICAL_DAMAGE_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::critical_damage_coef,
							nModType));
						break;

					case DIFF(P_CRITICAL_RATE_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::critical_rate_diff,
							nModType));
						break;

					case PER(P_CRITICAL_RATE_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::critical_rate_coef,
							nModType));
						break;

					case DIFF(P_MAGICAL_ATTACK_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::m_atk_diff_bonus,
							nModType));
						break;

					case PER(P_MAGICAL_ATTACK_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::m_atk_per_bonus,
							nModType));
						break;

					case DIFF(P_MAGIC_SPEED_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::cast_spd_diff,
							nModType));
						break;

					case PER(P_MAGIC_SPEED_BY_WEAPON):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon(
							pWTFlags, fParam, &CCreature::cast_spd_coef,
							nModType));
						break;

					case DIFF(P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP1):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::p_atk_diff_bonus,
							nModType, 0, 30));
						break;

					case PER(P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP1):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::p_atk_per_bonus,
							nModType, 0, 30));
						break;

					case DIFF(P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP2):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::p_atk_diff_bonus,
							nModType, 0, 60));
						break;

					case PER(P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP2):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::p_atk_per_bonus,
							nModType, 0, 60));
						break;

					case DIFF(P_CRITICAL_RATE_BY_WEAPON_BY_HP1):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::critical_rate_diff,
							nModType, 0, 30));
						break;

					case PER(P_CRITICAL_RATE_BY_WEAPON_BY_HP1):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::critical_rate_coef,
							nModType, 0, 30));
						break;

					case DIFF(P_CRITICAL_RATE_BY_WEAPON_BY_HP2):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::critical_rate_diff,
							nModType, 0, 60));
						break;

					case PER(P_CRITICAL_RATE_BY_WEAPON_BY_HP2):
						this->pSkillInfo->AddPumpEffect(
							new CSkillEffect_p_modify_by_weapon_hp(
							pWTFlags, fParam, &CCreature::critical_rate_coef,
							nModType, 0, 60));
						break;
				}
			}
			break;
			
	}

	// if you got here, skip the original yyaction ;)
	return true;
}

//-----------------------------------------------------------------


void InitializeSkillEffects()
{
	CompileTimeSizeCheck(CLexerForSkill, 0xE0);
	CompileTimeSizeCheck(CParserForSkill, 0x248);
	CompileTimeOffsetCheck(CParserForSkill, lexer, 0x150);
	CompileTimeOffsetCheck(CParserForSkill, pSkillInfo, 0xF0);

	// install my hooks into the original vmt
    static CLexerForSkill  *lexer  = NULL;
    lexer = new CLexerForSkill(true);
    static CParserForSkill *parser = NULL;
    parser = new CParserForSkill(true);

	CSkillInfo::extendClass();

	WriteInstructionCALL(0x79BEEB, 0x79BEF0, CParserForSkill_create);
	WriteInstructionCALL(0x79BFDA, 0x79BFDF, CParserForSkill_destructor);
	WriteInstructionCALL(0x8F6DCF, 0x8F6DD4, CSkillEffect_i_abnormal_time_change__ctor);
	WriteInstructionCALL(0x8F267D, 0x8F2682, CSkillEffect_i_dispel_by_slot__ctor);
	WriteInstructionCALL(0x8F6ECA, 0x8F6ECF, CSkillEffect_i_dispel_by_slot_probability__ctor);

	#define SUBST_TOKEN(Word, Token, SubstAction) \
		g_extTokenMap.add(WIDEN(Word), CLexerForSkill::Token, CParserForSkill::SubstAction)

	// EXTENDED FIELDS
	SUBST_TOKEN("trigger_skill", skill_name, TRIGGER_SKILL);
	SUBST_TOKEN("trigger_type", operate_type, TRIGGER_TYPE);
	SUBST_TOKEN("trigger_rate", reuse_delay, TRIGGER_RATE);

	// INSTANT EFFECTS
	SUBST_TOKEN("i_augment", i_mp_by_level, I_AUGMENT);
	SUBST_TOKEN("i_change_weapon", i_mp_by_level, I_CHANGE_WEAPON);
	SUBST_TOKEN("i_consume_souls", i_mp_by_level, I_CONSUME_SOULS);
	SUBST_TOKEN("i_consume_energy", i_mp_by_level, I_CONSUME_ENERGY);
	SUBST_TOKEN("i_death2", i_hp_drain, I_DEATH2);
	SUBST_TOKEN("i_blink", i_hp_drain, I_BLINK);
	SUBST_TOKEN("i_erase", i_mp_by_level, I_ERASE);
	SUBST_TOKEN("i_life_to_soul", i_mp_by_level, I_LIFE_TO_SOUL);
	SUBST_TOKEN("i_mana_burn", i_run_away, I_MANA_BURN);
	SUBST_TOKEN("i_remove_death_penalty", i_mp_by_level, I_REMOVE_DEATH_PENALTY);
	SUBST_TOKEN("i_rush", i_mp_by_level, I_RUSH);
	SUBST_TOKEN("i_soul_gathering", i_mp_by_level, I_SOUL_GATHERING);
	SUBST_TOKEN("i_summon_agathion", i_mp_by_level, I_SUMMON_AGATHION);
	SUBST_TOKEN("i_summon_friend", i_mp_by_level, I_SUMMON_FRIEND);
	SUBST_TOKEN("i_target_cancel_chance", i_mp_by_level, I_TARGET_CANCEL_CHANCE);
	SUBST_TOKEN("i_target_me_chance", i_mp_by_level, I_TARGET_ME_CHANCE);
	SUBST_TOKEN("i_transfer_soul", i_mp_by_level, I_TRANSFER_SOUL);
	SUBST_TOKEN("i_transform", i_mp_by_level, I_TRANSFORM);
	SUBST_TOKEN("i_cp_per_max", i_mp_by_level, I_CP_PER_MAX);
	SUBST_TOKEN("i_shadow_step", i_mp_by_level, I_SHADOW_STEP);
	SUBST_TOKEN("i_acquire_skill", i_mp_by_level, I_ACQUIRE_SKILL);

	// PUMP EFFECTS
	SUBST_TOKEN("p_block_icon_action", p_block_act, P_BLOCK_ICON_ACTION);
	SUBST_TOKEN("p_critical_damage_by_weapon", p_attack_speed_by_weapon, P_CRITICAL_DAMAGE_BY_WEAPON);
	SUBST_TOKEN("p_critical_rate_by_weapon", p_attack_speed_by_weapon, P_CRITICAL_RATE_BY_WEAPON);
	SUBST_TOKEN("p_magical_attack_by_weapon", p_attack_speed_by_weapon, P_MAGICAL_ATTACK_BY_WEAPON);
	SUBST_TOKEN("p_magic_speed_by_weapon", p_attack_speed_by_weapon, P_MAGIC_SPEED_BY_WEAPON);
	SUBST_TOKEN("p_physical_attack_by_weapon_by_hp1", p_attack_speed_by_weapon, P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP1);
	SUBST_TOKEN("p_physical_attack_by_weapon_by_hp2", p_attack_speed_by_weapon, P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP2);
	SUBST_TOKEN("p_critical_rate_by_weapon_by_hp1", p_attack_speed_by_weapon, P_CRITICAL_RATE_BY_WEAPON_BY_HP1);
	SUBST_TOKEN("p_critical_rate_by_weapon_by_hp2", p_attack_speed_by_weapon, P_CRITICAL_RATE_BY_WEAPON_BY_HP2);
	SUBST_TOKEN("p_disarm", p_block_act, P_DISARM);
	SUBST_TOKEN("p_charm_of_courage", p_block_act, P_CHARM_OF_COURAGE);

	// OPERATE CONDITIONS
	SUBST_TOKEN("can_summon_friend", can_summon, OP_CAN_SUMMON_FRIEND);
	SUBST_TOKEN("has_souls", energy_saved, OP_HAS_SOULS);
	SUBST_TOKEN("remain_mp_per", remain_hp_per, OP_REMAIN_MP_PER);
	SUBST_TOKEN("have_abnormal", energy_saved, OP_HAVE_ABNORMAL);
	SUBST_TOKEN("have_abnormal_level", check_level, OP_HAVE_ABNORMAL_LEVEL);
	SUBST_TOKEN("have_abnormal_block_cast", energy_saved, OP_HAVE_ABNORMAL_BLOCK_CAST);
	SUBST_TOKEN("target_class", remain_hp_per, OP_TARGET_CLASS);
	SUBST_TOKEN("target_not_class", energy_saved, OP_TARGET_CLASS);
	SUBST_TOKEN("check_cast_range", energy_saved, OP_CHECK_CAST_RANGE);
	SUBST_TOKEN("on_siege", can_summon, OP_ON_SIEGE);
	SUBST_TOKEN("target_not_boss", can_summon, OP_TARGET_NOT_BOSS);
}
