
; PIC18F46K40 Configuration Bit Settings
; ASM source line config statements

; CONFIG1L
  CONFIG  FEXTOSC = HS          ; External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
  CONFIG  RSTOSC = EXTOSC_4PLL  ; Power-up default value for COSC bits (EXTOSC operating per FEXTOSC bits (device manufacturing default))

; CONFIG1H
  CONFIG  CLKOUTEN = OFF        ; Clock Out Enable bit (CLKOUT function is disabled)
  CONFIG  CSWEN = OFF            ; Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
  CONFIG  FCMEN = OFF            ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

; CONFIG2L
  CONFIG  MCLRE = EXTMCLR       ; Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
  CONFIG  PWRTE = OFF           ; Power-up Timer Enable bit (Power up timer disabled)
  CONFIG  LPBOREN = OFF         ; Low-power BOR enable bit (ULPBOR disabled)
  CONFIG  BOREN = SBORDIS       ; Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

; CONFIG2H
  CONFIG  BORV = VBOR_2P45      ; Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
  CONFIG  ZCD = OFF             ; ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
  CONFIG  PPS1WAY = OFF          ; PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  DEBUG = OFF           ; Debugger Enable bit (Background debugger disabled)
  CONFIG  XINST = ON           ; Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

; CONFIG3L
  CONFIG  WDTCPS = WDTCPS_31    ; WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
  CONFIG  WDTE = OFF            ; WDT operating mode (WDT Disabled)

; CONFIG3H
  CONFIG  WDTCWS = WDTCWS_7     ; WDT Window Select bits (window always open (100%); software control; keyed access not required)
  CONFIG  WDTCCS = SC           ; WDT input clock selector (Software Control)

; CONFIG4L
  CONFIG  WRT0 = OFF            ; Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

; CONFIG4H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)
  CONFIG  SCANE = ON            ; Scanner Enable bit (Scanner module is available for use, SCANMD bit can control the module)
  CONFIG  LVP = ON              ; Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

; CONFIG5L
  CONFIG  CP = OFF              ; UserNVM Program Memory Code Protection bit (UserNVM code protection disabled)
  CONFIG  CPD = OFF             ; DataNVM Memory Code Protection bit (DataNVM code protection disabled)

; CONFIG5H

; CONFIG6L
  CONFIG  EBTR0 = OFF           ; Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

; CONFIG6H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

	CBLOCK	0x00
	R0	:1
	R1	:1
	R2	:1
	R3	:1
	R4	:1
	R5	:1
	R6	:1
	R7	:1
	R8	:1
	R9	:1
	R10	:1
	R11	:1
	R12	:1
	R13	:1
	R14	:1
	R15	:1
	ENDC
	
; Reset vector
        ORG		0x00
	bra	setup
	    
; High priority or default Interrupt vector
	ORG		0x08
	bra	hp_int
	
; Low priority Interrupt vector
	ORG		0x18
	bra	lp_int
	
	ORG		0x1a
; set up pic rutine
setup:
	movlb	0xf
	lfsr	SP, END_RAM
	bsf	NVMCON1, 7
	clrf	TBLPTRU
	clrf	LATA
	clrf	LATB
	clrf	LATC
	clrf	LATD
	clrf	LATE
	setf	TRISA
	setf	TRISB
	setf	TRISC
	setf	TRISD
	setf	TRISE
	clrf	ANSELA
	clrf	ANSELB
	clrf	ANSELC
	clrf	ANSELD
	clrf	ANSELE
	movlb	0xe
	movlw	0x55
	movwf	PPSLOCK
	movlw	0x55
	movwf	PPSLOCK
	bcf	PPSLOCK,0
	movlb	0x0
	goto	main
	return

lp_int:
	retfie	FAST
	
hp_int:
	movlb	0x0e
	btfsc	PIR6,CCP1IF, 1 ;timer2
	goto	timer_int
	retfie	FAST
	
;******************************************************************************;	    
; 
END_RAM	EQU     0xdff
ACC	EQU	WREG
SP	EQU	FSR2
FCY	EQU	.32000000
r0	EQU	R0
r1	EQU	R1
r2	EQU	R2
r3	EQU	R3
r4	EQU	R4
r5	EQU	R5
r6	EQU	R6
r7	EQU	R7
r8	EQU	R8
r9	EQU	R9
r10	EQU	R10
r11	EQU	R11
r12	EQU	R12
r13	EQU	R13
r14	EQU	R14
r15	EQU	R15
BIT0	EQU	0x01
BIT1	EQU	0x02
BIT2	EQU	0x04
BIT3	EQU	0x08
BIT4	EQU	0x10
BIT5	EQU	0x20
BIT6	EQU	0x40
BIT7	EQU	0x80