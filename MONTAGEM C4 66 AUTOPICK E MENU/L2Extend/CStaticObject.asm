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
	
	EXTERN	?pIndex@CStaticObject@@2PAEA:PTR
	EXTERN	?pIndex2@CStaticObject@@2PA_JA:PTR
	EXTERN	?pStatic@CStaticObject@@2PA_JA:PTR
	
	RETURN_960524	QWORD	960524h
	RETURN_7DF732	QWORD	7DF732h
	RETURN_7DFC37	QWORD	7DFC37h
	RETURN_7DFC23	QWORD	7DFC23h
	RETURN_960510	QWORD	960510h
	RETURN_7E09AC	QWORD	7E09ACh
	RETURN_7DF746	QWORD	7DF746h
	RETURN_7E0973	QWORD	7E0973h
	RETURN_9604F5	QWORD	9604F5h
	RETURN_7DF754	QWORD	7DF754h
	RETURN_7DFB25	QWORD	7DFB25h
	RETURN_7DFB36	QWORD	7DFB36h
	
.CODE

	?Code_7DF72A@CStaticObject@@SAXXZ PROC
	
		movzx   eax, byte ptr [?pIndex@CStaticObject@@2PAEA+rax]
		jmp		RETURN_7DF732		
	
	?Code_7DF72A@CStaticObject@@SAXXZ ENDP
	
	?Code_7DFC30@CStaticObject@@SAXXZ PROC
	
		mov     byte ptr [?pIndex@CStaticObject@@2PAEA+rbx], al
		jmp		RETURN_7DFC37		
	
	?Code_7DFC30@CStaticObject@@SAXXZ ENDP
	
	?Code_7DFC1B@CStaticObject@@SAXXZ PROC
	
		movzx   eax, byte ptr [?pIndex@CStaticObject@@2PAEA+rbx]
		jmp		RETURN_7DFC23			
	
	?Code_7DFC1B@CStaticObject@@SAXXZ ENDP
	
	?Code_96051D@CStaticObject@@SAXXZ PROC
	
		lea     rcx, [?pIndex@CStaticObject@@2PAEA]
		jmp		RETURN_960524		
	
	?Code_96051D@CStaticObject@@SAXXZ ENDP
	
	?Code_7DF73E@CStaticObject@@SAXXZ PROC
	
		cmp     byte ptr [?pIndex2@CStaticObject@@2PA_JA+rax], 0
		jmp		RETURN_7DF746			
	
	?Code_7DF73E@CStaticObject@@SAXXZ ENDP
	
	?Code_7E096B@CStaticObject@@SAXXZ PROC
	
		lea     rbx, [?pIndex2@CStaticObject@@2PA_JA+rbp*8]
		jmp		RETURN_7E0973
	
	?Code_7E096B@CStaticObject@@SAXXZ ENDP
	
	?Code_9604EE@CStaticObject@@SAXXZ PROC
	
		lea     rcx, [?pIndex2@CStaticObject@@2PA_JA]
		jmp		RETURN_9604F5	
	
	?Code_9604EE@CStaticObject@@SAXXZ ENDP
	
	?Code_7DF74C@CStaticObject@@SAXXZ PROC
	
		mov     rax, [?pStatic@CStaticObject@@2PA_JA+rcx*8]	
		jmp		RETURN_7DF754	
	
	?Code_7DF74C@CStaticObject@@SAXXZ ENDP
	
	?Code_7E09A4@CStaticObject@@SAXXZ PROC
	
		mov     [?pStatic@CStaticObject@@2PA_JA+rbp*8], rsi
		jmp		RETURN_7E09AC			
	
	?Code_7E09A4@CStaticObject@@SAXXZ ENDP
	
	?Code_960509@CStaticObject@@SAXXZ PROC
	
		lea     rcx, [?pStatic@CStaticObject@@2PA_JA]
		jmp		RETURN_960510			
	
	?Code_960509@CStaticObject@@SAXXZ ENDP
	
	?Code_7DFB1C@CStaticObject@@SAXXZ PROC
	
		mov     byte ptr [?pIndex2@CStaticObject@@2PA_JA+r9*8], 0
		jmp		RETURN_7DFB25			
	
	?Code_7DFB1C@CStaticObject@@SAXXZ ENDP
	
	?Code_7DFB2E@CStaticObject@@SAXXZ PROC
	
		mov     rcx, [?pStatic@CStaticObject@@2PA_JA+rax*8]
		jmp		RETURN_7DFB36			
	
	?Code_7DFB2E@CStaticObject@@SAXXZ ENDP
	
	
END
