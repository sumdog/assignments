
;Define Function
;GETCHAR EQU	$FE02
;PUTCHAR EQU	$F684

;Define Memory I/O
SREADY	 EQU	$00C4
SDATA 	 EQU	$00C7
SINMASK  EQU    $0020
SOUTMASK EQU    $0080

;Define ASCII 
KEYSS   EQU     $0053 ;S
KEYS    EQU     $0073 ;s
KEYLL   EQU     $004C ;L
KEYL    EQU     $006C ;l
KEYRR   EQU     $0052 ;R
KEYR    EQU     $0072 ;r
KEYGG   EQU     $0047 ;G
KEYG    EQU     $0067 ;g
KEYBS   EQU     $0008 ;(backspace)

  ORG	  $0800
  
;define datatypes
COUNT	   DW	   0
LAP	   DW	   0
CLOCKON    DB      0
LAPON      DB      0


;Primary Loop for program
;   1 - Check for any key actions
;   2 - Print output for user
;   3 - Wait remaining cycles
;   4 - Loop
Main:
            jsr KeyPoll
	    jsr AdjustTime
	    jsr ClearScreen
            jsr PrintTime
            jsr Wait
            bra Main

;Prints Register D to screen
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
; the counter
ClearScreen:
            ldd KEYBS
            ldab $07                   ;a = 7
	    dbeq b,clear_done          ;while a < 7; a--
	    jsr PutChar 
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
	    jsr PutChar
	    rts
	    
;Preforms time adjustments
AdjustTime:
            ldaa CLOCKON               ;A = (bool) clockon
	    cmpa #$0                   ;if(A = off)
	    beq clock_off              ;return
            ldd COUNT                  ;else increment counter
	    addd $0001
	    std COUNT
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
