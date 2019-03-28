
PIN0_0   EQU	0
PIN0_1   EQU	1
PIN0_2   EQU	2
PIN0_3   EQU	3
PIN0_4   EQU	4
PIN0_5   EQU	5
PIN0_6   EQU	6
PIN0_7   EQU	7
PIN1_0   EQU	8
PIN1_1   EQU	9
PIN1_2   EQU	10
PIN1_3   EQU	11
PIN1_4   EQU	12
PIN1_5   EQU	13
PIN1_6   EQU	14
PIN1_7   EQU	15
PIN2_0   EQU	16
PIN2_1   EQU	17
PIN2_2   EQU	18
PIN2_3   EQU	19
PIN2_4   EQU	20
PIN2_5   EQU	21
PIN2_6   EQU	22
PIN2_7   EQU	23
PIN3_0   EQU	24
PIN3_1   EQU	25
PIN3_2   EQU	26
PIN3_3   EQU	27
PIN3_4   EQU	28
PIN3_5   EQU	29
PIN3_6   EQU	30
PIN3_7   EQU	31

PORT0   EQU	0
PORT1   EQU	1
PORT2   EQU	2
PORT3   EQU	3

OUTPUT  EQU	0
INPUT   EQU	1

ONE	EQU	1
ZERO	EQU	0

;*********************************************************************
;void digitalWrite(char pin, char Value)
digitalWrite	macro	pin, value
		mov	R0, pin
		mov	R1, value
		call	digital_write
		endm
;*********************************************************************
;char digitalRead(char pin)
digitalRead	macro	pin
		mov	R0, pin
		call	digital_read
		endm
		;*********************************************************************
;;void pinMode(char pin, char mode)
pinMode		macro	pin, mode
		mov	R0, pin
		mov	R1, mode
		call	pin_mode
		endm

;*********************************************************************
;*********************************************************************
;void digital_write(char pin, char Value)
digital_write:
	mov	A, #0x07
	anl	A, R0
	mov	R2, reg1
	mov	R1, A
	mov	A, #23
	clr	C
	subb	A, R0
	jnc	digital_write_port2
	mov	R0, #0x3
	call	write_bit_port
	ret
digital_write_port2:
	mov	A, #15
	clr	C
	subb	A, R0
	jnc	digital_write_port1
	mov	R0, #0x2
	call	write_bit_port
	ret
digital_write_port1:
	mov	A, #7
	clr	C
	subb	A, R0
	jnc	digital_write_port0
	mov	R0, #0x1
	call	write_bit_port
	ret
digital_write_port0:
	mov	R0, #0x0
	call	write_bit_port
	ret

;*********************************************************************
;void pinMode(char pin, char mode)
pin_mode:
	cjne	R1,  #OUTPUT, $+5
	call	digital_Write
	ret

;*********************************************************************
;char digitalRead(char pin)
digital_read:
	mov	A, #0x07
	anl	A, R0
	mov	R1, A
	mov	A, #23
	clr	C
	subb	A, R0
	jnc	digital_read_port2
	mov	R0, P3
	call	read_bit
	ret
digital_read_port2:
	mov	A, #15
	clr	C
	subb	A, R0
	jnc	digital_read_port1
	mov	R0, P2
	call	read_bit
	ret
digital_read_port1:
	mov	A, #7
	clr	C
	subb	A, R0
	jnc	digital_read_port0
	mov	R0, P1
	call	read_bit
	ret
digital_read_port0:
	mov	R0, P0
	call	read_bit
	ret

;*********************************************************************
;*********************************************************************
;void write_bit( char Port, char Bit, char Value)
write_bit_port:
	dec	R2
	mov	A, R2
	jz	write_bit_set_port
	jmp	write_bit_clear_port
write_bit_set_port:
	cjne	R0,  #3, write_bit_set_port2
;write_bit_set_port3:
; PORT3   ************************************************************
	cjne	R1,  #0, write_bit_set_port3_bit1
	setb	P3.0
	ret
write_bit_set_port3_bit1:
	cjne	R1,  #1, write_bit_set_port3_bit2
	setb	P3.1
	ret
write_bit_set_port3_bit2:
	cjne	R1,  #2, write_bit_set_port3_bit3
	setb	P3.2
	ret
write_bit_set_port3_bit3:
	cjne	R1,  #3, write_bit_set_port3_bit4
	setb	P3.3
	ret
