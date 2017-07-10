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

#include "Global.H"
#include <windows.h>
#include <time.h>
#include "MemoryObject.h"
#include "NPCEvent.h"

class CObjectEx;
class NPCEvent;

class CNPC : public MemoryObject
{
	public:

		enum ArraySizes
		{
			ABNORMALS = 36,
			QUESTS = 26,
			EXT_SLOTS = EquipSlotType::Last - EquipSlotType::LastC4,
		};

		/* Functions */

		void AddAbnormalStatus(int nAbnormalType, int nLevel);
		void DeleteAbnormalStatus(int nAbnormalType);
		void DeleteAllAbnormalStatus();

		int& EquippedItemIndex(int nSlotType)
		{
			if (nSlotType > EquipSlotType::LastC4)
				return nExtEquipment[nSlotType - (EquipSlotType::LastC4 + 1)];
			else
				return nEquipment[nSlotType];
		}

		/* Variables */
		/* 0018 */ void	*ArgFuncTable;
		/* 0020 */ void	*pWorld;
		/* 0028 */ int	nObjectID;
		/* 002C */ int	nObjectID2;

		/* 0030 */ int	nType;
		/* 0034 */ int	_dw0034;
		/* 0038 */ int	_dw0038;
		/* 003C */ int	_dw003C;

		/* 0040 */ int	_dw0040;
		/* 0044 */ int	_dw0044;
		/* 0048 */ int	_dw0048;
		/* 004C */ int	_dw004C;

		/* 0050 */ CSharedData	*pSD;
		/* 0058 */ int	_dw0058;	//-1
		/* 005C */ int	_dw005C;	//0

		/* 0060 */ int	_dw0060;	//0
		/* 0064 */ int	_dw0064;
		/* 0068 */ void	*pObject;

		/* 0070 */ int	_dw0070;
		/* 0074 */ int	_dw0074;
		/* 0078 */ int	_dw0078;
		/* 007C */ int	_dw007C;

		/* 0080 */ int	_dw0080;
		/* 0084 */ int	_dw0084;
		/* 0088 */ void	*punk088;
		/* 0090 */ int	_dw0090;
		/* 0094 */ int	_dw0094;
		/* 0098 */ int	_dw0098;
		/* 009C */ int	_dw009C;
		
		/* 00A0 */ int	_dw00A0;
		/* 00A4 */ int	_dw00A4;
		/* 00A8 */ int	_dw00A8;
		/* 00AC */ int	_dw00AC;
		
		/* 00B0 */ int	_dw00B0;
		/* 00B4 */ int	_dw00B4;
		/* 00B8 */ void	*punk00B8;
		/* 00C0 */ int	_dw00C0; // +
		/* 00C4 */ int	_dw00C4;
		/* 00C8 */ int	_dw00C8;
		/* 00CC */ int	_dw00CC;
		/* 00D0 */ int	_dw00D0;
		/* 00D4 */ int	_dw00D4;
		/* 00D8 */ int	_dw00D8;
		/* 00DC */ int	_dw00DC;
		/* 00E0 */ int	_dw00E0;
		/* 00E4 */ int	_dw00E4;
		/* 00E8 */ int	_dw00E8;
		/* 00EC */ int	_dw00EC;
		/* 00F0 */ int	_dw00F0;
		/* 00F4 */ int	_dw00F4;
		/* 00F8 */ int	_dw00F8;
		/* 00FC */ int	_dw00FC;
		/* 0100 */ void *punk0100;
		/* 0108 */ INT64 _qw0100;

		/* 0110 */ void *punk0110;
		/* 0118 */ int	nFaceIndex;
		/* 011C */ int	nExp;
		/* 0120 */ int	nSp;

		/* 0124 */ int	nObjIdAdena;
		/* 0128 */ int  nEquipment[18];
		
		/* 0170 */ int	nDefaultINT;
		/* 0174 */ int	nDefaultSTR;
		/* 0178 */ int	nDefaultCON;
		/* 017C */ int	nDefaultMEN;
		/* 0180 */ int	nDefaultDEX;
		/* 0184 */ int	nDefaultWIT;
		
		/* 0188 */ double	fHP;
		/* 0190 */ double	fMP;
		/* 0198 */ double	fCP;
		
