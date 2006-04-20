;IO Ports for LEDs
DDRA   EQU   $0002                  ;Sets data direction (read/write)
DDRB   EQU   $0003
PORTA  EQU   $0000                  ;Data Memory Mapped I/O
PORTB  EQU   $0001
;PORT E for control signals (hour/min buttons)
PORTE   EQU  $08
DDRE    EQU  $09
PEAR    EQU  $0A

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
  ;setup Port direction
  ldaa #$FF
  staa DDRA
  staa DDRB


  ;setup Port E  
  ldaa #%10010000         ;Set PORTE to normal I/O mode
  staa PEAR
  ldaa #$00
  staa DDRE

  ;initalize clock to 12:00:00
  ldaa #$01
  ldab #$02
  stab HOURA
  staa HOURB
  
  ldaa #$00
  staa ICOUNT
  jsr InitalizeTimer
  
loop:

  jsr readButtons
  jsr ledDisplayTime  

  bra loop


;--Check for hour/minute button push
readButtons:
  ldaa PORTE
  staa BTMP
  cmpa #$9F
  beq state_off
state_on:
  ldaa KEYDOWN
  cmpa #$01
  beq button_skip
  bra button_continue
state_off:
  ldaa KEYDOWN
  cmpa #$00
  beq button_skip
  ldaa #$00
  staa KEYDOWN
  bra button_skip

button_continue:
  ldaa #$01
  staa KEYDOWN
  ldaa BTMP
  cmpa #$DF
  beq buttonMin
  cmpa #$BF
  beq buttonHour
  rts

buttonHour:
  ldaa HOURA
  inca
  staa HOURA
  jsr IncrementClock
  rts

buttonMin:
  ldaa MINNA
  inca
  staa MINNA
  jsr IncrementClock
button_skip:
  rts

;--Set Ports for LED output
ledDisplayTime:

   ;for(1 to 6; set appropiate light row)

   ;initalize loop
   ldx #SECA
   ldab #%00000001
   ldaa #$06

led_start_loop:
   
   ;check and save counter
   cmpa #$00
   beq led_done
   psha   

   ldaa 0,x
   jsr numToBits
   staa PORTA
   stab PORTB
   ldaa #$00
   staa PORTB
   lslb
   inx

   ;restore counter
   pula
   deca
   bra led_start_loop

led_done:
  
  rts

;--Sets number of bits for a number
;  
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

;--this was just eaier as it's own sub (called from IncrementClock)
AdjustDay:
   ldaa HOURA
   cmpa #$05
   bne no_day
   ldaa HOURB
   cmpa #$02
   bne no_day
   ldaa #$00
   staa SECA
   staa SECB
   staa MINNA
   staa MINNB
   staa HOURA
   staa HOURB
no_day
   rts



;--Ripples an increment throgh the clock
; *does not actually increment anything*
IncrementClock:

   ;for(1 to 6; set appropiate light row)

   ;initalize loop
   ldx #SECA
   ldy #SECB
   ldab #$06

iclock_start_loop:
   
   ;check loop
   cmpb #$00
   beq iclock_done

   ;check if counter is even or odd
   tfr b,a
   anda #%00000001
   cmpa #$00000001
   beq iclock_odd
   ldaa #$0A
   bra iclock_set

iclock_odd:
   ldaa #$06

iclock_set:

   jsr AdjustWithCarry

   inx
   iny

   ;restore counter
   decb
   bra iclock_start_loop

iclock_done:
  jsr adjustDay
  rts



;BEGIN Interurpt Functions---------------

;Called by Timer Interrupt
IntTime:
   ldaa ICOUNT                   ;4 Interrurpts = 1 second
   cmpa #$03                     ; so count and skip code
   beq  secmark                    ; block for ICOUNT<3
   inca
   staa ICOUNT
   bra intdone
 
secmark:
   ldab #$00                     ;Reset Interrurpt counter
   stab ICOUNT

   ;stuff here
   ldaa SECA
   adda #$01
   staa SECA
   jsr IncrementClock
   ;jsr debugDisplayTime


intdone:
   ldaa  #C7F                     ;Clear Interrupt Flag
   staa  TFLG1
   rti

;END Interurpt Functions---------------

;Variables
ICOUNT  DB $00	;Interrurpt counter (4 = 1 second)
BTMP    DB $00
KEYDOWN DB $00
SECA    DB $00
SECB    DB $00
MINNA   DB $00
MINNB   DB $00
HOURA   DB $00
HOURB   DB $00
DFORMAT DB "%d%d:%d%d:%d%d",CR,LF,0