include ..\L2Extend\windows.inc

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
	
	EXTERN	?SetAugment@CNPC@@SAXPEAV1@PEAVCSharedData@@@Z:PROC
	EXTERN	?DeleteAugment@CNPC@@SAXPEAV1@PEAVCSharedData@@@Z:PROC
	EXTERN	?ShowPledgeSkillList@CNPC@@SAXPEAV1@PEAVCSharedData@@@Z:PROC
	
	;------------------------------------------------------

.const

.code

FuncSetAugment		proc
	mov     rdx, [rdx]
	jmp		?SetAugment@CNPC@@SAXPEAV1@PEAVCSharedData@@@Z
FuncSetAugment		endp

FuncDeleteAugment		proc
			mov     rdx, [rdx]
			jmp		?DeleteAugment@CNPC@@SAXPEAV1@PEAVCSharedData@@@Z
FuncDeleteAugment		endp

FuncShowPledgeSkillList		proc
			mov     rdx, [rdx]
			jmp		?ShowPledgeSkillList@CNPC@@SAXPEAV1@PEAVCSharedData@@@Z
FuncShowPledgeSkillList		endp

END
