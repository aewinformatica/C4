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
#include "CSkillMod.h"

// YY Parser
#include "yywclex.h"
#include "yywcpars.h"

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

#ifndef YYSTYPE
union tagYYSTYPE {
	wchar_t*	id_value;
	int			int_value;
	double		num_value;
	LPVOID		ptr_value;
	long double	lnum_value;
};

#define YYSTYPE union tagYYSTYPE
#endif

#define yyattribute(index) (((YYSTYPE*)yyattributestackptr)[yytop + (index)])

class CLexerForSkill : public yywflexer
{
public:

	enum TokenType
	{
		ride_none = 65827,
		ride_star = 65827,
		ride_twilight = 65827,
		ride_wind = 65827,
		ride_wyvern = 65827,
		abnormal_lv = 65562,
		abnormal_time = 65561,
		abnormal_type = 65563,
		abnormal_visual_effect = 65565,
		activate_rate = 65557,
		affect_limit = 65570,
		affect_object = 65573,
		affect_range = 65571,
		affect_scope = 65569,
		affect_scope_height = 65574,
		all = 65824,
		armor_heavy = 65833,
		armor_light = 65833,
		armor_magic = 65833,
		armor_none = 65833,
		attr_animal_weakness = 65831,
		attr_beast_weakness = 65831,
		attr_bleed = 65831,
		attr_blunt = 65831,
		attr_boss = 65831,
		attr_bow = 65831,
		attr_bug_weakness = 65831,
		attr_construct_weakness = 65831,
		attr_dagger = 65831,
		attr_death = 65831,
		attr_derangement = 65831,
		attr_dragon_weakness = 65831,
		attr_dual = 65831,
		attr_dualfist = 65831,
		attr_earth = 65831,
		attr_etc = 65831,
		attr_fire = 65831,
		attr_fist = 65831,
		attr_giant_weakness = 65831,
		attr_hold = 65831,
		attr_holy = 65831,
		attr_none = 65831,
		attr_paralyze = 65831,
		attr_plant_weakness = 65831,
		attr_poison = 65831,
		attr_pole = 65831,
		attr_shock = 65831,
		attr_sleep = 65831,
		attr_sword = 65831,
		attr_unholy = 65831,
		attr_valakas = 65831,
		attr_water = 65831,
		attr_wind = 65831,
		attribute = 65578,
		back = 65830,
		balakas_scope = 65836,
		basic_property = 65559,
		blunt = 65832,
		bow = 65832,
		build_camp = 65587,
		c_chameleon_rest = 65820,
		c_fake_death = 65822,
		c_hp = 65823,
		c_mp = 65818,
		c_mp_by_level = 65821,
		c_rest = 65819,
		can_summon = 65594,
		can_summon_pet = 65593,
		can_summon_siege_golem = 65595,
		cast_range = 65550,
		check_level = 65603,
		check_sex = 65602,
		clan = 65837,
		consume_body = 65591,
		cub_attack_speed = 65714,
		cub_block_act = 65715,
		cub_heal = 65710,
		cub_hp = 65711,
		cub_hp_drain = 65709,
		cub_m_attack = 65708,
		cub_physical_attack = 65712,
		cub_physical_defence = 65713,
		dagger = 65832,
		dead_pledge = 65836,
		debuff = 65566,
		diff = 65829,
		door_treasure = 65834,
		dual = 65832,
		dualfist = 65832,
		effect = 65560,
		effect_point = 65564,
		effective_range = 65549,
		enemy = 65834,
		enemy_only = 65834,
		energy_saved = 65592,
		equip_shield = 65585,
		equip_weapon = 65582,
		fan = 65836,
		fan_range = 65572,
		fist = 65832,
		//friend = 65837,
		front = 65830,
		holything = 65834,
		hp_consume = 65547,
		i_add_hate = 65637,
		i_align_direction = 65700,
		i_backstab = 65656,
		i_change_face = 65683,
		i_change_hair_color = 65685,
		i_change_hair_style = 65684,
		i_confuse = 65649,
		i_consume_body = 65651,
		i_cp = 65687,
		i_death = 65701,
		i_death_link = 65659,
		i_delete_hate = 65641,
		i_delete_hate_of_me = 65658,
		i_dispel_all = 65660,
		i_dispel_by_category = 65631,
		i_dispel_by_slot = 65618,
		i_dispel_by_slot_probability = 65699,
		i_distrust = 65657,
		i_enchant_armor = 65632,
		i_enchant_weapon = 65633,
		i_energy_attack = 65644,
		i_escape = 65625,
		i_fatal_blow = 65621,
		i_fishing_cast = 65692,
		i_fishing_pumping = 65693,
		i_fishing_reeling = 65694,
		i_fishing_shot = 65695,
		i_fly_away = 65672,
		i_focus_energy = 65643,
		i_food_for_pet = 65662,
		i_give_contribution = 65682,
		i_harvesting = 65680,
		i_heal = 65622,
		i_holything_possess = 65638,
		i_hp = 65626,
		i_hp_by_level_self = 65652,
		i_hp_drain = 65623,
		i_hp_per_max = 65634,
		i_hp_self = 65681,
		i_install_camp = 65639,
		i_install_camp_ex = 65707,
		i_m_attack = 65624,
		i_m_attack_by_dist = 65691,
		i_m_attack_over_hit = 65676,
		i_mp = 65627,
		i_mp_by_level = 65636,
		i_mp_by_level_self = 65653,
		i_mp_per_max = 65635,
		i_open_common_recipebook = 65697,
		i_open_dwarf_recipebook = 65696,
		i_p_attack = 65619,
		i_p_attack_over_hit = 65620,
		i_physical_attack_hp_link = 65689,
		i_randomize_hate = 65642,
		i_rebalance_hp = 65702,
		i_register_siege_golem = 65673,
		i_remove_m_power = 65675,
		i_restoration = 65677,
		i_restoration_random = 65678,
		i_resurrection = 65629,
		i_run_away = 65650,
		i_save_position = 65671,
		i_soul_shot = 65645,
		i_sowing = 65679,
		i_sp = 65688,
		i_spirit_shot = 65646,
		i_spoil = 65654,
		i_summon = 65630,
		i_summon_dd_cubic = 65663,
		i_summon_debuff_cubic = 65667,
		i_summon_drain_cubic = 65664,
		i_summon_heal_cubic = 65665,
		i_summon_npc = 65686,
		i_summon_paralyze_cubic = 65668,
		i_summon_pet = 65661,
		i_summon_poison_cubic = 65666,
		i_summon_shock_cubic = 65670,
		i_summon_soul_shot = 65647,
		i_summon_spirit_shot = 65648,
		i_summon_water_dot_cubic = 65669,
		i_sweeper = 65655,
		i_target_cancel = 65704,
		i_target_me = 65705,
		i_teleport = 65706,
		i_transmit_m_power = 65674,
		i_unlock = 65640,
		inventory_normal = 65838,
		is_magic = 65540,
		item = 65834,
		item_consume = 65548,
		level = 65543,
		lv_bonus_rate = 65558,
		magic_level = 65541,
		mp_consume1 = 65545,
		mp_consume2 = 65546,
		next_action = 65575,
		not_friend = 65837,
		npc_body = 65834,
		op_2h_weapon = 65607,
		op_alignment = 65616,
		op_companion = 65609,
		op_energy_max = 65604,
		op_fishing_cast = 65611,
		op_fishing_pumping = 65612,
		op_fishing_reeling = 65612,
		op_home = 65605,
		op_m_power_count = 65600,
		op_m_power_type_2 = 65599,
		op_not_territory = 65615,
		op_resurrection = 65598,
		op_siege_hammer = 65597,
		op_sweeper = 65596,
		op_unlock = 65608,
		op_use_firecracker = 65610,
		op_wyvern = 65606,
		operate_cond = 65556,
		operate_type = 65544,
		others = 65834,
		p_2h_blunt_bonus = 65774,
		p_2h_sword_bonus = 65773,
		p_abnormal_rate_limit = 65802,
		p_area_damage = 65771,
		p_attack_attribute = 65735,
		p_attack_range = 65748,
		p_attack_speed = 65726,
		p_attack_speed_by_hp2 = 65785,
		p_attack_speed_by_weapon = 65753,
		p_avoid = 65730,
		p_avoid_agro = 65762,
		p_avoid_by_move_mode = 65757,
		p_avoid_rate_by_hp2 = 65783,
		p_block_act = 65738,
		p_block_buff = 65807,
		p_block_controll = 65739,
		p_block_debuff = 65808,
		p_block_getdamage = 65741,
		p_block_move = 65737,
		p_block_skill_physical = 65805,
		p_block_spell = 65740,
		p_breath = 65759,
		p_create_common_item = 65725,
		p_create_item = 65724,
		p_critical_damage = 65750,
		p_critical_damage_position = 65812,
		p_critical_rate = 65749,
		p_critical_rate_by_hp1 = 65776,
		p_critical_rate_by_hp2 = 65777,
		p_critical_rate_position_bonus = 65790,
		p_crystallize = 65729,
		p_cubic_mastery = 65766,
		p_damage_shield = 65760,
		p_defence_attribute = 65736,
		p_enlarge_storage = 65816,
		p_fatal_blow_rate = 65789,
		p_fear = 65742,
		p_fishing_mastery = 65801,
		p_heal_effect = 65770,
		p_hit = 65746,
		p_hit_at_night = 65772,
		p_hit_number = 65817,
		p_hp_regen = 65721,
		p_hp_regen_by_move_mode = 65755,
		p_luck = 65731,
		p_magic_critical_rate = 65795,
		p_magic_mp_cost = 65796,
		p_magic_speed = 65727,
		p_magical_attack = 65747,
		p_magical_defence = 65732,
		p_mana_charge = 65768,
		p_max_cp = 65745,
		p_max_hp = 65743,
		p_max_mp = 65744,
		p_mp_regen = 65722,
		p_mp_regen_by_move_mode = 65756,
		p_passive = 65761,
		p_physical_armor_hit = 65793,
		p_physical_attack = 65719,
		p_physical_attack_by_hp1 = 65778,
		p_physical_attack_by_hp2 = 65779,
		p_physical_defence = 65720,
		p_physical_defence_by_hp1 = 65780,
		p_physical_polarm_target_single = 65794,
		p_physical_shield_defence = 65792,
		p_physical_shield_defence_angle_all = 65797,
		p_preserve_abnormal = 65815,
		p_pvp_magical_skill_dmg_bonus = 65800,
		p_pvp_physical_attack_dmg_bonus = 65798,
		p_pvp_physical_skill_dmg_bonus = 65799,
		p_reduce_cancel = 65752,
		p_reduce_drop_penalty = 65791,
		p_reflect_skill = 65809,
		p_remove_equip_penalty = 65728,
		p_resist_abnormal_by_category = 65814,
		p_resist_dispel_by_category = 65813,
		p_reuse_delay = 65751,
		p_safe_fall_height = 65758,
		p_set_collected = 65765,
		p_shield_defence_rate = 65754,
		p_skill_critical = 65810,
		p_skill_critical_probability = 65811,
		p_speed = 65723,
		p_transfer_damage_summon = 65769,
		p_vampiric_attack = 65775,
		p_weight_limit = 65763,
		p_weight_penalty = 65767,
		party = 65836,
		pc_body = 65834,
		per = 65829,
		pledge = 65836,
		point_blank = 65836,
		pole = 65832,
		possess_holything = 65586,
		race_undead = 65835,
		range = 65836,
		recipe_common = 65838,
		recipe_dwarven = 65838,
		remain_hp_per = 65588,
		reuse_delay = 65554,
		ride_state = 65567,
		self = 65834,
		side = 65830,
		single = 65836,
		skill_begin = 65538,
		skill_cool_time = 65552,
		skill_end = 65576,
		skill_hit_cancel_time = 65553,
		skill_hit_time = 65551,
		skill_id = 65542,
		skill_name = 65539,
		square = 65836,
		square_pb = 65836,
		storage_private = 65838,
		summon = 65834,
		sword = 65832,
		t_hp = 65716,
		t_hp_fatal = 65718,
		t_mp = 65717,
		target = 65834,
		target_item_crystal_type = 65583,
		target_my_party = 65589,
		target_my_pledge = 65590,
		target_race = 65584,
		target_type = 65568,
		trade_buy = 65838,
		trade_sell = 65838,
		undead_real_enemy = 65837,
		wyvern_object = 65837,
		wyvern_scope = 65836,
		wyvern_target = 65834,

