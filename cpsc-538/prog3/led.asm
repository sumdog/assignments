
; Program #3a / CPSC-538 / Dumas
;
;    written by Sumit Khanna
;
;

;Define D-Bug 12 Function
;PRINTF  EQU  $F686
SETUVEC EQU  $F69A
GETCHAR EQU  $F682

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

;Define ASCII 
MINUS   EQU  $2D

  ORG $0800

;Data Definitions
NEGBIT  DB  $00
NUMA    DB  $00
NUMB    DB  $00

;Primary Loop for program
;   1 - Check for any key actions
;   2 - Print output for user
;   3 - Wait remaining cycles
;   4 - Loop
Main:

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
IntTime:
            ldaa  #C7F                     ;Clear Interrupt Flag
            staa  TFLG1
            rti

;END Interurpt Functions---------------


;--Reads two digit number and possible - sign 
;  from SCI0
ReadNumbers:
   lda $02
get_loop:
   jsr [GETCHAR,PCR]
   cmpb #MINUS
   
   rts















