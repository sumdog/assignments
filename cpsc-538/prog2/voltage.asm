
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
  jsr Convert
  bra loop

;--Pulls data from ATD (PAD6) and 
;  converts the unsigned 16-bit interger
;  to a value between 0 to 5 and stores
;  the whole part in VOLH and the fraction
;  in VOLL
Convert:
  ldaa #$06               ;Initializes ATD SCAN=0,MULT=0, PAD6
  staa ATDCTL5            ;Write clears flags

c_loop:                   ;Wait until ATD has data
  brclr ATDSTATA,#%10000000,c_loop

  jsr ClearScreen

  ldab ADRX2H
  ldaa #$00
  pshd
  ldd #DFORMAT
  jsr [PRINTF,PCR]
  puld


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