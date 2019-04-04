	
	INCLUDE "p18f46k40.inc"
	INCLUDE "macros.inc"
	INCLUDE "setup.inc"
	INCLUDE "delays.inc"
	INCLUDE "pins.inc"
	INCLUDE "lcd.inc"
	INCLUDE "math.inc"
	INCLUDE "print.inc"
	INCLUDE "serial.inc"
	    
;******************************************************************************;	    
;global variables
        CBLOCK
	number	: 4
	ENDC
	    
main:	
	delay	.1000
	call	timer_conf
	lcdBegin
	SerialBegin
	pinMode	PIN1, OUTPUT
	pinMode	PIN2, OUTPUT
	lcdWrite_string	string1
	
	movlf32	0x1, number
loop:
	digitalWrite	PIN1, ZERO
	delay	.500
	digitalWrite	PIN1, ONE
	delay	.500
	serialWrite_string  string2
	lcdCursor   0,1
	printUint32 lcd_write, number
	addlf32	1, number
	goto	loop
	
timer_conf:
	bsf	T1CON, 0
	movlw	0x04
	movwf	TMR1CLK
	movlw	0x80
	movwf	CCPR1H
	clrf	CCPR1L
	movlw	0x81
	movwf	CCP1CON
	movlw	0x01
	movwf	CCPTMRS
	
	movlb	0x0e
	bsf	PIE6,CCP1IE,1
	movlb	0x0
	movlw	0xc0
	movwf	INTCON
	return
	
timer_int:
	bcf	PIR6, CCP1IF
	movlb	0x0
	movlw	0x02
	xorwf	LATA, f
	retfie	FAST
	
;******************************************************************************;
;constants on flash
	
string1	DB		"hello world!",0
string2	DB		"hola mundo!",0x0a,0
cero	DB		0x30
	
	END