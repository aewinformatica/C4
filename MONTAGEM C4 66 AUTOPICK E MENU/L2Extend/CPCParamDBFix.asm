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
	RETURNADDR1								QWORD	8FF8B1h
	RETURNADDR2								QWORD	9006B6h
	
	return_44DE59							QWORD	44DE59h
	return_467BB7							QWORD   467BB7h
	return_7446D8							QWORD   7446D8h
	return_74468E							QWORD   74468Eh	
	return_744BE5							QWORD   744BE5h
	return_744B98							QWORD   744B98h	
	return_744D06							QWORD   744D06h
	return_744CCD							QWORD   744CCDh	
	return_744D86							QWORD   744D86h
	return_744D4D							QWORD   744D4Dh
	return_745400							QWORD   745400h
	return_7453C0							QWORD   7453C0h 
	return_745484							QWORD   745484h
	return_745440							QWORD   745440h	
	return_745593							QWORD   745593h
	return_745585							QWORD   745585h	
	return_791A1A							QWORD   791A1Ah
	return_79198F							QWORD   79198Fh	
	return_792032							QWORD   792032h
	return_791B9E							QWORD   791B9Eh	
	return_79DF93							QWORD   79DF93h
	return_79DFDB							QWORD   79DFDBh	
	return_79ED98							QWORD   79ED98h
	return_79ED64							QWORD   79ED64h
	return_7A043D							QWORD   7A043Dh
	return_7A03B2							QWORD   7A03B2h	
	return_7A0A24							QWORD   7A0A24h
	return_7A0864							QWORD   7A0864h	
	return_7AB044							QWORD   7AB044h
	return_7AB01E							QWORD   7AB01Eh
	sub_423EB0								QWORD	423EB0h
	return_8FFF76							QWORD	8FFF76h
	return_9000AB							QWORD	9000ABh
	return_744801							QWORD	744801h
	return_7448B8							QWORD	7448B8h

	
	; TABLES
	EXTRN									g_LexxerParserData:DWORD
	EXTRN									g_CPCParamDB:DWORD	

