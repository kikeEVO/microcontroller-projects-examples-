;============================================================================
; print macros
;============================================================================

;*********************************************************************
;void printString(void (*out)(char byte), char* string)
printString MACRO   out_func, string
	movlw	low out_func
	movwf	R0
	movlw	high out_func
	movwf	R1
	movlw	low string
	movwf	R2
	movlw	high string
	movwf	R3
	call	print_string
	ENDM
;*********************************************************************
;void printlnString(void (*out)(char byte), char* string)
printlnString	MACRO	out_func, string
	movlw	low out_func
	movwf	R0
	movlw	high out_func
	movwf	R1
	movlw	low string
	movwf	R2
	movlw	high string
	movwf	R3
	call	print_string
	movlw	0x0a
	movwf	R0
	call	out_func
	ENDM

;*********************************************************************
;void printUint16(void (*out)(char byte), uint_16 reg16b)
printUint16 MACRO   out_func, reg16b
	movlw	low out_func
	movwf	R0
	movlw	high out_func
	movwf	R1
	movff	reg16b, R2
	movff	reg16b+1, R3
	call	print_integer16
	ENDM

;*********************************************************************
;void printlnUint16(void (*out)(char byte), uint_16 reg16b)
printlnUint16	MACRO	out_func, reg16b
	movlw	low out_func
	movwf	R0
	movlw	high out_func
	movwf	R1
	movff	reg16b, R2
	movff	reg16b+1, R3
	call	print_integer16
	movlw	0x0a
	movwf	R0
	call	out_func
	ENDM

;*********************************************************************
;void printUint32(void (*out)(char byte), uint_32 reg32b)
printUint32 MACRO   out_func, reg32b
	movlw	low out_func
	movwf	R0
	movlw	high out_func
	movwf	R1
	pushd32	reg32b
	call	print_integer32
	addfsr	SP, 4
	ENDM

;*********************************************************************
;void printlnUint32(void (*out)(char byte), uint_32 reg32b)
printlnUint32	MACRO	out_func, reg32b
	movlw	low out_func
	movwf	R0
	movlw	high out_func
	movwf	R1
	pushd32	reg32b
	call	print_integer32
	addfsr	SP, 4
	movlw	0x0a
	movwf	R0
	call	out_func
	ENDM

;============================================================================
; print routines
;============================================================================

;*********************************************************************
;void print_string(void (*out)(char byte), char* string)
print_string:
	pushd16	R0
	movff16	R2, FSR0L
print_string_loop:
	movf	POSTINC0, w
	bz	print_string_loop_end
	movwf	R0
	movsf	[2], PCLATH
	movsf	[1], WREG
	callw
	pushd16	FSR0L
print_string_return:	
	popd16	FSR0L
	bra	print_string_loop
print_string_loop_end:
	addulnk	2

;*********************************************************************
;void print_integer16(void (*out)(char byte), uint16 number)
print_integer16:
	movff16	FSR2L, FSR1L
	subfsr	SP, .10
	pushd16	R0
	movff16	R2, R0
	clrf	POSTDEC1
print_integer16_loop:
	movlw	.10
	movwf	R2
	clrf	R3
	call	divide_uint16
	movlw	0x30
	addwf	R2, w
	movwf	POSTDEC1
	tstfsz	R0
	bra	print_integer16_loop
	tstfsz	R1
	bra	print_integer16_loop
	popd16	R0
	addfsr	FSR1, 1
	movff16	FSR1L, R2
	call	print_string
	addulnk	.10

;*********************************************************************
;void print_integer32(void (*out)(char byte), uint32 number)
print_integer32:
	movff16	R0, R4
	movsf	[1], R0
	movsf	[2], R1
	movsf	[3], R2
	movsf	[4], R3
	movff16	FSR2L, FSR1L
	subfsr	SP, .15
	pushd16	R4
	pushl	0
	pushl	0
	pushl	0
	pushl	.10
	clrf	POSTDEC1
print_integer32_loop:
	call	divide_uint32
	movlw	0x30
	addwf	R4, w
	movwf	POSTDEC1
	tstfsz	R0
	bra	print_integer32_loop
	tstfsz	R1
	bra	print_integer32_loop
	tstfsz	R2
	bra	print_integer32_loop
	tstfsz	R3
	bra	print_integer32_loop
	addfsr	SP, 4
	popd16	R0
	addfsr	FSR1, 1
	movff16	FSR1L, R2
	call	print_string
	addulnk	.15