		T_BLANK = 0,
		T_EQUAL = 65537,
		T_BSTRING                   = 0x10121,    // [s_skillname] -- or [codex_of_giants], yylval = 
		T_ID                        = 0x10122,    // identifier , yylval = strdup(yytext)
		T_INT                       = 0x10123,    // a) integer:  yylval = wcstol(yytext), or // b) @constant: yylval = CPrecompiledHeaderDB::Search(yytext+1)
	    T_NUM                       = 0x10124, 	  // double
	};

	virtual yywint_t yylex() { return 0; };  // fake
	virtual yywint_t yyaction(int action);
protected:
	__int64			dwC0;
	__int64			dwC8;
public:
	int				dwD0; // D0h
	int				dwD4; // D4h
	__int64			iD8; // D8h
	CLexerForSkill(bool bFakeInstance);
	CLexerForSkill() {};
};

//-------------------------------------------------
class CParserForSkill : public yywfparser
{
public:

	enum ActionType
	{
		// original parser actions (spelled in uppercase so as to
		// not be confused with their corresponding tokens)
		SKILL_BEGIN = 0,
		SKILL_END = 1,
		SKILL_NAME = 2,
		OPERATE_TYPE = 11,
		REUSE_DELAY = 21,
		ABNORMAL_TYPE = 30,
		TARGET_TYPE = 35,
		OP_REMAIN_HP_PER = 53,
		OP_ENERGY_SAVED = 57,
		OP_CAN_SUMMON = 59,
		OP_CHECK_LEVEL = 64,
		I_DISPEL_BY_SLOT = 107,
		I_HP_DRAIN = 112,
		I_MP_BY_LEVEL = 119,
		I_RUN_AWAY = 133,
		I_TRANSMIT_M_POWER = 158,
		P_BLOCK_ACT = 194,
		P_ATTACK_SPEED_BY_WEAPON = 209,
		P_HP_REGEN = 93,
	};

