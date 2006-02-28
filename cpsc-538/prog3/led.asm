
; Program #3a / CPSC-538 / Dumas
;
;    written by Sumit Khanna
;
;

;Define D-Bug 12 Function
PRINTF  EQU  $F686
SETUVEC EQU  $F69A
GETCHAR EQU  $F682
;GETLN   EQU  $F688


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

;IO Ports for LEDs
DDRA   EQU   $0002                  ;Sets data direction (read/write)
DDRB   EQU   $0003
PORTA  EQU   $0000                  ;Data Memory Mapped I/O
PORTB  EQU   $0001


;ASCII
MINUS   EQU  $2D
SPACE   EQU  $20
CR      EQU  $0D
LF      EQU  $0A


  ORG $0800

;Primary Loop for program
;   1 - Check for any key actions
;   2 - Print output for user
;   3 - Wait remaining cycles
;   4 - Loop
Main:


main_loop: 
   ;jsr ReadNumbers
   ;jsr sciDisplayNumber
   ldaa #$FF                     ;Set all port A/B bits for writing
   staa DDRA
   staa DDRB

   ldaa #$02
   ldx  #PORTA
   staa 0,x

   wai                           ;loop and wait
   bra main_loop

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

   ;Enable TCRE and set Prescaler TMASK2 (p182,p183)
   ldaa #TCRE
   staa TMSK2

   ;Set TC7 (p187) -- This adjusts our time interval
   ldd  #$c350
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
   ldaa  #C7F                     ;Clear Interrupt Flag
   staa  TFLG1
   rti

;END Interurpt Functions---------------

;--Reads two digit number and possible - sign 
;  from SCI0
ReadNumbers:

   ;inform user
   ldd #IFORMAT
   jsr [PRINTF,PCR]

   ;read first char
   jsr [GETCHAR,PCR]
   cmpb #MINUS
   bne rn_positive
   ;negative number
   ldaa #$01
   staa NEGBIT
   jsr [GETCHAR,PCR]

rn_positive:
   
rn_error:
   ldaa #$01
   staa VNUM
rn_clean:

   ;read 3 chars from stdin
;   ldd #$0003
;   pshd
;   ldd #INBUF
;   jsr [GETLN,PCR]
;   puld
   
   ;parse out numeric values
;   ldx #INBUF                    ;x = *INBUF[0]
;   ldaa [0,x]
;   cmpa #MINUS                   ;if(x[0] == '-')
;   bne num_positive
;   ldaa #$00                     ;set negative bit and parse
;   staa NEGBIT
;   ldaa [1,x]
;   ldy  #NUMA
;   jsr checkStoreNum
;   ldaa [2,x]
;   ldy #NUMB
;   jsr checkStoreNum
;   bra num_done
;num_positive: 
;   ldaa #$01                     ;set positive bit and parse
;   staa NEGBIT
;   ldy #NUMA
;   jsr checkStoreNum
;   ldaa [1,x]
;   ldy #NUMB
;   jsr checkStoreNum
;num_done:
   rts

;--Converts and stores the value of
; an ASCII number
; Reg[A] = number to check
; Reg[y] = location to store number
; Mem[VNUM] = 1 = invalid (valid left unchanged)
checkStoreNum:
  cmpa #$30
  blt csn_error
  cmpa #$39
  bgt csn_error
  suba #$30
  staa [0,y]
csn_error:
   ldaa #$01
   staa VNUM
csn_done:
   rts

;--Shows number to be displayed on terminal/SCI0
sciDisplayNumber:
  lda NEGBIT
  cmpa #$01
  bne sdn_positive
  ldx #MINUS
sdn_positive:
  ldx #SPACE
  lda #$00
  ldb NUMB
  pshd
  ldb NUMA
  pshd
sdn_display:
  pshx
  ldd #DFORMAT
  jsr [PRINTF,PCR]
  puld
  puld
  puld
  rts

;Data Definitions
NEGBIT  DB  $00
NUMA    DB  $00
NUMB    DB  $00
VNUM    DB  $00
DFORMAT DB   CR,LF,"Displaying Number: %c x %d x %d",0
EFORMAT DB   "Error Invalid Number",CR,LF,0
IFORMAT DB   "Input Number: ",0











