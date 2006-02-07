
;Define D-Bug 12 Function
;PUTCHAR EQU	$F684
;OUT4HEX  EQU   $F698
PRINTF   EQU   $F686
PUTCHAR  EQU   $F684
SETUVEC  EQU   $F69A

;Define Memory I/O
;SREADY	 EQU	$C4
;SDATA 	 EQU	$C7
;SINMASK  EQU    $20
;SOUTMASK EQU    $80

;Define ATD Registers
ATDCTL2 EQU     $62 ;ATD Control Register

;Define ATD masks
ATDMASK EQU     %11000010 ;Enable ATD, Fast Clear, Interrurpts for ATDCTL2


;Define Keys
KEYCR   EQU     $0D ;(Return)
CHARX   EQU     $58 ;ASCII X

  ORG $0800

Main:

  ;Initalize ATD unit
  bset ATDCTL2,ATDMASK  
  

  jsr ClearScreen
  jsr PrintVoltage
  wai

;Ckears Screen via CR (without LF)
ClearScreen:
  ldaa #$00
  ldab #KEYCR
  jsr [PUTCHAR,PCR]
  rts

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
;  1 if VOLL is greater than 5
;   exmaple: 4.6: XXXXXXXXX
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
VOLH       DB      $03   ;Whole number
VOLL       DB      $31   ;Tenth
FORMAT     DB      "Voltage: %d.%02d  ",0