write_bit_set_port3_bit4:
	cjne	R1,  #4, write_bit_set_port3_bit5
	setb	P3.4
	ret
write_bit_set_port3_bit5:
	cjne	R1,  #5, write_bit_set_port3_bit6
	setb	P3.5
	ret
write_bit_set_port3_bit6:
	cjne	R1,  #6, write_bit_set_port3_bit7
	setb	P3.6
	ret
write_bit_set_port3_bit7:
	setb	P3.7
	ret
; PORT2   ************************************************************
write_bit_set_port2:
	cjne	R0,  #2, write_bit_set_port1
	cjne	R1,  #0, write_bit_set_port2_bit1
	setb	P2.0
	ret
write_bit_set_port2_bit1:
	cjne	R1,  #1, write_bit_set_port2_bit2
	setb	P2.1
	ret
write_bit_set_port2_bit2:
	cjne	R1,  #2, write_bit_set_port2_bit3
	setb	P2.2
	ret
write_bit_set_port2_bit3:
	cjne	R1,  #3, write_bit_set_port2_bit4
	setb	P2.3
	ret
write_bit_set_port2_bit4:
	cjne	R1,  #4, write_bit_set_port2_bit5
	setb	P2.4
	ret
write_bit_set_port2_bit5:
	cjne	R1,  #5, write_bit_set_port2_bit6
	setb	P2.5
	ret
write_bit_set_port2_bit6:
	cjne	R1,  #6, write_bit_set_port2_bit7
	setb	P2.6
	ret
write_bit_set_port2_bit7:
	setb	P2.7
	ret
; PORT1   ************************************************************
write_bit_set_port1:
	cjne	R0,  #1, write_bit_set_port0
	cjne	R1,  #0, write_bit_set_port1_bit1
	setb	P1.0
	ret
write_bit_set_port1_bit1:
	cjne	R1,  #1, write_bit_set_port1_bit2
	setb	P1.1
	ret
write_bit_set_port1_bit2:
	cjne	R1,  #2, write_bit_set_port1_bit3
	setb	P1.2
	ret
write_bit_set_port1_bit3:
	cjne	R1,  #3, write_bit_set_port1_bit4
	setb	P1.3
	ret
write_bit_set_port1_bit4:
	cjne	R1,  #4, write_bit_set_port1_bit5
	setb	P1.4
	ret
write_bit_set_port1_bit5:
	cjne	R1,  #5, write_bit_set_port1_bit6
	setb	P1.5
	ret
write_bit_set_port1_bit6:
	cjne	R1,  #6, write_bit_set_port1_bit7
	setb	P1.6
	ret
write_bit_set_port1_bit7:
	setb	P1.7
	ret
; PORT0   ************************************************************
write_bit_set_port0:
	cjne	R1,  #0, write_bit_set_port0_bit1
	setb	P0.0
	ret
write_bit_set_port0_bit1:
	cjne	R1,  #1, write_bit_set_port0_bit2
	setb	P0.1
	ret
write_bit_set_port0_bit2:
	cjne	R1,  #2, write_bit_set_port0_bit3
	setb	P0.2
	ret
write_bit_set_port0_bit3:
	cjne	R1,  #3, write_bit_set_port0_bit4
	setb	P0.3
	ret
write_bit_set_port0_bit4:
	cjne	R1,  #4, write_bit_set_port0_bit5
	setb	P0.4
	ret
write_bit_set_port0_bit5:
	cjne	R1,  #5, write_bit_set_port0_bit6
	setb	P0.5
	ret
write_bit_set_port0_bit6:
	cjne	R1,  #6, write_bit_set_port0_bit7
	setb	P0.6
	ret
write_bit_set_port0_bit7:
	setb	P0.7
	ret

;clear bit port***************************************************
write_bit_clear_port:
	cjne	R0,  #3, write_bit_clear_port2
;write_bit_clear_port3:
; PORT3   ************************************************************
	cjne	R1,  #0, write_bit_clear_port3_bit1
	clr	P3.0
	ret
write_bit_clear_port3_bit1:
	cjne	R1,  #1, write_bit_clear_port3_bit2
	clr	P3.1
	ret
write_bit_clear_port3_bit2:
	cjne	R1,  #2, write_bit_clear_port3_bit3
	clr	P3.2
	ret
write_bit_clear_port3_bit3:
	cjne	R1,  #3, write_bit_clear_port3_bit4
	clr	P3.3
	ret
