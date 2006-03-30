; Program #4ab / CPSC-538 / Dumas
;
;   written by Sumit Khanna
;
;   This program will use the AD7569
;   to create a second-order filter
;   with a break of 125Mhz
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
SETUVEC EQU  $F69A
PRINTF  EQU  $F686
GETCHAR EQU  $F682

;ASCII constants
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
TCRE    EQU  %00001101 ; Turn off prescaling and enable Timer Compare 7


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
   
   ldd #$0000              ;Set Previous Output to 0 for
   std POUT

   staa PEAR
   jsr AskFreq
   jsr InitalizeTimer
main_loop:
   wai
   bra main_loop


;--Sets frequency and coefficents
AskFreq:
   ldd #AFORMAT
   jsr [PRINTF,PCR]
   jsr [GETCHAR,PCR]
   
   ;select correct block based on user input
   cmpb #$31
   beq feq10
   cmpb #$32
   beq feq15
   cmpb #$33
   beq feq20
   cmpb #$34
   beq feq50
   
   ldd #EFORMAT
   jsr [PRINTF,PCR]
   bra AskFreq
   
feq10:
   ldy #$0019
   lda #$49
   ldb #$1B
   bra setfeq
feq15:
   ldy #$0010
   lda #$51
   ldb #$13
   bra setfeq
feq20:
   ldy #$000C
   lda #$55
   ldb #$0F
   bra setfeq
feq50:
   ldy #$0005
   lda #$5D
   ldb #$07

setfeq:
   sty CMP7
   sta COX
   stb CONX
   ldd #GFORMAT
   jsr [PRINTF,PCR]
   rts


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
   ldd  CMP7
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

;--Called by Timer Interrupt
; * Calls input function
; * Runs filtering 
; * Calls output function
IntTime:
   jsr getADC
   jsr filter
   jsr sendDAC
   rti


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

   ldab SIGIN       ;Load value we brought in

   ;multiple current input by 1 - coeffcent
   ldaa CONX
   mul
   std TMPF

   ;multiple previous output by coeffecent
   ldab POUT
   ldaa COX
   mul

   ;Add them together
   addd TMPF

   ;scale back down by 100
   ldx #$64
   idiv

   ;pull quoitent into D
   pshx
   puld

   ;save output and previous value
   stab POUT
   stab SIGOUT
   
   rts

;Variables
SIGOUT  DB  $00  ;DTA Input value to send
SIGIN   DB  $00  ;ATD Output value recieved
POUT    DB  $00  ;Previous Output (T-1)
PPOUT   DB  $00  ;Previous Output (T-2)
TMPF    DW  $00  ;Temp 16-storage for formula

AFORMAT DB "Frequency:",CR,LF,"1)10kHz",CR,LF,"2)15kHz",CR,LF,"3)20kHz",CR,LF,"4)50kHz",CR,LF,0
EFORMAT DB "Invalid",CR,LF,0
GFORMAT DB "Starting Filter",CR,LF,0
CMP7    DW $0000
COX     DB $00
CONX    DB $00
