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

#include "CObject.h"
#include "CSharedData.h"
#include "CInventory.h"
#include "CSkillInfo.h"

using namespace std;

// Circular References
class CObject;
class CSummon;
class CSkillInfo;
class CCreature;

struct CBuffInfo
{
	CSkillInfo *pSkillInfo;
	int nCastTime;
	int nCastOnSelf;
	int nCasterID;
	int nSomething;
};

typedef vector<CBuffInfo> BuffVector;

struct CActiveCubicInfo
{
	/* 0000 */ void* pCubicInfo; // there, short nCubicId is at offset 0
	/* 0008 */ int   _unk08[10];
	/* 0030 sizeof */
};

typedef vector<CActiveCubicInfo> CubicVector;

#pragma pack( push, 1 )

class CCreature : public CObject
{
public:

	// These containers are defined as const because they use different
	// allocator in L2Server, so we must not modify them directly!

	typedef const std::map<int, int>        AcquiredSkillMap; // skill_id => skill_level
	typedef const std::map<int, int>        AttachedSkillMap; // skill_id => skill_level
	typedef const std::vector<CSkillKey>    AttachedSkillList;
	typedef const std::map<CSkillKey, int>  SkillReuseMap;    // skill_key => reuse_end

	CompileTimeSizeCheck(CCreature::AcquiredSkillMap::value_type, 8);
	CompileTimeSizeCheck(CCreature::AttachedSkillMap::value_type, 8);
	CompileTimeSizeCheck(CCreature::AttachedSkillList::value_type, 4);
	CompileTimeSizeCheck(CCreature::SkillReuseMap::value_type, 8);

	//Constructor
	CCreature();

	//AUTOPICK
	bool AddItemToInventory(CItem * pItem)
	{
		typedef bool (__fastcall * __AddItemToInventory)(CCreature*, CItem*);
		__AddItemToInventory xAddItemToInventory = (__AddItemToInventory)0x007FFD50L;

		return xAddItemToInventory(this, pItem);
	}
bool IsBoss() { return IsValidObject(VMTCBoss); }//WAGNER 2014 AUTOPICK
bool IsZZoldagu() { return IsValidObject(VMTCZzoldagu); }//WAGNER 2014 AUTOPICK



	void AcquireSkill(int nSkillId, int nLevel, bool bAllowDelevel = false, bool bLockMap = true)
	{
		typedef void (*FAcquireSkill)(CCreature*, int, int, bool, bool);
		FAcquireSkill(0x4F8760)(this, nSkillId, nLevel, bAllowDelevel, bLockMap);
	}

	void DeleteAcquiredSkill(int skillID)
	{
		typedef void (__thiscall *_DELETE_ACQUIRE_SKILL) (CCreature *, int);
		_DELETE_ACQUIRE_SKILL _DeleteAcquireSkill = (_DELETE_ACQUIRE_SKILL)0x004F8A70;
		_DeleteAcquireSkill(this, skillID);
	}

	bool HaveSkill(int skillID, int level)
	{
		typedef bool (__thiscall *_HAVE_SKILL) (CCreature *, int, int);
		_HAVE_SKILL _HaveSkill = (_HAVE_SKILL)0x004F0830;
		return ( _HaveSkill(this, skillID, level) );
	}

	void ModifyAcquireSkill(int skillID, int level)
	{
		typedef void (__thiscall *_MODIFY_ACQUIRE_SKILL) (CCreature *, int, int);
		_MODIFY_ACQUIRE_SKILL _ModifyAcquireSkill = (_MODIFY_ACQUIRE_SKILL)0x004F8BD0;
		_ModifyAcquireSkill(this, skillID, level);
	}

	// returns pointer into skillReuseMap, caller must lock it!
	DWORD* GetSkillUsedTime(int nSkillId, int nLevel)
	{
		typedef DWORD* (*FGetSkillUsedTime)(CCreature*, int, int);
		return FGetSkillUsedTime(0x4F1D40)(this, nSkillId, nLevel);
	}

	void SetSkillUsableTime(int nSkillId, int nLevel, DWORD* pdwTimeStamp, DWORD dwReuseDelay)
	{
		typedef void (*FSetSkillUsableTime)(CCreature*, int, int, DWORD*, DWORD);
		FSetSkillUsableTime(0x4F8D10)(this, nSkillId, nLevel, pdwTimeStamp, dwReuseDelay);
	}

