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

class CGameEvents
{
	public:

		static void Initialize();
		/*static void OnLeaveWorld(User *pUser);
		static void OnEnterWorld(User *pUser);
		static void OnValidateNoblesseSkills(VOID *pNoblessSystem, User *pUser);*/
		static void OnLoadData();
		static bool OnCreatureDie(CCreature *pCreature, CCreature *pEnemy);
		/*static bool OnUserDie(User *pUser, CCreature *pEnemy);
		static void OnInitializeSkillMod(CCreature *pCreature);
		static bool OnUserEquipItem(User *pUser, CItem *pItem, int nSlotType);
		static void OnUserUnequipItem1(User *pUser, CItem *pItem);
		static void OnUserUnequipItem2(User *pUser, int nSlotType);
		static void PlayerItemPickUp(CInventory *pInventory, CItem *pItem, int nChangedType);
		static void PetItemPickUp(CInventory *pInventory, CItem *pItem, int nChangedType);*/
		static INT32 GetPartyRoutingType(CParty *pParty, CItem *pItem);
		//static void OnSendETCBuffBar(CSocket *pSocket,const char *format, ...);
		//static void OnDieDropItem(User *pUser, bool bUnknown);
		static CCreature *OnCreatureConstruction(CCreature *pCreature);
		static CCreature *OnCreatureConstructionOther(CCreature *pCreature, const CCreature *pOther);
		static void OnCreatureDestruction(CCreature *pCreature);
		/*static bool OnInfectedSkillBy(CCreature *pCreature, CCreature *pSource, CSkillInfo *pSkillInfo);
		static bool OnUseItem(CCreature *pCreature, CItem *pItem, INT32 nUnknown);
		static void OnAbnormalTypeExpired(CSharedData *pSharedData, INT32 nAbnormalType);
		static void OnCreatureTalk(CCreature *pCreature, INT32 nUnknown);
		static bool OnIsRealEnemyTo(User *pUser, User *pAttacker);
		static bool OnIsEnemyTo(User *pUser, User *pAttacker);
		static int GetRelationTo(User *pUser, User *pAttacker);
		static bool OnNPCIsEnemyTo(CNPC *pNPC, CCreature *pCreature);
		static bool ItemUsable(CPet *pPet, CItem *pItem);*/
		static void OnDeleteObject(unsigned int nSID);
		static bool OnCreatureDropItem(CCreature* pCreature, CItem* pItem, INT32 nUnk, __int64 nUnk2);//WAGNER 201 AUTOPICKUP
};

extern "C"
{
	// ASM Hooks
	void GetPartyRoutingTypeHook();

	// ASM Wrappers
	INT32 CGameEvents_GetPartyRoutingType(CParty *pParty, CItem *pItem);
}