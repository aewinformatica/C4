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
#include "CIOCriticalSection.h"
#include "CIOObject.h"

//Function Table Addresses 
#define MEMORYOBJ_FUNCTION_TABLE_ADDR 0x97E3B8 
#define COBJECT_FUNCTION_TABLE_ADDR 0xA37138 
#define CGENERALOBJ_FUNCTION_TABLE_ADDR 0xA383A8 
#define CSTATICOBJ_FUNCTION_TABLE_ADDR 0xA75888 
#define CVEHICLE_FUNCTION_TABLE_ADDR 0xA9A068 
#define CCREATURE_FUNCTION_TABLE_ADDR 0x9B08B8 
#define CNPC_FUNCTION_TABLE_ADDR 0xA289D8 
#define CSUMMON_FUNCTION_TABLE_ADDR 0xA4A708 
#define CPET_FUNCTION_TABLE_ADDR 0xA4B078 
#define CBOSS_FUNCTION_TABLE_ADDR 0x988F78 
#define CZZOLDAGU_FUNCTION_TABLE_ADDR 0xAA09C8 
#define USER_FUNCTION_TABLE_ADDR 0xA871B8
#define CMERCHANT_FUNCTION_TABLE_ADDR 0xA1ABB8

class CAgitDecoVisible;
class CBattleCamp;
class CBoss;
class CDoor;
class CChair;
class CContainer;
class CControlTower;
class CEventController;
class CEventMatch;
class CGeneralServerObject;
class CHolyThing;
class CObserverRemains;
class CPet;
class CMerchant;
class CNPC;
class CSignBoard;
class CStaticObject;
class CSummon;
class CVehicle;

typedef int HearResult; // unknown enum
struct ItemDropStruct;

enum ObjectFieldType
{
	OFT_class_id                  =   0, // int (usually unnamed)
	OFT_race                      =  78, // int
	OFT_occupation                =  79, // int
	OFT_sex                       =  80, // int

	// itemdata:item
	OFT_armor_type                =   4, // int
	OFT_item_type                 =   5, // int
	OFT_slot_bit_type             =   6, // int[]
	OFT_blessed                   =   7, // int
	OFT_weight                    =   8, // int
	OFT_consume_type              =   9, // int
	OFT_soulshot_count            =  12, // int
	OFT_spiritshot_count          =  13, // int
	OFT_reduced_soulshot          =  14, // int[2]
	OFT_reduced_spiritshot        =  15, // int[2]
	OFT_immediate_effect          =  16, // int
	OFT_price                     =  20, // int
	OFT_default_price             =  21, // int
	OFT_item_skill                =  38, // wchar*
	OFT_material_type             =  39, // int
	OFT_crystal_type              =  40, // int
	OFT_crystal_count             =  41, // int
	OFT_weapon_type               =  51, // int
	OFT_attack_range              =  54, // int
	OFT_damage_range              =  57, // int[4]
	OFT_reduced_mp_consume        =  61, // int[2]
	OFT_damaged                   =  64, // int
	OFT_physical_defense          =  65, // int
	OFT_enchanted                 =  67, // int
	OFT_mp_bonus                  =  70, // int
	OFT_critical_attack_skill     =  71, // wchar*
	OFT_attack_skill              =  72, // wchar*
	OFT_magic_skill               =  73, // wchar* [, int]
	OFT_item_skill_enchanted_four =  74, // wchar*
	OFT_equip_pet                 =  75, // int[0..4]
	OFT_avoid_modify              = 172, // double
	OFT_hit_modify                = 173, // double
	OFT_etcitem_type              = 177, // int
	OFT_html                      = 182, // wchar*

	// itemdata:set
	OFT_slot_underwear            = 183, // int
	OFT_slot_rear                 = 184, // int
	OFT_slot_lear                 = 185, // int
	OFT_slot_neck                 = 186, // int
	OFT_slot_rfinger              = 187, // int
	OFT_slot_lfinger              = 188, // int
	OFT_slot_head                 = 189, // int
	OFT_slot_rhand                = 190, // int
	OFT_slot_lhand                = 191, // int
	OFT_slot_gloves               = 192, // int
	OFT_slot_chest                = 193, // int
	OFT_slot_legs                 = 194, // int
	OFT_slot_feet                 = 195, // int
	OFT_slot_back                 = 196, // int
	OFT_slot_rlhand               = 197, // int
	OFT_slot_additional           = 188, // int

