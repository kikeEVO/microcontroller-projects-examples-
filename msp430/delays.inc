; *****************************************************************************

;============================================================================
; delays macros
;============================================================================

; void delay(long millis)
delay	.macro	millis
		;mov		#$LO16(millis), R12
		;mov		#$HI16(millis), R13
		mov		#millis & 0xffff, R12
		mov		#millis>>16, R13
		calla	#delay_ms
		.endm

; void delay(long millis)
delayMicrosecons	.macro	micros
		mov		#micros, R12
		calla	#delay_us
		.endm

;============================================================================
; delays rutines
;============================================================================

; void delay_ms(long millis)
delay_ms:
		push	R12
		mov		#1000, R12
		calla	#delay_us
		pop		R12
		sub		#1, R12
		jc		delay_ms
		sub		#1, R13
		jc		delay_ms
		reta

; void delay_us(int micros)
delay_us:
		push	R15
		push	R15
		pop		R15
		pop		R15
		sub		#1, R12
		jnz		delay_us
		reta
