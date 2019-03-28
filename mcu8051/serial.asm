SerialBegin	macro
		call	serial_port_init
		endm

SerialWrite_byte	macro	character
		mov	reg0, character
		call	serial_port_send
		endm
SerialWrite_string	macro	string
		mov	R0, # LOW string
		mov	R1, # HIGH string
		call	serial_port_send_data_string
		endm
SerialWrite_const_string macro	string
		mov	R0, # LOW string
		mov	R1, # HIGH string
		call	serial_port_send_code_string
		endm

serial_bauds	EQU	256-(2*4000000/(384*9600))
;*********************************************************************
;void serial_port_init(void)
serial_port_init:
	mov	SCON, #0x40
	orl	PCON, #0x80
	mov	TH1, #serial_bauds
	orl	TMOD, #0x20
	orl	TCON, #0x40
	setb	TI
	ret

;*********************************************************************
;void serial_port_send(char byte)
serial_port_send:
	mov	C, TI
	jnc	$-2
	mov	SBUF, R0
	clr	TI
	ret

;void serial_port_send_code_string(const char* string)
serial_port_send_code_string:
	push	DPL
	push	DPH
	mov	DPL, R0
	mov	DPH, R1
	clr	A
	movc	A, @A+DPTR
	jz	$+13
	mov	C, TI
	jnc	$-2
	mov	SBUF, A
	clr	TI
	inc	DPTR
	ajmp	$-13
	pop	DPH
	pop	DPL
	ret

;*********************************************************************
;void serial_port_send_data_string(char* string)
serial_port_send_data_string:
	push	DPL
	push	DPH
	mov	DPL, R0
	mov	DPH, R1
	movx	A, @DPTR
	jz	$+13
	mov	C, TI
	jnc	$-2
	mov	SBUF, A
	clr	TI
	inc	DPTR
	sjmp	$-12
	pop	DPH
	pop	DPL
	ret