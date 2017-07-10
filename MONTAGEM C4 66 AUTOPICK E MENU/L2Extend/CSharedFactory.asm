include windows.inc

;   This file is part of L2Extend.
;
;   L2Extend is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.
;
;   L2Extend is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with L2Extend.  If not, see <http://www.gnu.org/licenses/>.


SLOT_HAIR                       equ     10h
SLOT_ALLDRESS                   equ     11h
SLOT_HAIRDECO                   equ     12h
SLOT_HAIRALL                    equ     13h
SLOT_RBRACELET                  equ     14h
SLOT_LBRACELET                  equ     15h

.CONST

	CItemFactory_FindObject                     dq      4745F0h
	CInventory_ContainsByIndex                  dq      6119D0h
	CInventory_GetByIndex                       dq      612B40h

.DATA

	EXTERN      CSharedData_EquipSlotCount:dword
	EXTERN      CSharedData_ExtEquipmentBegin:dword
	EXTERN      CSharedData_ExtEquipmentEnd:dword

	EXTERN      CCreature_EquipItemExt:proc
	EXTERN      CCreature_IsEquippedExt:proc
	EXTERN      CCreature_IsEquippedExtByObjectId:proc
	EXTERN      CCreature_ValidateAttachedSkillsExt:proc
	EXTERN      User_EquipItemCheckExt:proc


; Usage:
;
;   DEFINE_CheckEquipSlotOffset ebx
;
;   This defines function CSharedData_CheckEquipSlotOffset_ebx, which
;   checks (and possibly adjusts) equipment slot offset stored in the
;   ebx register.
;
;   The calling code is expected to use a conditional jump instruction
;   (jl) to check that the offset hasn't run beyond all equipment slots.
;
; Note:
;
;   It's absolutely necessary that 170h <= CSharedData_ExtEquipmentBegin
;   and CSharedData_ExtEquipmentBegin <= CSharedData_ExtEquipmentEnd,
;   even when there are no extended slots.

DEFINE_CheckEquipSlotOffset MACRO Register

FUNC_BEGIN CSharedData_CheckEquipSlotOffset_&Register&

		cmp     Register, 170h
		jl      Exit
		cmove   Register, CSharedData_ExtEquipmentBegin
		cmp     Register, CSharedData_ExtEquipmentEnd

	Exit:

		ret

FUNC_END CSharedData_CheckEquipSlotOffset_&Register&

ENDM


DEFINE_CheckEquipSlotOffset ebx
DEFINE_CheckEquipSlotOffset ecx
DEFINE_CheckEquipSlotOffset edx
DEFINE_CheckEquipSlotOffset edi


; When some piece of a creature's equipment needs to be examined,
; an item smart pointer CSPointer<CItem> is obtained like this:
;
;       mov     rax, [rbx+588h]
;       mov     r8d, [rax+rdi*4+128h]
;       lea     rdx, [rsp+78h+spItem]
;       lea     rcx, cs:0E412130h
;       call    CItemFactory_FindObject
;
; Luckily [rax+rdi*4+128h] can't cause crash even when rdi is an extended
; slot, but r8d will contain rubbish in such case. This macro can be used
; to define functions that load the correct item index into r8d before
; passing control to CItemFactory_FindObject.

DEFINE_CItemFactory_FindObjectFix MACRO Creature, Slot, Multiplier

FUNC_BEGIN CItemFactory_FindObjectFix_&Creature&_&Slot&_x&Multiplier&

		cmp     Slot, 48h/Multiplier
		jl      Continue

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [Creature+588h]
		mov     r8d, [rax+Slot*Multiplier-48h]

	Continue:

		jmp     CItemFactory_FindObject

FUNC_END CItemFactory_FindObjectFix_&Creature&_&Slot&_x&Multiplier&

ENDM


DEFINE_CItemFactory_FindObjectFix rbp, rbx, 1
DEFINE_CItemFactory_FindObjectFix rbp, r12, 4
DEFINE_CItemFactory_FindObjectFix rbx, rdi, 4
DEFINE_CItemFactory_FindObjectFix rdi, rbx, 4
DEFINE_CItemFactory_FindObjectFix r14, rbx, 1
DEFINE_CItemFactory_FindObjectFix r15, rbx, 1


FUNC_BEGIN Fix4DA830_CCreature_IsEquipped1

		cmp     ecx, 12h
		jl      Continue
		jne     NextExtSlot

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [rdi+588h]

	NextExtSlot:

		cmp     ecx, CSharedData_EquipSlotCount
		jl      Continue
		jmp     loc(4DA83Ah)

	Continue:

		jmp     loc(4DA825h)

FUNC_END Fix4DA830_CCreature_IsEquipped1


