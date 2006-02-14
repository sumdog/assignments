; Program #2 / CPSC-538 / Dumas
;
;  written by Sumit Khanna
;             <Sumit-Khanna@utc.edu>
;
; This is a simply voltage meter that 
; will measure voltage between 0 and 4.98
; by attaching wires to VSS (ground) and
; PAD-6
;


;Define D-Bug 12 Function
PRINTF   EQU   $F686
PUTCHAR  EQU   $F684

;Define ATD Registers
ATDCTL2  EQU     $62 ;ATD Control Registers
ATDCTL5  EQU     $65
ATDSTATA EQU     $66
PORTAD   EQU     $6F
ADRX2H   EQU     $74

;Define Keys
KEYCR   EQU     $0D ;(Return)
CHARX   EQU     $58 ;ASCII X

  ORG $0800

;--Main() program entry point
Main:

  ;Initalize ATD unit
  bset ATDCTL2,%10000010
  
  ;Wait for over 100 microseconds
  ; so ATD can initalize
  ldaa $C8
init_wait:
  dbne a,init_wait

  ;our main event loop
loop:
  jsr Pull
  jsr Convert
  jsr CheckRefresh
  ldaa REFRESH            ;Check to see if display needs refreshing
  cmpa #$00
  beq skip_paint
  jsr ClearScreen
  jsr PrintVoltage
skip_paint:
  jsr Wait
  bra loop

;--Wait loop to prevent
;  console flicker
Wait:
  ldd #$FFFF
wait_loop:
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  dbne d,wait_loop

  rts


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

;--Saves Previous Values 
; (to see if we need a refresh)
; (called by CheckRefresh)
SavePrev:
  ldaa VOLH
  staa VOLHPRV
  ldaa VOLL
  staa VOLLPRV
  rts

;--Checks to see if the screen needs to 
;  be refreshed and sets the REFRESH bit
CheckRefresh:
  ldab #$00               ;Set refresh = 0 
  stab REFRESH
  ldaa VOLL               ;if VOLL or VOLH have changed
  cmpa VOLLPRV            ; goto do_refresh
  bne do_refresh
  ldaa VOLH
  cmpa VOLHPRV
  bne do_refresh
  bra skip_refresh        ;if we get here, display does not need updating
do_refresh:               
  ldab #$01
  stab REFRESH
skip_refresh:
  jsr SavePrev            ;Reset PRVs for next time
  rts

;Converts the unsigned 8-bit interger
;  in [D] ([B] = data, [A] = 00)
;  to a value between 0 to 5 and stores
;  the whole part in VOLH and the fraction
;  (0 to 99) in VOLL
Convert:

  ldaa #$05                ; (n * 5) / 256
  mul
  ldx #$0100
  idiv
 
  pshd
  tfr x,d
  stab VOLH
  puld

  lda #$64                 ; (n * 100) / 256
  mul
  ldx #$0100
  idiv
  tfr x,d
  stab VOLL

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
;  4 per whole number (WOLH)
;  2 if VOLL is greater than 50
;  1 if VOLL is a quarter step (>25,>75)
;   exmaple: 4.60: XXXXXXXXX
PrintXBars:
  ldaa VOLH
  adda #$01          ;Add 1 for start_xx loop to get final X
  ldab #CHARX
start_4x:            ;Whole number loop
  cmpa #$00      
  dbeq a,done_4x 
  jsr PrintAnX
  jsr PrintAnX
  jsr PrintAnX
  jsr PrintAnX
  bra start_4x
done_4x:
  ldaa VOLL          
  cmpa #$19          ;VOLL > 25 (one X)
  blt done_x
  jsr PrintAnX
  cmpa #$32          ;VOLL > 50 (XX)
  blt done_x
  jsr PrintAnX
  cmpa #$4B           ;VOL > 75 (XXX)
  blt done_x
  jsr PrintAnX
done_x:  
  rts

;--Prints an X WITHOUT clobbering registeres A or B
PrintAnX:
  pshd
  ldaa #$00
  ldab #CHARX
  jsr [PUTCHAR,PCR]
  puld
  rts


;define datatypes
VOLH       DB      $00   ;Whole number
VOLL       DB      $00   ;Tenth
VOLHPRV    DB      $00   ;Screen Refresh vars
VOLLPRV    DB      $00
REFRESH    DB      $01   ;Refresh if equal to 1
FORMAT     DB      "Voltage: %d.%02d  ",0
