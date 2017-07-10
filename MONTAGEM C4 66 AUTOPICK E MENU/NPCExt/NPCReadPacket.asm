include ../L2Extend/windows.inc

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

	RETURNADDR1_RECEIVE									QWORD 5DDFB1h
	RETURNADDR2_RECEIVE									QWORD 5DE16Bh
	
	EXTERN												NPCReceiveData_Wrapper:PROC

FUNC_BEGIN NPCReadPackets_Hook
	
		XPUSHAD_ALL_NO_RAX

			movzx	r9d, byte ptr [r15+r13+10h]			; Packet ID
			movzx	r8d, word ptr [r15+r13+10h-02h]		; Packet Size
			lea		rdx, [r15+r13+10h+01h]				; Decrypted Packet Buffer
			mov		rcx, rbx							; CSocket *pSocket
			call	NPCReceiveData_Wrapper				; Incomming Packet Handler
			
		XPOPAD_ALL_NO_RAX
		
		test	al, al								; Receive New Packet (Yes/No?)
		jnz		Yes
	
		cmp     byte ptr [r15+r13+10h], 57h	
		jmp		RETURNADDR1_RECEIVE
	Yes:
		jmp		RETURNADDR2_RECEIVE
	
FUNC_END NPCReadPackets_Hook

END
include ../L2Extend/windows.inc

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

	RETURNADDR1_RECEIVE									QWORD 5DDFB1h
	RETURNADDR2_RECEIVE									QWORD 5DE16Bh
	
	EXTERN												NPCReceiveData_Wrapper:PROC

FUNC_BEGIN NPCReadPackets_Hook
	
		XPUSHAD_ALL_NO_RAX

			movzx	r9d, byte ptr [r15+r13+10h]			; Packet ID
			movzx	r8d, word ptr [r15+r13+10h-02h]		; Packet Size
			lea		rdx, [r15+r13+10h+01h]				; Decrypted Packet Buffer
			mov		rcx, rbx							; CSocket *pSocket
			call	NPCReceiveData_Wrapper				; Incomming Packet Handler
			
		XPOPAD_ALL_NO_RAX
		
		test	al, al								; Receive New Packet (Yes/No?)
		jnz		Yes
	
		cmp     byte ptr [r15+r13+10h], 57h	
		jmp		RETURNADDR1_RECEIVE
	Yes:
		jmp		RETURNADDR2_RECEIVE
	
FUNC_END NPCReadPackets_Hook

END