FUNC_BEGIN Fix4DAF8F_CCreature_ValidateBaseData

		; extended slots are not available in CSetItem
		cmp     rbp, 12h
		mov     edx, -1
		cmovb   edx, [rax+rbp*4+128h]
		ret

FUNC_END Fix4DAF8F_CCreature_ValidateBaseData


FUNC_BEGIN Fix4E1360_CCreature_IsEquipped2

		sub     rsp, 28h
		mov     [rsp+30h], r9
		mov     [rsp+38h], r10

		cmp     rsi, 10h                        ; hair and above slots are extended
		jge     ExtSlot

		cmp     [rcx+rsi*4+128h], ebx
		cmove   r8d, esi
		jmp     Exit

	ExtSlot:

		mov     r8d, esi                        ; nSlotType
		mov     edx, ebx                        ; nItemIndex
		mov     rcx, rdi                        ; pCreature
		call    CCreature_IsEquippedExt
		mov     r8d, eax
		or      eax, -1                         ; clear ZF

	Exit:

		mov     r10, [rsp+38h]
		mov     r9, [rsp+30h]
		add     rsp, 28h
		ret

FUNC_END Fix4E1360_CCreature_IsEquipped2


FUNC_BEGIN Fix4FA03D_CCreature_UseItem

		cmp     r11d, 12h
		jl      Continue
		jne     NextExtSlot

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [r13+588h]

	NextExtSlot:

		cmp     r11d, CSharedData_EquipSlotCount
		jl      Continue
		jmp		loc(4FA0ABh)

	Continue:

		jmp     loc(4FA030h)

FUNC_END Fix4FA03D_CCreature_UseItem


FUNC_BEGIN Fix5174B8_CCreature_ValidateAttachedSkills

		lea     rdx, [rsp+58h]                  ; pSkillKeys
		mov     rcx, rdi                        ; pCreature
		jmp     CCreature_ValidateAttachedSkillsExt

FUNC_END Fix5174B8_CCreature_ValidateAttachedSkills


FUNC_BEGIN Fix519A7C_CCreature_EquipItem

		jg      ExtSlot                         ; edi > 11h (alldress)
		ja      Default                         ; edi == 0h (underwear)

		cmp     edi, 10h                        ; hair slot needs different behaviour
		je      ExtSlot

		jmp     loc(519A82h)                    ; proceed to the switch

	Default:

		jmp     loc(519DCAh)                    ; default switch branch

	ExtSlot:

		mov     r8d, edi                        ; nSlotType
		mov     rdx, rsi                        ; pItem
		mov     rcx, rbx                        ; pCreature
		call    CCreature_EquipItemExt
		mov     r15b, al
		jmp     loc(519DE7h)                    ; check equipment and return r15b

FUNC_END Fix519A7C_CCreature_EquipItem


FUNC_BEGIN Fix51A197_CCreature_UnequipSlot

		cmp     esi, 12h
		jge     UnequipExtSlot

		cmp     esi, 10h
		je      UnequipHairSlot

		mov     dword ptr [rax+rsi*4+128h], -1
		jmp     Continue

	UnequipExtSlot:

		mov     edx, CSharedData_ExtEquipmentBegin
		add     rdx, rax
		mov     dword ptr [rdx+rsi*4-48h], -1
		jmp     Continue

	UnequipHairSlot:

		mov     edx, CSharedData_ExtEquipmentBegin
		mov     dword ptr [rax+168h], -1        ; clear hair
		cmp     dword ptr [rax+rdx+4], -1       ; is hairall empty?
		je      Continue
		mov     dword ptr [rax+rdx+0], -1       ; clear hairdeco
		mov     dword ptr [rax+rdx+4], -1       ; clear hairall

	Continue:

		jmp     loc(51A1A2h)

FUNC_END Fix51A197_CCreature_UnequipSlot


FUNC_BEGIN Fix51A47F_CCreature_UnequipItem

		cmp     edi, 12h
		jl      Continue
		cmove   esi, CSharedData_ExtEquipmentBegin
		cmp     edi, CSharedData_EquipSlotCount
		jl      Continue

	Break:

		jmp     loc(51A484h)

	Continue:

		jmp     loc(51A440h)

FUNC_END Fix51A47F_CCreature_UnequipItem


FUNC_BEGIN Fix571E8C_CDBSocket_LoadItemsPacket

		mov     eax, 571C70h                    ; continue
		mov     r9d, 571E92h                    ; done
		cmovb   r9, rax

		mov     edx, CSharedData_ExtEquipmentBegin
		mov     rcx, [rbx+588h]
		mov     eax, [rcx+168h]                 ; hair
		cmp     eax, [rcx+rdx+0]                ; hairdeco
		jne     Continue

		mov     dword ptr [rcx+rdx+0], -1       ; hairdeco = empty
		mov     [rcx+rdx+4], eax                ; hairall = hair

	Continue:

		jmp     r9

