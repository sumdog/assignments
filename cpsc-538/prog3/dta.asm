; Program #3b / CPSC-538 / Dumas
;
;   written by Sumit Khanna
;
;   This program will take a user input of an
;   8-bit Hex value (00 - FF) and send it to 
;   a Digital-to-Analog converter, causing it
;   to produce a voltage between 0 and 2.5
;
;   The DTA also acts as an ATD, so the program
;   will also read from the ATD to take the output
;   voltage and return back the original hex values
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
;   CLK is hooked to resistor and capacitor
;    in parallel
;   
;

;Define D-Bug 12 Function
PRINTF  EQU  $F686
GETLN   EQU  $F688
SCNHEX  EQU  $F68A


;ASCII
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
;   1 - Read Input (handles errors in subroutine)
;   2 - Display Input we are going to send
;   3 - Send to DTA
;   4 - Get ATD
;   5 - Display result from ATD
;   6 - loop
Main:
   ldaa #%11110111         ;Set Busy read, rest write
   staa DDRE
   ldaa #%10010000         ;Set PORTE to normal I/O mode
   staa PEAR
main_loop:
   jsr ReadInput
   jsr sciDisplayNum
   jsr sendDAC
   jsr getADC
   jsr sciReadNum
   bra main_loop

;--Checks busy flag on ATD and 
;   only returns after busy flag
;   is cleared (conversion is complete)
waitForConversion:
   ldaa PORTE
   anda #%00001000
   cmpa #%00001000
   beq complete
   ldd #BFORMAT
   jsr [PRINTF,PCR]
   bra waitForConversion
complete:
   ldd #CFORMAT
   jsr [PRINTF,PCR]
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

   ;wait for busy to clear
   ;jsr waitForConversion

   rts

;--Read user HEX input
;   if input is invalid, error shown
;    and used asked to retype input
;   will only return upon valid input
ReadInput:
   ldd #IFORMAT             ;Prompt User
   jsr [PRINTF,PCR]
   ldd #$0002              ;Read User Input
   pshd
   ldd #INBUF
   jsr [GETLN,PCR]
   puld
   ldd #HEXINPUT            ;Convert input to Hex
   pshd
   ldd #INBUF
   jsr [SCNHEX,PCR]
   cmpb #$00                ;check for errors
   bne ri_goodnum
   puld
   ldd #EFORMAT
   jsr [PRINTF,PCR]
   bra ReadInput
ri_goodnum:
   puld
   rts

;Variables
IFORMAT  DB  "Input Hex Number: ",0
EFORMAT  DB  CR,LF,"Invalid Number",CR,LF,0
DFORMAT  DB  CR,LF,"Sending %X",CR,LF,0
RFORMAT  DB  "Recieved %X",CR,LF,0
CFORMAT  DB  "Conversion Complete",CR,LF,0
BFORMAT  DB  "Busy",CR,LF,0
HEXINPUT DW  $00  ;DTA Input value to send
HEXOUT   DW  $00  ;ATD Output value recieved
INBUF    DS  $03  ;Buffer for user input
