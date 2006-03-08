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
PEAR    EQU  $0A


   ORG $0800

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

waitForConversion:
   ldaa PORTE
   anda #%00001000
   cmpa #%00001000
   beq complete
   ldd #BFORMAT
   jsr [PRINTF,PCR]
complete:
   ldd #CFORMAT
   jsr [PRINTF,PCR]
   rts


sciReadNum:
   ldd HEXOUT
   pshd
   ldd #RFORMAT
   jsr [PRINTF,PCR]
   puld
   rts

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

   jsr LongDelay

   ;WR/CS to high
   ldaa #%10110100
   staa PORTE
   nop
   nop
   nop
   nop

   ldaa #%10100100
   staa PORTE
   ;swi

   jsr waitForConversion

   ;pull CS/RD down
   ldaa #%00000100
   staa PORTE

   ;read from pins
   ldaa PORTT
   staa HEXOUT

   ldaa #$FF
   staa PORTE

   rts

sendDAC:
   ldaa #$FF               ;Set PORTT for writing
   staa DDRT
   ldaa #$FF         ;set WR/CS to high
   staa PORTE

   jsr LongDelay

   ldd  HEXINPUT           ;send data to converter
   stab PORTT

   jsr LongDelay

   ldaa #%11011011         ;Set WR/CS low
   staa PORTE

   jsr LongDelay
   ldaa #$FF         ;Bring them back high
   staa PORTE

   jsr waitForConversion

   rts

LongDelay:
   pshd
   ldd #$FFFF
ld_loop:
   nop
   nop
   nop
   nop
   nop
   dbne d,ld_loop   

   puld
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
CFORMAT  DB  "Conversion Complete",CR,LF,0
BFORMAT  DB  "Busy",CR,LF,0
HEXINPUT DW  $00
HEXOUT   DW  $00
INBUF    DS  $03