; setup rutine: set stack and data stack
; define the insterrupt vectors, also has
; some  constants


;FREQ	EQU	8000000
stack_start EQU	0xc0
data_stack_start EQU 0x80
GPRAM	 EQU	0x50
MATHRAM	 EQU	0x30

reg0	DATA	0x00
reg1	DATA	0x01
reg2	DATA	0x02
reg3	DATA	0x03
reg4	DATA	0x04
reg5	DATA	0x05
reg6	DATA	0x06
reg7	DATA	0x07
ireg0	DATA	0x08
ireg1	DATA	0x09
ireg2	DATA	0x0a
ireg3	DATA	0x0b
ireg4	DATA	0x0c
ireg5	DATA	0x0d
ireg6	DATA	0x0e
ireg7	DATA	0x0f

	org	00h	; Reset
	ajmp	setupMCU
	org	03h	; External 0
	reti
	org	0Bh	; Timer 0
IFDEF	TIMER0_INT
	ljmp	timer0_int_vect
ENDIF
	reti
	org	13h	; External 1
	reti
	org	1Bh	; Timer 1
	reti
	org	23h	; UART and SPI
	reti
	org	2Bh	; Timer 2
	reti
	org	33h	; Analog comparator
	reti
	org	3Bh	; External 2
	reti
	org	43h	; External 3
	reti
	org	4Bh	; Brown out
	reti

	org	53h


setupMCU:
	mov	SP, #stack_start
	mov	DPTR, #data_stack_start
	mov	P0, #0xff
	mov	P1, #0xff
	mov	P2, #0xff
	mov	P3, #0xff

;	main:

;	END