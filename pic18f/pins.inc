PIN1	.set	0x11
PIN2	.set	0x12
PIN3	.set	0x13
PIN4	.set	0x14
PIN5	.set	0x15
PIN6	.set	0x16
PIN7	.set	0x17
PIN8	.set	0x18
PIN9	.set	0x21
PIN10	.set	0x22
PIN11	.set	0x23
PIN12 	.set	0x24
PIN13	.set	0x25
PIN14	.set	0x26
PIN15	.set	0x27
PIN16	.set	0x28
PIN17 	.set	0x31
PIN18	.set	0x32
PIN19	.set	0x33
PIN20	.set	0x34
PIN21	.set	0x35
PIN22	.set	0x36
PIN23	.set	0x37
PIN24	.set	0x38
PIN25	.set	0x41
PIN26	.set	0x42
PIN27	.set	0x43
PIN28	.set	0x44
PIN29	.set	0x45
PIN30	.set	0x46
PIN31	.set	0x47
PIN32	.set	0x48
PIN33	.set	0x51
PIN34	.set	0x52
PIN35	.set	0x53
PIN36	.set	0x54

PORT1	.set	0
PORT2	.set	1
PORT3	.set	2
PORT4	.set	3
PORT5	.set	4

OUTPUT	.set	0
INPUT	.set	1

ONE	.set	1
ZERO	.set	0

TRUE	.set	1
FALSE	.set	0

;============================================================================
; pins macros
;============================================================================

;*********************************************************************
;void digitalWrite(char pin, char Value)
digitalWrite	MACRO	pin, value
	movlf	value, R1
	movlf	pin, R0
	call	digital_write
	ENDM

;*********************************************************************
;void pinMode(char pin, char mode)
pinMode	MACRO	pin, mode
	movlf	mode, R1
	movlf	pin, R0
	call	pin_mode
	ENDM

;*********************************************************************
;char digitalRead(char pin)
digitalRead MACRO	pin
	movlf	pin, R0
	call	digital_read
	ENDM


;============================================================================
; pins routines
;============================================================================

;*********************************************************************
;void digital_write(char pin, char Value)
digital_write:
	pushd16	FSR0L
	setf	FSR0H
	swapf	R0, w
	andlw	0x0f
	addlw	0x82
	movwf	FSR0L
	movlw	0x0f
	andwf	R0, f
	movlw	0x80
digital_write_loop:
	rlncf	WREG
	decfsz	R0, f
	bra	digital_write_loop
	tstfsz	R1
	iorwf	INDF0, f
	comf	WREG
	movf	R1, f
	btfsc	STATUS, Z
	andwf	INDF0, f
	popd16	FSR0L
	return	
	
;*********************************************************************
;void pin_mode(char pin, char mode)
pin_mode:
	pushd16	FSR0L
	setf	FSR0H
	swapf	R0, w
	andlw	0x0f
	addlw	0x87
	movwf	FSR0L
	movlw	0x0f
	andwf	R0, f
	movlw	0x80
pin_mode_loop:
	rlncf	WREG
	decfsz	R0, f
	bra	pin_mode_loop
	tstfsz	R1
	iorwf	INDF0, f
	comf	WREG
	movf	R1, f
	btfsc	STATUS, Z
	andwf	INDF0, f
	popd16	FSR0L
	return	
	
;*********************************************************************
;char digital_read(char pin)
digital_read:
	pushd16	FSR0L
	setf	FSR0H
	swapf	R0, w
	andlw	0x0f
	addlw	0x8c
	movwf	FSR0L
	movlw	0x0f
	andwf	R0, f
	movlw	0x80
digital_read_loop:
	rlncf	WREG
	decfsz	R0, f
	bra	digital_read_loop
	clrf	R0
	cpfseq	INDF0
	incf	R0, f
	popd16	FSR0L
	return