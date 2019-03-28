
;============================================================================
; print macros
;============================================================================

;*********************************************************************
;void printString(void (*out)(char byte), char* string)
printString .macro	out_func, string
			mova	out_func, R12
			mova	string, R13
			calla	#print_string
			.endm
;*********************************************************************
;void printlnString(void (*out)(char byte), char* string)
printlnString .macro	out_func, string
			mova	out_func, R12
			mova	string, R13
			calla	#print_string
			mov		#0xa, R12
			calla	out_func
			.endm

;*********************************************************************
;void printUint16(void (*out)(char byte), uint_16 reg16b)
printUint16	.macro	out_func, reg16b
			mova	out_func, R12
			mov		reg16b, R13
			calla	#print_integer16
			.endm

;*********************************************************************
;void printlnUint16(void (*out)(char byte), uint_16 reg16b)
printlnUint16	.macro	out_func, reg16b
			mova	out_func, R12
			mov		reg16b, R13
			calla	#print_integer16
			mov		#0xa, R12
			calla	out_func
			.endm

;*********************************************************************
;void printUint32(void (*out)(char byte), uint_32 reg32b)
printUint32	.macro	out_func, reg32b
			mova	out_func, R12
			mov32	reg32b, R13
			calla	#print_integer32
			.endm

;*********************************************************************
;void printlnUint32(void (*out)(char byte), uint_32 reg32b)
printlnUint32	.macro	out_func, reg32b
			mova	out_func, R12
			mov32	reg32b, R13
			calla	#print_integer32
			mov		#0xa, R12
			calla	out_func
			.endm

;============================================================================
; print routines
;============================================================================

;*********************************************************************
;void print_string(void (*out)(char byte), char* string)
print_string:
		mova	R12, R14
print_string_loop:
		mov.b	@R13+, R12
		tst.b	R12
		jz		print_string_loop_end
		pushm.a	#2, R14
		calla	R14
		popm.a	#2, R14
		jmp		print_string_loop
print_string_loop_end:
		reta

;*********************************************************************
;void print_integer16(void (*out)(char byte), uint16 number)
print_integer16:
		mova	R1,R4
		mova	R12, R5
		mov		R13,R12
		suba	#10, SP
		suba	#1, R4
		mov.b	#0, 0(R4)
print_integer16_loop:
		suba	#1, R4
		mov		#10, R13
		calla	#divide_uint16
		add		#0x30, R13
		mov.b	R13, 0(R4)
		tst		R12
		jnz		print_integer16_loop

		mova	R5, R12
		mova	R4, R13
		calla	#print_string
		adda	#10, SP
		reta

;*********************************************************************
;void print_integer32(void (*out)(char byte), uint32 number)
print_integer32:
		mova	SP,R15
		suba	#20, SP
		mova	R12, 0(SP)
		mova	R15, 4(SP)
		mov.b	#0, -1(R15)
		subx.a	#1, 4(SP)
		mov		R13, R12
		mov		R14, R13
print_integer32_loop:
		mov		#10, R14
		mov		#0, R15
		calla	#divide_uint32
		add		#0x30, R14
		subx.a	#1, 4(SP)
		mova	4(SP), R15
		mov.b	R14, 0(R15)
		tst		R12
		jnz		print_integer32_loop
		tst		R13
		jnz		print_integer32_loop
		mova	0(SP), R12
		mova	4(SP), R13
		calla	#print_string
		adda	#20, SP
		reta
