;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.0 #10562 (Linux)
;--------------------------------------------------------
	.module lab11
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _B
	.globl _ACC
	.globl _PSW
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	ljmp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;	lab11.c:2: int main()
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
;	lab11.c:4: P1 = 0b11111111;
	mov	_P1,#0xff
;	lab11.c:7: P3_3 = 0;
;	assignBit
	clr	_P3_3
;	lab11.c:8: P3_4 = 0;
;	assignBit
	clr	_P3_4
;	lab11.c:9: while(1)
00126$:
;	lab11.c:12: P0_0 = 1;
;	assignBit
	setb	_P0_0
;	lab11.c:13: P0_1 = 1;
;	assignBit
	setb	_P0_1
;	lab11.c:14: P0_2 = 1;
;	assignBit
	setb	_P0_2
;	lab11.c:15: P0_3 = 0;
;	assignBit
	clr	_P0_3
;	lab11.c:16: if(P0_4 == 0) // 3
	jb	_P0_4,00102$
;	lab11.c:18: P3_3 = 1;
;	assignBit
	setb	_P3_3
;	lab11.c:19: P3_4 = 1;
;	assignBit
	setb	_P3_4
;	lab11.c:20: P1 = 0b10110000;
	mov	_P1,#0xb0
00102$:
;	lab11.c:22: if(P0_5 == 0) // 2
	jb	_P0_5,00104$
;	lab11.c:24: P3_3 = 0;
;	assignBit
	clr	_P3_3
;	lab11.c:25: P3_4 = 1;
;	assignBit
	setb	_P3_4
;	lab11.c:26: P1 = 0b10100100;
	mov	_P1,#0xa4
00104$:
;	lab11.c:28: if(P0_6 == 0) // 1
	jb	_P0_6,00106$
;	lab11.c:30: P3_3 = 1;
;	assignBit
	setb	_P3_3
;	lab11.c:31: P3_4 = 0;
;	assignBit
	clr	_P3_4
;	lab11.c:32: P1 = 0b11111001;
	mov	_P1,#0xf9
00106$:
;	lab11.c:36: P0_0 = 1;
;	assignBit
	setb	_P0_0
;	lab11.c:37: P0_1 = 1;
;	assignBit
	setb	_P0_1
;	lab11.c:38: P0_2 = 0;
;	assignBit
	clr	_P0_2
;	lab11.c:39: P0_3 = 1;
;	assignBit
	setb	_P0_3
;	lab11.c:40: if(P0_4 == 0) // 6
	jb	_P0_4,00108$
;	lab11.c:42: P1 = 0b10000010;
	mov	_P1,#0x82
00108$:
;	lab11.c:44: if(P0_5 == 0) // 5
	jb	_P0_5,00110$
;	lab11.c:46: P1 = 0b00010010;
	mov	_P1,#0x12
00110$:
;	lab11.c:48: if(P0_6 == 0) // 4
	jb	_P0_6,00112$
;	lab11.c:50: P1 = 0b10111011;
	mov	_P1,#0xbb
00112$:
;	lab11.c:54: P0_0 = 1;
;	assignBit
	setb	_P0_0
;	lab11.c:55: P0_1 = 0;
;	assignBit
	clr	_P0_1
;	lab11.c:56: P0_2 = 1;
;	assignBit
	setb	_P0_2
;	lab11.c:57: P0_3 = 1;
;	assignBit
	setb	_P0_3
;	lab11.c:58: if(P0_4 == 0) // 9
	jb	_P0_4,00114$
;	lab11.c:60: P1 = 0b10010000;
	mov	_P1,#0x90
00114$:
;	lab11.c:62: if(P0_5 == 0) // 8
	jb	_P0_5,00116$
;	lab11.c:64: P1 = 0b10000000;
	mov	_P1,#0x80
00116$:
;	lab11.c:66: if(P0_6 == 0) // 7
	jb	_P0_6,00118$
;	lab11.c:68: P1 = 0b11111000;
	mov	_P1,#0xf8
00118$:
;	lab11.c:72: P0_0 = 0;
;	assignBit
	clr	_P0_0
;	lab11.c:73: P0_1 = 1;
;	assignBit
	setb	_P0_1
;	lab11.c:74: P0_2 = 1;
;	assignBit
	setb	_P0_2
;	lab11.c:75: P0_3 = 1;
;	assignBit
	setb	_P0_3
;	lab11.c:76: if(P0_4 == 0) // #
	jb	_P0_4,00120$
;	lab11.c:78: P1 = 0b10001000;
	mov	_P1,#0x88
00120$:
;	lab11.c:80: if(P0_5 == 0) // 0
	jb	_P0_5,00122$
;	lab11.c:82: P1 = 0b11000000;
	mov	_P1,#0xc0
00122$:
;	lab11.c:84: if(P0_6 == 0) // *
	jb	_P0_6,00126$
;	lab11.c:86: P1 = 0b01111111;
	mov	_P1,#0x7f
;	lab11.c:106: }
	sjmp	00126$
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
