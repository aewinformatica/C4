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

#include <windows.h>
#include "CObject.h"
#include "script/itemdata.h"

#pragma pack( push, 8 )

class CObject;
class CItem;
class CItemInfo;
class CSharedItemData;

struct ItemTypeForEnchantAdd
{
	enum _enum_t
	{
		// unconfirmed, just making notes
		none        = 0, // none, fist, fishingrod
		onehanded   = 1, // sword, blunt, dagger, pole, etc
		twohanded   = 2, // sword, blunt, dual, dualfist
		bow         = 3, // bow
	};
};

class CItemInfo 
{
	public:

		static CItemInfo* FromIndex(int itemInfoIndex)
		{
			if (itemInfoIndex < 0 || itemInfoIndex >= *(int*)(0x0BF71C4))
				return 0;
			return *(CItemInfo**)0x0E412178 + itemInfoIndex;
			CompileTimeSizeCheck(CItemInfo, 0x140);
		}

	/* 0000 */	__int64	qw00;
	/* 0008 */	int	default_action;
	/* 000C */	int	recipe_id;
	/* 0010 */	int	etcitem_type;
	/* 0014 */	int	weight;
	/* 0018 */	int	price;
	/* 001C */	int	default_price;
	/* 0020 */	short	item_skill_id;
	/* 0022 */	short	item_skill_lvl;
	/* 0024 */	short	critical_attack_skill_id;
	/* 0026 */	short	critical_attack_skill_lvl;
	/* 0028 */	short	attack_skill_id;
	/* 002A */	short	attack_skill_lvl;
	/* 002C */	short	magic_skill_id;
	/* 002E */	short	magic_skill_lvl;
	/* 0030 */	short	item_skill_enchanted_four_id;
	/* 0032 */	short	item_skill_enchanted_four_lvl;
	/* 0034 */	int magic_skill_prob;
	/* 0038 */	int armor_type;
	/* 003C */	int material_type;
	/* 0040 */	int soulshot_count;
	/* 0044 */	int spiritshot_count;
	/* 0048 */	int dw48;
	/* 004C */	int reduced_soulshot_prob; // reduced_soulshot={prob;count}
	/* 0050 */	int reduced_soulshot_count;
	/* 0054 */	int reduced_spiritshot_prob; // reduced_spiritshot={prob;count}
	/* 0058 */	int reduced_spiritshot_count;
	/* 005C */	int	crystalType;
	/* 0060 */	int	crystalCount;
	/* 0064 */	bool immediate_effect;
	/* 0068 */	int	dw68;
	/* 006c */	int	dw6C;
	/* 0070 */	int	dw70;
	/* 0074 */	bool	is_trade; 
				bool    is_drop;
				bool    is_destruct;
				bool    b77;
	/* 0078 */	bool magic_weapon;
	/* 007C */	int physical_damage;
	/* 0080 */	int random_damage;
	/* 0084 */	int weapon_type;  // 6=bow? 10=fishing_rod? used in User::EquipItem
	/* 0088 */	int _dw88;
	/* 008C */	int critical;
	/* 0090 */	int attack_range;
	/* 0094 */	int damage_range[4]; // damage_range={0;1;2;3}
	/* 00A4 */	int _dw0A4;
	/* 00A8 */	int reuse_delay;
	/* 00AC */	int mp_consume;
	/* 00B0 */	int reduced_mp_prob; // reduced_mp_consume={prob;consume}
	/* 00B4 */	int reduced_mp_consume;
	/* 00B8 */	int magical_damage;
	/* 00BC */	int durability;
	/* 00C0 */	int physical_defense;
	/* 00C4 */	int magical_defense;
	/* 00C8 */	unsigned char dual_fhit_rate;
	/* 00CA */	short mp_bonus; // signed word for sure
	/* 00CC */	int _dw0CC;
	/* 00D0 */	double hit_modify; // used in CCreature::WeaponHitCorrection (Weapon SA?)
	/* 00D8 */	double avoid_modify; // used in CCreature::AvoidCorrection (Shield penalty?)
	/* 00E0 */	double _f0E0;
	/* 00E8 */	double _f0E8;
	/* 00F0 */	int equip_pet[4]; // equip_pet={0;1;2;3}
	/* 0100 */	int _dw100[16];
};

struct ItemExInfo
{
	/* 0000*/ int locationSlot;
	/* 0004*/ int augmentationId;
	/* 0008*/ int mana;
	/* 000c*/ int nAtkAttrElement;
	/* 0010*/ int nAtkAttrValue;
	/* 0014*/ int nDefAttrFire;
	/* 0018*/ int nDefAttrWater;
	/* 001c*/ int nDefAttrWind;
	/* 0020*/ int nDefAttrEarth;
	/* 0024*/ int nDefAttrHoly;
	/* 0028*/ int nDefAttrUnholy;
	/* 002c*/ User *pOwner;
	/* 0034*/ int mana_counter;
	/* 0038*/ int manadroptimer;
};

class CSharedItemData 
{
	public:

