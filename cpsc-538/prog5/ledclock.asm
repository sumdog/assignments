;IO Ports for LEDs
DDRA   EQU   $0002                  ;Sets data direction (read/write)
DDRB   EQU   $0003
PORTA  EQU   $0000                  ;Data Memory Mapped I/O
PORTB  EQU   $0001

;D-bug12 functions
SETUVEC EQU  $F69A
PRINTF  EQU  $F686

;ASCII constants
CR      EQU  $0D
LF      EQU  $0A

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
TCRE    EQU  %00001101

  ORG $0800

Main:
  ldaa #$FF
  staa DDRA
  staa DDRB
  
  ;initalize clock to 12:00:00
  ldaa #$01
  ldab #$02
  stab HOURA
  staa HOURB
  
  jsr InitalizeTimer
  
loop:

  jsr ledDisplayTime
  
  bra loop


ledDisplayTime:

  ;digit 1 (second)
  ldaa SECA
  jsr numToBits
  ldab #%00000001
  staa PORTA
  stab PORTB
  ldab #$00
  stab PORTB
  
  ;digit 2 (second)
  ldaa SECB
  jsr numToBits
  ldab #%00000010
  staa PORTA
  stab PORTB
  ldab #$00
  stab PORTB
  
  ;digit 3 (minute)
  
  ;digit 4 (minute)
  
  ;digit 5 (hour)
  
  ;digit 6 (hour)
  
  rts


numToBits:
  ;cmpa #$00
  ;jsr zero
  cmpa #$01
  beq one
  cmpa #$02
  beq two
  cmpa #$03
  beq three
  cmpa #$04
  beq four
  cmpa #$05
  beq five
  cmpa #$06
  beq six
  cmpa #$07
  beq seven
  cmpa #$08
  bge eight

zero:
  ldaa #%00000000
  rts
one:
  ldaa #%10000000
  rts
two:
  ldaa #%11000000
  rts
three:
  ldaa #%11100000
  rts
four:
  ldaa #%11110000
  rts
five:
  ldaa #%11111000
  rts
six:
  ldaa #%11111100
  rts
seven:
  ldaa #%11111110
  rts
eight:
  ldaa #%11111111
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

debugDisplayTime:
   ldaa #$00
   ldab SECA
   pshd
   ldab SECB
   pshd
   ldab MINNA
   pshd
   ldab MINNB
   pshd
   ldab HOURA
   pshd
   ldab HOURB
   pshd
   ldd #DFORMAT
   jsr [PRINTF,PCR]
   puld
   puld
   puld
   puld
   puld
   puld
   rts


IncrementClock:
   ldaa SECA
   inca
   staa SECA

   ;seconds
   ldx  #SECA
   ldy  #SECB
   ldaa #$0A
   jsr AdjustWithCarry

   ;sec to min
   tfr  y,x
   ldy  #MINNA
   ldaa #$06
   jsr AdjustWithCarry

   ;minutes
   tfr y,x
   ldy #MINNB
   ldaa #$0A
   jsr AdjustWithCarry

   ;min to hour
   tfx y,x
   ldy #HOURA
   ldaa #$06
   jsr AdjustWithCarry
   
   ;check for day, else adjust hours
   ldab HOURA
   cmpb #$05
   bge hours
   ldaa #$00
   staa SECA
   staa SECB
   staa MINNA
   staa MINNB
   staa HOURA
   staa HOURB
   rts
   
   ;hours
hours:
   tfx y,x
   ldy #HOURB
   ldaa #$0A
   jsr AdjustWithCarry

   rts


;BEGIN Interurpt Functions---------------

;Called by Timer Interrupt
IntTime:
   ldab ICOUNT                   ;4 Interrurpts = 1 second
   cmpb #$03                     ; so count and skip code
   bge secmark                    ; block for ICOUNT<3
   incb
   stab ICOUNT
   rti
 
secmark:
   ldab #$00                     ;Reset Interrurpt counter
   stab ICOUNT

   ;stuff here
   jsr debugDisplayTime
   jsr IncrementClock

   ldaa  #C7F                     ;Clear Interrupt Flag
   staa  TFLG1
   rti

;END Interurpt Functions---------------

;Variables
ICOUNT  DB $00	;Interrurpt counter (4 = 1 second)
SECA    DB $00
SECB    DB $00
MINNA   DB $00
MINNB   DB $00
HOURA   DB $00
HOURB   DB $00
DFORMAT DB "%d%d:%d%d:%d%d",CR,LF,0