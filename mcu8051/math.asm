;*********************************************************************
;uint16 divide_uint32(uint16 num, uint16 den)
divide_uint16:
	mov	R6, #16
	clr	A
	mov	R4, A
	mov	R5, A
divide_uint16_loop:
	mov	A, R0
	add	A, ACC
	mov	R0, A
	mov	A, R1
	rlc	A
	mov	R1, A
	mov	A, R4
	rlc	A
	mov	R4, A
	mov	A, R5
	rlc	A
	mov	R5, A
	mov	A, R4
	subb	A, R2
	mov	B, A
	mov	A, R5
	subb	A, R3
	jc	$+8
	mov	R5, A
	mov	R4, B
	orl	reg0, #1
	djnz	R6, divide_uint16_loop
	mov	R2, reg4
	mov	R3, reg5
	ret

;*********************************************************************
;uint32 divide_uint32(uint32 num, uint32 den)
divide_uint32:
	mov	R4, #32
	mov	A, DPL
	add	A, #0xfd
	mov	DPL, A
	mov	A, DPH
	addc	A, #0xff
	mov	DPH, A
	movx	A, @DPTR
	mov	MATHRAM, A
	inc	DPTR
	movx	A, @DPTR
	mov	MATHRAM+1, A
	inc	DPTR
	movx	A, @DPTR
	mov	MATHRAM+2, A
	inc	DPTR
	movx	A, @DPTR
	mov	MATHRAM+3, A
	clr	A
	mov	MATHRAM+4, A
	mov	MATHRAM+5, A
	mov	MATHRAM+6, A
	mov	MATHRAM+7, A
divide_uint32_loop:
	mov	A, R0
	add	A, ACC
	mov	R0, A
	mov	A, R1
	rlc	A
	mov	R1, A
	mov	A, R2
	rlc	A
	mov	R2, A
	mov	A, R3
	rlc	A
	mov	R3, A
	mov	A, MATHRAM+4
	rlc	A
	mov	MATHRAM+4, A
	mov	A, MATHRAM+5
	rlc	A
	mov	MATHRAM+5, A
	mov	A, MATHRAM+6
	rlc	A
	mov	MATHRAM+6, A
	mov	A, MATHRAM+7
	rlc	A
	mov	MATHRAM+7, A
	mov	A, MATHRAM+4
	subb	A, MATHRAM
	mov	MATHRAM+8, A
	mov	A, MATHRAM+5
	subb	A, MATHRAM+1
	mov	MATHRAM+9, A
	mov	A, MATHRAM+6
	subb	A, MATHRAM+2
	mov	MATHRAM+10, A
	mov	A, MATHRAM+7
	subb	A, MATHRAM+3
	jc	$+16
	mov	MATHRAM+7, A
	mov	MATHRAM+6, MATHRAM+10
	mov	MATHRAM+5, MATHRAM+9
	mov	MATHRAM+4, MATHRAM+8
	orl	reg0, #1
	djnz	R4, divide_uint32_loop
	mov	A, DPL
	add	A, #0xfd
	mov	DPL, A
	mov	A, DPH
	addc	A, #0xff
	mov	DPH, A
	mov	A, MATHRAM+4
	movx	A, @DPTR
	inc	DPTR
	mov	A, MATHRAM+5
	movx	A, @DPTR
	inc	DPTR
	mov	A, MATHRAM+6
	movx	A, @DPTR
	inc	DPTR
	mov	A, MATHRAM+7
	movx	A, @DPTR
	ret

;*********************************************************************
;uint16 multiply_uint16(uint16 ope1, uint16 ope2)
multiply_uint16:
	mov	A, R0
	mov	B, reg2
	mul	AB
	mov	R4, A
	mov	R5, B
	mov	A, R0
	mov	B, reg3
	mul	AB
	add	A, R5
	mov	R5,A
	mov	A, B
	addc	A, #0
	mov	R6, A
	mov	A, R1
	mov	B, reg2
	mul	AB
	add	A, R5
	mov	R5,A
	mov	A, B
	addc	A, R6
	mov	R6, A
	clr	A
	addc	A, #0
	mov	R7, A
	mov	A, R1
	mov	B, reg3
	mul	AB
	add	A, R6
	mov	R6,A
	mov	A, B
	addc	A, R7
	mov	R3, A
	mov	R2, reg6
	mov	R1, reg5
	mov	R0, reg4
	ret

