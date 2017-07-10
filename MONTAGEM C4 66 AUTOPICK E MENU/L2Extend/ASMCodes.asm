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

			RETURNADDR1								QWORD 63F142h
			RETURNADDR2_A							QWORD 85EACFh
			RETURNADDR2_B							QWORD 85ECEEh			
			ret_6B8BBE								QWORD 6B8BBEh
			
			EXTRN									DoExitApplication:PROC
			EXTERN									?GladiatorTyrantsFix@CPPFixes@@SAXPEAVUser@@PEAVCSkillInfo@@@Z:PROC
			
			ValidateCP							QWORD 4DBA50h
			ValidateAllWeapon					QWORD 516FE0h
			ReturnAddr							QWORD 4FFE78h
.CODE

	ExitCrash	PROC
	
		XPUSHAD_ALL
		
		call	DoExitApplication
		
		XPOPAD_ALL
		
		jmp		RETURNADDR1
	
	ExitCrash	ENDP
	
	LastUsedPacketFix1 proc
	
		cmp esi, 0Dh
		je exit
		mov dword ptr [rsp+20h], 1BEh
		jmp RETURNADDR2_A
	
		exit:
	
			jmp RETURNADDR2_B
		
	LastUsedPacketFix1 endp	

C5_GladiatorTyransFix		proc
		mov		rdx, rax
		mov		rcx, rbp
		call	?GladiatorTyrantsFix@CPPFixes@@SAXPEAVUser@@PEAVCSkillInfo@@@Z
		xor		esi, esi
		jmp		ret_6B8BBE
C5_GladiatorTyransFix		endp

RangeHook proc
	call ValidateCP
	mov rcx,rdi
	call ValidateAllWeapon
	jmp ReturnAddr
RangeHook endp

BsGotDamageBy proc
	cmp rax, 00A871B8h ;check if is User
	je short BsFix ;if User jump to BsFix
	 
	mov rax, [rax+5F8h] ; normal execution
	call rax
	 
	mov rax, 7AF6E5h ;back to exit point
	jmp rax
BsGotDamageBy endp

BsFix proc
	mov r8, rcx ;pUser
	mov rcx, [rcx+588h] ;CSharedData
	mov rax, [rcx+198h] ; Current CP

	mov rcx, r8
	mov rcx, [rcx+588h] ;CSharedData
	xor r9, r9
	mov [rcx+198h], r9 ; Decrease CP to 0
	mov rcx, r8 ;pUser
	mov [rsp+10h], rax ;Store CurrentCP
	xor rax, rax
	mov rax, [rcx]
	mov rax, [rax+5F8h]
	mov r9d, 1
	call rax ;Call Creature::GotDamageBy

	mov rax, [rbp+588h] ;pUser
	mov r8, [rsp+10h] ;Restore CP
	mov [rax+198h], r8 
	xor r8, r8
	mov rcx, rbp ;pUser
	mov rax, 008464A0h ; User::SendHPInfo
	call rax
	mov rax, 7AF6E5h
	jmp rax
BsFix endp

END