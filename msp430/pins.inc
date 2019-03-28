PIN1	.set	1
PIN2	.set	2
PIN3	.set	3
PIN4	.set	4
PIN5	.set	5
PIN6	.set	6
PIN7	.set	7
PIN8	.set	8
PIN9	.set	9
PIN10	.set	10
PIN11	.set	11
PIN12 	.set	12
PIN13	.set	13
PIN14	.set	14
PIN15	.set	15
PIN16	.set	16
PIN17 	.set	17
PIN18	.set	18
PIN19	.set	19
PIN20	.set	20
PIN21	.set	21
PIN22	.set	22
PIN23	.set	23
PIN24	.set	24
PIN25	.set	25
PIN26	.set	26
PIN27	.set	27
PIN28	.set	28
PIN29	.set	29
PIN30	.set	30
PIN31	.set	31
PIN32	.set	32
PIN33	.set	33
PIN34	.set	34
PIN35	.set	35
PIN36	.set	36
PIN37	.set	37
PIN38	.set	38
PIN39	.set	39
PIN40	.set	40
PIN41	.set	41
PIN42	.set	42
PIN43	.set	43
PIN44	.set	44

PORT1	.set	1
PORT2	.set	2
PORT3	.set	3
PORT4	.set	4
PORT5	.set	5
PORT6	.set	6
PORT7	.set	7
PORT8	.set	8

OUTPUT	.set	1
INPUT	.set	0

HIGH	.set	1
LOW		.set	0

TRUE	.set	1
FALSE	.set	0

;============================================================================
; pins macros
;============================================================================

;*********************************************************************
;void digitalWrite(char pin, char Value)
digitalWrite	.macro	pin, value
				mov.b	value, R13
				mov.b	pin, R12
				calla	#digital_write
				.endm

;*********************************************************************
;void pinMode(char pin, char mode)
pinMode			.macro	pin, mode
				mov.b	mode, R13
				mov.b	pin, R12
				calla	#pin_mode
				.endm

;*********************************************************************
;char digitalRead(char pin)
digitalRead		.macro	pin
				mov.b	pin, R12
				calla	#digital_read
				.endm


;============================================================================
; pins routines
;============================================================================

;*********************************************************************
;void digital_write(char pin, char Value)
digital_write:
		rla		R12
		adda	#pins_value, R12
		mov		@R12, R12
		tst		R12
		jz		digital_write_end
		mov		R12, R14
		and		#0xff, R14
		swpb	R12
		and		#0x0f, R12
		adda	#pins_base, R12
		mov		@R12, R12
		tst.b	R13
		jnz		digital_write_set
		bic.b	R14, 2(R12)
		reta
digital_write_set:
		bis.b	R14, 2(R12)
digital_write_end:
		reta

;*********************************************************************
;char digital_read(char pin)
digital_read:
		rla		R12
		adda	#pins_value, R12
		mov		@R12, R12
		tst		R12
		jz		digital_write_end
		mov		R12, R13
		and		#0xff, R13
		swpb	R12
		and		#0x0f, R12
		adda	#pins_base, R12
		mov		@R12, R12
		bit.b	R13, 0(R12)
		jz		digital_read_zero
		mov.b	#TRUE, R12
		reta
digital_read_zero:
		mov.b	#FALSE, R12
		reta

;*********************************************************************
;void pin_mode(char pin, char mode)
pin_mode:
		rla		R12
		adda	#pins_value, R12
		mov		@R12, R12
		tst		R12
		jz		digital_write_end
		mov		R12, R14
		and		#0xff, R14
		swpb	R12
		and		#0x0f, R12
		adda	#pins_base, R12
		mov		@R12, R12
		tst.b	R13
		jnz		pin_mode_set
		bic.b	R14, 4(R12)
		jmp		pin_mode_gpio_set
pin_mode_set:
		bis.b	R14, 4(R12)
pin_mode_gpio_set:
		bic.b	R14, 6(R12)
		bic.b	R14, 8(R12)
		bic.b	R14, 10(R12)
pin_mode_end:
		reta

;============================================================================
; pins constands
;============================================================================

pins_value	.word	0x000
			.word	0x000,0x004,0xa02,0xa01,0xa04,0x008,0x804,0xa08,0xc02,0xc01
			.word	0xe02,0xe04,0xe08,0x802,0x801,0x000,0x808,0x610,0x880,0x000
			.word	0x000,0x000,0x401,0x402,0x404,0x408,0x010,0x020,0x680,0xe01
			.word	0x602,0x604,0x608,0x220,0x240,0xc08,0x410,0x420,0x440,0x480
			.word	0x001,0x002,0x840,0x820

pins_base	.word	0x200,0x201,0x220,0x221,0x240,0x241,0x260,0x261