	// npcdata:npc
	OFT_exp                       =  88, // double (or int, but Set(double) is called in the end)
	OFT_acquire_exp_rate          = 178, // double (or int, but Set(double) is called in the end)
};

class CObject : public CIOObject
{
	public:

		/* 0x020 */     int nSID;
		/* 0x024 */     int nObjectID;
		/* 0x028 */     int nObjectType;
		/* 0x02C */     int nTimerStateType; // 3 - sleep mode
											 // 4 - freezing

		enum VTable
        {
                VMTMemoryObject		= 0x97E3B8,
                VMTCObject			= 0xA37138,
                VMTCGeneralObject	= 0xA383A8,
                VMTCStaticObject	= 0xA75888,
                VMTCVehicle			= 0xA9A068,
                VMTCCreature		= 0x9B08B8,
                VMTCNPC				= 0xA289D8,
                VMTCSummon			= 0xA4A708,
                VMTCPet				= 0xA4B078,
                VMTCBoss			= 0x988F78,
                VMTCZzoldagu		= 0xAA09C8,
                VMTUser				= 0xA871B8,
				VMTPledge			= 0xA53448,
				VMTCAlliance		= 0x97DE58,
				VMTCMerchant		= 0xA1ABB8,
				VMTCItem			= 0xA07CF8,
				VMTCWeapon			= 0xA0B368,
				VMTCEtcItem			= 0xA0A448,
				VMTCAsset			= 0xA09558,
				VMTCArmor			= 0xA09CC8,
				VMTCAccessary		= 0xA08DC8,
				VMTCQuestItem		= 0XA0ABD8,
				VMTCDoor			= 0X9E20F8
        };

		CItem* NewObjectItem(bool isTrueInstance)
		{
			typedef CItem *(__thiscall *_f) (CObject*const, bool);
			_f xf = (_f)0x0062D9C0L;
			return xf(this, isTrueInstance);
		}