		/* 01A0 */ void *punk01A0[11];
		/* 01F8 */ void *punk01f8;
		/* 0200 */ void *punk0200;
		/* 0208 */ void *punk0208;
		/* 0210 */ void *punk0210;
		/* 0218 */ void *punk0218;
		/* 0220 */ void *punk0220;
		/* 0228 */ void *punk0228;
		/* 0230 */ void *punk0230;
		/* 0238 */ int _n238;
		/* 023c */ int _n23c;
		/* 0240 */ int _n240;
		/* 0244 */ void *punk0244;
		/* 024C */ int x;
		/* 0250 */ int y;
		/* 0254 */ int z;
		/* 0258 */ int d;
		/* 025C */ void *punk025C;
		/* 0264 */ void *punk0264;
		/* 026C */ void *punk026C;
		/* 0274 */ void *punk0274;
		/* 027C */ void *punk027C;
		/* 0284 */ void *punk0284;
		/* 028C */ void *punk028C;
		/* 0294 */ void *punk0294;
		/* 029C */ void *punk029C;
		/* 02A4 */ int _n2A4;
		/* 02A8 */ int _n2A8;
		/* 02AC */ int _n2AC;
		/* 02B0 */ int _n2B0;
		/* 02B4 */ int _n2B4;
		/* 02B8 */ int _n2B8;
		/* 02BC */ int _n2BC;
		/* 02C0 */ int _n2C0;
		/* 02C4 */ int _n2C4;
		/* 02C8 */ int _n2C8;
		/* 02CC */ int _n2CC;
		/* 02D0 */ int _n2D0;
		/* 02D4 */ int _n2D4;
		/* 02D8 */ int _n2D8;
		/* 02DC */ int _n2DC;
		/* 02E0 */ int _n2E0;
		/* 02E4 */ int _n2E4;
		/* 02E8 */ int _n2E8;
		/* 02EC */ int _n2EC;
		/* 02F0 */ int _n2F0;
		/* 02F4 */ int _n2F4;
		/* 02F8 */ int _n2F8;
		/* 02FC */ int _n2FC;
		/* 0300 */ int _n300;
		/* 0304 */ int _n304;
		/* 0308 */ int _n308;
		/* 030C */ int _n30C;
		/* 0310 */ int _n310;
		/* 0314 */ int _n314;
		/* 0318 */ int _n318;
		/* 031C */ int _n31C;

		/* 0320 */ int nIsPledgeLeader;
		/* 0324 */ int nAllianceId;
		/* 0328 */ int _n328;
		/* 032C */ int _n32C;

		/* 0330 */ int _n330;
		/* 0334 */ int _n334;
		/* 0338 */ int _n338;
		/* 033C */ void *punk033C;
		/* 0344 */ int _n0344;
		/* 0348 */ int _n0348;
		/* 034C */ int _n034C;

		/* 0350 */ int _n350;
		/* 0354 */ int _n354;
		/* 0358 */ int _n358;
		/* 035C */ int _n35C;

		/* 0360 */ double _f360;
		/* 0368 */ int nIsSpiritshot; //Spiritshot /Blessed spiritshot = 1
		/* 036C */ int bIsRiding;
		
		/* 0370 */ double SpiritShotMulti;
		/* 0378 */ int _n378; // shouldn't be int64/double? .text:4E74E7 mov [rax+378h], r14
		/* 037C */ bool bSoulShot;
		/* 037D */ bool _b37D;
		/* 037E */ short _w37E;
		
		/* 0380 */ double fSoulShotPower;
		/* 0388 */ bool bSpiritShot;
		/* 0389 */ bool _b389;
		/* 038A */ short _w38A;
		/* 038C */ int _n38C;

		/* 0390 */ double fSpiritShotPower;
		/* 0398 */ int _n398;
		/* 039C */ int _n39C;

		/* 03A0 */ int _n3A0;
		/* 03A4 */ int _n3A4;
		/* 03A8 */ int _n3A8;
		/* 03AC */ int _n3AC;

		/* 03B0 */ int _n3B0;
		/* 03B4 */ int _n3B4;
		/* 03B8 */ int _n3B8;
		/* 03BC */ int _n3BC;

		/* 03C0 */ int _n3C0;
		/* 03C4 */ int _n3C4; // must be 0 or message 1065, While operating a private store or workshop, you cannot discard, destroy, or trade an item.
		/* 03C8 */ int _n3C8;
		/* 03CC */ int _n3CC;