	void ValidateParameters()
	{
		typedef void (__thiscall *_VALIDATE_PARAMETERS) (CCreature *);
		_VALIDATE_PARAMETERS _ValidateParameters = (_VALIDATE_PARAMETERS)0x00517ED0;
		_ValidateParameters(this);
	}

	void ValidateSkillMod()
	{
		typedef void (__thiscall *_VALIDATE_SKILLMOD) (CCreature *pCreature);
		_VALIDATE_SKILLMOD xValidateSkillMod = (_VALIDATE_SKILLMOD)0x004FEA80L;
		xValidateSkillMod(this);
	}

	void ValidateAllOnSIM()
	{
		typedef void (__thiscall *_VAS) (CCreature *pCreature);
		_VAS xVas = (_VAS)0x004FFDC0L;
		xVas(this);
	}

	void ValidateSkillList()
	{
		typedef void (__thiscall *_VALIDATE_SKILL_LIST) (CCreature *);
		_VALIDATE_SKILL_LIST _ValidateSkillList = (_VALIDATE_SKILL_LIST)0x00509B80;
		_ValidateSkillList(this);
	}

	void ValidateAttachedSkills()
	{
		typedef void (__thiscall *_VALIDATE_ATTACHED_SKILLS) (CCreature *pCreature);
		_VALIDATE_ATTACHED_SKILLS xValidateAttachedSkills = (_VALIDATE_ATTACHED_SKILLS)0x005173F0L;
		xValidateAttachedSkills(this);
	}

	bool InfectedSkillBy(CCreature *pSource, void *pSkillInfo)
	{
		typedef bool (*_INFECTSKILLBY) (CCreature *pMyself, CCreature *pSource, void *SkillInfo);
		_INFECTSKILLBY _InfectedSkillBy = (_INFECTSKILLBY)0x00504FD0L;
		return _InfectedSkillBy(this, pSource, pSkillInfo);
	}

	void CreatureUseItem(void *pItem)
	{
		typedef void (*_CUI)(CCreature *pCreature, void *pItem, UINT32 unknown);
		_CUI _CreatureUseItem = (_CUI)(0x004F9C40L);
		_CreatureUseItem(this, pItem, 0);
	}

    bool IsValidSD()
    {
        if(this)
		{
            __try
			{ 
				if(this->SD && this->SD > (CSharedData *)0xC019FF) { double A = this->SD->x; return true; }
			}
            __except(EXCEPTION_EXECUTE_HANDLER)
			{ 
				/* Invalid pointer */
				/* Preventing Crash ;) */
			}
        }

		return false;
    }

	bool IsValidCreature()
	{
		if( IsValidObject(VMTCCreature)
			|| IsValidObject(VMTCNPC)
			|| IsValidObject(VMTCSummon)
			|| IsValidObject(VMTCBoss)
			|| IsValidObject(VMTCZzoldagu)
			|| IsValidObject(VMTUser)
			|| IsValidObject(VMTCPet)
			|| IsValidObject(VMTCMerchant) )
		{
			if(IsValidSD())
			{
				return true;
			}
		}

		return false;
	}

	bool IsValidUser()
	{
		if( IsValidObject(VMTUser) && IsValidSD())
			return true;
		else
			return false;
	}

	bool IsValidSummon()
	{
		return IsValidObject(VMTCSummon);
	}

	bool IsValidPet()
	{
		return IsValidObject(VMTCPet);
	}

	bool IsValidNPC()
	{
		return IsValidObject(VMTCNPC);
	}

	bool IsValidMerchant()
	{
		return IsValidObject(VMTCMerchant);
	}

	bool IsAlive()
	{
		if ( SD->nIsAlive == 1 )
			return true;
		else
			return false;
	}

	INT32 GetAcquiredSkillLevel(INT32 SkillID)
	{
		typedef INT32 (*_GASL)(CCreature *pCreature, INT32 SkillID);
		_GASL _GetAcquiredSkillLevel = (_GASL)(0x004F05E0L);
		return _GetAcquiredSkillLevel(this, SkillID);
	}

