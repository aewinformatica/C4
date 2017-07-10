include windows.inc

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


.data

	extern      CParserForSkill_FindAbnormalType:proc


CSKILLEFFECT_WITH_ABNORMAL macro addr, name, ab_off, ab_reg
local aName
.const
	aName       byte "&name&",0

FUNC_BEGIN CSkillEffect_&name&__ctor

		sub     rsp, 38h
		mov     [rsp+30h], rbp                        ; pParser
		mov     [rsp+28h], rcx                        ; pSkillEffect
		mov     [rsp+20h], ab_reg                     ; wszSlotName

		; call original constructor
		call    loc(addr)

		; extended abnormal type search
		mov     r8, [rsp+20h]                         ; wszSlotName
		lea     rdx, aName                            ; szEffectName
		mov     rcx, [rsp+30h]                        ; pParser
		call    CParserForSkill_FindAbnormalType
		mov     rcx, [rsp+28h]                        ; pSkillEffect
		mov     [rcx+(ab_off)], eax

		; return pSkillEffect
		mov     rax, [rsp+28h]
		add     rsp, 38h
		ret

FUNC_END CSkillEffect_&name&__ctor
endm

CSKILLEFFECT_WITH_ABNORMAL 7B4520h, i_abnormal_time_change, 10h, rdx
CSKILLEFFECT_WITH_ABNORMAL 7A5190h, i_dispel_by_slot, 10h, rdx
CSKILLEFFECT_WITH_ABNORMAL 7B5F60h, i_dispel_by_slot_probability, 10h, rdx


END