		/* 03D0 */ int _n3D0;
		/* 03D4 */ int _n3D4;
		/* 03D8 */ int nIsNewbieC4;
		/* 03DC */ int nCharId;

		/* 03E0 */ int nDefaultWeaponType;
		/* 03E4 */ int _n3E4;
		/* 03E8 */ int nDefaultAttackRange;
		/* 03EC */ int nDefaultDamageRange[4];
		/* 03FC */ int nDefaultRandomDamage;

		/* 0400 */ int nDefaultBasePhysAttack;
		/* 0404 */ int _n404;
		/* 0408 */ int nDefaultBaseAttackSpeed;
		/* 040C */ int nDefaultBaseCritical;

		/* 0410 */ int _n410;
		/* 0414 */ int nBaseAttackSpeed;
		/* 0418 */ int nBaseCritical;

		/* 041C */ int nINT;
		/* 0420 */ int nSTR;
		/* 0424 */ int nCON;
		/* 0428 */ int nMEN;
		/* 042C */ int nDEX;
		/* 0430 */ int nWIT;
		
		/* 0434 */ int nHenna1;
		/* 0438 */ int nHenna2;
		/* 043C */ int nHenna3;
		/* 0440 */ int _n440;

		//=====================//

		/* 0444 */ int nLevel;
		/* 0448 */ int _n448;
		/* 044C */ int _n44C;
		/* 0450 */ int _n450;
		/* 0454 */ int _n454;
		/* 0458 */ int _n458;
		/* 045C */ int _n45C;
		/* 0460 */ int _n460;
		/* 0464 */ int _n464;
		/* 0468 */ int _n468;
		/* 046C */ int _n46C;
		/* 0470 */ int _n470;
		/* 0474 */ int _n474;
		/* 0478 */ int _n478;
		/* 047C */ int _n47C;
		/* 0480 */ int _n480;
		/* 0484 */ int _n484;
		/* 0488 */ double _f488; // returned from sub_4D21E0 (CCreature vfunc6B8)

		/* 0490 */ int nMaxSlot;
		/* 0494 */ int nCurrSlot;
		/* 0498 */ int nCurrWeight;
		/* 049C */ int _n49C;

		/* 04A0 */ double fMaxLoad;
		/* 04A8 */ double fOrgHP;
		/* 04B0 */ double fOrgMP;
		/* 04B8 */ double fOrgCP;
		/* 04C0 */ double fMaxHP;
		/* 04C8 */ double fMaxMP;
		/* 04D0 */ double fMaxCP;
		/* 04D8 */ double _fHpRegen;
		/* 04E0 */ double _fMpRegen;
		/* 04E8 */ double _fCpRegen;
		/* 04F0 */ double fOrgHpRegen;
		/* 04F8 */ double fOrgMpRegen;
		/* 0500 */ double fOrgCpRegen;
		/* 0508 */ double fOrgSpeed; // sub_4D8E90 (CCreature vfunc498) returns (fNoise / f508)
		/* 0510 */ double fNoise;
		/* 0518 */ double fHit;
		/* 0520 */ double fAvoid;
		/* 0528 */ double _f528;
		/* 0530 */ double _f530;
		/* 0538 */ double fAccuracy;
		/* 0540 */ double fEvasion;
		/* 0548 */ double _f548; // sub_4D8E10 (CCreature vfunc3D8) sets
		                         //     f548 = (fAttackSpeed > 0 ? 500 / fAttackSpeed : 1.8)
		                         // sub_4D8E60 (CCreature vfunc490) returns
		                         //     (nWeaponAtkSpeed > 0 ? 1.8 / f548 : 1.0)

		/* 0550 */ int _n550;
		/* 0554 */ int _n554;
		/* 0558 */ int _n558;
		/* 055C */ int _n55C;
		/* 0560 */ int _n560;
		/* 0564 */ int _n564;
		
		/* 0568 */ int nWeaponID;
		/* 056C */ int nWeaponType;
		
		/* 0570 */ int nMaterialType;
		/* 0574 */ int _n574;
		/* 0578 */ int _n578;
		/* 057C */ int nWeaponRange;

