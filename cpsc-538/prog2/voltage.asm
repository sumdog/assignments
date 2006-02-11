
;Define D-Bug 12 Function
;PUTCHAR EQU	$F684
;OUT4HEX  EQU   $F698
PRINTF   EQU   $F686
PUTCHAR  EQU   $F684
;SETUVEC  EQU   $F69A

;Define Memory I/O
;SREADY	 EQU	$C4
;SDATA 	 EQU	$C7
;SINMASK  EQU    $20
;SOUTMASK EQU    $80

;Define ATD Registers
ATDCTL2  EQU     $62 ;ATD Control Registers
ATDCTL5  EQU     $65
ATDSTATA EQU     $66
PORTAD   EQU     $6F
ADRX2H   EQU     $74

;Define ATD masks
;ATDMASK EQU     %11000010 ;Enable ATD, Fast Clear, Interrurpts for ATDCTL2


;Define Keys
KEYCR   EQU     $0D ;(Return)
CHARX   EQU     $58 ;ASCII X

  ORG $0800

;--Main() program entry point
Main:

  ;Initalize ATD unit
  bset ATDCTL2,%10000000
  
  ;Wait for over 100 microseconds
  ; so ATD can initalize
  ldaa $C8
init_wait:
  dbne a,init_wait

loop:
  ;jsr Pull
  ldd #$0080
  jsr Convert
  jsr ClearScreen
  jsr PrintVoltage
  wai
  bra loop

;--Pulls data from ATD (PAD6) and 
;  stores it in [B] ([A] set to 0)
Pull:
  ldaa #$06               ;Initializes ATD SCAN=0,MULT=0, PAD6
  staa ATDCTL5            ;Write clears flags

c_loop:                   ;Wait until ATD has data
  brclr ATDSTATA,#%10000000,c_loop

  ldab ADRX2H             ;pull 8-bit signed result
  ldaa #$00

  rts

;Converts the unsigned 8-bit interger
;  in [D] ([B] = data, [A] = 00)
;  to a value between 0 to 5 and stores
;  the whole part in VOLH and the fraction
;  (0 to 99) in VOLL, rounding 100 to 99
;  for VOLL

Convert:
  ldx #$33                ;divide by 51 to get quotient between 0 and 5
  idiv

  pshd                    ;x will be a whole number ready for VOLH
  tfr x,d                 ; ----DEBUG NOTE (should this be d,x?) 
  stab VOLH               
  puld

  ldaa #$02               ;Scale 0 - 50 to 0 - 100
  mul                     ;  since multiplying by 2 can give us
  tba                     ;  a 100, we give 99 for 100, losing
  ;mina #$64               ;  1/100 point in accuracy with a tradeoff
  staa VOLL               ;  of less math
  
  rts


;Clears Screen via CR (without LF)
ClearScreen:
  ldaa #$00
  ldab #KEYCR
  jsr [PUTCHAR,PCR]
  rts

;Prints Voltage in the format
;  Voltage 5.0   XXXXXXXXXX
;  (calls PrintXBars for analogue bar)
PrintVoltage:
  lda #$00           ;Load 0 into high bit
  ldb VOLL           ;Printf args
  pshd
  ldb VOLH
  pshd
  ldd #FORMAT
  jsr [PRINTF,PCR]   ;Print numerical voltage
  puld               ;clean stack
  puld
  jsr PrintXBars
  rts

;Prints X bars
;  2 per whole number (WOLH)
;  1 if VOLL is greater than 50
;   exmaple: 4.60: XXXXXXXXX
PrintXBars:
  ldaa VOLH
  adda #$01          ;Add 1 for start_xx loop to get final X
  ldab #CHARX
start_xx:            ;Whole number loop
  cmpa #$00      
  dbeq a,done_xx
  psha
  ldaa #$00
  ldab #CHARX
  jsr [PUTCHAR,PCR]
  jsr [PUTCHAR,PCR]
  pula  
  bra start_xx
done_xx:
  ldaa VOLL          ;Half step X (VOLL > 50)
  cmpa #$32          ; 50
  blt done_x
  ldaa #$00
  ldab #CHARX
  jsr [PUTCHAR,PCR]
done_x:  
  rts

;define datatypes
VOLH       DB      $00   ;Whole number
VOLL       DB      $00   ;Tenth
FORMAT     DB      "Voltage: %d.%02d  ",0
DFORMAT    DB      "%u",0 
