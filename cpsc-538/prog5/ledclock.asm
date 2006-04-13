;IO Ports for LEDs
DDRA   EQU   $0002                  ;Sets data direction (read/write)
DDRB   EQU   $0003
PORTA  EQU   $0000                  ;Data Memory Mapped I/O
PORTB  EQU   $0001

  ORG $0800

Main:
  ldaa #$FF
  staa DDRA
  staa DDRB
loop:
  ldaa #%00000011
  ldab #%00000011
  ;ldaa #$FF
  ;ldab #$FF
  staa PORTA
  stab PORTB

  ;ldaa #$00
  ;staa PORTA
  ;staa PORTB
  
  ;ldaa #%00000010
  ;ldab #%00000001
  ;staa PORTA
  ;stab PORTB

;  ldaa #$F

  bra loop