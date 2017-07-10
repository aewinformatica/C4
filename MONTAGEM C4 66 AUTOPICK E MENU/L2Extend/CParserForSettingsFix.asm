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

	; RETURN PLACES
	RETURNADDR1								QWORD	84B85Ch
	RETURNADDR2								QWORD	85F204h
	RETURNADDR3								QWORD	85FC03h
	RETURNADDR4								QWORD	851E14h

	EXTRN									g_SettingsDB:QWORD
	EXTRN                                   g_nMinStatTable:QWORD
	EXTRN									g_nMaxStatTable:QWORD
	EXTRN									g_nRecStatTable:QWORD			

.CODE

	CParserForSettings_InitialStatsFix_Hook1	PROC
	
		cmp		eax, 5			; Kamael Race
		jne		Exit
		
		mov		rbx, [rdi+588h]
		mov		ebx, [rbx+0C4h]	; Sex
		
		cmp		ebx, 1			; Is Female ?
		je		IsFemale

		IsMale:
			xor		rbx, rbx
			mov     ebx, 7Bh	; Male Kamael Class ID
			jmp     Exit
			
		IsFemale:
			xor		rbx, rbx		
			mov     ebx, 7Ch	; Female Kamael Class ID
			jmp		Exit
		
		Exit:
			jmp		RETURNADDR1
		
	CParserForSettings_InitialStatsFix_Hook1	ENDP
	
	CParserForSettings_InitialStatsFix_Hook2	PROC
	
		; Maximum Stat Table
		
		lea		r13, g_SettingsDB
		add		r13, g_nMaxStatTable
		
		lea     rcx, [r8+r8*2]
		lea     rdx, [rsp+0F8h]
		mov     eax, [r13+rcx*8+04h]
		mov     [rdx], eax
		mov     eax, [r13+rcx*8+10h]
		mov     [rdx+4], eax
		mov     eax, [r13+rcx*8+08h]
		mov     [rdx+8], eax
		mov     eax, [r13+rcx*8+00h]
		mov     [rdx+0Ch], eax
		mov     eax, [r13+rcx*8+14h]
		mov     [rdx+10h], eax
		mov     eax, [r13+rcx*8+0Ch]
		mov     [rdx+14h], eax
		lea     rdx, [rsp+110h]
		
		; Minimum Stat Table
		
		lea		r13, g_SettingsDB
		add		r13, g_nMinStatTable
				
		mov     eax, [r13+rcx*8+04h]
		mov     [rdx], eax
		mov     eax, [r13+rcx*8+10h]
		mov     [rdx+4], eax
		mov     eax, [r13+rcx*8+08h]
		mov     [rdx+8], eax
		mov     eax, [r13+rcx*8+00h]
		mov     [rdx+0Ch], eax
		mov     eax, [r13+rcx*8+14h]
		mov     [rdx+10h], eax
		mov     eax, [r13+rcx*8+0Ch]
		mov     [rdx+14h], eax
		lea     rdx, [rsp+0E0h]
		
		; Recommended Stat Table
		
		lea		r13, g_SettingsDB
		add		r13, g_nRecStatTable
		
		mov     eax, [r13+rcx*8+04h]
		mov     [rdx], eax
		mov     eax, [r13+rcx*8+10h]
		mov     [rdx+4], eax
		mov     eax, [r13+rcx*8+08h]
		mov     [rdx+8], eax
		mov     eax, [r13+rcx*8+00h]
		mov     [rdx+0Ch], eax
		mov     eax, [r13+rcx*8+14h]
		mov     [rdx+10h], eax
		mov     eax, [r13+rcx*8+0Ch]
		mov     [rdx+14h], eax
		mov		r13, 400000h
	
		jmp RETURNADDR2
	
	CParserForSettings_InitialStatsFix_Hook2	ENDP
	
	CParserForSettings_InitialStatsFix_Hook3	PROC
	
		movsxd  rax, dword ptr [rbx+r15+689A10h]
		lea     rcx, [rax+rax*2]
		mov     [rsp+0D8h], rcx
		lea		r15, g_SettingsDB
		add		r15, g_nMinStatTable		
		mov     eax, [r15+rcx*8+00h]
		mov     [rsp+0D4h], eax
		lea		r15, g_SettingsDB
		add		r15, g_nMaxStatTable		
		mov     edx, [r15+rcx*8+00h]
		mov     [rsp+0D0h], edx
		lea		r15, g_SettingsDB
		add		r15, g_nMinStatTable		
		mov     r8d, [r15+rcx*8+0Ch]
		mov     [rsp+0C8h], r8d
		lea		r15, g_SettingsDB
		add		r15, g_nRecStatTable		
		mov     r9d, [r15+rcx*8+0Ch]
		lea		r15, g_SettingsDB
		add		r15, g_nMaxStatTable		
		mov     r10d, [r15+rcx*8+0Ch]
		lea		r15, g_SettingsDB
		add		r15, g_nMinStatTable		
		mov     r11d, [r15+rcx*8+04h]
		lea		r15, g_SettingsDB
		add		r15, g_nRecStatTable		
		mov     ebx, [r15+rcx*8+04h]
		lea		r15, g_SettingsDB
		add		r15, g_nMaxStatTable		
		mov     edi, [r15+rcx*8+04h]
		lea		r15, g_SettingsDB
		add		r15, g_nMinStatTable		
		mov     esi, [r15+rcx*8+08h]
		lea		r15, g_SettingsDB
		add		r15, g_nRecStatTable		
		mov     ebp, [r15+rcx*8+08h]
		lea		r15, g_SettingsDB
		add		r15, g_nMaxStatTable			
		mov     r12d, [r15+rcx*8+08h]
		lea		r15, g_SettingsDB
		add		r15, g_nMinStatTable		
		mov     r13d, [r15+rcx*8+14h]
		lea		r15, g_SettingsDB
		add		r15, g_nRecStatTable		
		mov     r14d, [r15+rcx*8+14h]
		lea		r15, g_SettingsDB
		add		r15, g_nMaxStatTable		
		mov     r15d, [r15+rcx*8+14h]
		mov     eax, 2000h
		mov     rcx, [rsp+0C0h]
		sub     eax, ecx
		mov     [rsp+0CCh], eax
		mov     eax, ecx
		lea     rcx, [rsp+rax+100h]
		mov     eax, [rsp+0D4h]
		mov     [rsp+0B0h], eax
		mov     rdx, [rsp+0D8h]
		lea		r8, g_SettingsDB
		add		r8, g_nRecStatTable		
		mov     eax, [r8+rdx*8+00h]
		mov     r8, 400000h		
		mov     [rsp+0A8h], eax
		mov     edx, [rsp+0D0h]
		mov     [rsp+0A0h], edx
		mov     r8d, [rsp+0C8h]
		mov     [rsp+98h], r8d
		mov     [rsp+90h], r9d
		mov     [rsp+88h], r10d
		mov     [rsp+80h], r11d
		mov     [rsp+78h], ebx
		mov     [rsp+70h], edi
		mov     [rsp+68h], esi
		mov     [rsp+60h], ebp
		mov     [rsp+58h], r12d
		mov     [rsp+50h], r13d
		mov     [rsp+48h], r14d
		mov     [rsp+40h], r15d
		mov     rdx, [rsp+0D8h]
		lea		r15, g_SettingsDB
		add		r15, g_nMinStatTable		
		mov     eax, [r15+rdx*8+10h]
		mov     [rsp+38h], eax
		lea		r15, g_SettingsDB
		add		r15, g_nRecStatTable		
		mov     eax, [r15+rdx*8+10h]
		mov     [rsp+30h], eax
		lea		r15, g_SettingsDB
		add		r15, g_nMaxStatTable		
		mov     eax, [r15+rdx*8+10h]
		mov     [rsp+28h], eax
		mov     r15, 400000h		
		
		jmp RETURNADDR3
	
	CParserForSettings_InitialStatsFix_Hook3	ENDP
	
	CParserForSettings_InitialStatsFix_Hook4	PROC
	
		dec		ecx
		
		mov		rdi, [rbx+588h]
		mov		edx, [rdi+0C4h]	; Sex
		
		cmp		edx, 1			; Is Female ?
		je		IsFemale

		IsMale:
			xor		rdx, rdx
			mov     edi, 7Bh	; Male Kamael Class ID
			jmp     Exit
			
		IsFemale:
			xor		rdx, rdx		
			mov     edi, 7Ch	; Female Kamael Class ID
			jmp		Exit
		
		Exit:
			jmp		RETURNADDR4
		
	CParserForSettings_InitialStatsFix_Hook4	ENDP		
	
END