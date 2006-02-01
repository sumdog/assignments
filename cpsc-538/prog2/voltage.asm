
;Define D-Bug 12 Function
;PUTCHAR EQU	$F684
;OUT4HEX  EQU   $F698
PRINTF   EQU   $F686
PUTCHAR  EQU   $F684

;Define Memory I/O
SREADY	 EQU	$C4
SDATA 	 EQU	$C7
SINMASK  EQU    $20
SOUTMASK EQU    $80

;Define Keys
KEYCR   EQU     $0D ;(Return)

  ORG $0800

Main:
  jsr ClearScreen
  jsr PrintVoltage
  bra Main

;Ckears Screen via CR (without LF)
ClearScreen:
  ldaa #$00
  ldab #KEYCR
  jsr [PUTCHAR,PCR]
  rts

PrintVoltage:
  lda #$00           ;Load 0 into high bit
  ldb VOLH           ;Printf args
  pshd
  ldb VOLL
  pshd
  ldd #FORMAT
  jsr [PRINTF,PCR]   ;Print numerical voltage
  puld               ;clean stack
  puld
  lda VOLH           ;Print X chars
  
  rts

;define datatypes
VOLH       DB      $00   ;Whole number
VOLL       DB      $00   ;Tenth
FORMAT     DB      "Voltage: %d.%d  ",0
