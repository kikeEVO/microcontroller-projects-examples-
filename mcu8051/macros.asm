;*********************************************************************
pushData	macro	sreg
		inc	DPTR
		mov	A, sreg
		movx	@DPTR, A
		endm
;*********************************************************************
popData		macro	sreg
		movx	A, @DPTR
		mov	sreg, A
		mov	A, DPL
		add	A, #0xFF
		mov	DPL, A
		mov	A, DPH
		addc	A, #0xFF
		mov	DPH, A
		endm
;*********************************************************************
addDPTR		macro	value
		mov	A, DPL
		add	A, # LOW (value)
		mov	DPL, A
		mov	A, DPH
		addc	A, # HIGH (value AND 0xff00)
		mov	DPH, A
		endm
;*********************************************************************
inc16		macro	sreg
		mov	A, sreg
		add	A, #1
		mov	sreg, A
		mov	A, sreg +1
		addc	A, #0
		mov	sreg +1, A
		endm
;*********************************************************************
setBite		macro	reg, bite
		orl	reg, # 1 SHL bite
		endm

;*********************************************************************
clrBite		macro	reg, bite
IF bite EQ 0
		anl	reg, #0xfe
ELSEIF bite EQ 1
		anl	reg, #0xfd
ELSEIF bite EQ 2
		anl	reg, #0xfb
ELSEIF bite EQ 3
		anl	reg, #0xf7
ELSEIF bite EQ 4
		anl	reg, #0xef
ELSEIF bite EQ 5
		anl	reg, #0xdf
ELSEIF bite EQ 6
		anl	reg, #0xbf
ELSEIF bite EQ 7
		anl	reg, #0x7f
ENDIF
		endm