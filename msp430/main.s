; *****************************************************************************
		.cdecls C,LIST,"msp430.h"

; *****************************************************************************

;============================================================================
; *****************************************************************************
;-------------------------------------------------------------------------------
        .text
        .global main
        .retain
        .retainrefs

;============================================================================
; include rutines
;============================================================================

		.include 	"macros.inc"
		.include	"delays.inc"
		.include	"setup.inc"
		.include	"pins.inc"
		.include	"serial.inc"
		.include	"lcd.inc"
		.include	"math.inc"
		.include 	"print.inc"

;============================================================================
; macros
;============================================================================

;============================================================================
; main
;============================================================================
main:
		calla	#start_up
		delay	1000
		SerialBegin
		lcdBegin
		pinMode	#PIN41, #OUTPUT
		pinMode	#PIN42, #OUTPUT

		lcdCursor	#0, #0
		lcdWrite_string	#cadena2
		serialWrite_string	#cadena

		calla	#timer_config
		mov32	#0, &count
loop:
		delay	500
		digitalWrite #PIN41, #HIGH
		delay	500
		digitalWrite #PIN41, #LOW

		lcdCursor	#0, #1
		printString #lcd_write, #cadena3
		printUint32	#lcd_write, &count
		printlnUint32	#serial_write, &count

		add32	#1, &count

		jmp		loop

timer_config:
		mov		# TASSEL__ACLK | ID__1 | MC__UP | TAIE_0, &TA0CTL
		mov		# CM_0 | CAP__COMPARE | OUTMOD0 | CCIE_1, &TA0CCTL0
		mov		# TAIDEX__1, &TA0EX0
		mov		#32768, &TA0CCR0

		nop
		bis		#GIE, SR
		nop

		reta

TIMER_ISR:
		bic 	#TAIFG, &TA0CTL
		pushm.a	#12, R15
		xor.b	#1, &toggle_bit
		digitalWrite #PIN42, &toggle_bit
		popm.a	#12, R15
		reti

;============================================================================
; code strings
;============================================================================

cadena	.string "hola mundo",0x0a,0
cadena2	.string "hello world",0
cadena3	.string "c = ",0

;============================================================================
; interrupt vectors define
;============================================================================

		.sect TIMER0_A0_VECTOR
		.short TAC0_INT

;============================================================================
; data memory
;============================================================================
		.data
count	.word	0,0
toggle_bit .byte 0

;============================================================================
; interrupt vectors redirect on RAM
;============================================================================
TAC0_INT:
		mova	#TIMER_ISR, PC
		.end