	enum SubstActionType
	{
		// new custom actions are not visible to the original parser,
		// so their exact values don't really matter
		SUBST_ACTIONS = 70000,

		TRIGGER_SKILL,
		TRIGGER_TYPE,
		TRIGGER_RATE,

		// OPERATE CONDITIONS
		OP_CAN_SUMMON_FRIEND,
		OP_REMAIN_MP_PER,
		OP_HAS_SOULS,
		OP_CHECK_CAST_RANGE,
		OP_HAVE_ABNORMAL,
		OP_HAVE_ABNORMAL_LEVEL,
		OP_HAVE_ABNORMAL_BLOCK_CAST,
		OP_REMAIN_CP_PER,
		OP_TARGET_CLASS,
		OP_TARGET_NOT_CLASS,
		OP_TARGET_NOT_BOSS,
		OP_ON_SIEGE,

		// INSTANT EFFECTS
		I_TRANSFORM,
		I_SUMMON_FRIEND,
		I_RUSH,
		I_ERASE,
		I_TARGET_CANCEL_CHANCE,
		I_REMOVE_DEATH_PENALTY,
		I_SUMMON_AGATHION,
		I_DEATH2,
		I_MANA_BURN,
		I_TARGET_ME_CHANCE,
		I_AUGMENT,
		I_CHANGE_WEAPON,
		I_CONSUME_SOULS,
		I_LIFE_TO_SOUL,
		I_SOUL_GATHERING,
		I_TRANSFER_SOUL,
		I_CP_PER_MAX,
		I_CONSUME_ENERGY,
		I_BLINK,
		I_SHADOW_STEP,
		I_ACQUIRE_SKILL,

