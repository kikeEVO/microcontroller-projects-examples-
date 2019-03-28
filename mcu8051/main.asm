; MCU 8051 - Test1
; Very simple code with mcu8051ide

FREQ	EQU	8000000

	ISEG 	at 0x30
count: 	DS	1

	XSEG 	at 0x10
my_string: DS	20

	CSEG 	at 0x0

INCLUDE 'macros.asm'
INCLUDE 'setup.asm'

;*********************************************************************
main:
	call	Timer0_port_init
	SerialBegin
	delay	2000
	lcdBegin
	lcdCursor #0, #0
	printConstString lcd_write, string2
	memcpyCsegXseg my_string, string1, 14
	lcdCursor #0, #1
	pushData	#0xff
	pushData	#0xff
loop:
	printString serial_port_send, my_string
	lcdCursor #0, #1
	popData	reg1
	popData	reg0
	inc16	reg0
	pushData	reg0
	pushData	reg1
	printUint16	lcd_write, reg0
	digitalWrite #PIN3_6, #ZERO
	delay	500
	digitalWrite #PIN3_6, #ONE
	delay	500
	sjmp	loop

;*********************************************************************
Timer0_port_init:
	mov	TMOD, #0x01
	setb	ET0
	setb	EA
	setb	TR0
	mov	count, #0
	ret

;*********************************************************************
TIMER0_INT	EQU	0
timer0_int_vect:
	mov	ireg0, PSW
	mov	PSW, 0x18
	mov	R1, 0x20
	mov	R3, count
	inc	count
	cjne	R3, #5, timer0_int_vect_end
	setb	0x20
	mov	C, P3.7
	jnc	$+4
	clr	0x20
	mov	C, 0x20
	mov	P3.7, C
	mov	count, #0
timer0_int_vect_end:
	mov	0x20, R1
	mov	PSW, ireg0
	reti

;*********************************************************************
;*********************************************************************
INCLUDE 'math.asm'
INCLUDE 'pins.asm'
INCLUDE 'delays.asm'
INCLUDE 'lcd.asm'
INCLUDE	'serial.asm'
INCLUDE	'memory.asm'
INCLUDE 'print.asm'

string1:
	DB	'hello world!',0x0a,0
string2:
	DB	'hola mundo!',0

	END
; parameters and return values
; [r0, r1, r2, r3]
; uint8, unt8, unt8, unt8
; uint8, unt8, unt16
; unt16, unt16
; unt32
; the other parameters are sended through DPTR as a increment stack