	void DeleteItemInInventory(int nItemID, int nAmount)
	{
 		typedef void (__fastcall * __DeleteItemInInventory)(CCreature*, int ItemID, int Amount);
 		__DeleteItemInInventory _DeleteItemInInventory = (__DeleteItemInInventory)0x004EF8C0L;
 		_DeleteItemInInventory(this, nItemID, nAmount);
	}


	void AddItemToInventory(int nItemID, int nAmount, int nEnchant = 0)
	{
		typedef void (__fastcall * __AddItemToInventory)(CCreature *Creature, int ItemID, int Amount, bool bIsPick, int nEnchanted, int nBless, int nEroded);
		__AddItemToInventory xAddItemToInventory = (__AddItemToInventory)0x004EF130L;
		
		xAddItemToInventory(this, nItemID, nAmount, 0, nEnchant, 0, 0);
	}

	void ChangeTarget(CObject * pTarget, bool bByUser)
	{
		typedef void (__thiscall *_CHANGE_TARGET) (CCreature *, CObject *, bool);
		_CHANGE_TARGET _ChangeTarget = (_CHANGE_TARGET)0x004EEA70;

		_ChangeTarget(this, pTarget, bByUser);
	}

	void SetMaxMagicLevel()
	{
		typedef void (__thiscall *_SMML) (CCreature *pCreature);
		_SMML xSetMaxMagicLevel = (_SMML)0x004EACB0L;
		xSetMaxMagicLevel(this);
	}

	bool Die(CCreature *pEnemy)
	{
		typedef bool (__thiscall *_DIE) (CCreature *MySelf, CCreature *Enemy);
		_DIE xDie = (_DIE)0x00511D70L;
		return ( xDie(this, pEnemy) );
	}

	void DispelAllByGM()
	{
		typedef bool (__thiscall *_DAGM) (CCreature *pMySelf);
		_DAGM xDispelAllByGM = (_DAGM)0x00502A00L;
		xDispelAllByGM(this);
	}

	bool ValidateBaseCP()
	{
		typedef bool (__fastcall * ValidateBCPS) (CCreature*);
		ValidateBCPS _ValidateBCPS = (ValidateBCPS) 0x004DBA50;
		return _ValidateBCPS(this);
	}
	 
	bool ValidateAllOnWeapon()
	{
		typedef bool (__fastcall * __ValidateAllOnWeapon) (CCreature*);
		__ValidateAllOnWeapon _ValidateAllOnWeapon = (__ValidateAllOnWeapon) 0x00516FE0;
		return _ValidateAllOnWeapon(this);
	}

	bool ValidateCPRegen()
	{
		typedef bool (__fastcall * _VLREGEN) (CCreature*);
		_VLREGEN xVlRegen = (_VLREGEN) 0x004DBBD0L;
		return xVlRegen(this);
	}

	bool ValidateHPRegen()
	{
		typedef bool (__fastcall * _VLREGEN) (CCreature*);
		_VLREGEN xVlRegen = (_VLREGEN) 0x004DBD90L;
		return xVlRegen(this);
	}

	bool ValidateMPRegen()
	{
		typedef bool (__fastcall * _VLREGEN) (CCreature*);
		_VLREGEN xVlRegen = (_VLREGEN) 0x004DBF60L;
		return xVlRegen(this);
	}

	void Action(CCreature *pCreature, DWORD dOption1, DWORD dOption2)
	{
		typedef void(__fastcall *__ct)(CCreature*, CCreature *, DWORD dOption1, DWORD dOption2);
		__ct _ct = (__ct) 0x004E46C0;
		if(this->IsValidCreature())
		{
			if(pCreature->IsValidCreature())
			{
				_ct(this, pCreature, dOption1, dOption2);
			}
		}
	}

	INT32 UnequipItem(int slotId)
	{
		typedef INT32 (*t)(CCreature*, int slotId);
		t f = (t)0x00519F30;
		return f(this,slotId);
	}

	INT32 UnequipItem(CItem* pItem)
	{
		typedef INT32 (*t)(CCreature*, CItem*);
		t f = (t)0x00826A90;
		return f(this,pItem);
	}

	CSharedItemData* GetEquipedWeapon()
	{
		typedef CSharedItemData* (*t)(CCreature*);
		t f = (t)0x004E4560;
		return f(this);
	}

	bool DestroyItem(int id, int count)
	{
		typedef bool (*t)(CCreature*, int, int);
		t f = (t)0x4EF8C0;
		return f(this, id, count);
	}

