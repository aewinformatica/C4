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
	EXTRN									g_SkillAcquireDB:QWORD
	
	; -----------------------------------------------------

	RETURNADDR1								QWORD	79D5CAh
	RETURNADDR2								QWORD	906BE3h	
	RETURNADDR3								QWORD	79CDF1h
	RETURNADDR5								QWORD	79D5DDh

	; -----------------------------------------------------

	sub_4D4530								QWORD	4D4530h
	sub_9068A0								QWORD	9068A0h
	
	; -------------------------------------------------------------------------------------------------------------------
	; AUTO LEARNING

	RETURNADDR4_01                            QWORD    51547Ah
	RETURNADDR4_02                            QWORD    5154A6h
	RETURNADDR4_03                            QWORD    5154DFh
	RETURNADDR4_04                            QWORD    5155FAh
	RETURNADDR4_05                            QWORD    515622h
	RETURNADDR4_06                            QWORD    51565Bh
	RETURNADDR4_07                            QWORD    515CECh
	RETURNADDR4_08                            QWORD    515D15h
	RETURNADDR4_09                            QWORD    515D4Ah
	RETURNADDR4_10                            QWORD    518E8Ah
	RETURNADDR4_11                            QWORD    518EB3h
	RETURNADDR4_12                            QWORD    518EEFh
	RETURNADDR4_13                            QWORD    5194BAh
	RETURNADDR4_14                            QWORD    5194E3h
	RETURNADDR4_15                            QWORD    519518h
	RETURNADDR4_16                            QWORD    84DD1Ah
	RETURNADDR4_17                            QWORD    84DD46h
	RETURNADDR4_18                            QWORD    84DD7Fh
	RETURNADDR4_19                            QWORD    85250Ah
	RETURNADDR4_20                            QWORD    852533h
	RETURNADDR4_21                            QWORD    852568h
	RETURNADDR4_22                            QWORD    854D3Ah
	RETURNADDR4_23                            QWORD    854D63h
	RETURNADDR4_24                            QWORD    854D98h
	RETURNADDR4_25                            QWORD    854DFAh
	RETURNADDR4_26                            QWORD    854E23h
	RETURNADDR4_27                            QWORD    854E58h
	RETURNADDR4_28                            QWORD    51548Bh
	RETURNADDR4_29                            QWORD    5154B3h
	RETURNADDR4_30                            QWORD    51560Bh
	RETURNADDR4_31                            QWORD    51562Fh
	RETURNADDR4_32                            QWORD    515CFEh
	RETURNADDR4_33                            QWORD    515D22h
	RETURNADDR4_34                            QWORD    518E9Ch
	RETURNADDR4_35                            QWORD    518EC0h
	RETURNADDR4_36                            QWORD    5194CCh
	RETURNADDR4_37                            QWORD    5194F0h
	RETURNADDR4_38                            QWORD    84DD2Bh
	RETURNADDR4_39                            QWORD    84DD53h
	RETURNADDR4_40                            QWORD    85251Ch
	RETURNADDR4_41                            QWORD    852540h
	RETURNADDR4_42                            QWORD    854D4Ch
	RETURNADDR4_43                            QWORD    854D70h
	RETURNADDR4_44                            QWORD    854E0Ch
	RETURNADDR4_45                            QWORD    854E30h
	
