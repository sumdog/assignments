
;Define D-Bug 12 Function
;PUTCHAR EQU	$F684
;OUT4HEX  EQU   $F698
PRINTF   EQU   $F686
PUTCHAR  EQU   $F684
SETUVEC  EQU   $F69A

;Define Memory I/O
SREADY	 EQU	$C4
SDATA 	 EQU	$C7
SINMASK  EQU    $20
SOUTMASK EQU    $80

;Define Keys
KEYCR   EQU     $0D ;(Return)
CHARX   EQU     $58 ;ASCII X

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
  jsr PrintXBars
  rts

;Prints X bars
;  2 per whole number (WOLH)
;  1 if VOLL is greater than 5
;   exmaple: 4.6: XXXXXXXXX
PrintXBars:
  ldaa VOLH
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
  ldaa VOLL          ;Half step X (VOLL > 5)
  cmpa #$05
  ble done_x
  ldaa #$00
  ldab #CHARX
  jsr [PUTCHAR,PCR]
done_x:  
  rts

;define datatypes
VOLH       DB      $05   ;Whole number
VOLL       DB      $06   ;Tenth
FORMAT     DB      "Voltage: %d.%d  ",0
