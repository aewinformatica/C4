//#include "stdafx.h"
#include "CParty.h"
#include "CItem.h"
#include "CCreature.h"
#include "User.h"
#include "CSummon.h"
#include "CPet.h"
#include "CInventory.h"
#include "CGameEvents.h"


class CCreature;
class CPet;
class User;
class CParty;
class CItem;
class CInventory;

INT32 nCGameEvents__OnCreatureDropItem = 0; 
bool CGameEvents::OnCreatureDropItem(CCreature* pNpc, CItem* pItem, INT32 nUnk, __int64 nUnk2) 
{ 
L2SERVER_SHARED_GUARD(nCGameEvents__OnCreatureDropItem); 
TLS_TRACE_BEGIN; 
typedef bool (__fastcall*_TNDI)(CCreature*, CItem*, INT32, __int64); 
_TNDI _NDI = (_TNDI)0x6BB940; 
bool bRet = true; 
if(pItem->IsValidItem() && pNpc->IsValidCreature()) 
{ 
  if(!pNpc->IsBoss() && !pNpc->IsMinion() && !pNpc->IsValidUser()) 
  { 
   CCreature* pLastKiller = pNpc->SD->pObjectEx->pGeneralInfo->pLastKiller; 
   User* pUser; 
   if(!pLastKiller->IsValidCreature()) 
   { 
    TLS_TRACE_END; 
    return false; 
   } 

   if(pLastKiller->IsValidUser()) 
    pUser = (User*)pLastKiller; 

   else if(pLastKiller->IsValidSummon()) 
    pUser = ((CSummon*)pLastKiller)->GetMaster();
 
   else if(pLastKiller->IsValidPet()) 
    pUser = ((CPet*)pLastKiller)->GetMaster();
 
   else 
    pUser = NULL; 
   if(pUser != NULL && pItem->SD->nClassID != 8689 && pItem->SD->nClassID != 8190) 
   { 
    CParty* pParty = pUser->GetParty(); 
    pItem->SD->x = pNpc->SD->x; 
    pItem->SD->y = pNpc->SD->y; 
    pItem->SD->z = pNpc->SD->z; 
    if(pParty->IsValidParty()) 
    { 
         pNpc->GetInventory()->Pop(pItem->SD->itemIndex, false); 
         if(pItem->SD->nClassID == 57) 
          pParty->DistributeAdena(pItem->SD->amount, 0, pItem->SD->nDBID, pItem); 
         else if(pParty->GetPartyRoutingType() != 0) 
          pParty->RouteItem(pItem, pUser); 
         else 
          pUser->AddItemToInventory(pItem); 
    } 
    else 
    { 
         if(pUser->GetInventory()->CheckAddable(pItem->SD->nClassID, pItem->SD->amount)) 
         { 
          pNpc->GetInventory()->Pop(pItem->SD->itemIndex, false); 
          pUser->AddItemToInventory(pItem); 
         } 
         else 
          bRet = _NDI(pNpc, pItem, nUnk, nUnk2); 
    } 
   } 
   else 
    bRet = _NDI(pNpc, pItem, nUnk, nUnk2); 
   TLS_TRACE_END; 
   return bRet; 
  } 
  else 
  { 
   bRet = _NDI(pNpc, pItem, nUnk, nUnk2); 
   TLS_TRACE_END; 
   return bRet; 
  } 
} 
else 
{ 
  TLS_TRACE_END; 
  return false; 
} 
}

