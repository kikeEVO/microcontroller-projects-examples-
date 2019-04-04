;*********************************************************************
;*********************************************************************
LCD_P4	EQU	PIN9
LCD_P5	EQU	PIN10
LCD_P6	EQU	PIN11
LCD_P7	EQU	PIN12
LCD_RS	EQU	PIN13
LCD_E	EQU	PIN14

;============================================================================
; lcd macros
;============================================================================

;*********************************************************************
;void lcdBegin(void)
lcdBegin    MACRO
	call	init_lcd
	ENDM

;*********************************************************************
;void lcdCommand(char command)
lcdCommand  MACRO   command
	movlw	command
	movwf	R0
	call	lcd_command
	ENDM

;*********************************************************************
;void lcdWrite(char data_lcd)
lcdWrite    MACRO   data_lcd
	movlw	data_lcd
	movwf	R0
	call	lcd_write
	ENDM

;*********************************************************************
;void lcdCursor(int index_x, int index_y)
lcdCursor   MACRO   index_x, index_y
	movlw	index_y
	movwf	R1
	movlw	index_x
	movwf	R0
	call	lcd_cursor
	ENDM

;*********************************************************************
;void lcdWrite_string(char* data_lcd)
lcdWrite_string	MACRO	string
	movlw	high string
	movwf	R1
	movlw	low string
	movwf	R0
	call	lcd_write_string_const
	ENDM

;============================================================================
; delays rutines
;============================================================================

;*********************************************************************
;void init_lcd(void)
init_lcd:
	pinMode	LCD_E, OUTPUT
	pinMode	LCD_RS, OUTPUT
	pinMode	LCD_P4, OUTPUT
	pinMode	LCD_P5, OUTPUT
	pinMode	LCD_P6, OUTPUT
	pinMode	LCD_P7, OUTPUT
	digitalWrite	LCD_E, ZERO
	digitalWrite	LCD_RS, ZERO
	
	delay	.50
	movlf	0x30, R2
	rcall	lcd_put_4bits
	delay	.40
	rcall	lcd_put_4bits
	delay	.40
	rcall	lcd_put_4bits
	delay	.40
	movlf	0x20, R2
	rcall	lcd_put_4bits

	delay	.10
	movlf	0x28, R0
	rcall	lcd_command
	delay	.10
	movlf	0x0f, R0
	rcall	lcd_command
	delay	.10
	movlf	0x01, R0
	rcall	lcd_command
	delay	.10
	movlf	0x06, R0
	rcall	lcd_command
	return

;*********************************************************************
;void lcd_command(char command)
lcd_command:
	movff	R0, R2
	digitalWrite	LCD_RS, ZERO
	rcall	lcd_put_4bits
	swapf	R2, f
	rcall	lcd_put_4bits
	return

;*********************************************************************
;void lcd_write(char data)
lcd_write:
	movff	R0, R2
	digitalWrite	LCD_RS, ONE
	rcall	lcd_put_4bits
	swapf	R2, f
	rcall	lcd_put_4bits
	return

;*********************************************************************
;void lcd_cursor(int x, int y)
lcd_cursor:
	movlw	0x0f
	andwf	R0, w
	tstfsz	R1
	addlw	0x40
	addlw	0x80
	movwf	R0
	rcall	lcd_command
	return

;*********************************************************************
;void lcd_write_string(char* string)
;lcd_write_string:
;	movff	R1, FSR0H
;	movff	R0, FSR0L
;lcd_write_string_loop:
;	movf	POSTINC0, w
;	bz	lcd_write_string_end
;	movwf	R0
;	rcall	lcd_write
;	bra	lcd_write_string_loop
;lcd_write_string_end:
;	return
	
;*********************************************************************
;void lcd_write_string_const(char* string)
lcd_write_string_const:
	movff	R1, TBLPTRH
	movff	R0, TBLPTRL
lcd_write_string_const_loop:
	tblrd*+
	movf	TABLAT, w
	bz	lcd_write_string_const_end
	movwf	R0
	pushd16	TBLPTRL
	rcall	lcd_write
	popd16	TBLPTRL
	bra	lcd_write_string_const_loop
lcd_write_string_const_end:
	return
	
;*********************************************************************
lcd_put_4bits:
	movf	R2, w
	andlw	BIT4
	movwf	R1
	movlw	LCD_P4
	movwf	R0
	call	digital_write
	movf	R2, w
	andlw	BIT5
	movwf	R1
	movlw	LCD_P5
	movwf	R0
	call	digital_write
	movf	R2, w
	andlw	BIT6
	movwf	R1
	movlw	LCD_P6
	movwf	R0
	call	digital_write
	movf	R2, w
	andlw	BIT7
	movwf	R1
	movlw	LCD_P7
	movwf	R0
	call	digital_write
	movlw	LCD_E
	movwf	R0
	setf	R1
	call	digital_write
	delayMicrosecons 1
	movlw	LCD_E
	movwf	R0
	clrf	R1
	call	digital_write
	delayMicrosecons .40
	return