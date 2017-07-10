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

#include "CGameEvents.h"

void CGameEvents::Initialize()
{
	/*// Entering / Leaving World
	WriteMemoryDWORD(0xA87738, (INT32)CGameEvents::OnEnterWorld);
	WriteMemoryDWORD(0xA87740, (INT32)CGameEvents::OnLeaveWorld);
	WriteMemoryDWORD(0xA87760, (INT32)CGameEvents::OnUserDie);*/
	WriteMemoryDWORD(0x9B0E60, (INT32)CGameEvents::OnCreatureDie);
	WriteInstruction(0x6C39AC, (INT32)CGameEvents::OnCreatureDie, 0, 0xE8);
	WriteInstruction(0x81E23C, (INT32)CGameEvents::OnCreatureDie, 0, 0xE8);
	WriteInstruction(0x7515CB, (INT32)CGameEvents::OnCreatureDie, 0, 0xE8);/*
	WriteInstruction(0x6BA41E, (INT32)CGameEvents::OnValidateNoblesseSkills, 0, 0xE8);
	WriteInstruction(0x84D3BF, (INT32)CGameEvents::OnValidateNoblesseSkills, 0, 0xE8);
	WriteInstruction(0x8526B3, (INT32)CGameEvents::OnValidateNoblesseSkills, 0, 0xE8);
	*/
	WriteInstruction(0x64357B, (INT32)CGameEvents::OnLoadData, 0, 0xE8);
	
	/*WriteInstruction(0x4D7EC2, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);
	WriteInstruction(0x4FFB5B, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);
	WriteInstruction(0x518246, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);
	WriteInstruction(0x518B58, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);
	WriteInstruction(0x575EE9, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);
	WriteInstruction(0x84AF0A, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);
	WriteInstruction(0x851D23, (INT32)CGameEvents::OnInitializeSkillMod, 0, 0xE8);*/
	/*WriteMemoryDWORD(0xA876B8, (INT32)CGameEvents::OnUserEquipItem);
	WriteMemoryDWORD(0xA876C0, (INT32)CGameEvents::OnUserUnequipItem1);
	WriteMemoryDWORD(0xA876C8, (INT32)CGameEvents::OnUserUnequipItem2);
	WriteInstruction(0x581B1E, (INT32)CGameEvents::PlayerItemPickUp, 0, 0xE8);
	WriteInstruction(0x581C3B, (INT32)CGameEvents::PlayerItemPickUp, 0, 0xE8);
	WriteInstruction(0x54C4DB, (INT32)CGameEvents::PetItemPickUp, 0, 0xE8);
	WriteInstruction(0x54C5FE, (INT32)CGameEvents::PetItemPickUp, 0, 0xE8);*/
	WriteInstruction(0x8BF783, (INT32)GetPartyRoutingTypeHook, 0, 0xE9);
	/*WriteInstruction(0x8000B2, (INT32)CGameEvents::OnSendETCBuffBar, 0, 0xE8);
	WriteInstruction(0x81E88E, (INT32)CGameEvents::OnDieDropItem, 0, 0xE8);*/
	WriteInstruction(0x6CAE5E, (INT32)CGameEvents::OnCreatureConstruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x84ABF4, (INT32)CGameEvents::OnCreatureConstruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6BED7B, (INT32)CGameEvents::OnCreatureConstructionOther, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6BECA5, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6BB38D, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6CAFFD, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x84C270, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x84CBB0, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6BF0A0, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6BED0D, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE8);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x84CB95, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE9);//SEM ISSO O AUTOPICK NAO FUNCIONA
	WriteInstruction(0x6BB36C, (INT32)CGameEvents::OnCreatureDestruction, 0, 0xE9);//SEM ISSO O AUTOPICK NAO FUNCIONA
	/*WriteInstruction(0x42571B, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x4257C6, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x798D52, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x798E9C, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x7992CF, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x799444, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x7995CF, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x7996E2, (INT32)CGameEvents::OnInfectedSkillBy, 0, 0xE8);
	WriteInstruction(0x80E7F8, (INT32)CGameEvents::OnUseItem, 0, 0xE8); // in User::UseItem
	WriteMemoryDWORD(0xA4B590, (INT32)CGameEvents::OnUseItem);          // in CPet vftable
	WriteInstruction(0x50F3E3, (INT32)CGameEvents::OnAbnormalTypeExpired, 0, 0xE8);
	WriteMemoryDWORD(0xA873E8, (INT32)CGameEvents::OnIsRealEnemyTo);
	WriteMemoryDWORD(0xA873F0, (INT32)CGameEvents::OnIsEnemyTo);
	WriteInstruction(0x4D8959, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x513BDE, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x800C71, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x80FFC5, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x8102D5, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x8107ED, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x852C72, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x853000, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteInstruction(0x8536F1, (INT32)CGameEvents::GetRelationTo, 0, 0xE8);
	WriteMemoryDWORD(0xA28C10, (INT32)CGameEvents::OnNPCIsEnemyTo);
	WriteMemoryDWORD(0xAA0C00, (INT32)CGameEvents::OnNPCIsEnemyTo);
	WriteInstruction(0x4FA3E0, (INT32)CGameEvents::ItemUsable, 0, 0xE8);*/
	WriteInstruction(0x62E34A, (INT32)CGameEvents::OnDeleteObject, 0, 0xE8);
	WriteMemoryDWORD(0x9B0E60, (INT32)CGameEvents::OnCreatureDie);
	WriteInstruction(0x6C39AC, (INT32)CGameEvents::OnCreatureDie, 0, 0xE8);
	WriteInstruction(0x81E23C, (INT32)CGameEvents::OnCreatureDie, 0, 0xE8);
	WriteInstruction(0x7515CB, (INT32)CGameEvents::OnCreatureDie, 0, 0xE8);
	WriteInstruction(0x64357B, (INT32)CGameEvents::OnLoadData, 0, 0xE8);	
	WriteInstruction(0x8BF783, (INT32)GetPartyRoutingTypeHook, 0, 0xE9);
	/*WriteMemoryDWORD(0xA28C10, (INT32)CGameEvents::OnNPCIsEnemyTo);
	WriteMemoryDWORD(0xAA0C00, (INT32)CGameEvents::OnNPCIsEnemyTo);*/
		WriteInstruction(0x62E34A, (INT32)CGameEvents::OnDeleteObject, 0, 0xE8);
		//if(GlobalVars::GVs()->pSubSystems->nAutoPickUp == 1)
	WriteMemoryQWORD(0xA28F00L, (INT32)CGameEvents::OnCreatureDropItem);//SEM ISSO O AUTOPICK NAO FUNCIONA
}