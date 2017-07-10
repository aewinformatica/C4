include ../L2Extend/windows.inc 

THUNK_FUNC macro Addr, Name
FUNC_BEGIN Name
	jmp    loc(Addr)
FUNC_END Name
endm

.code

tls_trace_begin proc

	XPUSHAD_ALL
	
	xor		rbp, rbp
	xor		r8, r8
	xor		rdx, rdx
	mov		r12, rcx				;func name
	mov     ebp, 8
	mov     rax, gs:[58h]
	mov     rcx, [rax]
	movsxd  r8, dword ptr [rcx+rbp]
	mov     rsi, 400000h
	movsxd  rdx, dword ptr [rsi+r8*4+17289B0h]
	lea     eax, [rdx+1]
	mov     [rsi+r8*4+17289B0h], eax
	mov     rax, r8
	imul    rax, 3E8h
	add     rax, rdx
	mov     [rsi+rax*8+170D430h], rdi
	mov     rcx, r8
	imul    rcx, 64h
	add     rcx, rdx
	mov     r9, 20FC690h
	mov		r9, [r9]
	mov     rax, [r9+10h]
	mov     [rax+rcx*2], r11w
	mov     rax, [r9+10h]
	mov     word ptr [rax+rcx*2+2], 0
	mov     rax, [r9+10h]
	mov     [r8+rax+2710h], dl
	
	XPOPAD_ALL
	ret
tls_trace_begin endp

tls_trace_end proc
	XPUSHAD_ALL
	
	mov     r9, 20FC690h
	mov		r9, [r9]
	mov     r13, 8h
	mov     rbp, 400000h
	mov     rax, gs:[58h]
	mov     rcx, [rax]
	movsxd  rdx, dword ptr [r13+rcx]
	dec     dword ptr [rbp+rdx*4+17289B0h]
	mov     ecx, dword ptr [rbp+rdx*4+17289B0h]
	dec     cl
	mov     rax, [r9+10h]
	mov     [rdx+rax+2710h], cl
	
	XPOPAD_ALL
	ret
tls_trace_end endp

npc_shared_guard proc
	mov rax, 41ABD0h
	jmp rax
npc_shared_guard endp

END
