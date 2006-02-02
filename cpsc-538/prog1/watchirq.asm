
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
;  Note: all page numbers come from the
;        Motorola M68HC12 Data Sheet Manual
;         (Rev. 8 7.2003)
;

;Define D-Bug 12 Function
PRINTF  EQU  $F686
SETUVEC EQU  $F69A

;Define Timer Location
TIMER7  EQU  $10       ; Timer7 for D-Bug12 SetUserVector()
TIOCS   EQU  $80       ; In capt/out compare select
TSCR    EQU  $86       ; Timer System Control Register (p179)
TCTL1   EQU  $88       ; Timer In/Out Pins
TCTL2   EQU  $89
TCTL3   EQU  $8A
TCTL4   EQU  $8B
TMSK1   EQU  $8C       ; Timer mask reg
TMSK2   EQU  $8D       ; Timer Interrupt Mask 2 Register (p182)
TFLG1   EQU  $8E       ; TFLG1 offset
TC7     EQU  $9E       ; Timer compare register 7 (p187)
TEN     EQU  %10000000 ; Timer enable bit
C7F     EQU  %10000000 ; Output compare 2 Flag
C7I     EQU  C7F       ; Interrupt enable
IOS7    EQU  %10000000 ; Select OC2
TCRE    EQU  %00001100


;Define Memory I/O
SREADY	 EQU	$C4
SCTRL    EQU    $C3     ;SCI Control Register 2 (p209)
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
            ;Set keyinput Interrupt Handler
            ldd  #IntKey
            pshd
            ldd #$000B
            ldx SETUVEC
	    jsr 0,x
            puld
            ldaa #%00101100
            staa SCTRL

            ;Setup Timer Interrupt Handler
            ldd  #IntTime
            pshd
            ldd  #TIMER7
            ldx  SETUVEC
            jsr  0,x
            puld

            bset  TIOCS,IOS7  ;Bit to enable IOS7 in TIOS (p151)

            ;Disable I/O pins
            ldaa  #$0
            staa  TCTL1
            staa  TCTL2
            staa  TCTL3
            staa  TCTL4

            ;Enable TCRE and set Prescaler TMASK2 (p182,p183)
            ldaa  #TCRE
            staa  TMSK2


            ;Set TC7 (p187) -- This adjusts our time interval
            ldd	  #$c350
            std	  TC7

            ;Mask to enable TEN in TSCR (p153) (DO THIS LAST)
            ldaa  #C7F
            staa  TFLG1	          ; Clear C7F
            bset  TMSK1,C7I       ; Enable TC7 Interrupt
            ; Enable the Timer system
            bset  TSCR,TEN
            cli                   ; Unmask global interrupts

main_loop:                               
            wai                           ;loop and wait
            bra main_loop


;BEGIN Interurpt Functions---------------

;Called by Timer Interrupt
; * Adjusts time by 1ms
; * Clears Screen
; * Prints Time
; * Resets Timer Interrupt
IntTime:
            jsr AdjustTime
            jsr ClearScreen
            jsr PrintTime
            ldaa  #C7F                     ;Clear Interrupt Flag
            staa  TFLG1
            rti

;Called when a key is pressed and then calls
; appropiate function 
; (clears register B)
IntKey:
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
            rti

;END Interurpt Functions---------------

;BEGIN KEYBOARD FUNCTIONS--------------

;G/g - Starts the clock
StartClock:
            ldaa #$01
	    staa CLOCKON
            rti

;L/l - Starts or Stops the lap
StartStopLap:
            ;swi
            ldab LAPON
            cmpb #$01
            beq stoplap
            ldaa #$01         ;set lap bit
	    staa LAPON
            movb TSEC,LTSEC   ;copy current time to lap
	    movb SEC,LSEC
	    movb MIN,LMIN
            rti
stoplap:
            ldaa #$00
            staa LAPON
            rti

;S/s - Stops the clock
StopClock:
            ldaa #$00
	    staa CLOCKON
            rti

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
	    rti

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
