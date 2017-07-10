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

class CSetItem
{
public:

	/* 0000 */      void* _vmt;
	/* 0008 */      int nSetID;
	/* 000C */      int nSlotUnderWear;
	/* 0010 */      int nSlotREar;
	/* 0014 */      int nSlotLEar;
	/* 0018 */      int nSlotNeck;
	/* 001C */      int nSlotRFinger;
	/* 0020 */      int nSlotLFinger;
	/* 0024 */      int nSlotHead;
	/* 0028 */      int nSlotRHand;
	/* 002C */      int nSlotLHand;
	/* 0030 */      int nSlotGloves;
	/* 0034 */      int nSlotChest;
	/* 0038 */      int nSlotLegs;
	/* 003C */      int nSlotFeet;
	/* 0040 */      int nSlotBack;
	/* 0044 */      int nSlotRLHand;
	/* 0048 */      int _unk0048;
	/* 004C */      int _unk004C;
	/* 0050 */      int _unk0050;
	/* 0054 */      int nAdditionalSlotType; // additional_slot=[x] in itemdata.txt
	/* 0058 */      double fPDefPerBonus1;
	/* 0060 */      double fMDefPerBonus1;
	/* 0068 */      double fMaxHPBonusDiff1;
	/* 0070 */      double fMaxMPBonusDiff1;
	/* 0078 */      double fBreathDiff1;
	/* 0080 */      double _unk0080;
	/* 0088 */      double fCastSpdPerBonus1;
	/* 0090 */      double fSpeedDiff1;
	/* 0098 */      double fPDefPerBonus2;
	/* 00A0 */      double fMDefPerBonus2;
	/* 00A8 */      double fMaxHPBonusDiff2;
	/* 00B0 */      double fMaxMPBonusDiff2;
	/* 00B8 */      double fBreathDiff2;
	/* 00C0 */      double _unk00C0;
	/* 00C8 */      double fSpeedDiff2;
	/* 00D0 */      double fCastSpdPerBonus2;
	/* 00D8 */      double fPAtkPerBonus1;
	/* 00E0 */      double fMAtkPerBonus1;
	/* 00E8 */      double fHPRegenPerBonus1;
	/* 00F0 */      double fMPRegenPerBonus1;
	/* 00F8 */      double fAvoidRateDiff1;
	/* 0100 */      double fShieldDefRatePerBonus1;
	/* 0108 */      double fWeightPenaltyDiff1;
	/* 0110 */      double fCreature1290hPerBonus1;
	/* 0118 */      double fCreature1240hPerBonus1;
	/* 0120 */      int nStrBonus;
	/* 0124 */      int nConBonus;
	/* 0128 */      int nDexBonus;
	/* 012C */      int nIntBonus;
	/* 0130 */      int nMenBonus;
	/* 0134 */      int nWitBonus;
	/* 0138 */      double fPAtkPerBonus2;
	/* 0140 */      double fMAtkPerBonus2;
	/* 0148 */      double fHPRegenPerBonus2;
	/* 0150 */      double fMPRegenPerBonus2;
	/* 0158 */      double fAvoidRateDiff2;
	/* 0160 */      double fShieldDefRatePerBonus2;
	/* 0168 */      double fWeightPenaltyDiff2;
	/* 0170 */      double fCreature1290hPerBonus2;
	/* 0178 */      double fCreature1240hPerBonus2;
	/* 0180 */      int nStrBonus2; // for when additional slot is equiped
	/* 0184 */      int nConBonus2;
	/* 0188 */      int nDexBonus2;
	/* 018C */      int nIntBonus2;
	/* 0190 */      int nMenBonus2;
	/* 0194 */      int nWitBonus2;
	/* 0198 */      std::wstring wstrSetSkillName;
	/* 01C0 */      std::wstring wstrSetEffectSkillName;
	/* 01E8 */      std::wstring wstrSetAdditionalSkillName;
	/* 0210 */  
};
