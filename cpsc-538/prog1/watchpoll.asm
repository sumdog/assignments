
;Define D-Bug 12 Function
;PUTCHAR EQU	$F684
OUT4HEX  EQU   $F698
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
KEYBS   EQU     $08 ;(backspace)

  ORG $0800

;Primary Loop for program
;   1 - Check for any key actions
;   2 - Print output for user
;   3 - Wait remaining cycles
;   4 - Loop
Main:
            jsr KeyPoll
	    jsr AdjustTime
            jsr PrintTime
	    ;jsr ClearScreen
            ;jsr Wait
            bra Main

;Prints Register B to screen
PutChar:
            brclr SREADY,#SOUTMASK,PutChar
	    stab SDATA
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

;Prints enough backspaces to clear
; the counter (7 backspace chars)
ClearScreen:
            ldab #KEYBS 
            ldaa $07                   ;a = 7
clear_loop:
	    dbeq a,clear_done          ;while a < 7; a--
	    jsr PutChar
	    bra clear_loop 
clear_done:
	    rts

;Prints the output
PrintTime:
            ldaa LAPON                 ;A = (bool) lapon
	    cmpa #$1                   ;if (A = on)
	    beq show_lap               ; goto show_lap
            ldd COUNT                  ;else load count
	    bra show
show_lap:
            ldd LAP
show:
	    ;ldx OUT4HEX
	    ;jsr 0,x
	    ;jsr PutChar
	    ;tab
	    ;jsr PutChar
	    ;ldd #!4
	    ;pshd
	    ldd #FORMAT
	    ldx PRINTF
	    jsr 0,x
	    swi
	    ;jsr [PRINTF,PCR]
	    ;puld
	    rts
	    
;Preforms time adjustments
AdjustTime:
            ldaa CLOCKON               ;A = (bool) clockon
	    cmpa #$0                   ;if(A = off)
	    beq clock_off              ;return
	    inc COUNT
clock_off:
	    rts

;Loops nops for the remainder of time
Wait:
            nop
            rts

;BEGIN KEYBOARD FUNCTIONS--------------

;G/g - Starts the clock
StartClock:
            ldaa #$01
	    staa CLOCKON
            rts

;L/l - Starts or Stops the lap
StartStopLap:
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
	    ldd #$0000
	    std COUNT 
reset_ignore:
	    rts

;END KEYBOARD FUNCTIONS--------------


;define datatypes
COUNT	   DW	   $0000
LAP	   DW	   $0000
CLOCKON    DB      $00
LAPON      DB      $00
FORMAT     DB      "Eh",0