		/* 0580 */ int nDamageRange1;
		/* 0584 */ int nDamageRange2;
		/* 0588 */ int nDamageRange3;
		/* 058C */ int nDamageRange4;
		/* 0590 */ int nWeaponRandomDmg;
		/* 0594 */ int nWeaponPhysDmg;
		/* 0598 */ int _n598;
		/* 059C */ int nWeaponAtkSpeed;
		/* 05A0 */ int nNoWeaponCritical;
		/* 05A4 */ int nWeaponMagicDmg;
		/* 05A8 */ int _n5A8;
		/* 05AC */ int _n5AC;

		/* 05B0 */ double fPAtk;
		/* 05B8 */ double fPDef;
		/* 05C0 */ double fMAtk;
		/* 05C8 */ double fMDef;
		/* 05D0 */ double fAtkSpeed;
		/* 05D8 */ double fBaseCritical;
		/* 05E0 */ double _f5E0;
		/* 05E8 */ double fBaseAtkSpeed;
		/* 05F0 */ double fBaseCastSpeed;

		/* 05F8 */ int _n5F8;
		/* 05FC */ int _n5FC;
		/* 0600 */ int _n600;
		/* 0604 */ int _n604;
		/* 0608 */ int _n608;
		/* 060C */ int _n60C;
		/* 0610 */ int _n610;
		/* 0614 */ int _n614;

		/* 0618 */ int nBuilderLevel;

		/* 061C */ int _n61C;
		/* 0620 */ int _n620;
		/* 0624 */ int _n624;
		/* 0628 */ int _n628;
		/* 062C */ int nLastBlowWeaponClassID;
		/* 0630 */ int nSSQRoundNumber;
		/* 0634 */ int nSSQPart;
		/* 0638 */ int _n638;
		/* 063C */ int nSealSelectionNo;
		/* 0640 */ int _n640;
		/* 0644 */ int _n644;
		/* 0648 */ int _n648;
		/* 064C */ int _n64C;
		/* 0650 */ int _n650;
		/* 0654 */ int _n654;
		/* 0658 */ int _n658;
		/* 065C */ void *punk65C;
		/* 0664 */ int nInPeaceZone;
		/* 0668 */ int nInBattleField;
		/* 066C */ wchar_t wszAI[64];
		/* 06EC */ int _n6EC;
		/* 06F0 */ int _n6F0;
		/* 06F4 */ int _n6F4;
		/* 06F8 */ int _n6F8;
		/* 06FC */ int _n6FC;

		/* 0700 */ void *punk0700;
		/* 0708 */ int _n0708;
		/* 070C */ int _n070C;
		/* 0710 */ int _n0710;
		/* 0714 */ int _n0714;
		/* 0718 */ int _n0718;
		/* 071C */ int _n071C;
		/* 0720 */ int _n0720;
		/* 0724 */ int _n0724;
		/* 0728 */ int _n0728;
		/* 072C */ int _n072C;
		/* 0730 */ int _n0730;
		/* 0734 */ void *punk0734;
		/* 073C */ void *punk073C;
		/* 0744 */ int _n0744;
		/* 0748 */ double _f748; // used in CCreature::WeaponHitCorrection
		/* 0750 */ double _f750; // used in CCreature::AvoidCorrection
		/* 0758 */ int _n0758;
		/* 075C */ int _n075C;
		/* 0760 */ int _n0760;
		/* 0764 */ int _n0764;
		/* 0768 */ int _n0768;
		/* 076C */ int _n076C;
		/* 0770 */ int _n0770;
		/* 0774 */ int _n0774;
		/* 0778 */ int nSummonType;
		/* 077C */ int _n077C;
		/* 0780 */ int nMasterID;
		/* 0784 */ int _n0784;
		/* 0788 */ int nNPCClassID; // same as pCreature->nObjectType
		/* 078C */ int nWeightPoint;
		/* 0790 */ int nRespawnTime;
		/* 0794 */ int nClanRelationIndex;
		/* 0798 */ int nClanRelationUnk1;
		/* 079C */ int nClanRelationUnk2;
		/* 07A0 */ int _n07A0;
		/* 07A4 */ int _n07A4;
		/* 07A8 */ int _n07A8;
		/* 07AC */ int _n07AC;
		/* 07B0 */ int nClanHelpRange;				// default 500 (.text:00000000004D7F58)
		/* 07B4 */ int _n07B4;
		/* 07B8 */ double nAcquireExpRate;			//transform NPCData acquire_exp_rate from int to double
		/* 07C0 */ int nPState;
		/* 07C4 */ int _n07C4;
		/* 07C8 */ int _n07C8;
		/* 07CC */ int _n07CC;
		/* 07D0 */ int _n07D0;
		/* 07D4 */ int _n07D4;
		/* 07D8 */ CSharedData *pMasterSD;
		/* 07E0 */ int nAction;
		/* 07E4 */ int _n07E4;
		/* 07E8 */ int _n07E8;
		/* 07EC */ int _n07EC;
		/* 07F0 */ int _n07F0;
		/* 07F4 */ int _n07F4;
		/* 07F8 */ int _n07F8;
		/* 07FC */ int _n07FC;

