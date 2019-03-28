; *****************************************************************************

FREQ_M	.set	16000000
FREQ_SM	.set	5000000
FREQ_A	.set	32768

;BIT0	.set	0x0001
;BIT1	.set	0x0002
;BIT2	.set	0x0004
;BIT3	.set	0x0008
;BIT4	.set	0x0010
;BIT5	.set	0x0020
;BIT6	.set	0x0040
;BIT7	.set	0x0080
;BIT8	.set	0x0100
;BIT9	.set	0x0200
BIT10	.set	0x0400
BIT11	.set	0x0800
BIT12	.set	0x1000
BIT13	.set	0x2000
BIT14	.set	0x4000
BIT15	.set	0x8000

;============================================================================
; start_up
;============================================================================
start_up:
		; MCLK	16MHz DCO
		; ACLK  32KHz LFXT
		; SMCLLK 5MHz MODOSC
		mov		# WDTPW | WDTHOLD, &WDTCTL
		mov		# FRCTLPW | NWAITS_2, &FRCTL0
		bic		# LOCKLPM5, &PM5CTL0
		mov		# CSKEY, &CSCTL0
		mov		# DCORSEL | DCOFSEL_4, &CSCTL1
		mov		# SELA_0 | SELS_4 | SELM_3, &CSCTL2
		mov		# DIVA_0 | DIVS_0 | DIVM_0, &CSCTL3
		mov		# HFXTOFF | VLOOFF, &CSCTL4
		mov		# 0, &CSCTL5
		mov		# 0, &CSCTL6

		mov.w	# 0, &P1SEL0
		mov.w	# 0, &P1SEL1
		mov.w	# 0, &P3SEL0
		mov.w	# 0, &P3SEL1
		mov.w	# 0, &P5SEL0
		mov.w	# 0, &P5SEL1
		mov.w	# 0, &P7SEL0
		mov.w	# 0, &P7SEL1
		mov.w	# 0, &P1REN
		mov.w	# 0, &P3REN
		mov.w	# 0, &P5REN
		mov.w	# 0, &P7REN
		mov.w	# 0, &P1DIR
		mov.w	# 0, &P3DIR
		mov.w	# 0, &P5DIR
		mov.w	# 0, &P7DIR
		mov.w	# 0, &P1OUT
		mov.w	# 0, &P3OUT
		mov.w	# 0, &P5OUT
		mov.w	# 0, &P7OUT

		reta
