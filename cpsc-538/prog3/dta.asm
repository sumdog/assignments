; Program #3b / CPSC-538 / Dumas
;
;   written by Sumit Khanna
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


   ORG $0800

Main:
   ldaa #$FF               ;Set PORT E for writing
   staa DDRE
main_loop:
   jsr ReadInput
   jsr sciDisplayNum
   jsr sendDAC
   bra main_loop:

sciDisplayNum:
   ldd HEXINPUT
   pshd
   ldd #DFORMAT
   jsr [PRINTF,PCR]
   puld
   rts

getADC:
   ldaa #$00               ;Set PORTT for reading
   staa DDRT

   rts

sendDAC:
   ldaa #$FF               ;Set PORTT for writing
   staa DDRT
   ldaa #$00               ;Reset DAC
   staa PORTE
   ldd  HEXINPUT           ;send data to converter
   stab PORTT
   ldaa #$FF               ;Tell DAC to update registers
   staa PORTE
   rts

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


IFORMAT  DB  "Input Hex Number: ",0
EFORMAT  DB  CR,LF,"Invalid Number",CR,LF,0
DFORMAT  DB  CR,LF,"Sending %X",CR,LF,0
RFORMAT  DB  "Recieved %X",CR,LF,0
HEXINPUT DW  $00
INBUF    DS  $03