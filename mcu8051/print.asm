;*********************************************************************
;void printString(void (*out)(char byte), char* string)
printString	macro	out_func, string
		mov	R0, #LOW out_func
		mov	R1, #HIGH out_func
		mov	R2, #LOW string
		mov	R3, #HIGH string
		call	print_string
		endm
		;*********************************************************************
;void printString(void (*out)(char byte), char* string)
printConstString macro	out_func, string
		mov	R0, #LOW out_func
		mov	R1, #HIGH out_func
		mov	R2, #LOW string
		mov	R3, #HIGH string
		call	print_string_const
		endm

;*********************************************************************
;void printUint16(void (*out)(char byte), uint_16 reg16b)
printUint16	macro	out_func, reg16b
		mov	R2, reg16b
		mov	R3, reg16b +1
		mov	R0, #LOW out_func
		mov	R1, #HIGH out_func
		call	print_integer16
		endm

;*********************************************************************
;void print_string(void (*out)(char byte), char* string)
print_string:
	push	DPL
	push	DPH
	mov	GPRAM, R0
	mov	GPRAM+1, R1
	mov	DPL, R2
	mov	DPH, R3
print_string_loop:
	movx	A, @DPTR
	jz	print_string_end
	mov	R0, #LOW print_string_ret
	mov	R1, #HIGH print_string_ret
	push	reg0
	push	reg1
	push	GPRAM
	push	GPRAM+1
	mov	R0,A
	ret
print_string_ret:
	inc	DPTR
	jmp	print_string_loop
print_string_end:
	pop	DPH
	pop	DPL
	reti

;*********************************************************************
;void print_string(void (*out)(char byte), char* string)
print_string_const:
	push	DPL
	push	DPH
	mov	GPRAM, R0
	mov	GPRAM+1, R1
	mov	DPL, R2
	mov	DPH, R3
print_string_const_loop:
	clr	A
	movc	A, @A+DPTR
	jz	print_string_const_end
	mov	R0, #LOW print_string_const_ret
	mov	R1, #HIGH print_string_const_ret
	push	reg0
	push	reg1
	push	GPRAM
	push	GPRAM+1
	mov	R0,A
	ret
print_string_const_ret:
	inc	DPTR
	jmp	print_string_const_loop
print_string_const_end:
	pop	DPH
	pop	DPL
	reti
;*********************************************************************
;void print_integer16(void (*out)(char byte), int16 number)
print_integer16:
	mov	GPRAM, R0
	mov	GPRAM+1, R1
	mov	GPRAM+2, DPL
	mov	GPRAM+3, DPH
	mov	R0, reg2
	mov	R1, reg3
print_integer16_loop:
	mov	R2, #10
	mov	R3, #0
	lcall	divide_uint16
	inc	DPTR
	mov	A, R2
	add	A, #0x30
	movx	@DPTR, A
	cjne	R0, #0, print_integer16_loop
	cjne	R1, #0, print_integer16_loop
print_integer16_loop2:
	movx	A, @DPTR
	mov	R0, #LOW print_integer16_ret
	mov	R1, #HIGH print_integer16_ret
	push	reg0
	push	reg1
	push	GPRAM
	push	GPRAM+1
	mov	R0,A
	ret
print_integer16_ret:
	mov	A, DPL
	add	A, #0xFF
	mov	DPL, A
	mov	A, DPH
	addc	A, #0xFF
	mov	DPH, A
	cjne	A, GPRAM+3, print_integer16_loop2
	mov	A, DPL
	cjne	A, GPRAM+2, print_integer16_loop2
	ret

;	END