	void CheckAbnormalVisualEffect()
	{
		typedef void (*t)(CCreature*);
		t f = (t)0x4E52B0;
		f(this);
	}

	//EquipSlotType IsEquiped(int nSlotType)
	//{
	//	typedef EquipSlotType (*t)(CCreature*, int);
	//	t f = (t)0x4E11D0;
	//	return f(this, nSlotType);
	//}

	bool CCreature::IsEquiped(int nItemIndex)
	{
		typedef bool (*t)(CCreature*, int);
		t f = (t)0x4DA780;
		return f(this, nItemIndex);
	}

	double Distance(double x1, double y1, double z1);

	void Lock(WCHAR* file, int line);
	void Unlock();
	bool DispelAll(int magic_level, CSkillInfo *pSkillInfo);

	bool FindBuffByAT(int nAbnormalType, CBuffInfo* pBuffInfo);

	double GetAttributeBonus(CCreature* pOpponent)
	{
		typedef double (*FGetAttributeBonus)(CCreature*, CCreature*);
		return FGetAttributeBonus(0x4E01F0)(this, pOpponent);
	}

	double GetDefenseAttributeValue(int nAttribute)
	{
		// substitutes sub_4D8F10
		if (nAttribute >= 1 && nAttribute <= 33)
			return this->dDefAttribute[nAttribute];
		else
			return 1.0;
	}

	CInventory* GetInventory()
	{
		return IsValidCreature() ? &inventory : 0;
	}

	CItem* GetEquippedItem(int nSlotType)
	{
		if (IsValidCreature())
		{
			int nItemIndex = SD->EquippedItemIndex(nSlotType);
			return inventory.GetItemByIndex(nItemIndex);
		}
		return 0;
	}

	CItemInfo* GetEquippedItemInfo(int nSlotType)
	{
		CSharedItemData* pItemSD = GetEquippedItemSD(nSlotType);
		return pItemSD ? pItemSD->GetItemInfo() : 0;
	}

	CSharedItemData* GetEquippedItemSD(int nSlotType)
	{
		int nItemIndex = SD->EquippedItemIndex(nSlotType);
		return CSharedItemData::FromIndex(nItemIndex);
	}

	void InitializeBuilderCmdMod()
	{
		typedef void (*t)(CCreature*);
		t f = (t)0x4DDB90;
		f(this);
	}

	void GetEquippedObjectIdType(int nSlotType, int* pObjectId, int* pObjectType);