FUNC_END Fix571E8C_CDBSocket_LoadItemsPacket


FUNC_BEGIN Fix7C4328_CSkillEffect_p_set_collected_Pump

		; extended slots are not available in CSetItem
		cmp     rsi, 12h
		mov     edx, -1
		cmovb   edx, [rax+rsi*4+128h]
		ret

FUNC_END Fix7C4328_CSkillEffect_p_set_collected_Pump


FUNC_BEGIN Fix7F2EFB_CTrade_CheckTradable

		cmp     ecx, 12h
		jl      Continue
		jne     NextExtSlot

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [rsi+588h]

	NextExtSlot:

		cmp     ecx, CSharedData_EquipSlotCount
		jl      Continue
		jmp     loc(7F2F1Fh)

	Continue:

		jmp     loc(7F2EF0h)

FUNC_END Fix7F2EFB_CTrade_CheckTradable


FUNC_BEGIN Fix8212CB_User_SendPackageSendableList

		cmp     ecx, 12h
		jl      Continue
		jne     NextExtSlot

		mov     r8d, CSharedData_ExtEquipmentBegin
		lea     rax, [rax+r8-170h]

	NextExtSlot:

		cmp     ecx, CSharedData_EquipSlotCount
		jl      Continue
		jmp     loc(8212E3h)

	Continue:

		jmp     loc(8212C0h)

FUNC_END Fix8212CB_User_SendPackageSendableList


FUNC_BEGIN Fix825BDE_User_EquipItem

		cmp     r12, 12h
		jl      Continue

		mov     r9d, CSharedData_ExtEquipmentBegin
		add     r9, rax
		mov     edx, [r9+r12*4-48h]

	Continue:

		jmp     CInventory_ContainsByIndex

FUNC_END Fix825BDE_User_EquipItem


FUNC_BEGIN Fix825CF0_User_EquipItem

		jne     NotDress
		jmp     loc(825CF6h)

	NotDress:

		cmp     ebx, 10h                        ; hair slot needs special treatment
		jge     ExtSlot
		jmp     loc(825DBFh)

	ExtSlot:

		mov     r8d, ebx                        ; nSlotType
		mov     rdx, r13                        ; pItem
		mov     rcx, rbp                        ; pUser
		call    User_EquipItemCheckExt
		jmp     loc(8261CFh)

FUNC_END Fix825CF0_User_EquipItem


FUNC_BEGIN Fix826BDB_User_UnequipItem

		cmp     ecx, 12h
		jl      Continue
		jne     NextExtSlot

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [rbx+588h]

	NextExtSlot:

		cmp     ecx, CSharedData_EquipSlotCount
		jl      Continue
		jmp     loc(826BE1h)

	Continue:

		jmp     loc(826BD0h)

FUNC_END Fix826BDB_User_UnequipItem


FUNC_BEGIN Fix82FCB4_User_PrivateStoreBuyListReq

		cmp     ebx, 48h
		jl      Continue

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [rsi+588h]
		mov     edx, [rax+rbx-48h]

	Continue:

		jmp     CInventory_GetByIndex

FUNC_END Fix82FCB4_User_PrivateStoreBuyListReq


FUNC_BEGIN Fix87A74F_CUserSocket_SellPacket

		cmp     ecx, 12h
		jl      Continue
		jne     NextExtSlot

		mov     eax, CSharedData_ExtEquipmentBegin
		add     rax, [rbp+588h]

	NextExtSlot:

		cmp     ecx, CSharedData_EquipSlotCount
		jl      Continue
		jmp     loc(87A75Ch)

	Continue:

		jmp     loc(87A744h)

FUNC_END Fix87A74F_CUserSocket_SellPacket


FUNC_BEGIN Fix8A5D64_CWarehouseDeposit_RequestEx

		cmp     rdi, 12h
		jge     ExtSlot

		cmp     [rcx+rdi*4+128h], eax
		ret

	ExtSlot:

		mov     edx, CSharedData_ExtEquipmentBegin
		add     rdx, rcx
		cmp     [rdx+rdi*4-48h], eax
		ret

FUNC_END Fix8A5D64_CWarehouseDeposit_RequestEx


FUNC_BEGIN Fix8A75A4_CWarehouseDeposit_Request

		cmp     rdi, 12h
		jge     ExtSlot

		cmp     [rcx+rdi*4+128h], eax
		ret

	ExtSlot:

		mov     edx, CSharedData_ExtEquipmentBegin
		add     rdx, rcx
		cmp     [rdx+rdi*4-48h], eax
		ret

FUNC_END Fix8A75A4_CWarehouseDeposit_Request


END