.CODE

	CParserForPCParameter_LexxerFix_Hook1	PROC
	
		push	r8

		lea		r8, g_LexxerParserData
		mov     eax, [r8+rdx*8+00h]
		mov     [rcx], eax
		mov     eax, [r8+rdx*8+04h]
		mov     [rcx+4], eax
		mov     eax, [r8+rdx*8+08h]
		mov     [rcx+8], eax
		mov     eax, [r8+rdx*8+0Ch]
		mov     [rcx+0Ch], eax
		
		pop		r8
		
		jmp		RETURNADDR1
		
	CParserForPCParameter_LexxerFix_Hook1	ENDP
	
	CParserForPCParameter_LexxerFix_Hook2	PROC
	
		push	r8
	
		lea		r8, g_LexxerParserData
		mov     eax, [r8+rcx*8+00h]
		mov     [rdi], eax
		mov     eax, [r8+rcx*8+04h]
		mov     [rdi+4], eax
		mov     eax, [r8+rcx*8+08h]
		mov     [rdi+8], eax
		mov     eax, [r8+rcx*8+0Ch]
		mov     ecx, 15h
		mov     [rdi+0Ch], eax
		
		pop		r8
		
		jmp		RETURNADDR2
			
	CParserForPCParameter_LexxerFix_Hook2	ENDP
	
	BuilderCMD_SetClass_Class_Hook PROC
		
		 movsxd  rbx, eax
         cmp     ebx, 89h
         jmp	 [return_44DE59]
		
	BuilderCMD_SetClass_Class_Hook ENDP
	
	BuilderCMD_SetSubJob_Class_Hook PROC
		
		mov     r12d, eax
		cmp 	eax, 89h
		jmp		[return_467BB7]
		
	BuilderCMD_SetSubJob_Class_Hook ENDP
	
	PCParam_Getter_Class_Hook1 PROC
		
		ja      SHORT JMP1
		cmp 	r9d, 89h
		jmp		[return_74468E]
		
	JMP1:
		jmp		[return_7446D8]
		
	PCParam_Getter_Class_Hook1 ENDP
	
	PCParam_Getter_Class_Hook2 PROC
	
		ja      SHORT JMP2
		cmp 	r8d, 89h
		jmp		[return_744B98]
		
	JMP2:
		jmp		[return_744BE5]
		
	PCParam_Getter_Class_Hook2 ENDP
	
	PCParam_Getter_Class_Hook3 PROC
	
		ja      SHORT JMP3
		cmp 	r8d, 89h
		jmp		[return_744CCD]
		
	JMP3:
		jmp		[return_744D06]
		
	PCParam_Getter_Class_Hook3 ENDP
	
	PCParam_Getter_Class_Hook4 PROC
	
		ja      SHORT JMP4
		cmp 	r8d, 89h
		jmp		[return_744D4D]
		
	JMP4:
		jmp		[return_744D86]
		
	PCParam_Getter_Class_Hook4 ENDP
	
	PCParam_Getter_Class_Hook5 PROC
	
		ja      SHORT JMP5
		cmp 	r8d, 89h
		jmp		[return_7453C0]
		
	JMP5:
		jmp		[return_745400]
		
	PCParam_Getter_Class_Hook5 ENDP
	
	PCParam_Getter_Class_Hook6 PROC
	
		ja      SHORT JMP6
		cmp 	r8d, 89h
		jmp		[return_745440]
		
	JMP6:
		jmp		[return_745484]
		
	PCParam_Getter_Class_Hook6 ENDP
	
	PCParam_Getter_Class_Hook7 PROC
	
		cmp 	edx, 89h
		ja      SHORT JMP7
		jmp		[return_745585]
		
	JMP7:
		jmp		[return_745593]
		
	PCParam_Getter_Class_Hook7 ENDP
	
	CShortCut_DeleteShortcut_Class_Hook PROC
	
		cmp 	edi, 89h
		ja      SHORT JMP_CSDSCH
		jmp		[return_79198F]
		
	JMP_CSDSCH:
		jmp		[return_791A1A]
		
	CShortCut_DeleteShortcut_Class_Hook ENDP
	
	CShortCut_Add_Class_Hook PROC
	
		cmp 	r14d, 89h
		ja      SHORT JMP_CSACH
		jmp		[return_791B9E]
		
	JMP_CSACH:
		jmp		[return_792032]
		
	CShortCut_Add_Class_Hook ENDP
	
	CSkillEnchantChecker_CheckLearnable_Class_Hook PROC
	
		cmp     ecx, 77h
		jl		SHORT True_OccupationID_CSECCLCH
		cmp		ecx, 83h
		jl		SHORT False_OccupationID_CSECCLCH
		cmp		ecx, 87h
		je		SHORT False_OccupationID_CSECCLCH
		cmp     ecx, 89h
		jl      SHORT True_OccupationID_CSECCLCH
		
	False_OccupationID_CSECCLCH:
		jmp		[return_79DF93]
	True_OccupationID_CSECCLCH:
		jmp		[return_79DFDB]
		
	CSkillEnchantChecker_CheckLearnable_Class_Hook ENDP
	
	CSkillEnchantChecker_CheckRequestEnchantSkill_Class_Hook PROC
	
		cmp     eax, 77h
		jl		SHORT True_OccupationID_CSECCRESCH
		cmp		eax, 83h
		jl		SHORT False_OccupationID_CSECCRESCH
		cmp		eax, 87h
		je		SHORT False_OccupationID_CSECCRESCH
		cmp     eax, 89h
		jl      SHORT True_OccupationID_CSECCRESCH
		
	False_OccupationID_CSECCRESCH:
		jmp		[return_79ED98]
	True_OccupationID_CSECCRESCH:
		jmp		[return_79ED64]
		
	CSkillEnchantChecker_CheckRequestEnchantSkill_Class_Hook ENDP
	
	CSkillEnchantChecker_CheckNpcShowEnchantSkillList_Class_Hook PROC
	
		cmp     ecx, 77h
		jl		SHORT True_OccupationID_CSECCNSESLCH
		cmp		ecx, 83h
		jl		SHORT False_OccupationID_CSECCNSESLCH
		cmp		ecx, 87h
		je		SHORT False_OccupationID_CSECCNSESLCH
		cmp     ecx, 89h
		jl      SHORT True_OccupationID_CSECCNSESLCH
		
	False_OccupationID_CSECCNSESLCH:
		jmp		[return_7A043D]
	True_OccupationID_CSECCNSESLCH:
		jmp		[return_7A03B2]
		
	CSkillEnchantChecker_CheckNpcShowEnchantSkillList_Class_Hook ENDP
	
	CSkillEnchantChecker_CheckNpcEnchantSkillSuggestion_Class_Hook PROC
	
		cmp     edx, 77h
		jl		SHORT True_OccupationID_CSECCNESSCH
		cmp		edx, 83h
		jl		SHORT False_OccupationID_CSECCNESSCH
		cmp		edx, 87h
		je		SHORT False_OccupationID_CSECCNESSCH
		cmp     edx, 89h
		jl      SHORT True_OccupationID_CSECCNESSCH
		
	False_OccupationID_CSECCNESSCH:
		jmp		[return_7A0A24]
	True_OccupationID_CSECCNESSCH:
		jmp		[return_7A0864]
		
	CSkillEnchantChecker_CheckNpcEnchantSkillSuggestion_Class_Hook ENDP
	
	CSkillEffect_i_inform_Class_Hook PROC
	
		cmp 	eax, 89h
		jl      SHORT JMP_CSEICH
		jmp		[return_7AB01E]
		
	JMP_CSEICH:
		jmp		[return_7AB044]
		
	CSkillEffect_i_inform_Class_Hook ENDP
	
	ORG_MP_REG_System_Hook PROC
		
		mov     edx, 8
		mov     rcx, r15
		call    sub_423EB0
		mov		r8,rax
		mov     edx, 7
		mov     rcx, r15
		call    sub_423EB0
		mov     edx, 6
		mov     rcx, r15
		mov     r14, rax
		call    sub_423EB0
		mov     edx, 5
		mov     rcx, r15
		mov     r13, rax
		call    sub_423EB0
		mov     edx, 4
		mov     rcx, r15
		mov     r12, rax
		call    sub_423EB0
		mov     edx, 3
		mov     rcx, r15
		mov     rbp, rax
		call    sub_423EB0
		mov     edx, 2
		mov     rcx, r15
		mov     rbx, rax
		call    sub_423EB0
		mov     edx, 1
		mov     rcx, r15
		mov     rsi, rax
		call    sub_423EB0
		xor     edx, edx
		mov     rcx, r15
		mov     rdi, rax
		call    sub_423EB0
		movlpd  xmm0, qword ptr [r8]
		movsd   qword ptr [rsp+68h], xmm0
		movlpd  xmm0, qword ptr [r14]
		movlpd  xmm1, qword ptr [r13]
		movsd   qword ptr [rsp+60h], xmm0
		movlpd  xmm0, qword ptr [r12]
		movsd   qword ptr [rsp+58h], xmm1
		movlpd  xmm1, qword ptr [rbp]
		movsd   qword ptr [rsp+50h], xmm0
		movlpd  xmm0, qword ptr [rbx]
		movsd   qword ptr [rsp+48h], xmm1
		movlpd  xmm1, qword ptr [rsi]
		movsd   qword ptr [rsp+40h], xmm0
		movlpd  xmm0, qword ptr [rdi]
		movsd   qword ptr [rsp+38h], xmm1
		movlpd  xmm1, qword ptr [rax]
		movsd   qword ptr [rsp+30h], xmm0
		movsd   qword ptr [rsp+28h], xmm1
		jmp	return_9000AB
		
	ORG_MP_REG_System_Hook ENDP
	
	ORG_HP_REG_System_Hook PROC
		
		mov     edx, 8
		mov     rcx, r15
		call    sub_423EB0
		mov		r8,rax
		mov     edx, 7
		mov     rcx, r15
		call    sub_423EB0
		mov     edx, 6
		mov     rcx, r15
		mov     r14, rax
		call    sub_423EB0
		mov     edx, 5
		mov     rcx, r15
		mov     r13, rax
		call    sub_423EB0
		mov     edx, 4
		mov     rcx, r15
		mov     r12, rax
		call    sub_423EB0
		mov     edx, 3
		mov     rcx, r15
		mov     rbp, rax
		call    sub_423EB0
		mov     edx, 2
		mov     rcx, r15
		mov     rbx, rax
		call    sub_423EB0
		mov     edx, 1
		mov     rcx, r15
		mov     rsi, rax
		call    sub_423EB0
		xor     edx, edx
		mov     rcx, r15
		mov     rdi, rax
		call    sub_423EB0
		movlpd  xmm0, qword ptr [r8]
		movsd   qword ptr [rsp+68h], xmm0
		movlpd  xmm0, qword ptr [r14]
		movlpd  xmm1, qword ptr [r13]
		movsd   qword ptr [rsp+60h], xmm0
		movlpd  xmm0, qword ptr [r12]
		movsd   qword ptr [rsp+58h], xmm1
		movlpd  xmm1, qword ptr [rbp]
		movsd   qword ptr [rsp+50h], xmm0
		movlpd  xmm0, qword ptr [rbx]
		movsd   qword ptr [rsp+48h], xmm1
		movlpd  xmm1, qword ptr [rsi]
		movsd   qword ptr [rsp+40h], xmm0
		movlpd  xmm0, qword ptr [rdi]
		movsd   qword ptr [rsp+38h], xmm1
		movlpd  xmm1, qword ptr [rax]
		movsd   qword ptr [rsp+30h], xmm0
		movsd   qword ptr [rsp+28h], xmm1
		jmp	return_8FFF76
		
	ORG_HP_REG_System_Hook ENDP
	
	Fixxing_Offset_Global_Array_Org_HP_CP PROC
	
		movsd   qword ptr [rax*8+r10+0bde44h], xmm0
		movlpd  xmm0, qword ptr [rsp+80h]
		movsd   qword ptr [rax*8+r10+0bde44h+8h], xmm0
		movlpd  xmm0, qword ptr [rsp+88h]
		movsd   qword ptr [rax*8+r10+0bde44h+10h], xmm0
		movlpd  xmm0, qword ptr [rsp+90h]
		movsd   qword ptr [rax*8+r10+0bde44h+18h], xmm0
		movlpd  xmm0, qword ptr [rsp+98h]
		movsd   qword ptr [rax*8+r10+0bde44h+20h], xmm0
		movlpd  xmm0, qword ptr [rsp+0A0h]
		movsd   qword ptr [rax*8+r10+0bde44h+28h], xmm0
		movlpd  xmm0, qword ptr [rsp+0A8h]
		movsd   qword ptr [rax*8+r10+0bde44h+30h], xmm0
		movlpd  xmm0, qword ptr [rsp+0B0h]
		movsd   qword ptr [rax*8+r10+0bde44h+38h], xmm0
		movlpd  xmm0, qword ptr [rsp+0B8h]
		movsd   qword ptr [rax*8+r10+0bde44h+40h], xmm0
		jmp return_744801

	Fixxing_Offset_Global_Array_Org_HP_CP ENDP
	
	Fixxing_Offset_Global_Array_Org_MP PROC
	
		movsd   qword ptr [rax*8+r10+0e4f64h], xmm0
		movlpd  xmm0, qword ptr [rsp+80h]
		movsd   qword ptr [rax*8+r10+0e4f64h+8h], xmm0
		movlpd  xmm0, qword ptr [rsp+88h]
		movsd   qword ptr [rax*8+r10+0e4f64h+10h], xmm0
		movlpd  xmm0, qword ptr [rsp+90h]
		movsd   qword ptr [rax*8+r10+0e4f64h+18h], xmm0
		movlpd  xmm0, qword ptr [rsp+98h]
		movsd   qword ptr [rax*8+r10+0e4f64h+20h], xmm0
		movlpd  xmm0, qword ptr [rsp+0A0h]
		movsd   qword ptr [rax*8+r10+0e4f64h+28h], xmm0
		movlpd  xmm0, qword ptr [rsp+0A8h]
		movsd   qword ptr [rax*8+r10+0e4f64h+30h], xmm0
		movlpd  xmm0, qword ptr [rsp+0B0h]
		movsd   qword ptr [rax*8+r10+0e4f64h+38h], xmm0
		movlpd  xmm0, qword ptr [rsp+0B8h]
		movsd   qword ptr [rax*8+r10+0e4f64h+40h], xmm0
		jmp return_7448B8

	Fixxing_Offset_Global_Array_Org_MP ENDP

END