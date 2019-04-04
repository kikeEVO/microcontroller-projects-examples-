; *****************************************************************************

;============================================================================
; delays macros
;============================================================================

; void delay(long millis)
delay	MACRO	millis 
	movlw	high millis>>16
	movwf	R3
	movlw	low millis>>16
	movwf	R2
	movlw	high millis
	movwf	R1
	movlw	low millis
	movwf	R0
	call	delay_ms
	ENDM

; void delay(int millis)
delayMicrosecons    MACRO	micros
	movlw	high micros
	movwf	R1
	movlw	low micros
	movwf	R0
	call	delay_us
	ENDM

;============================================================================
; delays rutines
;============================================================================

; void delay_ms(long millis)
delay_ms:
	pushd	R0
	pushd	R1
	movlw	high .1000
	movwf	R1
	movlw	low .1000
	movwf	R0
	rcall	delay_us
	popd	R1
	popd	R0
	decf	R0,f
	bc	delay_ms
	decf	R1,f
	bc	delay_ms
	decf	R2,f
	bc	delay_ms
	decf	R3,f
	bc	delay_ms
	return

; void delay_us(int micros)
delay_us:
	local a = ((FCY/.4000000)-3)
	while a > 0
	    nop
a = a-1
	endw
	decf	R0,f
	bc	delay_us
	decf	R1,f
	bc	delay_us
	return