		/* 0800 */ int _n0800;
		/* 0804 */ int _n0804;
		/* 0808 */ int _n0808;
		/* 080C */ int _n080C;
		/* 0810 */ int nFlag;
		/* 0814 */ int nCurrentFeed;
		/* 0818 */ int nMaxFeed;
		/* 081C */ int nPetDBID;
		/* 0820 */ int nStriderLevel;
		/* 0824 */ int _n0824;
		/* 0828 */ int nMaxMagicLevel;
		/* 082C */ int OldAbnormalTable[20][2];
		/* 08CC */ int nDBValue;
		/* 08D0 */ int nDualGara1;
		/* 08D4 */ int nDualGara2;
		/* 08D8 */ int nTradeSkillLevel;
		/* 08DC */ int nMakerParam1;
		/* 08E0 */ int nMakerParam2;
		/* 08E4 */ int nMakerParam3;
		/* 08E8 */ UINT64 PledgePower1;				// Chronicle 4 Pledge Powers Are Stored Here
		/* 08F0 */ UINT64 PledgePower2;				// Never Used / Unknown
		/* 08F8 */ UINT64 PledgePower3;				// Never Used / Unknown
		/* 0900 */ UINT64 PledgePower4;				// Never Used / Unknown
		/* 0908 */ int nLang;						// Korea=0, USA=1, Japan=2, Taiwan=3, China=4, Thailand=5
		/* 090C */ int _n90C;						// End of the Original Shared Data

		// additional FIXED-offset members

		// please, move members that you know don't need to be at a particular offset
		// to the next section; this is too fragile, and we could also use pack (8) in the future
		// -- Light'm

		/* 0910 */ AbnormalInfo AbnormalTable[ABNORMALS];	// New Abnormal Table
		/* 0A30 */ int nPledgeType;
		/* 0A34 */ CObjectEx *pObjectEx;
		/* 0A3C */ QuestData Quests[QUESTS];
		/* 0BDC */ bool bCWOwner;					// True = Has Cursed Weapon
		/* 0BDD */ INT8 restbCWOwner[3];
		/* 0BE0 */ __int64 nExp64;					// new 64-bit experience
		/* 0BE8 */ bool nIsPackageSell;
		/* 0BE9 */ bool nIsDuel;
		/* 0BEA */ INT64 nC5Privileges;
		/* 0BF2 */ INT32 nTitleColor;
		/* 0BF6 */ INT32 nLevelJoinAcademy;
		/* 0BFA */ INT32 nEnchantType;
		/* 0BFE */ INT32 nSponsorID;
		/* 0C02 */ INT32 nApprenticeID;
		/* 0C06 */ INT32 nRank;
		/* 0C0A */ INT32 nAugmentationID;
		/* 0C0E */ INT32 nAugmentSkillID;
		/* 0C10 */ int _unk0c10;
		/* 0C14 */ int _unk0c14;
		/* 0C18 */ int _unk0c18;
		/* 0C1C */ int _unk0c1C;
		/* 0C20 */ int _unk0c20;
		/* 0C24 */ int _unk0c24;
		/* 0C28 */ int _unk0c28;
		/* 0C2C */ int _unk0c2C;
		/* 0C30 */ int _unk0c30;


		// additional RANDOM-offset members

		int nExtEquipment[EXT_SLOTS];

		static void SetAugment(CNPC *pNPC, CSharedData *talker);
		static void DeleteAugment(CNPC *pNPC, CSharedData *talker);
		static void ShowPledgeSkillList(CNPC *pNPC, CSharedData *talker);
		static CNPC* Find(unsigned int id);
		int HandleEvent(NPCEvent* pEvent);
};