		// PUMP EFFECTS
		P_BLOCK_ICON_ACTION,
		P_CRITICAL_DAMAGE_BY_WEAPON,
		P_CRITICAL_RATE_BY_WEAPON,
		P_MAGICAL_ATTACK_BY_WEAPON,
		P_MAGIC_SPEED_BY_WEAPON,
		P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP1,
		P_PHYSICAL_ATTACK_BY_WEAPON_BY_HP2,
		P_CRITICAL_RATE_BY_WEAPON_BY_HP1,
		P_CRITICAL_RATE_BY_WEAPON_BY_HP2,
		P_DISARM,
		P_CHARM_OF_COURAGE,
	};

	virtual void yyaction(int action);

	// returns true if the original yyaction should be skipped
	bool ExtendedAction(int nAction, int nSubstAction);

//protected:
	CSkillInfo*				pSkillInfo; // 0F0;
	//__int64					i0F8; // bool [11]
	// __int64					i100;
	bool					wpn_type[16]; // 0xF8 
	__int64					i108;
	__int64					i110;
	__int64					i118;
	__int64					i120;
	__int64					i128;
	__int64					i130;
	__int64					i138;
	__int64					i140;
	__int64					i148;
	CLexerForSkill		    lexer; // 0150h
	void*					p230;  // 0230;
	void*					p238;
	void*					p240;
	CParserForSkill(bool bFakeInstance);
	CParserForSkill() {};
};

class CSkillExtTokenMap
{
public:

	typedef const wchar_t*                    KeyType;
	typedef CLexerForSkill::TokenType         TokenType;
	typedef CParserForSkill::ActionType       ActionType;
	typedef CParserForSkill::SubstActionType  SubstActionType;

	void add(KeyType word, TokenType nToken, SubstActionType nAction)
	{
		ValueType& value = m_map[word];
		value.nToken = nToken;
		value.nSubstAction = nAction;
	}

	bool find(KeyType word, TokenType* pToken, SubstActionType* pAction)
	{
		MyMap::const_iterator it = m_map.find(word);
		if (it == m_map.end())
			return false;

		*pToken = it->second.nToken;
		*pAction = it->second.nSubstAction;
		return true;
	}

private:

	struct KeyComp
	{
		bool operator() (KeyType left, KeyType right) const
		{
			return wcscmp(left, right) < 0;
		}
	};

	struct ValueType
	{
		TokenType       nToken;
		SubstActionType nSubstAction;
	};

	typedef std::map<KeyType, ValueType, KeyComp> MyMap;
	MyMap m_map;
};

void InitializeSkillEffects();