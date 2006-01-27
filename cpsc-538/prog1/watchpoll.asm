  ORG	  $0800

;Define Function
GETCHAR EQU	$FE02
PUTCHAR EQU	$F684

;Define Memory I/O
BOOLIN	EQU	$00C4
DATAIN	EQU	$00C7

BOOLOUT EQU     $102E
DATAOUT EQU     $102F

;Define ASCII 
KEYSS   EQU     $0053 ;S
KEYS    EQU     $0073 ;s
KEYLL   EQU     $004C ;L
KEYL    EQU     $006C ;l
KEYRR   EQU     $0052 ;R
KEYR    EQU     $0072 ;r
KEYGG   EQU     $0047 ;G
KEYG    EQU     $0067 ;g

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
	    jsr ClearScreen
            jsr PrintTime
            jsr Wait
            bra Main


;Poll for a command and if present, call
; appropiate function 
; (clears register B)
KeyPoll:
            clrb                        
            brclr BOOLIN,$0020,key_ret ;Check to see if we have input
	    ldab DATAIN                ;Read in input
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
            nop
	    rts

;Prints the output
;  If(
PrintTime:
            nop
	    rts

;Loops nops for the remainder of time
;  if(CLOCKON) { increment COUNT }
;  if(LAPON)   { increment LAP }
Wait:
            nop
            rts

;BEGIN KEYBOARD FUNCTIONS--------------

;G/g - Starts the clock
StartClock:
            rts

;L/l - Starts or Stops the lap
StartStopLap:
            nop
            rts

;S/s - Stops the clock
StopClock:
            nop 
            rts

;R/r - Resets the counter 
;      (ignored of counter is running)
RestClock:
           nop
	   rts

;END KEYBOARD FUNCTIONS--------------
