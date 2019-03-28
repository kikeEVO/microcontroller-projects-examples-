;*********************************************************************
;*********************************************************************
LCD_P4	.set	PIN11
LCD_P5	.set	PIN12
LCD_P6	.set	PIN13
LCD_P7	.set	PIN14
LCD_RS	.set	PIN17
LCD_E	.set	PIN18

;============================================================================
; lcd macros
;============================================================================

;*********************************************************************
;void lcdBegin(void)
lcdBegin	.macro
			calla	#init_lcd
			.endm

;*********************************************************************
;void lcdCommand(char command)
lcdCommand	.macro	command
			mov		command, R12
			calla	#lcd_command
			.endm

;*********************************************************************
;void lcdWrite(char data_lcd)
lcdWrite	.macro	data_lcd
			mov.b	data_lcd, R12
			calla	#lcd_write
			.endm

;*********************************************************************
;void lcdCursor(int index_x, int index_y)
lcdCursor	.macro	index_x, index_y
			mov		index_x, R12
			mov		index_y, R13
			calla	#lcd_cursor
			.endm

;*********************************************************************
;void lcdWrite_string(char* data_lcd)
lcdWrite_string	.macro	string
			mova	string, R12
			calla	#lcd_write_string
			.endm

;*********************************************************************
lcd_put_4bits	.macro	four_bits
			mov		four_bits, R13
			and.b	#BIT4, R13
			mov		#LCD_P4, R12
			calla	#digital_write
			mov		four_bits, R13
			and.b	#BIT5, R13
			mov		#LCD_P5, R12
			calla	#digital_write
			mov		four_bits, R13
			and.b	#BIT6, R13
			mov		#LCD_P6, R12
			calla	#digital_write
			mov		four_bits, R13
			and.b	#BIT7, R13
			mov		#LCD_P7, R12
			calla	#digital_write
			digitalWrite	#LCD_E, #HIGH
			delayMicrosecons 1
			digitalWrite	#LCD_E, #LOW
			delayMicrosecons 10
			.endm

;============================================================================
; delays rutines
;============================================================================

;*********************************************************************
;void init_lcd(void)
init_lcd:
		delay	40
		pinMode	#LCD_E, #OUTPUT
		pinMode	#LCD_RS, #OUTPUT
		pinMode	#LCD_P4, #OUTPUT
		pinMode	#LCD_P5, #OUTPUT
		pinMode	#LCD_P6, #OUTPUT
		pinMode	#LCD_P7, #OUTPUT
		digitalWrite	#LCD_E, #LOW
		digitalWrite	#LCD_RS, #LOW

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
		reta

;*********************************************************************
;void lcd_command(char command)
lcd_command:
		mov		R12, R15
		digitalWrite	#LCD_RS, #LOW
		lcd_put_4bits R15
		rlam	#4, R15
		lcd_put_4bits R15
		reta

;*********************************************************************
;void lcd_write(char data)
lcd_write:
		mov		R12, R15
		digitalWrite	#LCD_RS, #HIGH
		lcd_put_4bits R15
		rlam	#4, R15
		lcd_put_4bits R15
		reta

;*********************************************************************
;void lcd_cursor(int x, int y)
lcd_cursor:
		and.b	#0x0f, R12
		swpb	R13
		rram	#2, R13
		and.b	#0x40, R13
		add.b	R13, R12
		add.b	#0x80, R12
		calla	#lcd_command
		reta

;*********************************************************************
;void lcd_write_string(char* string)
lcd_write_string:
		mova	R12, R11
lcd_write_string_loop:
		mov.b	@R11+, R12
		tst.b	R12
		jz		lcd_write_string_end
		calla	#lcd_write
		jmp		lcd_write_string_loop
lcd_write_string_end:
		reta
