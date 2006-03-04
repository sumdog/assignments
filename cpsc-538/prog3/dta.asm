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


   ORG $0800

Main:
   jsr ReadInput
   jsr sciDisplayNum
   bra Main

sciDisplayNum:
   ldd HEXINPUT
   pshd
   ldd #DFORMAT
   jsr [PRINTF,PCR]
   rts

ReadInput:
   ldd #IFORMAT             ;Prompt User
   jsr [PRINTF,PCR]
   ldd #INBUF               ;Read User Input
   pshd
   ldd $0002
   jsr [GETLN,PCR]
   puld
   ldd #HEXINPUT            ;Convert input to Hex
   pshd
   ldd #INBUF
   jsr [SCNHEX,PCR]
   puld
   ;swi
   ;cmpb #$00                ;check for errors
   ;bne ri_goodnum
   ;ldd #EFORMAT
   ;jsr [PRINTF,PCR]
   ;bra ReadInput
;ri_goodnum:
   rts


IFORMAT  DB  CR,LF,"Input Hex Number: ",0
EFORMAT  DB  "Invalid Number",CR,LF,0
DFORMAT  DB  "Sending %X",CR,LF,0
HEXINPUT DW  $0000
INBUF    DS  $03