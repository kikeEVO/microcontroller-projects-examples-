; delay retines

;delay_const EQU ((FREQ/168000)-1);8000000
delay_ms_const EQU ((4000000/168000)-1)
delay_us_const EQU ((4000000/168000)-1)

;*********************************************************************
; void delay(long milli_seconds)
delay		macro	millis
		mov	R0, # LOW millis
		mov	R1, # HIGH millis
		mov	R2, #0
		mov	R3, #0
		call	delay_ms
		endm
;*********************************************************************
; void delayMicrosecons(long micro_seconds)
delayMicrosecons	macro	micros
		mov	R0, micros
		call	delay_us
		endm
;*********************************************************************
; void delay_ms(long milli_seconds)
delay_ms:
	mov	A, #delay_ms_const
delay_ms_loop:
	dec 	A
	nop
	mov 	R0, reg0
	mov 	R0, reg0
	mov 	R0, reg0
	mov 	R0, reg0
	mov 	R0, reg0
	cjne	A, #0xff, delay_ms_loop
	dec	R0
	cjne	R0, #0xff, delay_ms
	dec	R1
	cjne	R1, #0xff, delay_ms
	dec	R2
	cjne	R2, #0xff, delay_ms
	dec	R3
	cjne	R3, #0xff, delay_ms
	ret
	
;*********************************************************************
;void delay_us(char micro_seconds)
delay_us:
	dec	R0
	cjne	R0, #0x0, delay_us
	ret

;	END