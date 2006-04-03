; Program #4ab / CPSC-538 / Dumas
;
;   written by Sumit Khanna
;
;   This program will use the AD7569
;   to create a second-order filter
;   with a break of 125Mhz
;
;   Sampling at 10kHz   
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
;  2.5kHz Sampling (delay loop)

;ASCII constants
CR      EQU  $0D
LF      EQU  $0A

;I/O Ports
PORTT   EQU  $AE
DDRT    EQU  $AF
PORTE   EQU  $08
DDRE    EQU  $09
PEAR    EQU  $0A


   ORG $0800

;--Main Entry Point
;   * Set read/write modes for ports
;   * Set PORTE to be a normal (vs specalized) port
;   * Read Input
;   * Filter
;   * Send output
;   * Delay
;   * Loop
Main:
   ldaa #%11110111         ;Set Busy read, rest write
   staa DDRE
   ldaa #%10010000         ;Set PORTE to normal I/O mode
   
   ldd #$0000              ;Set Previous Output to 0 for
   std POUT

   staa PEAR
   
   ;initalize all values to zero
   ldaa #$00
   staa PIN
   staa POUT
   staa PPOUT

main_loop:
   jsr getADC
   jsr filter
   jsr sendDAC
   jsr Delay
   jsr Delay
   jsr Delay
   bra main_loop

;--Delay loop
;  (run 3 times to get 2500Hz samples
Delay:
   ldaa #$FF
d2: 
   deca
   bne d2
   rts


;--Retrieves a voltage from the ATD
;   stores result in SIGIN
getADC:
   ldaa #$00               ;Set PORTT for reading
   staa DDRT

   ;set ST to low
   ldaa #%10110100
   staa PORTE


   ;check busy
waitForConversion:
   ldaa PORTE
   anda #%00001000
   cmpa #%00001000
   beq complete
   bra waitForConversion
complete:
  
   ;pull CS/RD to low
   ldaa #%00000100
   staa PORTE

   ;read from pins
   ldaa PORTT
   staa SIGIN

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


   ldb  SIGOUT           ;send data to converter
   stab PORTT


   ldaa #%11011011         ;Set WR/CS low
   staa PORTE
  
   ldaa #$FF         ;Bring them back high
   staa PORTE

   rts

;--Function to handle filtering of input
filter:

   ;first coefficent
   ldab PIN
   ldaa #$08
   mul
   std TMPF

   ;2nd coefficent scaled by 100 (10kHz)
   ldab POUT
   ldaa #$9C
   mul
   addd TMPF
   std TMPF
  
   ;coefficent 3
   ldab PPOUT
   ldaa #$40
   mul
   std TMPS   

   ;subtract
   ldd TMPF
   subd TMPS

   ldx #$0064
   idiv
   pshx
   puld

   ;set output
   stab SIGOUT

   ;move everyting back one
   ldaa POUT
   stab POUT
   staa PPOUT
   ldaa SIGIN
   staa PIN
   
   rts

;Variables
SIGOUT  DB  $00  ;DTA Input value to send
SIGIN   DB  $00  ;ATD Output value recieved
PIN     DB  $00  ;Previous Input
POUT    DB  $00  ;Previous Output (T-1)
PPOUT   DB  $00  ;Previous Output (T-2)
TMPF    DW  $00  ;Temp 16-bit storage for formula
TMPS    DW  $00  ;Temp 16-bit storage for formula