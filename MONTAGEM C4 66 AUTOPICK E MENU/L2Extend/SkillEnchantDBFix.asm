include windows.inc

;   This file is part of L2Extend.

;   L2Extend is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.

;   L2Extend is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.

;   You should have received a copy of the GNU General Public License
;   along with L2Extend.  If not, see <http://www.gnu.org/licenses/>.

;	You May Not Make Commercial Use of any of our content, and any kind
;	of newer implementations will be need to be shared and commited.

.DATA

	; -----------------------------------------------------
	; GLOBAL DATABASE
	
	EXTRN	g_SkillEnchantDB:PTR
	
	;------------------------------------------------------
	
	aChddb		db 'c','h','d','d','b',0
	aChdd		db 'c','h','d','d',0
	aDd1		db 'd','d',0
	
	;------------------------------------------------------
	
	;------------------------------------------------------
	
	RETURNADDR1								QWORD	79F199h
	RETURNADDR2								QWORD	7A0927h
	RETURNADDR5								QWORD	846B51h
	RETURNADDR6								QWORD	846BBFh
	RETURNADDR7								QWORD	846A37h
	
	;------------------------------------------------------
	
.CODE

		SkillEnchantInfoFix_Hook1	PROC

		; 79F194:
	
		mov     r8d, r13d	
		cmp		r8d, 101
		jge		NEXT
		mov		r8d, 101
NEXT:
		mov     edx, ebp

		jmp		[RETURNADDR1]

	SkillEnchantInfoFix_Hook1	ENDP
	
	SkillEnchantInfoFix_Hook2	PROC

		; 7A0922:

		mov     r8d, esi		
		cmp		r8d, 101
		jge		NEXT
		mov		r8d, 101
NEXT:
		mov     edx, ebx

		jmp		[RETURNADDR2]

	SkillEnchantInfoFix_Hook2	ENDP

	SkillEnchantInfoFix_Hook5	PROC

		; 846B1A:
		mov     r8, [rbx]
		mov     edx, 1F9Ch
		sub     edx, ebp        ; __int64
		movsxd  rax, ebp
		lea     rcx, [rsp+rax+0C0h] ; char *
		mov     eax, [r8+0Ch]
		mov     [rsp+20h], eax
		mov     r9d, [r8]       ; int
		lea     r8, aDd1       ; "dd"

		jmp		[RETURNADDR5]

	SkillEnchantInfoFix_Hook5	ENDP
	
	SkillEnchantInfoFix_Hook6	PROC

		; 846B96:
		lea     rcx, [rsp+0C0h]
		mov     [rsp+38h], rcx
		mov     [rsp+30h], ebp
		mov     [rsp+28h], rax
		xor		rax, rax
		mov     [rsp+20h], rax
		mov     r9d, 17h
		mov     r8d, 0FEh
		lea     rdx, aChddb      ; "chddb"

		jmp		[RETURNADDR6]

	SkillEnchantInfoFix_Hook6	ENDP
	
	SkillEnchantInfoFix_Hook7	PROC

		; 846A1F:
		mov     [rsp+28h], rax
		xor		rax, rax
		mov     [rsp+20h], rax
		mov     r9d, 17h
		mov     r8d, 0FEh
		lea     rdx, aChdd       ; "chdd"

		jmp		[RETURNADDR7]

	SkillEnchantInfoFix_Hook7	ENDP

END