        bool IsValidObject(VTable vTable)
        {
            if(this)
			{
                __try
				{ 
					if(*(VTable*)this == vTable) return true; 
				}
                __except(EXCEPTION_EXECUTE_HANDLER)
				{ 
					/* Invalid pointer */
					/* Preventing Crash ;) */
				}
            }

			return false;
        }

/* 00A8 */  virtual FVector     GetPosition() = 0;
/* 00B0 */  virtual HeadingDir  GetHeading() = 0;
/* 00B8 */  virtual int         GetSharedDataIndex() = 0;

/* 00C0 */  virtual CObject*    Copy() = 0;
/* 00C8 */  virtual void        Delete() = 0;

/* 00D0 */  virtual bool        IsVehicle() = 0;
/* 00D8 */  virtual CVehicle*   AsVehicle() = 0;

/* 00E0 */  virtual bool        IsNPC() = 0;
/* 00E8 */  virtual bool        IsPet() = 0;
/* 00F0 */  virtual bool        IsSummon() = 0;
/* 00F8 */  virtual bool        IsMerchant() = 0;
/* 0100 */  virtual bool        IsBoss() = 0;
/* 0108 */  virtual bool        IsMinion() = 0;

/* 0110 */  virtual CSummon*    AsSummon() = 0;
/* 0118 */  virtual CPet*       AsPet() = 0;
/* 0120 */  virtual CNPC*       AsNPC() = 0;
/* 0128 */  virtual CMerchant*  AsMerchant() = 0;
/* 0130 */  virtual CBoss*      AsBoss() = 0;

/* 0138 */  virtual bool        IsWeapon() = 0;
/* 0140 */  virtual bool        IsArmor() = 0;
/* 0148 */  virtual bool        IsAccessory() = 0;
/* 0150 */  virtual bool        IsQuestItem() = 0;
/* 0158 */  virtual bool        IsAsset() = 0;
/* 0160 */  virtual bool        IsEtcItem() = 0;
/* 0168 */  virtual bool        IsStaticObject() = 0;
/* 0170 */  virtual bool        IsDoor() = 0;
/* 0178 */  virtual bool        IsHolyThing() = 0;
/* 0180 */  virtual bool        IsBattleCamp() = 0;
/* 0188 */  virtual bool        IsSignBoard() = 0;
/* 0190 */  virtual bool        IsObserverRemains() = 0;
/* 0198 */  virtual bool        IsChair() = 0;
/* 01A0 */  virtual bool        IsControlTower() = 0;
/* 01A8 */  virtual bool        IsEventController() = 0;
/* 01B0 */  virtual bool        IsGeneralServerObject() = 0;
/* 01B8 */  virtual bool        IsAgitDecoVisible() = 0;
/* 01C0 */  virtual bool        IsEventMatch() = 0;

/* 01C8 */  virtual CStaticObject*        AsStaticObject() = 0;
/* 01D0 */  virtual CDoor*                AsDoor() = 0;
/* 01D8 */  virtual CHolyThing*           AsHolyThing() = 0;
/* 01E0 */  virtual CBattleCamp*          AsBattleCamp() = 0;
/* 01E8 */  virtual CSignBoard*           AsSignBoard() = 0;
/* 01F0 */  virtual CObserverRemains*     AsObserverRemains() = 0;
/* 01F8 */  virtual CChair*               AsChair() = 0;
/* 0200 */  virtual CControlTower*        AsControlTower() = 0;
/* 0208 */  virtual CEventController*     AsEventController() = 0;
/* 0210 */  virtual CGeneralServerObject* AsGeneralServerObject() = 0;
/* 0218 */  virtual CAgitDecoVisible*     AsAgitDecoVisible() = 0;
/* 0220 */  virtual CEventMatch*          AsEventMatch() = 0;

/* 0228 */  virtual CContainer*           GetContainer() = 0;

/* 0230 */  virtual bool        IsRealEnemyTo(CCreature* pAttacker) = 0;
/* 0238 */  virtual bool        IsEnemyTo(CCreature *pAttacker) = 0;
/* 0240 */  virtual bool        IsMakeAttackerGuilty(CCreature *pAttacker) = 0;
/* 0248 */  virtual bool        IsMakeAttackerChao(CCreature *pAttacker) = 0;
/* 0250 */  virtual bool        IsActiveOrAlive() = 0;

/* 0258 */  virtual bool        _vfunc0258() = 0; // return false
/* 0260 */  virtual bool        _vfunc0260() = 0; // return false

/* 0268 */  virtual HearResult  Hear(CObject* obj, const WCHAR *name, wchar_t* str, int spt) = 0;
/* 0270 */  virtual void        InSight(CObject *pObject) = 0;
/* 0278 */  virtual void        OutOfSight(CObject *pObject) = 0;
/* 0280 */  virtual FVector     GetMeleeAttackPosition(CCreature* pCreature) = 0;

/* 0288 */  virtual void        SetPV(ObjectFieldType name, std::vector<ItemDropStruct*>* pItemItemDropList) = 0;
/* 0290 */  virtual void        SetV(ObjectFieldType name, std::vector<int>* pIntVector) = 0;
/* 0298 */  virtual void        SetD(ObjectFieldType name, double value) = 0;
/* 02A0 */  virtual void        SetI64(ObjectFieldType name, __int64 value) = 0;
/* 02A8 */  virtual void        SetI(ObjectFieldType name, int value) = 0;
/* 02B0 */  virtual void        SetWI(ObjectFieldType name, const wchar_t* value, int prob) = 0;
/* 02B8 */  virtual void        SetW(ObjectFieldType name, const wchar_t* value) = 0;

/* 02C0 */  virtual const wchar_t*  GetObjectName() = 0;
/* 02C8 */  virtual unsigned int    GetDBID() = 0;
/* 02D0 */  virtual void            SetDBID(unsigned int nDBID) = 0;
};
