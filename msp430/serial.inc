; *****************************************************************************

;============================================================================
; Serial macros
;============================================================================

;*********************************************************************
;void SerialBegin(void)
SerialBegin	.macro
			calla	#serial_begin
			.endm

;*********************************************************************
;void serialWrite(char byte_serial)
serialWrite	.macro	byte_serial
			mov.b	byte_serial, R12
			calla	#serial_write
			.endm

;*********************************************************************
;void serialWrite_string(char* data_lcd)
serialWrite_string	.macro	string
			mova	string, R12
			calla	#serial_write_string
			.endm

;============================================================================
; Serial rutines
;============================================================================

; void serial_begin(void)
serial_begin:
		bis.b	# BIT0 | BIT1, &P2SEL1
		mov		# UCSWRST, &UCA0CTLW0
		mov		# UCSSEL__SMCLK, &UCA0CTLW0
		mov		# FREQ_SM/9600, &UCA0BRW
		reta

; void serial_write(char byte)
serial_write:
		bit		#UCTXIFG,&UCA0IFG
		jz		serial_write
		mov.b	r12, &UCA0TXBUF
		reta

; void serial_write_string(char* string)
serial_write_string:
		mov.b	@R12+, R13
		cmp.b	#0, R13
		jz		serial_write_string_end
serial_write_string_wait:
		bit		#UCTXIFG, &UCA0IFG
		jz		serial_write_string_wait
		mov.b	R13, &UCA0TXBUF
		jmp		serial_write_string
serial_write_string_end:
		reta