write_bit_clear_port3_bit4:
	cjne	R1,  #4, write_bit_clear_port3_bit5
	clr	P3.4
	ret
write_bit_clear_port3_bit5:
	cjne	R1,  #5, write_bit_clear_port3_bit6
	clr	P3.5
	ret
write_bit_clear_port3_bit6:
	cjne	R1,  #6, write_bit_clear_port3_bit7
	clr	P3.6
	ret
write_bit_clear_port3_bit7:
	clr	P3.7
	ret
; PORT2   ************************************************************
write_bit_clear_port2:
	cjne	R0,  #2, write_bit_clear_port1
	cjne	R1,  #0, write_bit_clear_port2_bit1
	clr	P2.0
	ret
write_bit_clear_port2_bit1:
	cjne	R1,  #1, write_bit_clear_port2_bit2
	clr	P2.1
	ret
write_bit_clear_port2_bit2:
	cjne	R1,  #2, write_bit_clear_port2_bit3
	clr	P2.2
	ret
write_bit_clear_port2_bit3:
	cjne	R1,  #3, write_bit_clear_port2_bit4
	clr	P2.3
	ret
write_bit_clear_port2_bit4:
	cjne	R1,  #4, write_bit_clear_port2_bit5
	clr	P2.4
	ret
write_bit_clear_port2_bit5:
	cjne	R1,  #5, write_bit_clear_port2_bit6
	clr	P2.5
	ret
write_bit_clear_port2_bit6:
	cjne	R1,  #6, write_bit_clear_port2_bit7
	clr	P2.6
	ret
write_bit_clear_port2_bit7:
	clr	P2.7
	ret
; PORT1   ************************************************************
write_bit_clear_port1:
	cjne	R0,  #1, write_bit_clear_port0
	cjne	R1,  #0, write_bit_clear_port1_bit1
	clr	P1.0
	ret
write_bit_clear_port1_bit1:
	cjne	R1,  #1, write_bit_clear_port1_bit2
	clr	P1.1
	ret
write_bit_clear_port1_bit2:
	cjne	R1,  #2, write_bit_clear_port1_bit3
	clr	P1.2
	ret
write_bit_clear_port1_bit3:
	cjne	R1,  #3, write_bit_clear_port1_bit4
	clr	P1.3
	ret
write_bit_clear_port1_bit4:
	cjne	R1,  #4, write_bit_clear_port1_bit5
	clr	P1.4
	ret
write_bit_clear_port1_bit5:
	cjne	R1,  #5, write_bit_clear_port1_bit6
	clr	P1.5
	ret
write_bit_clear_port1_bit6:
	cjne	R1,  #6, write_bit_clear_port1_bit7
	clr	P1.6
	ret
write_bit_clear_port1_bit7:
	clr	P1.7
	ret
; PORT0   ************************************************************
write_bit_clear_port0:
	cjne	R1,  #0, write_bit_clear_port0_bit1
	clr	P0.0
	ret
write_bit_clear_port0_bit1:
	cjne	R1,  #1, write_bit_clear_port0_bit2
	clr	P0.1
	ret
write_bit_clear_port0_bit2:
	cjne	R1,  #2, write_bit_clear_port0_bit3
	clr	P0.2
	ret
write_bit_clear_port0_bit3:
	cjne	R1,  #3, write_bit_clear_port0_bit4
	clr	P0.3
	ret
write_bit_clear_port0_bit4:
	cjne	R1,  #4, write_bit_clear_port0_bit5
	clr	P0.4
	ret
write_bit_clear_port0_bit5:
	cjne	R1,  #5, write_bit_clear_port0_bit6
	clr	P0.5
	ret
write_bit_clear_port0_bit6:
	cjne	R1,  #6, write_bit_clear_port0_bit7
	clr	P0.6
	ret
write_bit_clear_port0_bit7:
	clr	P0.7
	ret

;*********************************************************************
;void write_bit( char byte, char Bit, char value)
write_bit:
	mov	A, #0x80
	rl	A
	dec	R1
	cjne	R1, #0xff, $-2
	orl	reg0, A
	cjne	R2, #0, $+6
	cpl	A
	anl	reg0, A
	ret

;*********************************************************************
;char read_bit( char byte, char Bit)
read_bit:
	mov	A, R0
	rl	A
	rr	A
	dec	R1
	cjne	R1, #0xff, $-2
	anl	A, #1
	mov	R0, A
	ret

;	END