include windows.inc

THUNK_FUNC macro Addr, Name
FUNC_BEGIN Name
	jmp    loc(Addr)
FUNC_END Name
endm

.code

tls_trace_begin proc
	push rdi
	push r12
	push rbp
	push r13
	mov r13, rcx					;func name
	xor     rdi, rdi				;make sure rdi does not have garbage in high dword
	mov     rdi, 1A6116ECh
	mov     edi, [rdi]
	mov     r12, 4C158h
	mov     rax, gs:[58h]
	mov     rcx, [rax+rdi*8]
	movsxd  rdx, dword ptr [r12+rcx]
	mov     rbp, 400000h
	movsxd  rcx, dword ptr [rbp+rdx*4+1179D70h]
	lea     eax, [rcx+1]
	mov     [rbp+rdx*4+1179D70h], eax
	imul    rdx, 3E8h
	add     rdx, rcx
	mov     [rbp+rdx*8+115E7F0h], r13
	pop r13
	pop rbp
	pop r12
	pop rdi
	ret
tls_trace_begin endp

tls_trace_end proc
	push rdi
	push r12
	push rbp
	xor     rdi, rdi				;make sure rdi does not have garbage in high dword
	mov     rdi, 1A6116ECh
	mov     edi, [rdi]
	mov     r12, 4C158h
	mov     rbp, 400000h
	mov     rax, gs:[58h]
	mov     rcx, [rax+rdi*8]
	movsxd  rax, dword ptr [r12+rcx]
	dec     dword ptr [rbp+rax*4+1179D70h]
	xor     al, al
	pop rbp
	pop r12
	pop rdi
	ret
tls_trace_end endp

l2server_shared_guard proc
	mov rax, 401500h
	jmp rax
l2server_shared_guard endp

THUNK_FUNC 9151A0h, l2server_free
THUNK_FUNC 9164A0h, l2server_malloc
THUNK_FUNC 912BC0h, l2server_operator_delete
THUNK_FUNC 912D80h, l2server_operator_new

; L2ServerFunctions::free
THUNK_FUNC 9151A0h, ?free@L2ServerFunctions@@SAXPEAX@Z

; L2ServerFunctions::malloc
THUNK_FUNC 9164A0h, ?malloc@L2ServerFunctions@@SAPEAX_K@Z

; L2ServerFunctions::operator_delete
THUNK_FUNC 912BC0h, ?operator_delete@L2ServerFunctions@@SAXPEAX@Z

; L2ServerFunctions::operator_new
THUNK_FUNC 912D80h, ?operator_new@L2ServerFunctions@@SAPEAX_K@Z

; NpcServer::Send
THUNK_FUNC 6CCD40h, ?Send@NpcServer@@QEAAXPEBDZZ

END
