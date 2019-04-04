;*********************************************************************
;uint16 divide_uint32(uint16 num, uint16 den)
divide_uint16:
	movlw	.16
	movwf	R6
	clrf	R4
	clrf	R5
divide_uint16_loop:
	bcf	STATUS, C
	rlcf	R0, f
	rlcf	R1, f
	rlcf	R4, f
	rlcf	R5, f
	movf	R2, w
	subwf	R4, w
	movf	R3, w
	subwfb	R5, w
	bnc	divide_uint16_src_des
	movf	R2, w
	subwf	R4, f
	movf	R3, w
	subwfb	R5, f
	incf	R0, f
divide_uint16_src_des:
	decf	R6, f
	bnz	divide_uint16_loop
	movff	R4, R2
	movff	R5, R3
	return

;*********************************************************************
;uint32 multiply_uint16(uint16 ope1, uint16 ope2)
multiply_uint16:
	movlw	.16
	movwf	R8
	clrf	R4
	clrf	R5
	clrf	R6
	clrf	R7
multiply_uint16_loop:
	bcf	STATUS, C
	rlcf	R4
	rlcf	R5
	rlcf	R6
	rlcf	R7
	rlcf	R0, f
	rlcf	R1, f
	bnc	multiply_uint16_no_bit
	movf	R2, w
	addwf	R4, f
	movf	R3, w
	addwfc	R5, f
	movlw	0
	addwfc	R6, f
	addwfc	R7, f
multiply_uint16_no_bit:
	decf	R8, f
	bnz	multiply_uint16_loop
	movff	R4, R0
	movff	R5, R1
	movff	R6, R2
	movff	R7, R3
	return

;*********************************************************************
;uint32 divide_uint32(uint32 num, uint32 den)
divide_uint32:
	movlw	.32
	movwf	R12
	clrf	R4
	clrf	R5
	clrf	R6
	clrf	R7
	movsf	[1], R8
	movsf	[2], R9
	movsf	[3], R10
	movsf	[4], R11
divide_uint32_loop:
	bcf	STATUS, C
	rlcf	R0, f
	rlcf	R1, f
	rlcf	R2, f
	rlcf	R3, f
	rlcf	R4, f
	rlcf	R5, f
	rlcf	R6, f
	rlcf	R7, f
	movf	R8, w
	subwf	R4, w
	movf	R9, w
	subwfb	R5, w
	movf	R10, w
	subwfb	R6, w
	movf	R11, w
	subwfb	R7, w
	bnc	divide_uint32_src_des
	movf	R8, w
	subwf	R4, f
	movf	R9, w
	subwfb	R5, f
	movf	R10, w
	subwfb	R6, f
	movf	R11, w
	subwfb	R7, f
	incf	R0, f
divide_uint32_src_des:
	decf	R12,f
	bnz	divide_uint32_loop
	return


;*********************************************************************
;uint32 multiply_uint16(uint32 ope1, uint32 ope2)
multiply_uint32:

	return