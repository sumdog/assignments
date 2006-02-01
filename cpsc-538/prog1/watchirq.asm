
; Program #1 / CPSC-538 / Dumas
;
;    written by Sumit Khanna
;
;  This is a simple stopwatch program written 
;  for the HC12. It should be assembled using 
;  asm12.exe that comes with MGTEK MiniIDE.
;
;  G - Starts the stopwatch
;  S - Stops the stopwatc
;  L - Sets the Lap
;  R - Resets the Stopwatch (only when stopped)
;
;  This program uses interurpts. See watchpoll.asm
;  for an example that uses a wait loop
;

;Define D-Bug 12 Function
PRINTF   EQU   $F686

;Define Memory I/O
SREADY	 EQU	$C4
SDATA 	 EQU	$C7
SINMASK  EQU    $20
SOUTMASK EQU    $80

;Define ASCII 
KEYSS   EQU     $53 ;S
KEYS    EQU     $73 ;s
KEYLL   EQU     $4C ;L
KEYL    EQU     $6C ;l
KEYRR   EQU     $52 ;R
KEYR    EQU     $72 ;r
KEYGG   EQU     $47 ;G
KEYG    EQU     $67 ;g
KEYCR   EQU     $0D ;(Return)

  ORG $0800

;Primary Loop for program
;   1 - Check for any key actions
;   2 - Print output for user
;   3 - Wait remaining cycles
;   4 - Loop
Main:
            wai


;BEGIN Interurpt Functions-------------

TimeShift:
            jsr AdjustTime
            jsr ClearScreen
            jsr PrintTime
            rts

;Poll for a command and if present, call
; appropiate function 
; (clears register B)
KeyPoll:
            clrb                        
            brclr SREADY,#SINMASK,key_ret ;Check to see if we have input
	    ldab SDATA                 ;Read in input
            cmpb #KEYSS                ;Start comparison of keys
            beq StopClock
            cmpb #KEYS
            beq StopClock
            cmpb #KEYLL
            beq StartStopLap
            cmpb #KEYL
            beq StartStopLap
            cmpb #KEYRR
            beq RestClock
            cmpb #KEYR
            beq RestClock
            cmpb #KEYGG
            beq StartClock
            cmpb #KEYG
            beq StartClock
key_ret                                ;no input or unrecognized key
            rts

;END Interurpt Functions---------------

;BEGIN KEYBOARD FUNCTIONS--------------

;G/g - Starts the clock
StartClock:
            ldaa #$01
	    staa CLOCKON
            rts

;L/l - Starts or Stops the lap
StartStopLap:
            ldab LAPON
            cmpb #$01
            beq stoplap
            ldaa #$01         ;set lap bit
	    staa LAPON
            movb TSEC,LTSEC   ;copy current time to lap
	    movb SEC,LSEC
	    movb MIN,LMIN
            rts
stoplap:
            ldaa #$00
            staa LAPON
            rts

;S/s - Stops the clock
StopClock:
            ldaa #$00
	    staa CLOCKON
            rts

;R/r - Resets the counter 
;      (ignored of counter is running)
RestClock:
            ldaa CLOCKON
	    cmpa #$01
	    beq reset_ignore
	    clr TSEC
	    clr SEC
	    clr MIN
reset_ignore:
	    rts

;END KEYBOARD FUNCTIONS--------------

;Prints Register B to screen
PutChar:
            brclr SREADY,#SOUTMASK,PutChar
	    stab SDATA
            rts

;Clears the screen by
; sending a CR (without a LF)
ClearScreen:
            ldab #KEYCR 
 	    jsr PutChar
	    rts

;Prints the output
PrintTime:
            ldaa #$00                  ;clear high bit of D
            ldab LAPON                 ;B = (bool) lapon
	    cmpb #$1                   ;if (B = on)
	    beq show_lap               ; goto show_lap
            ldab TSEC                  ;Load ms, s and min
            pshd
            ldab SEC
            pshd
            ldab MIN
            pshd
	    bra show
show_lap:
            ldab LTSEC                 ;Load Lap ms, s and min
            pshd
            ldab LSEC
	    pshd
	    ldab LMIN
	    pshd
show:
	    ldd #FORMAT                
	    ldx PRINTF
	    jsr 0,x
	    puld
	    puld
	    puld
	    rts
	    
;Preforms time adjustments
AdjustTime:
            ldaa CLOCKON               ;A = (bool) clockon
	    cmpa #$0                   ;if(A = off)
	    beq clock_off              ;return
	    inc TSEC
	    ;handle m-seconds
	    ldx #TSEC
	    ldy #SEC
	    ldaa #$0A
	    jsr AdjustWithCarry
	    ;handle seconds
	    ldx #SEC
	    ldy #MIN
	    lda #$3C
	    jsr AdjustWithCarry
	    
clock_off:
	    rts

;Adjusts and carry
; X = Mem location of Adjust
; Y = Mem location of cary
; A = amount to break
;
;   example: mem[X] = 10
;            mem[Y] = 12
;                A  = 10
;   returns: mem[X] = 0
;            mem[Y] = 13
AdjustWithCarry:
	    cmpa 0,x
	    bne adjustcontinue
	    inc 0,y
	    clr 0,x
adjustcontinue:
            rts



;define datatypes
CLOCKON    DB      $00
LAPON      DB      $00
FORMAT     DB      "%02d:%02d.%1d",0
TSEC       DB      $00
SEC        DB      $00
MIN        DB      $00
LTSEC      DB      $00
LSEC       DB      $00
LMIN       DB      $00
