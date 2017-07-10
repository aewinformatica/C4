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

include windows.inc

extern  CSkillDB_GetSkillInfo:proc


; replaces pSkillKey->level with <skill_level>

CSkillDB_GetSkillInfo1 macro suffix, skill_level
FUNC_BEGIN CSkillDB_GetSkillInfo1__&suffix&

		mov     ax, skill_level
		mov     [rdx+2], ax
		jmp     CSkillDB_GetSkillInfo

FUNC_END CSkillDB_GetSkillInfo1__&suffix&
endm

CSkillDB_GetSkillInfo1 1, 1
CSkillDB_GetSkillInfo1 ax, ax
CSkillDB_GetSkillInfo1 bx, bx
CSkillDB_GetSkillInfo1 bp, bp
CSkillDB_GetSkillInfo1 si, si
CSkillDB_GetSkillInfo1 r12w, r12w
CSkillDB_GetSkillInfo1 r13w, r13w
CSkillDB_GetSkillInfo1 r14w, r14w
CSkillDB_GetSkillInfo1 r15w, r15w

CSkillDB_GetSkillInfo1 r11_22h, [r11+22h]
CSkillDB_GetSkillInfo1 r14_18h, [r14+18h]
CSkillDB_GetSkillInfo1 rax_1Ch, [rax+1Ch]
CSkillDB_GetSkillInfo1 rbx_1Ch, [rbx+1Ch]
CSkillDB_GetSkillInfo1 rdi_04h, [rdi+04h]
CSkillDB_GetSkillInfo1 rsp_34h, [rsp+34h+8]
CSkillDB_GetSkillInfo1 rsp_38h, [rsp+38h+8]
CSkillDB_GetSkillInfo1 rsp_40h, [rsp+40h+8]
CSkillDB_GetSkillInfo1 rsp_44h, [rsp+44h+8]


; replaces pSkillKey->level with <base_ptr->level_off>

CSkillDB_GetSkillInfo1i macro suffix, base_ptr, level_off
FUNC_BEGIN CSkillDB_GetSkillInfo1i__&suffix&

		mov     rax, base_ptr
		mov     ax, [rax] level_off
		mov     [rdx+2], ax
		jmp     CSkillDB_GetSkillInfo

FUNC_END CSkillDB_GetSkillInfo1i__&suffix&
endm

CSkillDB_GetSkillInfo1i r12_38h__item_skill, [r12+38h], [22h]
CSkillDB_GetSkillInfo1i rdi_38h__item_skill, [rdi+38h], [22h]
CSkillDB_GetSkillInfo1i rsi_38h__item_skill, [rsi+38h], [22h]


;CSkillDB_GetSkillInfo2 macro suffix, skill_code
;FUNC_BEGIN CSkillDB_GetSkillInfo2__&suffix&
;
;		mov     eax, skill_code
;		rol     eax, 16
;		mov     [rdx], eax
;		jmp     CSkillDB_GetSkillInfo
;
;FUNC_END CSkillDB_GetSkillInfo2__&suffix&
;endm


;CSkillDB_GetSkillInfo2i macro suffix, base_ptr, skill_off
;FUNC_BEGIN CSkillDB_GetSkillInfo2i__&suffix&
;
;		mov     rax, base_ptr
;		mov     eax, [rax] skill_off
;		rol     eax, 16
;		mov     [rdx], eax
;		jmp     CSkillDB_GetSkillInfo
;
;FUNC_END CSkillDB_GetSkillInfo2i__&suffix&
;endm


CSkillKey_cmp_level macro suffix, left, right, then, else
FUNC_BEGIN CSkillKey_cmp_level__&suffix&

		cmp     left, right
		jb      Below
		jmp     loc(else)

	Below:
		jmp     loc(then)

FUNC_END CSkillKey_cmp_level__&suffix&
endm

CSkillKey_cmp_level 79C1AEh, [rax+1Ah], r8w, 79C1B4h, 79C1BAh
CSkillKey_cmp_level 79C1E3h, r8w, [rdi+1Ah], 79C1F0h, 79C1E9h


CSkillKey_init macro suffix, this, id, level
FUNC_BEGIN CSkillKey_init__&suffix&

		mov     this, id
		mov     this [2], level
		ret

FUNC_END CSkillKey_init__&suffix&
endm

CSkillKey_init rsp_30h__edi_ebx, [rsp+38h], di, bx
CSkillKey_init rsp_C0h__r13_r12, [rsp+0C8h], r13w, r12w


FUNC_BEGIN CSkillKey_less

		mov     ecx, [rcx]
		mov     edx, [rdx]
		rol     ecx, 10h
		rol     edx, 10h
		cmp     ecx, edx
		setb    al
		ret

FUNC_END CSkillKey_less


END
