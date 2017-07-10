.586
.model		flat,c

include ../L2Extend/windows.inc 

THUNK_FUNC macro Addr, Name
FUNC_BEGIN Name
	jmp    loc(Addr)
FUNC_END Name
endm

.data

.code
ASSUME fs:NOTHING ; 

tls_trace_begin proc Func:DWORD
	push eax
	push ecx
	push edx
	push ebp
	mov		ebp, [Func]				;func name
	xor     eax, eax				;make sure eax does not have garbage in high dword
	mov     eax, 1F4DDB8h
	mov     ecx, FS:[2Ch]
	mov     eax, [eax]
	push    esi
	mov     esi, [ecx+eax*4]
	mov     eax, [esi+8]
	mov     ecx, [eax*4+8EA678h]
	lea     edx, [ecx+1]
	mov     [eax*4+8EA678h], edx
	imul    eax, 3E8h
	add     eax, ecx
	mov     [eax*4+8D4DB0h], ebp
	pop esi
	pop ebp
	pop edx
	pop ecx
	pop eax
	ret
tls_trace_begin endp

tls_trace_end proc
	push eax
	xor     eax, eax				;make sure eax does not have garbage in high dword
	mov     eax, 1F4DDB8h
	mov     ecx, fs:[2Ch]
	mov     eax, [eax]
	push    esi
	mov     esi, [ecx+eax*4]
	mov     esi, [esi+8]
	mov		eax, fs:[0]
	mov     ecx, [eax+8h]
	mov		eax, 0FFFFFFFFh
	add     [esi*4+8EA678h], eax
	pop     esi
	mov     fs:[0], ecx	
	pop     eax
	ret
tls_trace_end endp

cashed_shared_guard proc
	mov eax, 4014B0h
	jmp eax
cashed_shared_guard endp

END
