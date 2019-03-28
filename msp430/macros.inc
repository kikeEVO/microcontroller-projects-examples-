;============================================================================
; macros
;============================================================================

mov32		.macro	src, dst
			assembly mov.w, src, dst, 1
			assembly mov.w, src, dst, 2, 1
			.endm

inc32		.macro	dst
			add32	#1, dst
			.endm

dec32		.macro	dst
			sub32	#1, dst
			.endm

add32		.macro	src, dst
			assembly add.w, src, dst, 1
			assembly addc.w, src, dst, 2, 1
			.endm

sub32		.macro	src, dst
			assembly sub.w, src, dst, 1
			assembly subc.w, src, dst, 2, 1
			.endm

push32		.macro	dst
			assembly push.w, , dst, 1, 0
			assembly push.w, , dst, 2, 1
			.endm

pop32		.macro	dst
			assembly pop.w, , dst, 2
			assembly pop.w, , dst, 1, 0
			.endm

assembly	.macro	inst, src, dst, n, last
			.var	TMP1_B, TMP1_E, TMP2_B, TMP2_E, LEN1, LEN2, REG1, REG2
			.eval	n-1, n
			.eval	$symlen(src),LEN1
			.eval	$symlen(dst),LEN2
			.asg	:src(1):, TMP1_B
			.asg	:src(1):, TMP1_B
			.asg	:dst(1):, TMP2_B
			.asg	:src(LEN1):, TMP1_E
			.asg	:dst(LEN2):, TMP2_E

			.if ($symcmp(TMP1_B,"@") = 0)
				.if ($symcmp(TMP1_E,"+") != 0)
					.if (LEN1 < 4)
						.asg	":src(2,2):", REG1
					.else
						.asg	":src(2,3):", REG1
					.endif
					.asg	src+, src
				.endif
			.endif
			.if ($symcmp(TMP2_B,"@") = 0)
				.if ($symcmp(TMP2_E,"+") != 0)
					.if (LEN1 < 4)
						.asg	":dst(2,2):", REG2
					.else
						.asg	":dst(2,3):", REG2
					.endif
					.asg	dst+, dst
				.endif
			.endif

			.if ($isreg(dst) = 1)
				.if ($isreg(src) = 1)
					inst	src+n, dst+n
				.elseif ($symcmp(TMP1_B,"#") = 0)
					inst	src>>(n*16)&0xffff, dst+n
				.elseif ($symcmp(TMP1_B,"@") = 0)
					inst	src, dst+n
					.if ($symcmp(last,"1") = 0) & ($symcmp(TMP1_E,"+") != 0)
						suba	#(n+1)*2, REG1
					.endif
				.elseif ($symcmp(TMP1_E,")") = 0)
					inst	(n*2)+src, dst+n
				.elseif (LEN1 = 0)
					inst	dst+n
				.else
					inst	src+(n*2), dst+n
				.endif

			.elseif ($symcmp(TMP2_B,"#") = 0)
				.if ($isreg(src) = 1)
					inst	src+n, dst>>(n*16)&0xffff
				.elseif ($symcmp(TMP1_B,"#") = 0)
					inst	(src>>(n*16)) & 0xffff, dst>>(n*16)&0xffff
				.elseif ($symcmp(TMP1_B,"@") = 0)
					inst	src, dst>>(n*16)&0xffff
					.if ($symcmp(last,"1") = 0) & ($symcmp(TMP1_E,"+") != 0)
						suba	#(n+1)*2, REG1
					.endif
				.elseif ($symcmp(TMP1_E,")") = 0)
					inst	(n*2)+src, dst>>(n*16)&0xffff
				.elseif (LEN1 = 0)
					inst	dst>>(n*16)&0xffff
				.else
					inst	src+(n*2), dst>>(n*16)&0xffff
				.endif

			.elseif ($symcmp(TMP2_B,"@") = 0)
				.if ($isreg(src) = 1)
					inst	src+n, dst
				.elseif ($symcmp(TMP1_B,"#") = 0)
					inst	src>>(n*16)&0xffff, dst
				.elseif ($symcmp(TMP1_B,"@") = 0)
					inst	src, dst
					.if ($symcmp(last,"1") = 0) & ($symcmp(TMP1_E,"+") != 0)
						suba	#(n+1)*2, REG1
					.endif
				.elseif ($symcmp(TMP1_E,")") = 0)
					inst	(n*2)+src, dst
				.elseif (LEN1 = 0)
					inst	dst
				.else
					inst	src+(n*2), dst
				.endif
				.if ($symcmp(last,"1") = 0) & ($symcmp(TMP2_E,"+") != 0)
					suba	#(n+1)*2, REG2
				.endif

			.elseif ($symcmp(TMP2_E,")") = 0)
				.if ($isreg(src) = 1)
					inst	src+n, (n*2)+dst
				.elseif ($symcmp(TMP1_B,"#") = 0)
					inst	src>>(n*16)&0xffff, (n*2)+dst
				.elseif ($symcmp(TMP1_B,"@") = 0)
					inst	src, (n*2)+dst
					.if ($symcmp(last,"1") = 0) & ($symcmp(TMP1_E,"+") != 0)
						suba	#(n+1)*2, REG1
					.endif
				.elseif ($symcmp(TMP1_E,")") = 0)
					inst	(n*2)+src, (n*2)+dst
				.elseif (LEN1 = 0)
					inst	(n*2)+dst
				.else
					inst	src+(n*2), (n*2)+dst
				.endif

			.else
				.if ($isreg(src) = 1)
					inst	src+n, dst+(n*2)
				.elseif ($symcmp(TMP1_B,"#") = 0)
					inst	src>>(n*16)&0xffff, dst+(n*2)
				.elseif ($symcmp(TMP1_B,"@") = 0)
					inst	src, dst+(n*2)
					.if ($symcmp(last,"1") = 0) & ($symcmp(TMP1_E,"+") != 0)
						suba	#(n+1)*2, REG1
					.endif
				.elseif ($symcmp(TMP1_E,")") = 0)
					inst	(n*2)+src, dst+(n*2)
				.elseif (LEN1 = 0)
					inst	dst+(n*2)
				.else
					inst	src+(n*2), dst+(n*2)
				.endif
			.endif
			.endm
