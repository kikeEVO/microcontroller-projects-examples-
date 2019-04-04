; *****************************************************************************

;============================================================================
; Serial macros
;============================================================================

;*********************************************************************
;void SerialBegin(void)
SerialBegin MACRO
	call	serial_begin
	ENDM

;*********************************************************************
;void serialWrite(char byte_serial)
serialWrite MACRO   byte_serial
	movlw	byte_serial
	movwf	R0
	call	serial_write
	ENDM

;*********************************************************************
;void serialWrite_string(char* data_lcd)
serialWrite_string  MACRO	string
	movlw	high string
	movwf	R1
	movlw	low string
	movwf	R0
	call	serial_write_string
	ENDM

;============================================================================
; Serial rutines
;============================================================================

; void serial_begin(void)
serial_begin:
	bcf	TRISC, 6
	pushd	BSR
	movlb	0xe
	movlw	0x09
	movwf	RC6PPS
	popd	BSR
	movlw	0x80
	movwf	RC1STA
	clrf	BAUD1CON
	movlw	.51
	movwf	SP1BRGL
	movlw	0x20
	movwf	TX1STA
	return

; void serial_write(char byte)
serial_write:
	btfss	TX1STA, 1
	bra	serial_write
	movff	R0, TX1REG
	return

; void serial_write_string(char* string)
serial_write_string:
	movff	R1, TBLPTRH
	movff	R0, TBLPTRL
serial_write_string_loop:
	tblrd*+
	movf	TABLAT, w
	bz	serial_write_string_end
	movwf	R0
	rcall	serial_write
	bra	serial_write_string_loop
serial_write_string_end:
	return