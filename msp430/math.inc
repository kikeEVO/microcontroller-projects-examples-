;*********************************************************************
;uint16 divide_uint32(uint16 num, uint16 den)
divide_uint16:
		mov		#16, R15
		mov		#0, R14
divide_uint16_loop:
		rla		R12
		rlc		R14
		cmp		R13, R14
		jl		divide_uint16_src_des
		sub		R13, R14
		bis		#1, R12
divide_uint16_src_des
		dec		R15
		jnz		divide_uint16_loop
		mov		R14, R13
		reta

;*********************************************************************
;uint32 multiply_uint16(uint16 ope1, uint16 ope2)
multiply_uint16:
		mov		#0, R15
		mov		R15, R10
		mov		R15, R11
multiply_uint16_loop:
		rra		R12
		jnc		divide_uint16_no_bit
		add		R13, R10
		addc	R14, R11
divide_uint16_no_bit
		rla		R13
		rlc		R14
		sub		#1, R15
		jnz		divide_uint16_loop
		mov		R10, R12
		mov		R11, R12
		ret

;*********************************************************************
;uint32 divide_uint32(uint32 num, uint32 den)
divide_uint32:
		mov		#32, R9
		mov		#0, R10
		mov		#0, R11
divide_uint32_loop:
		rla		R12
		rlc		R13
		rlc		R10
		rlc		R11
		mov		R10, R7
		mov		R11, R8
		sub		R14, R7
		subc	R15, R8
		jl		divide_uint32_src_des
		sub		R14, R10
		subc	R15, R11
		bis		#1, R12
divide_uint32_src_des
		sub		#1, R9
		jnz		divide_uint32_loop
		mov		R10, R14
		mov		R11, R15
		reta


;*********************************************************************
;uint32 multiply_uint16(uint32 ope1, uint32 ope2)
multiply_uint32:

		ret
