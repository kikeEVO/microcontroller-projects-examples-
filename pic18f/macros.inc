;============================================================================
; macros
;============================================================================

pushd	MACRO	reg
	movff	reg, POSTDEC2
	ENDM

popd	MACRO	reg
	movff	PREINC2, reg
	ENDM
	
pushd16	MACRO	reg
	movff	reg+1, POSTDEC2
	movff	reg, POSTDEC2
	ENDM

popd16	MACRO	reg
	movff	PREINC2, reg
	movff	PREINC2, reg+1
	ENDM

pushd32	MACRO	reg
	movff	reg+3, POSTDEC2
	movff	reg+2, POSTDEC2
	movff	reg+1, POSTDEC2
	movff	reg, POSTDEC2
	ENDM

popd32	MACRO	reg
	movff	PREINC2, reg
	movff	PREINC2, reg+1
	movff	PREINC2, reg+2
	movff	PREINC2, reg+3
	ENDM

movff16	MACRO	src, dst
	movff	src+1, dst+1
	movff	src, dst
	ENDM	
	
movff32	MACRO	src, dst
	movff	src+3, dst+3
	movff	src+2, dst+2
	movff	src+1, dst+1
	movff	src, dst
	ENDM
	
movlf	MACRO	imm, reg
	movlw	imm
	movwf	reg
	ENDM
	
movlf16	MACRO	imm, reg
	movlw	high imm
	movwf	reg+1
	movlw	low imm
	movwf	reg
	ENDM
	
movlf32	MACRO	imm, reg
	movlw	low imm
	movwf	reg
	movlw	high imm
	movwf	reg+1
	movlw	low (imm>>16)
	movwf	reg+2
	movlw	high (imm>>16)
	movwf	reg+3
	ENDM
	
addlf	MACRO	imm, reg
	movlw	imm
	addwf	reg, f
	ENDM
	
addlfc	MACRO	imm, reg
	movlw	imm
	addwfc	reg, f
	ENDM
	
addlf16	MACRO	imm, reg
	movlw	low imm
	addwf	reg, f
	movlw	high imm
	addwfc	reg+1, f
	ENDM
	
addlf32	MACRO	imm, reg
	movlw	low imm
	addwf	reg, f
	movlw	high imm
	addwfc	reg+1, f
	movlw	low (imm>>16)
	addwfc	reg+2, f
	movlw	high (imm>>16)
	addwfc	reg+3, f
	ENDM
	
incf16	MACRO	reg
	incf	reg, f
	movlw	0
	addwfc	reg+1, f
	ENDM
	
incf32	MACRO	reg
	incf	reg, f
	movlw	0
	addwfc	reg+1, f
	addwfc	reg+2, f
	addwfc	reg+3, f
	ENDM
	
sublf16	MACRO	imm, reg
	movlw	low imm
	subwf	reg, f
	movlw	high imm
	subwfb	reg+1, f
	ENDM
	
sublf32	MACRO	imm, reg
	movlw	low imm
	subwf	reg, f
	movlw	high imm
	subwfb	reg+1, f
	movlw	low (imm>>16)
	subwfb	reg+2, f
	movlw	high (imm>>16)
	subwfb	reg+3, f
	ENDM
	
decf16	MACRO	reg
	decf	reg, f
	movlw	0
	subwfb	reg+1, f
	ENDM
	
decf32	MACRO	reg
	decf	reg, f
	movlw	0
	subwfb	reg+1, f
	subwfb	reg+2, f
	subwfb	reg+3, f
	ENDM