;*********************************************************************
;uint32 multiply_uint16(uint32 ope1, uint32 ope2)
multiply_uint32:
	mov	A, DPL
	add	A, #0xfd
	mov	DPL, A
	mov	A, DPH
	addc	A, #0xff
	mov	DPH, A
	movx	A, @DPTR
	mov	MATHRAM, A
	inc	DPTR
	movx	A, @DPTR
	mov	MATHRAM+1, A
	inc	DPTR
	movx	A, @DPTR
	mov	MATHRAM+2, A
	inc	DPTR
	movx	A, @DPTR
	mov	MATHRAM+3, A
	mov	MATHRAM+4, R0
	mov	MATHRAM+5, R1
	mov	MATHRAM+6, R2
	mov	MATHRAM+7, R3

	mov	R2, MATHRAM
	mov	R3, MATHRAM+1
	acall	multiply_uint16
	mov	MATHRAM+8, R0
	mov	MATHRAM+9, R1
	mov	MATHRAM+10, R2
	mov	MATHRAM+11, R3

	mov	R0, MATHRAM
	mov	R1, MATHRAM+1
	mov	R2, MATHRAM+6
	mov	R3, MATHRAM+7
	acall	multiply_uint16
	mov	A, R0
	add	A, MATHRAM+10
	mov	MATHRAM+10, A
	mov	A, R1
	addc	A, MATHRAM+11
	mov	MATHRAM+11, A
	mov	A, R2
	addc	A, #0
	mov	MATHRAM+12, A
	mov	A, R3
	addc	A, #0
	mov	MATHRAM+13, A

	mov	R0, MATHRAM+2
	mov	R1, MATHRAM+3
	mov	R2, MATHRAM+4
	mov	R3, MATHRAM+5
	acall	multiply_uint16
	mov	A, R0
	add	A, MATHRAM+10
	mov	MATHRAM+10, A
	mov	A, R1
	addc	A, MATHRAM+11
	mov	MATHRAM+11, A
	mov	A, R2
	addc	A, MATHRAM+12
	mov	MATHRAM+12, A
	mov	A, R3
	addc	A, MATHRAM+13
	mov	MATHRAM+13, A
	clr	A
	addc	A, #0
	mov	MATHRAM+14, A

	mov	R0, MATHRAM+2
	mov	R1, MATHRAM+3
	mov	R2, MATHRAM+6
	mov	R3, MATHRAM+7
	acall	multiply_uint16
	mov	A, R0
	add	A, MATHRAM+12
	mov	MATHRAM+12, A
	mov	A, R1
	addc	A, MATHRAM+13
	mov	MATHRAM+13, A
	mov	A, R2
	addc	A, MATHRAM+14
	mov	MATHRAM+14, A
	mov	A, R3
	addc	A, MATHRAM+15
	mov	MATHRAM+15, A

	mov	A, DPL
	add	A, #0xfd
	mov	DPL, A
	mov	A, DPH
	addc	A, #0xff
	mov	DPH, A
	mov	A, MATHRAM+12
	movx	@DPTR, A
	inc	DPTR
	mov	A, MATHRAM+13
	movx	@DPTR, A
	inc	DPTR
	mov	A, MATHRAM+14
	movx	@DPTR, A
	inc	DPTR
	mov	A, MATHRAM+15
	movx	@DPTR, A
	mov	R0, MATHRAM+8
	mov	R1, MATHRAM+9
	mov	R2, MATHRAM+10
	mov	R3, MATHRAM+11
	ret

;	END