.CODE

	CSkillAcquireLexer_DatabaseOffsetFix_Hook1	PROC

		; 79D5BF

		lea     rcx, [rdi+0F80h]
		lea     rsi, sub_4D4530

		jmp		RETURNADDR1

	CSkillAcquireLexer_DatabaseOffsetFix_Hook1	ENDP

	CSkillAcquireLexer_DatabaseOffsetFix_Hook2	PROC

		; 906BD9

		lea     rcx, [rax+rbx+0F80h]
		call    sub_9068A0

		jmp		RETURNADDR2

	CSkillAcquireLexer_DatabaseOffsetFix_Hook2	ENDP

	CSkillAcquireLexer_DatabaseOffsetFix_Hook3	PROC

		; 79CDE7

		lea     rbx, [rbp+0F90h]
		mov     r15d, 77h

		jmp		RETURNADDR3

	CSkillAcquireLexer_DatabaseOffsetFix_Hook3	ENDP
	
	CSkillAcquireLexer_DatabaseOffsetFix_Hook4	PROC
	
		; 79D5D6
		
		lea edx, [rbp+20h]	; a - Size of CSkillAcquireInfo | Size of Array [a * b] -> CSkillAcquireDB
		lea r8d, [rbp+89h]	; b - Max Occupations
	
		jmp		RETURNADDR5
	
	CSkillAcquireLexer_DatabaseOffsetFix_Hook4	ENDP
	
	; CCreature::LevelDown()
	
	CSkillAcquireLexer_AutoLearnFixHook01	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]
		jmp		RETURNADDR4_01
	CSkillAcquireLexer_AutoLearnFixHook01	ENDP
	
	CSkillAcquireLexer_AutoLearnFixHook02	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rbx
		mov		rcx, [rcx]
		jmp		RETURNADDR4_02
	CSkillAcquireLexer_AutoLearnFixHook02	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook03	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]
		jmp		RETURNADDR4_03
	CSkillAcquireLexer_AutoLearnFixHook03	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook04	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]	
		jmp		RETURNADDR4_04
	CSkillAcquireLexer_AutoLearnFixHook04	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook05	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rbx
		mov		rcx, [rcx]
		jmp		RETURNADDR4_05
	CSkillAcquireLexer_AutoLearnFixHook05	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook06	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]
		jmp		RETURNADDR4_06
	CSkillAcquireLexer_AutoLearnFixHook06	ENDP	
	
	; CCreature::LevelUp()
	
	CSkillAcquireLexer_AutoLearnFixHook07	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]
		jmp		RETURNADDR4_07
	CSkillAcquireLexer_AutoLearnFixHook07	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook08	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rdi
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_08
	CSkillAcquireLexer_AutoLearnFixHook08	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook09	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]	
		jmp		RETURNADDR4_09
	CSkillAcquireLexer_AutoLearnFixHook09	ENDP	
	
	; CCreature::EnterWorld()
	
	CSkillAcquireLexer_AutoLearnFixHook10	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_10
	CSkillAcquireLexer_AutoLearnFixHook10	ENDP
	
	CSkillAcquireLexer_AutoLearnFixHook11	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rdi
		mov		rcx, [rcx]	
		jmp		RETURNADDR4_11
	CSkillAcquireLexer_AutoLearnFixHook11	ENDP
	
	CSkillAcquireLexer_AutoLearnFixHook12	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_12
	CSkillAcquireLexer_AutoLearnFixHook12	ENDP	
	
	; CCreature::ChangeClass()
	
	CSkillAcquireLexer_AutoLearnFixHook13	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_13
	CSkillAcquireLexer_AutoLearnFixHook13	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook14	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rbx
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_14
	CSkillAcquireLexer_AutoLearnFixHook14	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook15	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_15
	CSkillAcquireLexer_AutoLearnFixHook15	ENDP
	
	; User::EnterWorld()	
	
	CSkillAcquireLexer_AutoLearnFixHook16	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]	
		jmp		RETURNADDR4_16
	CSkillAcquireLexer_AutoLearnFixHook16	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook17	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rdi
		mov		rcx, [rcx]	
		jmp		RETURNADDR4_17
	CSkillAcquireLexer_AutoLearnFixHook17	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook18	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]	
		jmp		RETURNADDR4_18
	CSkillAcquireLexer_AutoLearnFixHook18	ENDP	
	
	; User::ValidateSubJobParameters()
	
	CSkillAcquireLexer_AutoLearnFixHook19	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_19
	CSkillAcquireLexer_AutoLearnFixHook19	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook20	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rdi
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_20
	CSkillAcquireLexer_AutoLearnFixHook20	ENDP
	
	CSkillAcquireLexer_AutoLearnFixHook21	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_21
	CSkillAcquireLexer_AutoLearnFixHook21	ENDP
	
	; User::OnChangeSubJobEnd()
	
	CSkillAcquireLexer_AutoLearnFixHook22	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_22
	CSkillAcquireLexer_AutoLearnFixHook22	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook23	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rbx
		mov		rcx, [rcx]			
		jmp		RETURNADDR4_23
	CSkillAcquireLexer_AutoLearnFixHook23	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook24	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]				
		jmp		RETURNADDR4_24
	CSkillAcquireLexer_AutoLearnFixHook24	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook25	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]				
		jmp		RETURNADDR4_25
	CSkillAcquireLexer_AutoLearnFixHook25	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook26	PROC
		lea		rcx, g_SkillAcquireDB+0F88h
		add		rcx, rbx
		mov		rcx, [rcx]				
		jmp		RETURNADDR4_26
	CSkillAcquireLexer_AutoLearnFixHook26	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook27	PROC
		lea		rax, g_SkillAcquireDB+0F88h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_27
	CSkillAcquireLexer_AutoLearnFixHook27	ENDP
	
	; CCreature::LevelDown()	
	
	CSkillAcquireLexer_AutoLearnFixHook28	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rbx
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_28
	CSkillAcquireLexer_AutoLearnFixHook28	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook29	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rbx
		mov		rax, [rax]	
		jmp		RETURNADDR4_29
	CSkillAcquireLexer_AutoLearnFixHook29	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook30	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rbx
		mov		rcx, [rcx]	
		jmp		RETURNADDR4_30
	CSkillAcquireLexer_AutoLearnFixHook30	ENDP
	
	CSkillAcquireLexer_AutoLearnFixHook31	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rbx
		mov		rax, [rax]	
		jmp		RETURNADDR4_31
	CSkillAcquireLexer_AutoLearnFixHook31	ENDP
	
	; CCreature::LevelUp()
	
	CSkillAcquireLexer_AutoLearnFixHook32	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rdi
		mov		rcx, [rcx]
		jmp		RETURNADDR4_32
	CSkillAcquireLexer_AutoLearnFixHook32	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook33	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rdi
		mov		rax, [rax]
		jmp		RETURNADDR4_33
	CSkillAcquireLexer_AutoLearnFixHook33	ENDP
	
	; CCreature::EnterWorld()	
	
	CSkillAcquireLexer_AutoLearnFixHook34	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rdi
		mov		rcx, [rcx]			
		jmp		RETURNADDR4_34
	CSkillAcquireLexer_AutoLearnFixHook34	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook35	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_35
	CSkillAcquireLexer_AutoLearnFixHook35	ENDP
	
	; CCreature::ChangeClass()	
	
	CSkillAcquireLexer_AutoLearnFixHook36	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rbx
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_36
	CSkillAcquireLexer_AutoLearnFixHook36	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook37	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_37
	CSkillAcquireLexer_AutoLearnFixHook37	ENDP
	
	; User::EnterWorld()	
	
	CSkillAcquireLexer_AutoLearnFixHook38	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rdi
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_38
	CSkillAcquireLexer_AutoLearnFixHook38	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook39	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_39
	CSkillAcquireLexer_AutoLearnFixHook39	ENDP
	
	; User::ValidateSubJobParameters()	
	
	CSkillAcquireLexer_AutoLearnFixHook40	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rdi
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_30
	CSkillAcquireLexer_AutoLearnFixHook40	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook41	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rdi
		mov		rax, [rax]		
		jmp		RETURNADDR4_41
	CSkillAcquireLexer_AutoLearnFixHook41	ENDP
	
	; User::OnChangeSubJobEnd()
	
	CSkillAcquireLexer_AutoLearnFixHook42	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rbx
		mov		rcx, [rcx]		
		jmp		RETURNADDR4_42
	CSkillAcquireLexer_AutoLearnFixHook42	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook43	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_43
	CSkillAcquireLexer_AutoLearnFixHook43	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook44	PROC
		lea		rcx, g_SkillAcquireDB+0F90h
		add		rcx, rbx
		mov		rcx, [rcx]			
		jmp		RETURNADDR4_44
	CSkillAcquireLexer_AutoLearnFixHook44	ENDP	
	
	CSkillAcquireLexer_AutoLearnFixHook45	PROC
		lea		rax, g_SkillAcquireDB+0F90h
		add		rax, rbx
		mov		rax, [rax]		
		jmp		RETURNADDR4_45
	CSkillAcquireLexer_AutoLearnFixHook45	ENDP	
	
END