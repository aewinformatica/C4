.586
.model		flat,c

include ../L2Extend/windows.inc 

.data
	ret_458563	DWORD	458563h
	ret_458767	DWORD	458767h
	ret_458844	DWORD	458844h
	ret_4580A1	DWORD	4580A1h
	ret_4582A3	DWORD	4582A3h
	ret_45838E	DWORD	45838Eh
	
	DBConn__BindNullable	DWORD	42AD20h
	CPledge__CPledge		DWORD	453420h

.code

LoadPledgeAdd1 proc
	mov     [esp+108h], esi
	mov     [esp+10Ch], esi
	mov     [esp+110h], esi
	mov     [esp+114h], esi
	mov     [esp+118h], esi
	mov     [esp+11Ch], esi
	mov		eax, 0FFFFFFFFh
	mov     [esp+14h], eax
	jmp		ret_458563
LoadPledgeAdd1 endp

LoadPledgeByNameAdd1 proc
	mov     [esp+108h], esi
	mov     [esp+10Ch], esi
	mov     [esp+110h], esi
	mov     [esp+114h], esi
	mov     [esp+118h], esi
	mov     [esp+11Ch], esi
	mov		eax, 0FFFFFFFFh
	mov     [esp+14h], eax
	jmp		ret_4580A1
LoadPledgeByNameAdd1 endp

LoadPledgeAdd2 proc
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+108h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+10Ch]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+110h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+114h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+118h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+11Ch]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	mov		eax, 0FFFFFFFFh
	mov     edi, [esp+504h]
	jmp		ret_458767
LoadPledgeAdd2 endp

LoadPledgeByNameAdd2 proc
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+108h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+10Ch]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+110h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+114h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+118h]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	lea     ecx, [esp+14h]
	push    ecx             ; StrLen_or_Ind
	lea     edx, [esp+11Ch]
	push    edx             ; TargetValue
	lea     ecx, [esp+84h]
	call    DBConn__BindNullable
	mov     eax, [56ADC8h]
	jmp		ret_4582A3
LoadPledgeByNameAdd2 endp

LoadPledgeAdd3 proc
	call    CPledge__CPledge
	push	ecx
	push	edx
	mov		edx, eax
	mov		cl, byte ptr [esp+108h]
	mov		byte ptr [edx+148h], cl	
	mov		cl, byte ptr [esp+10Ch]
	mov		byte ptr [edx+149h], cl	
	mov		cl, byte ptr [esp+110h]
	mov		byte ptr [edx+14Ah], cl	
	mov		cl, byte ptr [esp+114h]
	mov		byte ptr [edx+14Bh], cl	
	mov		cl, byte ptr [esp+118h]
	mov		byte ptr [edx+14Ch], cl	
	mov		cl, byte ptr [esp+11Ch]
	mov		byte ptr [edx+14Dh], cl
	pop		edx
	pop		ecx
	jmp		ret_458844
LoadPledgeAdd3 endp

LoadPledgeByNameAdd3 proc
	call    CPledge__CPledge
	push	ecx
	push	edx
	mov		edx, eax
	mov		cl, byte ptr [esp+108h]
	mov		byte ptr [edx+148h], cl	
	mov		cl, byte ptr [esp+10Ch]
	mov		byte ptr [edx+149h], cl	
	mov		cl, byte ptr [esp+110h]
	mov		byte ptr [edx+14Ah], cl	
	mov		cl, byte ptr [esp+114h]
	mov		byte ptr [edx+14Bh], cl	
	mov		cl, byte ptr [esp+118h]
	mov		byte ptr [edx+14Ch], cl	
	mov		cl, byte ptr [esp+11Ch]
	mov		byte ptr [edx+14Dh], cl
	pop		edx
	pop		ecx
	jmp		ret_45838E
LoadPledgeByNameAdd3 endp

END
