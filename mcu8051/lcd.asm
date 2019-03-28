;*********************************************************************
;*********************************************************************
LCD_P4   EQU	PIN1_3
LCD_P5   EQU	PIN1_2
LCD_P6   EQU	PIN1_1
LCD_P7   EQU	PIN1_0
LCD_RS   EQU	PIN1_4
LCD_E	 EQU	PIN1_5

;*********************************************************************
;void lcdBegin(void)
lcdBegin	macro
		call	init_lcd
		endm

;*********************************************************************
;void lcdCommand(char command)
lcdCommand	macro	command
		mov	R0, command
		call	lcd_command
		endm
;*********************************************************************
;void lcdData(char data_lcd)
lcdWrite	macro	data_lcd
		mov	R0, data_lcd
		call	lcd_write
		endm
;*********************************************************************
;void lcdCursor(char index_x, char index_y)
lcdCursor	macro	index_x, index_y
		mov	R0, index_x
		mov	R1, index_y
		call	lcd_cursor
		endm
;*********************************************************************
;void lcdData_string(char data_lcd)
lcdWrite_string	macro	string
		mov	R0, # LOW string
		mov	R1, # HIGH string
		call	lcd_write_data_string
		endm
		;*********************************************************************
;void lcdData_string(char data_lcd)
lcdWrite_const_string	macro	string
		mov	R0, # LOW string
		mov	R1, # HIGH string
		call	lcd_write_code_string
		endm
		;*********************************************************************
lcd_enable	macro
		digitalWrite	#LCD_E, #ONE
		delayMicrosecons #1
		digitalWrite	#LCD_E, #ZERO
		delayMicrosecons #1
		endm

lcd_put_4bits	macro	four_bits
		mov	R0, four_bits
		mov	R1, #4
		call	read_bit
		mov	R1, reg0
		mov	R0, #LCD_P4
		call	digital_Write
		mov	R0, four_bits
		mov	R1, #5
		call	read_bit
		mov	R1, reg0
		mov	R0, #LCD_P5
		call	digital_Write
		mov	R0, four_bits
		mov	R1, #6
		call	read_bit
		mov	R1, reg0
		mov	R0, #LCD_P6
		call	digital_Write
		mov	R0, four_bits
		mov	R1, #7
		call	read_bit
		mov	R1, reg0
		mov	R0, #LCD_P7
		call	digital_Write
		lcd_enable
		endm
;*********************************************************************
;void init_lcd(void)
init_lcd:
	delay	40
	digitalWrite	#LCD_E, #ZERO
	digitalWrite	#LCD_RS, #ZERO

	lcd_put_4bits #0x30
	delay	10
	lcd_put_4bits #0x30
	delay	10
	lcd_put_4bits #0x30
	delay	10
	lcd_put_4bits #0x20
	delay	10

	lcdCommand #0x28
	delay	10
	lcdCommand #0x0f
	delay	10
	lcdCommand #0x01
	delay	10
	lcdCommand #0x06
	ret

;*********************************************************************
;void lcd_command(char command)
lcd_command:

	mov	R4, reg0
	digitalWrite	#LCD_RS, #ZERO
	lcd_put_4bits reg4
	mov	A, reg4
	swap	A
	mov	R4, A
	lcd_put_4bits reg4

	ret

;*********************************************************************
;void lcd_data(char data)
lcd_write:
	mov	R4, reg0
	digitalWrite	#LCD_RS, #ONE
	lcd_put_4bits reg4
	mov	A, reg4
	swap	A
	mov	R4, A
	lcd_put_4bits reg4
	ret

;*********************************************************************
;void lcd_write_code_string(const char* string)
lcd_write_code_string:
	push	DPL
	push	DPH
	mov	DPL, R0
	mov	DPH, R1
	mov	A, #0
	movc	A, @A+DPTR
	jz	$+8
	mov	R0, A
	acall	lcd_write
	inc	DPTR
	ajmp	$-9
	pop	DPH
	pop	DPL
	ret

;*********************************************************************
;void lcd_write_code_string(char* string)
lcd_write_data_string:
	push	DPL
	push	DPH
	mov	DPL, R0
	mov	DPH, R1
	movx	A, @DPTR
	jz	$+8
	mov	R0, A
	acall	lcd_write
	inc	DPTR
	ajmp	$-7
	pop	DPH
	pop	DPL
	ret



;*********************************************************************
;void lcd_cursor(int x, int y)
lcd_cursor:
	mov	A, #15
	subb	A, R0
	jnc	$+4
	mov	R0, #0x15
	mov	A, #0
	cjne	R1, #1, $+5
	mov	A, #0x40
	add	A, #0x80
	add	A, R0
	mov	R0, A
	lcall	lcd_command
	ret

;	END