	/* 0030 */      int _dw0030[2];
	/* 0038 */      int _dw0038[2];
	/* 0040 */      int _dw0040[338];
    /* 0588 */      CSharedData *SD;
    /* 0590 */      int _dw0590[2];
    /* 0598 */      CIOCriticalSection* pReadLock;
    /* 05A0 */      CInventory inventory;
    /* 0608 */      int nCurrentSetID;
    /* 060C */      int _dw060C;
    /* 0610 */      int _dw0610[2];
    /* 0618 */      INT8 _dw0614[0x88];
	/* 06A0 */		double base_p_def_diff_bonus;
	/* 06A8 */		double base_m_def_diff_bonus;
	/* 06B0 */		double base_hp_diff_bonus;
	/* 06B8 */		double base_mp_diff_bonus;
	/* 06C0 */		double base_spd_diff_bonus;
	/* 06C8 */		double p_atk_per_bonus;			// default 1.0
	/* 06D0 */		double p_atk_diff_bonus;
	/* 06D8 */		double p_def_per_bonus;			// default 1.0
	/* 06E0 */		double p_def_diff_bonus;
	/* 06E8 */		double m_atk_per_bonus;			// default 1.0 - p_magical_attack
	/* 06F0 */		double m_atk_diff_bonus;
	/* 06F8 */		double m_def_per_bonus;			// default 1.0 - p_magical_defence
	/* 0700 */		double m_def_diff_bonus;
	/* 0708 */		double hp_regen_coef;			// default 1.0
	/* 0710 */		double hp_regen_diff;
	/* 0718 */		double mp_regen_coef;			// default 1.0
	/* 0720 */		double mp_regen_ciff;
	/* 0728 */		double spd_coef;				// default 1.0
	/* 0730 */		double spd_diff;
	/* 0738 */		double atk_spd_coef;			// default 1.0
	/* 0740 */		double cast_spd_coef;			// default 1.0 - p_magic_speed
	/* 0748 */		double cast_spd_diff;			// p_magic_speed
	/* 0750 */		double phit_2h_bonus_diff;		// p_2h_sword_bonus, p_2h_blunt_bonus, p_physical_armor_hit
	/* 0758 */		double avoid_rate_diff;			// p_avoid, p_avoid_rate_by_hp1, p_avoid_rate_by_hp2, p_set_collected
	/* 0760 */		double critical_rate_coef;		// default 1.0 - p_critical_rate, p_critical_rate_by_hp1, p_critical_rate_by_hp2
	/* 0768 */		double critical_rate_diff;		// p_critical_rate, p_critical_rate_by_hp1, p_critical_rate_by_hp2
	/* 0770 */		double magic_critical_rate_coef;	// default 1.0 - res = WIT*0.5*magic_critical_rate_coef + magic_critical_rate_diff
	/* 0778 */		double magic_critical_rate_diff;
	/* 0780 */		bool can_move;					// default true, 0 - p_block_move
	/* 0781 */		bool allow_cub_action;			// default true, 0 - p_cub_block_act
	/* 0782 */		bool can_controll;				// default true, 0 - p_block_controll, user can't control own char
	/* 0783 */		bool can_get_spell;				// default true, 0 - p_block_spell
	/* 0784 */		bool can_get_physical_skill_dmg;	// default true, 0 - p_block_skill_physical
	/* 0785 */		bool can_get_special_skill_dmg;	// default true, 0 - p_block_skill_special
	/* 0786 */		bool preserve_abnormal_on_die;	// default false, 1 - p_preserve_abnormal
	/* 0787 */		bool can_get_hp_dmg;			// default true, 0 - is in petrified state, look at p_block_getdamage
	/* 0788 */		bool can_get_mp_dmg;			// default true, 0 - is in petrified state, look at p_block_getdamage
	/* 0789 */		bool reduce_drop_penalty;		// default false, 1 - p_reduce_drop_penalty, charm of luck
	/* 078A */		bool under_dear;				// default false, 1 - p_fear
	/* 078B */		bool damage_shield;				// default false, 1 - p_damage_shield
	/* 078C */		bool vampiric_attack;			// default false, 1 - p_vampiric_attack
	/* 078D */		bool pump_attack;				// default false, 1 -- p_critical_rate_by_hp1, p_critical_rate_by_hp2, p_physical_attack_by_hp1, p_physical_attack_by_hp2, p_physical_defence_by_hp1, p_physical_defence_by_hp2, p_avoid_rate_by_hp1, p_avoid_rate_by_hp2, p_attack_speed_by_hp1, p_attack_speed_by_hp2
	/* 078E */		bool b78E_zero;					// default false, not used for skill-mod
	/* 078F */		bool b78F_zero;					// default false, not used for skill-mod
	/* 0790 */		double dDamageShield_Diff;		// default 1.0
	/* 0798 */		double dVampiricAttack_Per;		// default 1.0
	/* 07A0 */		double dPhysical_armor_hit;		// default 1.0, used in s_agile_movement
	/* 07A8 */		double max_hp_bonus_diff;		// p_set_collected, p_max_hp
	/* 07B0 */		double max_hp_bonus_coef;		// default 1.0, p_max_hp
	/* 07B8 */		double max_mp_bonus_diff;		// p_max_mp
	/* 07C0 */		double max_mp_bonus_coef;		// default 1.0, p_max_mp
	/* 07C8 */		double max_cp_bonus_diff;		// p_max_cp
	/* 07D0 */		double max_cp_bonus_coef;		// default 1.0, p_max_cp
	/* 07D8 */		double fAttackRange_diff;
	/* 07E0 */		double fAttackRange_coef;		// default 1.0
	/* 07E8 */		double critical_damage_diff;		// p_critical_damage, i_backstab, i_fatal_blow
	/* 07F0 */		double critical_damage_coef;		// default 1.0, p_critical_damage, i_backstab, i_fatal_blow
	/* 07F8 */		double phys_skill_reuse_delay_coef;		// default 1.0, p_reuse_delay
	/* 0800 */		double mag_skill_reuse_delay_coef;		// default 1.0
	/* 0808 */		double type2_skill_reuse_delay_coef;	// default 1.0
	/* 0810 */		double reduce_cancel_diff;		// p_reduce_cancel
	/* 0818 */		double reduce_cancel_coef;		// default 1.0
	/* 0820 */		double atk_spd_by_weapon_coef;	// default 1.0, p_attack_speed_by_weapon
	/* 0828 */		double atk_spd_by_weapon_diff;
	/* 0830 */		double shield_def_rate_coef;	// default 1.0, p_shield_defence_rate
	/* 0838 */		int henna_int_bonus;
	/* 083C */		int henna_str_bonus;
	/* 0840 */		int henna_con_bonus;
	/* 0844 */		int henna_men_bonus;
	/* 0848 */		int henna_dex_bonus;
	/* 084C */		int henna_wit_bonus;
	/* 0850 */		double hp_regen_by_move_mode_coef[4];	// default 1.0, CSkillEffect_p_hp_regen_by_move_mode
	/* 0870 */		double hp_regen_by_move_mode_diff[4];
	/* 0890 */		double mp_regen_by_move_mode_coef[4];	// default 1.0, CSkillEffect_p_mp_regen_by_move_mode
	/* 08B0 */		double mp_regen_by_move_mode_diff[4];
	/* 08D0 */		double avoid_by_move_mode_coef[4];		// CSkillEffect_p_avoid_by_move_mode
	/* 08F0 */		double avoid_by_move_mode_diff[4];		// 0 .. 3
	/* 0910 */		double safe_fall_height_coef;	// default 1.0
	/* 0918 */		double safe_fall_height_diff;
	/* 0920 */		double breath_coef;				// default 1.0, CSkillEffect_p_breath
	/* 0928 */		double breath_diff;
	/* 0930 */		double weight_limit_coef;		// default 1.0, CSkillEffect_p_weight_limit
	/* 0938 */		int    weight_penalty;			// weight limit, CSkillEffect_p_weight_penalty
	/* 093C */		int _dw93c;
	/* 0940 */		double trade_coef[6];			// default 1.0, CSkillEffect_p_trade
	/* 0970 */		int    mana_charge;				// CSkillEffect_p_mana_charge
	/* 0974 */		int	_dw974;
	/* 0978 */		double heal_effect_coef;		// default 1.0, CSkillEffect_p_heal_effect
	/* 0980 */		int transfer_damage_summon;		// CSkillEffect_p_transfer_damage_summon
	/* 0984 */		int _dw984;
	/* 0988 */		double area_damage_coef;		// default 1.0, CSkillEffect_p_area_damage
	/* 0990 */		double area_damage_diff;
	/* 0998 */		double hit_at_night_coef;		// default 1.0, CSkillEffect_p_hit_at_night__Pump
	/* 09A0 */		double hit_at_night_diff;
	/* 09A8 */		int avoid_agro;					// CSkillEffect_p_avoid_agro::Pump
	/* 09AC */		int _dw9AC;
	/* 09B0 */		double fatal_blow_rate_coef;	// default 1.0, CSkillEffect_p_fatal_blow_rate::Pump
	/* 09B8 */		double fatal_blow_rate_diff;
	/* 09C0 */		double critical_rate_position_bonus_front_coef;	// default 1.0, CSkillEffect_p_critical_rate_position_bonus::Pump
	/* 09C8 */		double critical_rate_position_bonus_front_diff;
	/* 09D0 */		double critical_rate_position_bonus_side_coef;	// default 1.0
	/* 09D8	*/		double critical_rate_position_bonus_side_diff;
	/* 09E0 */		double critical_rate_position_bonus_back_coef;	// default 1.0
	/* 09E8 */		double critical_rate_position_bonus_back_diff;
	/* 09F0 */		double critical_damage_position_front_coef;		// default 1.0, CSkillEffect_p_critical_damage_position__Pump
	/* 09F8 */		double critical_damage_position_front_diff;
	/* 0A00 */		double critical_damage_position_side_coef;		// default 1.0
	/* 0A08 */		double critical_damage_position_side_diff;
	/* 0A10 */		double critical_damage_position_back_coef;		// default 1.0
	/* 0A18 */		double critical_damage_position_back_diff;
	/* 0A20 */		double physical_shield_defence_coef;			// default 1.0, installed in p_physical_shield_defence
	/* 0A28 */		double physical_shield_defence_diff;			// installed in p_physical_shield_defence
	/* 0A30 */		double phys_skill_mp_cost_coef;	// default 1.0, installed in p_magic_mp_cost
	/* 0A38 */		double phys_skill_mp_cost_diff; // installed in p_magic_mp_cost
	/* 0A40 */		double mag_skill_mp_cost_coef;	// default 1.0, installed in p_magic_mp_cost
	/* 0A48 */		double mag_skill_mp_cost_diff;	// installed in p_magic_mp_cost
	/* 0A50 */		double type2_skill_mp_cost_coef;	// default 1.0, installed in p_magic_mp_cost
	/* 0A58 */		double type2_skill_mp_cost_diff;	// installed in p_magic_mp_cos
	/* 0A60 */		double d_pvp_physical_attack_dmg_bonus;			// default 1.0, installed in p_pvp_physical_attack_dmg_bonus
	/* 0A68 */		double d_pvp_physical_skill_dmg_bonus;			// default 1.0, installed in p_pvp_physical_skill_dmg_bonus skill-effect  
	/* 0A70 */		double d_pvp_magical_skill_dmg_bonus;			// default 1.0, installed in p_pvp_magical_skill_dmg_bonus skill-effect
	/* 0A78 */		bool bAegis;					// default false, 1 - p_physical_shield_defence_angle_all
	/* 0A79 */		bool bFocusAttack;				// default false, 1 - p_physical_polarm_target_single
	/* 0A7A */		bool bAbnormalRateLimit;		// default false, 1 - p_abnormal_rate_limit
	/* 0A7B */		bool bBlockBuff;				// default false, used in CCreature::InfectedSkillBy?; CSkillEffect_p_block_buff::Pump
	/* 0A7C */		bool bBlockDebuff;				// default false, used in CCreature::InfectedSkillBy?; CSkillEffect_p_block_debuff::Pump
	/* 0A7D */		INT8 _dwA7D[0x3];
	/* 0A80 */		int skill_critical;				// default 26??, CSkillEffect_p_skill_critical
	/* 0A84 */		int _dwA84;
	/* 0A88 */		double skill_critical_probability_coef;			// default 1.0
	/* 0A90 */		double skill_critical_probability_diff;
	/* 0A98 */		int nIsMagic0_resist;			// used in CSkillInfo::ActivateSkill?
	/* 0A9C */		int nIsMagic1_resist;			// used in CSkillInfo::ActivateSkill?
	/* 0AA0 */		int nIsMagic2_resist;			// used in CSkillInfo::ActivateSkill?
	/* 0AA4 */		int _dwAA4;
	/* 0AA8 */		double dResistDispelByCategory_SlotBuff;		// default 1.0
	/* 0AB0 */		double dResistDispelByCategory_SlotDebuff;		// default 1.0
	/* 0AB8 */		double dResistAbnormalByCategory_SlotBuff;		// default 1.0
	/* 0AC0 */		double dResistAbnormalByCategory_SlotDeBuff;	// default 1.0
	/* 0AC8 */		int allowed_grade;
	/* 0ACC */		__int64 enlarge_storage;  // CSkillEffect_p_enlarge_storage::Pump
					// 0 - inventory_normal, 1 - storage_private, 2 - ??, 3 - trade_sell, 4 - trade_buy
					// 5 - recipe_dwarven, 6 - recipe_common
	/* 0AD4 */      __int64 _qw0AD4;
	/* 0ADC */      __int64 _qw0ADC;
	/* 0AE4 */      int _dw0AE4;
	/* 0AE8 */		int hit_number;			// CSkillEffect_p_hit_number 
	/* 0AEC */		INT8 _dw0AEC[0x35];
	/* 0B20 */      __int64 _b0B20;
	/* 0B28 */      __int64 _b0B28;
	/* 0B30 */      __int64 _b0B30;
	/* 0B39 */      BYTE _b0B39;
	/* 0B3A */      BYTE _b0B3A;
	/* 0B3B */      BYTE _b0B3B;
	/* 0B3C */      BYTE _b0B3C;
	/* 0B3D */      BYTE _b0B3D;
	/* 0B3E */      BYTE _b0B3E;
	/* 0B3F */      BYTE _b0B3F;
    /* 0B40 */      BYTE _b0B40;
    /* 0B41 */      bool bOnBattlefield;
    /* 0B42 */      BYTE _b0B42;
    /* 0B43 */      BYTE _b0B43;
	/* 0B44 */      BYTE _b0B44;
	/* 0B45 */      BYTE _b0B45;
	/* 0B46 */      BYTE _b0B46;
	/* 0B47 */      BYTE _b0B47;
	/* 0B48 */      BYTE _b0B48;
	/* 0B49 */      BYTE _b0B49;
	/* 0B4A */      BYTE _b0B4A;
    /* 0B4B */      INT8 _b0B4B[5];
	/* 0B50 */      __int64 _b0B50; //or double
	/* 0B58 */      __int64 _b0B58; //or double
	/* 0B60 */      __int64 _b0B60; //or double
	/* 0B68 */      __int64 _b0B68; //or double
	/* 0B70 */      __int64 _b0B70; //or double
	/* 0B78 */      INT8 _dw0B78[0x30];
	/* 0BA8 */		INT32 nExpDec;
	/* 0BAC */		INT32 nCharges;
	/* 0BB0 */		INT8 _DW0BB0[0x3B];
	/* 0BEB */		bool _dwBEB;
	/* 0BEC */		INT8 _dw0BEC[0xB8];
    /* 0CA4 */      BYTE _b0CA4;
    /* 0CA5 */      bool bCombatMode;
    /* 0CA6 */      BYTE _b0CA6;
    /* 0CA7 */      BYTE _b0CA7;
    /* 0CA8 */      BYTE _b0CA8[0x20];
	/* 0CC8 */		int	nCompObjectID;
	/* 0CCC */		int	_dw0CCC;
	/* 0CD0 */      int nTargetObjectID;
	/* 0CD4 */      int _dw0CD4;
    /* 0CD8 */		void *pCCreatureController;
	/* 0CE0 */      int _dw0CE0[2];
	/* 0CE8 */      CIOCriticalSection acquiredSkillLock;
	/* 0D18 */      AcquiredSkillMap   acquiredSkillMap;
	/* 0D30 */      CIOCriticalSection attachedSkillLock;
	/* 0D60 */      AttachedSkillMap   attachedSkillMap;
	/* 0D78 */      AttachedSkillList  attachedSkillList;
	/* 0D98 */      CIOCriticalSection skillReuseLock;
	/* 0DC8 */      SkillReuseMap      skillReuseMap;
	/* 0DE0 */      CIOCriticalSection lockBuff;
	/* 0E10 */      CIOCriticalSection lockCubic;
	/* 0E40 */      BuffVector vBuff;
	/* 0E60 */      CubicVector vCubic;
	/* 0E80 */      CBuffInfo lifeForce;
	/* 0E98 */      CIOCriticalSection lifeForceLock;
	/* 0EC8 */      CIOCriticalSection _lock0EC8;
	/* 0EF8 */      std::map<void*, void*> _map0EF8; // unknown map, sizeof(value_type) == 0x10
	/* 0F10 */      int _unk0F10[30];
	/* 0F88 */      int nCurrentAbnormalEffect;
	/* 0F8C */      int _unk0F8C;
	/* 0F90 */      CIOCriticalSection _lock0F90;
	/* 0FC0 */      int _unk0FC0[6];
	/* 0FD8 */      CIOCriticalSection _lock0FD8;
	/* 1008 */      int _unk1008[126];
	/* 1200 */      bool bAtkAttribute[34];
	/* 1222 */      WORD _w1222;
	/* 1224 */      int _dw1224;
	/* 1228 */      double dDefAttribute[34];
	/* 1338 */      int _dw1338[16];
	/* 1378 */      CIOCriticalSection _lock1378;
	/* 13A8 */      int _dw13A8[14];
	/* 13E0 */      CIOCriticalSection _lock13E0;
	/* 1410 */      int _dw1410[56];
};

CompileTimeOffsetCheck(CCreature, acquiredSkillMap,   0xD18);
CompileTimeOffsetCheck(CCreature, attachedSkillLock,   0xD30);
CompileTimeOffsetCheck(CCreature, attachedSkillMap,   0xD60);
CompileTimeOffsetCheck(CCreature, attachedSkillList,  0xD78);
CompileTimeOffsetCheck(CCreature, skillReuseMap,      0xDC8);

#pragma pack( pop )