;*********************************************************************
;void memcpyCsegXseg(char* dst, const char* src, int len)
memcpyCsegXseg	macro	string1, string2, length
		mov	A, #LOW length
		movx	@DPTR, A
		inc	DPTR
		mov	A, #HIGH length
		movx	@DPTR, A
		mov	R0, # LOW string1
		mov	R1, # HIGH string1
		mov	R2, # LOW string2
		mov	R3, # HIGH string2
		call	copy_code_to_xdata
		endm

;*********************************************************************
;void copy_code_to_xdata(char* dst, const char* src, int len)
copy_code_to_xdata:
	push	DPL
	push	DPH
	movx	A, @DPTR
	mov	R5, A
	mov	A, DPL
	clr	C
	subb	A, #1
	mov	DPL, A
	mov	A, DPH
	subb	A, #0
	mov	DPH, A
	movx	A, @DPTR
	mov	R4, A
	dec	R4
	cjne	R4, #0xff, $+9
	dec	R5
	cjne	R5, #0xff, $+5
	ajmp	$+25
	mov	DPL, R2
	mov	DPH, R3
	clr	A
	movc	A, @A+DPTR
	inc	DPTR
	mov	R2, DPL
	mov	R3, DPH
	mov	DPL, R0
	mov	DPH, R1
	movx	@DPTR, A
	inc	DPTR
	mov	R0, DPL
	mov	R1, DPH
	ajmp	$-31
	pop	DPH
	pop	DPL
	ret