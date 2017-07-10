EXTRN	?IsItemOnOtherCreature@CDestroyItem@@CA_NPEAVUser@@PEAVCItem@@@Z:PROC
.const
	ret_870137		dq 870137h
	ret_870041		dq 870041h

.code
?Code_87012F@CDestroyItem@@CAXXZ	proc
		xor		rax, rax
		mov		rdx, rdi
		mov		rcx, rsi
		call	?IsItemOnOtherCreature@CDestroyItem@@CA_NPEAVUser@@PEAVCItem@@@Z
		cmp		rax, 0
		jz		undef_item_or_user
		jmp		[ret_870041]
undef_item_or_user:		
		mov     dword ptr [rsp+20h], 1671h
		jmp		[ret_870137]
?Code_87012F@CDestroyItem@@CAXXZ	endp

end
