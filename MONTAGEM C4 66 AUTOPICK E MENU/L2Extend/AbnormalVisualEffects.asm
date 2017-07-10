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

RETURNADDR1																		QWORD	8F7386h
RETURNADDR2																		QWORD	8F0E3Dh
EXTERN																			AVESystem_FindAVEID:PROC

.CODE

	AVESystem_Hook PROC

	; Verifying if an AVEID is Found in the Extended Parser
	
	XPUSHAD_ALL_NO_RAX	

	mov		rcx, rdx
	call	AVESystem_FindAVEID
	cmp		eax, 0h								; Checking if an AVE ID was found or not in the parser
	
	je		AVE_NOT_FOUND
	jne		AVE_FOUND
	
	AVE_FOUND:
	
		mov     rbx, [rbp+0F0h]
		mov     dword ptr [rbx+0D4h], eax		; Setting the AVE ID on the SkillData Parser
		XPOPAD_ALL_NO_RAX
		jmp		RETURNADDR1

	AVE_NOT_FOUND:
	
		mov     rax, [rbp+0F0h]					; Return to L2Server and let it set this to 0
		XPOPAD_ALL_NO_RAX
		jmp		RETURNADDR2
	
	AVESystem_Hook ENDP

END

