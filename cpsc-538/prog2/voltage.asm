
;Define D-Bug 12 Function
;PUTCHAR EQU	$F684
OUT4HEX  EQU   $F698
PRINTF   EQU   $F686
PUTCHAR EQU    $F684

;Define Memory I/O
SREADY	 EQU	$C4
SDATA 	 EQU	$C7
SINMASK  EQU    $20
SOUTMASK EQU    $80

;Define Keys
KEYBS    EQU    $0008

  ORG $0800

Main:
  jsr ClearScreen
  jsr PrintVoltage
  bra Main

ClearScreen:
  ldaa $07                   ;a = 7
clear_loop:
  dbeq a,clear_done          ;while a < 7; a--
  psha
  ldd #KEYBS
  jsr [PUTCHAR,PCR]
  pula
  bra clear_loop
clear_done:
  rts

PrintVoltage:
  lda VOLTAGE
  rts

;define datatypes
VOLTAGE	   DB	   $00