		static CSharedItemData* FromIndex(int itemIndex)
		{
			if (itemIndex < 0 || itemIndex >= *(int*)(0x0BF71C0))
				return 0;
			return *(CSharedItemData**)0x0E412138 + itemIndex;
			CompileTimeSizeCheck(CSharedItemData, 0x90);
		}

		CItemInfo* GetItemInfo()
		{
			return CItemInfo::FromIndex(this->itemInfoIndex);
		}

	/* 0000 */ ItemExInfo *exInfo;
	/* 0008 */	double	x;		
	/* 0010 */	double	y;
	/* 0018 */	double	z;
	/* 0020 */	int		dw20;	// /* 0B0h : 0408D10h */    virtual void func_0B0() {};
	/* 0024 */	int		nObjectID;    // item_id; sid in ItemList packet
	/* 0028 */	int		itemIndex;
	/* 002C */	int		containerIndex;
	/* 0030 */	int		itemInfoIndex; // used in CSharedItemData_GetInfo_78DE20
	/* 0034 */	int		VehicleIndex;
	/* 0038 */  __int64 i38;
	/* 0040 */  __int64 i40;
	/* 0048 */  __int64 i48;
	/* 0050 */ 	int	isLoot; // used in CWorld::PickItem, Amped CItem::TimerExpired hook
	/* 0054 */	int	prevItemIndex;
	/* 0058 */	int	nextItemIndex;
	/* 005C */	int	dw5C;
	/* 0060 */	int	dw60;
	/* 0064 */	int	state; // =1 in AtomicDropItem2::Do();
	/* 0068 */	int	amount;
	/* 006C */	int	nDBID;
	/* 0070 */	int	nClassID; // from itemdata.txt
	/* 0074 */	int	item_type; // aka itemType2  0-weapon  1-shield/armor  2-ring/earring/necklace  3-questitem  4-adena  5-etcitem
	/* 0078 */	int	bodyPart; // slot bit (1 << slotType)

				union {
	/* 007C */		int bless;
	/* 007C */		int lotto_round; // [lottery_ticket] only
	/* 007C */		int race_lane;   // [monster_race_ticket%] only
				};

	/* 0080 */	int	consume_type;
	/* 0084 */	int	damaged;

				union {
	/* 0088 */		int enchant;
	/* 0088 */		int pet_level;
	/* 0088 */		int lotto_numbers; // [lottery_ticket] only, 20-bit mask
	/* 0088 */		int race_round;    // [monster_race_ticket%] only
				};

	/* 008C */	int	dw8C;

	// I don't know if any offsets are wrong, but size should be 0x90
	// -- Light'm
	// 0090 */	int	timerIndex;
};

enum CrystalType
{
	CRYSTAL_NONE = 0x00,
	CRYSTAL_D = 0x01,
	CRYSTAL_C = 0x02,
	CRYSTAL_B = 0x03,
	CRYSTAL_A = 0x04,
	CRYSTAL_S = 0x05,
    CRYSTAL_S80 = 0x06
};

class CItem : public CObject
{
public:
	
	/* 0030 */	CSharedItemData *SD;
	/* 0038 */	CItemInfo* II;
	/* 0040 */  CRITICAL_SECTION *cs_Item;
	/* 0048 */	INT64 __qw0048[2];

	/* 02D8 */  virtual int         _vfunc02D8() = 0; // return 0
	/* 02E0 */  virtual bool        _vfunc02E0() = 0; // return true
	/* 02E8 */  virtual bool        IsTrade() = 0;
	/* 02F0 */  virtual bool        IsDrop() = 0;
	/* 02F8 */  virtual bool        IsDestruct() = 0;
	/* 0300 */  virtual bool        _vfunc0300() = 0; // return false

	bool IsValidSD();
	bool IsValidItem();
	bool IsHerbItem();
	bool IsValidCWeapon();
	bool IsValidCEtcWeapon();
	bool IsValidCAsset();
	bool IsValidCArmor();
	bool IsValidCAccessary();
	bool IsValidCQuestItem();

	bool IsLotteryTicket() const
	{
		return nObjectType == 4442;
	}

	bool IsMonsterRaceTicket() const
	{
		return nObjectType == 4443 || nObjectType == 4444;
	}

	static void CItemConstructor(CSharedItemData *itemSharedData);
	static void CItemDestructor(CSharedItemData *itemSharedData);

	static CSPointer<CItem> FindItemSP(int nItemIndex)
	{
		typedef void (*FFindItem)(__int64, CSPointer<CItem>*, int);
		__int64 pItemFactory = 0x0E412130;
		CSPointer<CItem> tmp;
		FFindItem(0x4745F0)(pItemFactory, &tmp, nItemIndex);
		return tmp;
	}
};

class CAccessary : public CItem
{
};

class CAsset : public CItem
{
};

class CArmor : public CItem
{
};

class CQuestItem : public CItem
{
};

class CWeapon : public CItem
{
};

class CEtcItem : public CItem
{
public:
	/* 58 */	BYTE	unk058;
	/* 59 */	BYTE	unk059;
	/* 5A */	BYTE	unk05A;
	/* 5B */	BYTE	unk05B;
	/* 5c */	int		unk05c;
};

#pragma pack( pop )
