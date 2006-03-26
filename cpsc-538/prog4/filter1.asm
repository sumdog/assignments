; Program #4a / CPSC-538 / Dumas
;
;   written by Sumit Khanna
;
;   This program will use the AD7569
;   to create a first-order, low-pass filter
;   with a cutoff of 500Mhz
;
;
;   M68HC12B32 Pin    AD7569 Pins
;   --------------    -----------
;   PT[0...7]         DB[0...7]
;   PE[7]             RD
;   PE[6]             ST
;   PE[5]             CS
;   PE[3]             BUSY
;   PE[2]             WR
;
;   AD7569 Other Pins
;   -----------------
;   RESET and RANGE are set to high
;   INT is set to ground
;   CLK is connected to resistor and capacitor
;    in parallel
;   
;

;Define D-Bug 12 Function
PRINTF  EQU  $F686
SETUVEC EQU  $F69A

;ASCII
CR      EQU  $0D
LF      EQU  $0A

;I/O Ports
PORTT   EQU  $AE
DDRT    EQU  $AF
PORTE   EQU  $08
DDRE    EQU  $09
PEAR    EQU  $0A

;Timer Constants
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
TCRE    EQU  %00001101


   ORG $0800

;--Main Entry Point
;   * Set read/write modes for ports
;   * Set PORTE to be a normal (vs specalized) port
;   * Setup Timers
;   * Wait
Main:
   ldaa #%11110111         ;Set Busy read, rest write
   staa DDRE
   ldaa #%10010000         ;Set PORTE to normal I/O mode
   staa PEAR
   ;jsr InitalizeTimer
main_loop:
   ;jsr getADC
   ;jsr sciReadNum
   ;ldaa HEXOUT
   ;staa HEXINPUT
   ;ldd  #$FFFF
   ;std HEXINPUT
   ;staa HEXINPUT
   ;stab HEXOUT
   ;jsr sciDisplayNum
   jsr getADC
   ldd HEXOUT
   tab
   std HEXINPUT
   jsr sendDAC
   bra main_loop

;--Called by Main procedure to start Timer
InitalizeTimer:
   ;Setup Timer Interrupt Handler
   ldd  #IntTime
   pshd
   ldd  #TIMER7
   ldx  SETUVEC
   jsr 0,x
   puld

   bset TIOCS,IOS7  ;Bit to enable IOS7 in TIOS (p151)

   ;Disable I/O pins
   ldaa #$0
   staa TCTL1
   staa TCTL2
   staa TCTL3
   staa TCTL4

   ;Enable TCRE and set Prescaler of 32 TMASK2 (p182,p183)
   ldaa #TCRE
   staa TMSK2

   ;Set TC7 (p187) -- This adjusts our time interval
   ldd  #$F424
   std  TC7

   ;Mask to enable TEN in TSCR (p153) (DO THIS LAST)
   ldaa  #C7F
   staa  TFLG1	          ; Clear C7F
   bset  TMSK1,C7I       ; Enable TC7 Interrupt
   ;Enable the Timer system
   bset  TSCR,TEN
   cli                   ; Unmask global interrupts
   rts

;BEGIN Interurpt Functions---------------

;Called by Timer Interrupt
IntTime:
   jsr getADC
   jsr filter
   jsr sendDAC
   rti


;--Checks busy flag on ATD and 
;   only returns after busy flag
;   is cleared (conversion is complete)
waitForConversion:
   ldaa PORTE
   anda #%00001000
   cmpa #%00001000
   beq complete
   ;ldd #BFORMAT
   ;jsr [PRINTF,PCR]
   bra waitForConversion
complete:
   ;ldd #CFORMAT
   ;jsr [PRINTF,PCR]
   rts

;--Displays number recieved from ATD
sciReadNum:
   ldd HEXOUT
   pshd
   ldd #RFORMAT
   jsr [PRINTF,PCR]
   puld
   rts

;--Displays number sent to DTA
sciDisplayNum:
   ldd HEXINPUT 
   pshd
   ldd #DFORMAT
   jsr [PRINTF,PCR]
   puld
   rts

;--Retrieves a voltage from the ATD
;   stores result in HEXOUT
getADC:
   ldaa #$00               ;Set PORTT for reading
   staa DDRT

   ;set ST to low
   ldaa #%10110100
   staa PORTE

   ;wait
   nop
   nop
   nop
   nop

   ;check busy
   jsr waitForConversion

   ;pull CS/RD to low
   ldaa #%00000100
   staa PORTE

   ;read from pins
   ldaa PORTT
   staa HEXOUT

   ;set all control signal back to high
   ldaa #$FF
   staa PORTE

   rts

;--sends hex value to DTA
;   only returns when conversion is complete
sendDAC:
   ldaa #$FF               ;Set PORTT for writing
   staa DDRT
   ldaa #$FF               ;set WR/CS to high
   staa PORTE


   ldd  HEXINPUT           ;send data to converter
   stab PORTT


   ldaa #%11011011         ;Set WR/CS low
   staa PORTE
  
   ldaa #$FF         ;Bring them back high
   staa PORTE

   rts

filter:
   ldaa HEXOUT       ;Load value we brought in
   ldab POUT         ;Load previous Output



   staa POUT         ;Store output for next cycle
   staa HEXIN        ;Filtered Value to send Back Out
   rts

;Variables
DFORMAT  DB  CR,LF,"Sending %X",CR,LF,0
RFORMAT  DB  "Recieved %X",CR,LF,0
CFORMAT  DB  "Conversion Complete",CR,LF,0
BFORMAT  DB  "Busy",CR,LF,0
HEXINPUT DW  $00  ;DTA Input value to send
HEXOUT   DW  $00  ;ATD Output value recieved
POUT     DB  $00  ;Previous Output
