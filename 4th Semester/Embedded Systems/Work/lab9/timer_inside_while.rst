                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.0 #10562 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module timer_inside_while
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _CY
                                     13 	.globl _AC
                                     14 	.globl _F0
                                     15 	.globl _RS1
                                     16 	.globl _RS0
                                     17 	.globl _OV
                                     18 	.globl _F1
                                     19 	.globl _P
                                     20 	.globl _PS
                                     21 	.globl _PT1
                                     22 	.globl _PX1
                                     23 	.globl _PT0
                                     24 	.globl _PX0
                                     25 	.globl _RD
                                     26 	.globl _WR
                                     27 	.globl _T1
                                     28 	.globl _T0
                                     29 	.globl _INT1
                                     30 	.globl _INT0
                                     31 	.globl _TXD
                                     32 	.globl _RXD
                                     33 	.globl _P3_7
                                     34 	.globl _P3_6
                                     35 	.globl _P3_5
                                     36 	.globl _P3_4
                                     37 	.globl _P3_3
                                     38 	.globl _P3_2
                                     39 	.globl _P3_1
                                     40 	.globl _P3_0
                                     41 	.globl _EA
                                     42 	.globl _ES
                                     43 	.globl _ET1
                                     44 	.globl _EX1
                                     45 	.globl _ET0
                                     46 	.globl _EX0
                                     47 	.globl _P2_7
                                     48 	.globl _P2_6
                                     49 	.globl _P2_5
                                     50 	.globl _P2_4
                                     51 	.globl _P2_3
                                     52 	.globl _P2_2
                                     53 	.globl _P2_1
                                     54 	.globl _P2_0
                                     55 	.globl _SM0
                                     56 	.globl _SM1
                                     57 	.globl _SM2
                                     58 	.globl _REN
                                     59 	.globl _TB8
                                     60 	.globl _RB8
                                     61 	.globl _TI
                                     62 	.globl _RI
                                     63 	.globl _P1_7
                                     64 	.globl _P1_6
                                     65 	.globl _P1_5
                                     66 	.globl _P1_4
                                     67 	.globl _P1_3
                                     68 	.globl _P1_2
                                     69 	.globl _P1_1
                                     70 	.globl _P1_0
                                     71 	.globl _TF1
                                     72 	.globl _TR1
                                     73 	.globl _TF0
                                     74 	.globl _TR0
                                     75 	.globl _IE1
                                     76 	.globl _IT1
                                     77 	.globl _IE0
                                     78 	.globl _IT0
                                     79 	.globl _P0_7
                                     80 	.globl _P0_6
                                     81 	.globl _P0_5
                                     82 	.globl _P0_4
                                     83 	.globl _P0_3
                                     84 	.globl _P0_2
                                     85 	.globl _P0_1
                                     86 	.globl _P0_0
                                     87 	.globl _B
                                     88 	.globl _ACC
                                     89 	.globl _PSW
                                     90 	.globl _IP
                                     91 	.globl _P3
                                     92 	.globl _IE
                                     93 	.globl _P2
                                     94 	.globl _SBUF
                                     95 	.globl _SCON
                                     96 	.globl _P1
                                     97 	.globl _TH1
                                     98 	.globl _TH0
                                     99 	.globl _TL1
                                    100 	.globl _TL0
                                    101 	.globl _TMOD
                                    102 	.globl _TCON
                                    103 	.globl _PCON
                                    104 	.globl _DPH
                                    105 	.globl _DPL
                                    106 	.globl _SP
                                    107 	.globl _P0
                                    108 ;--------------------------------------------------------
                                    109 ; special function registers
                                    110 ;--------------------------------------------------------
                                    111 	.area RSEG    (ABS,DATA)
      000000                        112 	.org 0x0000
                           000080   113 _P0	=	0x0080
                           000081   114 _SP	=	0x0081
                           000082   115 _DPL	=	0x0082
                           000083   116 _DPH	=	0x0083
                           000087   117 _PCON	=	0x0087
                           000088   118 _TCON	=	0x0088
                           000089   119 _TMOD	=	0x0089
                           00008A   120 _TL0	=	0x008a
                           00008B   121 _TL1	=	0x008b
                           00008C   122 _TH0	=	0x008c
                           00008D   123 _TH1	=	0x008d
                           000090   124 _P1	=	0x0090
                           000098   125 _SCON	=	0x0098
                           000099   126 _SBUF	=	0x0099
                           0000A0   127 _P2	=	0x00a0
                           0000A8   128 _IE	=	0x00a8
                           0000B0   129 _P3	=	0x00b0
                           0000B8   130 _IP	=	0x00b8
                           0000D0   131 _PSW	=	0x00d0
                           0000E0   132 _ACC	=	0x00e0
                           0000F0   133 _B	=	0x00f0
                                    134 ;--------------------------------------------------------
                                    135 ; special function bits
                                    136 ;--------------------------------------------------------
                                    137 	.area RSEG    (ABS,DATA)
      000000                        138 	.org 0x0000
                           000080   139 _P0_0	=	0x0080
                           000081   140 _P0_1	=	0x0081
                           000082   141 _P0_2	=	0x0082
                           000083   142 _P0_3	=	0x0083
                           000084   143 _P0_4	=	0x0084
                           000085   144 _P0_5	=	0x0085
                           000086   145 _P0_6	=	0x0086
                           000087   146 _P0_7	=	0x0087
                           000088   147 _IT0	=	0x0088
                           000089   148 _IE0	=	0x0089
                           00008A   149 _IT1	=	0x008a
                           00008B   150 _IE1	=	0x008b
                           00008C   151 _TR0	=	0x008c
                           00008D   152 _TF0	=	0x008d
                           00008E   153 _TR1	=	0x008e
                           00008F   154 _TF1	=	0x008f
                           000090   155 _P1_0	=	0x0090
                           000091   156 _P1_1	=	0x0091
                           000092   157 _P1_2	=	0x0092
                           000093   158 _P1_3	=	0x0093
                           000094   159 _P1_4	=	0x0094
                           000095   160 _P1_5	=	0x0095
                           000096   161 _P1_6	=	0x0096
                           000097   162 _P1_7	=	0x0097
                           000098   163 _RI	=	0x0098
                           000099   164 _TI	=	0x0099
                           00009A   165 _RB8	=	0x009a
                           00009B   166 _TB8	=	0x009b
                           00009C   167 _REN	=	0x009c
                           00009D   168 _SM2	=	0x009d
                           00009E   169 _SM1	=	0x009e
                           00009F   170 _SM0	=	0x009f
                           0000A0   171 _P2_0	=	0x00a0
                           0000A1   172 _P2_1	=	0x00a1
                           0000A2   173 _P2_2	=	0x00a2
                           0000A3   174 _P2_3	=	0x00a3
                           0000A4   175 _P2_4	=	0x00a4
                           0000A5   176 _P2_5	=	0x00a5
                           0000A6   177 _P2_6	=	0x00a6
                           0000A7   178 _P2_7	=	0x00a7
                           0000A8   179 _EX0	=	0x00a8
                           0000A9   180 _ET0	=	0x00a9
                           0000AA   181 _EX1	=	0x00aa
                           0000AB   182 _ET1	=	0x00ab
                           0000AC   183 _ES	=	0x00ac
                           0000AF   184 _EA	=	0x00af
                           0000B0   185 _P3_0	=	0x00b0
                           0000B1   186 _P3_1	=	0x00b1
                           0000B2   187 _P3_2	=	0x00b2
                           0000B3   188 _P3_3	=	0x00b3
                           0000B4   189 _P3_4	=	0x00b4
                           0000B5   190 _P3_5	=	0x00b5
                           0000B6   191 _P3_6	=	0x00b6
                           0000B7   192 _P3_7	=	0x00b7
                           0000B0   193 _RXD	=	0x00b0
                           0000B1   194 _TXD	=	0x00b1
                           0000B2   195 _INT0	=	0x00b2
                           0000B3   196 _INT1	=	0x00b3
                           0000B4   197 _T0	=	0x00b4
                           0000B5   198 _T1	=	0x00b5
                           0000B6   199 _WR	=	0x00b6
                           0000B7   200 _RD	=	0x00b7
                           0000B8   201 _PX0	=	0x00b8
                           0000B9   202 _PT0	=	0x00b9
                           0000BA   203 _PX1	=	0x00ba
                           0000BB   204 _PT1	=	0x00bb
                           0000BC   205 _PS	=	0x00bc
                           0000D0   206 _P	=	0x00d0
                           0000D1   207 _F1	=	0x00d1
                           0000D2   208 _OV	=	0x00d2
                           0000D3   209 _RS0	=	0x00d3
                           0000D4   210 _RS1	=	0x00d4
                           0000D5   211 _F0	=	0x00d5
                           0000D6   212 _AC	=	0x00d6
                           0000D7   213 _CY	=	0x00d7
                                    214 ;--------------------------------------------------------
                                    215 ; overlayable register banks
                                    216 ;--------------------------------------------------------
                                    217 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        218 	.ds 8
                                    219 ;--------------------------------------------------------
                                    220 ; internal ram data
                                    221 ;--------------------------------------------------------
                                    222 	.area DSEG    (DATA)
                                    223 ;--------------------------------------------------------
                                    224 ; overlayable items in internal ram 
                                    225 ;--------------------------------------------------------
                                    226 	.area	OSEG    (OVR,DATA)
                                    227 ;--------------------------------------------------------
                                    228 ; Stack segment in internal ram 
                                    229 ;--------------------------------------------------------
                                    230 	.area	SSEG
      000008                        231 __start__stack:
      000008                        232 	.ds	1
                                    233 
                                    234 ;--------------------------------------------------------
                                    235 ; indirectly addressable internal ram data
                                    236 ;--------------------------------------------------------
                                    237 	.area ISEG    (DATA)
                                    238 ;--------------------------------------------------------
                                    239 ; absolute internal ram data
                                    240 ;--------------------------------------------------------
                                    241 	.area IABS    (ABS,DATA)
                                    242 	.area IABS    (ABS,DATA)
                                    243 ;--------------------------------------------------------
                                    244 ; bit data
                                    245 ;--------------------------------------------------------
                                    246 	.area BSEG    (BIT)
                                    247 ;--------------------------------------------------------
                                    248 ; paged external ram data
                                    249 ;--------------------------------------------------------
                                    250 	.area PSEG    (PAG,XDATA)
                                    251 ;--------------------------------------------------------
                                    252 ; external ram data
                                    253 ;--------------------------------------------------------
                                    254 	.area XSEG    (XDATA)
                                    255 ;--------------------------------------------------------
                                    256 ; absolute external ram data
                                    257 ;--------------------------------------------------------
                                    258 	.area XABS    (ABS,XDATA)
                                    259 ;--------------------------------------------------------
                                    260 ; external initialized ram data
                                    261 ;--------------------------------------------------------
                                    262 	.area XISEG   (XDATA)
                                    263 	.area HOME    (CODE)
                                    264 	.area GSINIT0 (CODE)
                                    265 	.area GSINIT1 (CODE)
                                    266 	.area GSINIT2 (CODE)
                                    267 	.area GSINIT3 (CODE)
                                    268 	.area GSINIT4 (CODE)
                                    269 	.area GSINIT5 (CODE)
                                    270 	.area GSINIT  (CODE)
                                    271 	.area GSFINAL (CODE)
                                    272 	.area CSEG    (CODE)
                                    273 ;--------------------------------------------------------
                                    274 ; interrupt vector 
                                    275 ;--------------------------------------------------------
                                    276 	.area HOME    (CODE)
      000000                        277 __interrupt_vect:
      000000 02 00 06         [24]  278 	ljmp	__sdcc_gsinit_startup
                                    279 ;--------------------------------------------------------
                                    280 ; global & static initialisations
                                    281 ;--------------------------------------------------------
                                    282 	.area HOME    (CODE)
                                    283 	.area GSINIT  (CODE)
                                    284 	.area GSFINAL (CODE)
                                    285 	.area GSINIT  (CODE)
                                    286 	.globl __sdcc_gsinit_startup
                                    287 	.globl __sdcc_program_startup
                                    288 	.globl __start__stack
                                    289 	.globl __mcs51_genXINIT
                                    290 	.globl __mcs51_genXRAMCLEAR
                                    291 	.globl __mcs51_genRAMCLEAR
                                    292 	.area GSFINAL (CODE)
      00005F 02 00 03         [24]  293 	ljmp	__sdcc_program_startup
                                    294 ;--------------------------------------------------------
                                    295 ; Home
                                    296 ;--------------------------------------------------------
                                    297 	.area HOME    (CODE)
                                    298 	.area HOME    (CODE)
      000003                        299 __sdcc_program_startup:
      000003 02 00 62         [24]  300 	ljmp	_main
                                    301 ;	return from main will return to caller
                                    302 ;--------------------------------------------------------
                                    303 ; code
                                    304 ;--------------------------------------------------------
                                    305 	.area CSEG    (CODE)
                                    306 ;------------------------------------------------------------
                                    307 ;Allocation info for local variables in function 'main'
                                    308 ;------------------------------------------------------------
                                    309 ;rotateState               Allocated to registers r6 r7 
                                    310 ;moveState                 Allocated to registers r4 r5 
                                    311 ;rotate                    Allocated to registers 
                                    312 ;move                      Allocated to registers 
                                    313 ;i                         Allocated to registers r2 r3 
                                    314 ;------------------------------------------------------------
                                    315 ;	timer_inside_while.c:6: int main(){
                                    316 ;	-----------------------------------------
                                    317 ;	 function main
                                    318 ;	-----------------------------------------
      000062                        319 _main:
                           000007   320 	ar7 = 0x07
                           000006   321 	ar6 = 0x06
                           000005   322 	ar5 = 0x05
                           000004   323 	ar4 = 0x04
                           000003   324 	ar3 = 0x03
                           000002   325 	ar2 = 0x02
                           000001   326 	ar1 = 0x01
                           000000   327 	ar0 = 0x00
                                    328 ;	timer_inside_while.c:7: P0 = 0x55;
      000062 75 80 55         [24]  329 	mov	_P0,#0x55
                                    330 ;	timer_inside_while.c:8: P1 = 0x55;
      000065 75 90 55         [24]  331 	mov	_P1,#0x55
                                    332 ;	timer_inside_while.c:9: P2 = 0x55;
      000068 75 A0 55         [24]  333 	mov	_P2,#0x55
                                    334 ;	timer_inside_while.c:10: P3 = 0x55;
      00006B 75 B0 55         [24]  335 	mov	_P3,#0x55
                                    336 ;	timer_inside_while.c:12: P3_0 = 0;
                                    337 ;	assignBit
      00006E C2 B0            [12]  338 	clr	_P3_0
                                    339 ;	timer_inside_while.c:13: P3_1 = 1;
                                    340 ;	assignBit
      000070 D2 B1            [12]  341 	setb	_P3_1
                                    342 ;	timer_inside_while.c:15: int rotateState = 0;
      000072 7E 00            [12]  343 	mov	r6,#0x00
      000074 7F 00            [12]  344 	mov	r7,#0x00
                                    345 ;	timer_inside_while.c:16: int moveState = 0;
      000076 7C 00            [12]  346 	mov	r4,#0x00
      000078 7D 00            [12]  347 	mov	r5,#0x00
                                    348 ;	timer_inside_while.c:20: while(1){
      00007A                        349 00113$:
                                    350 ;	timer_inside_while.c:21: P1 = 0x55;
      00007A 75 90 55         [24]  351 	mov	_P1,#0x55
                                    352 ;	timer_inside_while.c:22: P2 = 0xAA;
      00007D 75 A0 AA         [24]  353 	mov	_P2,#0xaa
                                    354 ;	timer_inside_while.c:23: for(int i=0;i<100;i++){
      000080 7A 00            [12]  355 	mov	r2,#0x00
      000082 7B 00            [12]  356 	mov	r3,#0x00
      000084                        357 00116$:
      000084 C3               [12]  358 	clr	c
      000085 EA               [12]  359 	mov	a,r2
      000086 94 64            [12]  360 	subb	a,#0x64
      000088 EB               [12]  361 	mov	a,r3
      000089 64 80            [12]  362 	xrl	a,#0x80
      00008B 94 80            [12]  363 	subb	a,#0x80
      00008D 50 07            [24]  364 	jnc	00101$
      00008F 0A               [12]  365 	inc	r2
      000090 BA 00 F1         [24]  366 	cjne	r2,#0x00,00116$
      000093 0B               [12]  367 	inc	r3
      000094 80 EE            [24]  368 	sjmp	00116$
      000096                        369 00101$:
                                    370 ;	timer_inside_while.c:26: if(rotateState){
      000096 EE               [12]  371 	mov	a,r6
      000097 4F               [12]  372 	orl	a,r7
      000098 60 06            [24]  373 	jz	00105$
                                    374 ;	timer_inside_while.c:28: rotateState = 0;
      00009A 7E 00            [12]  375 	mov	r6,#0x00
      00009C 7F 00            [12]  376 	mov	r7,#0x00
      00009E 80 07            [24]  377 	sjmp	00106$
      0000A0                        378 00105$:
                                    379 ;	timer_inside_while.c:30: else if(!rotateState)
      0000A0 EE               [12]  380 	mov	a,r6
      0000A1 4F               [12]  381 	orl	a,r7
                                    382 ;	timer_inside_while.c:33: rotateState = 1;
      0000A2 70 03            [24]  383 	jnz	00106$
      0000A4 7E 01            [12]  384 	mov	r6,#0x01
      0000A6 FF               [12]  385 	mov	r7,a
      0000A7                        386 00106$:
                                    387 ;	timer_inside_while.c:36: if(moveState){
      0000A7 EC               [12]  388 	mov	a,r4
      0000A8 4D               [12]  389 	orl	a,r5
      0000A9 60 06            [24]  390 	jz	00110$
                                    391 ;	timer_inside_while.c:38: moveState = 0;
      0000AB 7C 00            [12]  392 	mov	r4,#0x00
      0000AD 7D 00            [12]  393 	mov	r5,#0x00
      0000AF 80 07            [24]  394 	sjmp	00111$
      0000B1                        395 00110$:
                                    396 ;	timer_inside_while.c:40: else if(!moveState)
      0000B1 EC               [12]  397 	mov	a,r4
      0000B2 4D               [12]  398 	orl	a,r5
                                    399 ;	timer_inside_while.c:43: moveState = 1;
      0000B3 70 03            [24]  400 	jnz	00111$
      0000B5 7C 01            [12]  401 	mov	r4,#0x01
      0000B7 FD               [12]  402 	mov	r5,a
      0000B8                        403 00111$:
                                    404 ;	timer_inside_while.c:46: P1 = 0xAA;
      0000B8 75 90 AA         [24]  405 	mov	_P1,#0xaa
                                    406 ;	timer_inside_while.c:47: P2 = 0x55;
      0000BB 75 A0 55         [24]  407 	mov	_P2,#0x55
                                    408 ;	timer_inside_while.c:50: }
      0000BE 80 BA            [24]  409 	sjmp	00113$
                                    410 	.area CSEG    (CODE)
                                    411 	.area CONST   (CODE)
                                    412 	.area XINIT   (CODE)
                                    413 	.area CABS    (ABS,CODE)
