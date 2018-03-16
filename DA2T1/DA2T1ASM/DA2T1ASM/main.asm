; Tenniel Takenaka-Fuller
; Design Assignment 2 Task 1 Assembly 
; ((8Mhz / 1024) * .25) - 1 = 0x07A0

.org 0

LDI R16, 4
SBI DDRB, 2 ;PB2 is an output
LDI R17, 0 ; use this to XOR to turn LED on
OUT PORTB, R17
LDI R20, 5 ;Used to set the prescaler
STS TCCR1B, R20 ;Prescaler = 1024

;-------------------------------------
start:
RCALL makeDelay ;Create the delay
EOR R17, R16 ;XOR to toogle the led light
OUT PORTB, R17
RJMP start ; repeat as a while(1)

;-------------------------------------
makeDelay:
 LDS R29, TCNT1H ;Load the higher bit of counter to R29
 LDS R28, TCNT1L ;load the lower bit of counter to R28
 CPI R28, 0xA0 ;Compare lower bit to 0xA0
 BRSH body ; if the lower value is higher than 0xAO jump to compare high reg 
 RJMP makeDelay

 ;-------------------------------------
body:
 CPI R29, 0x07	; comparing if higher is 0x07
 BRSH finito
 RJMP makeDelay

 ;-------------------------------------
finito:
 LDI R20, 0x00
 STS TCNT1H, R20 ;resetting the counter to 0 for next round
 LDI R20, 0x00
 STS TCNT1L, R20 ;resetting the counter to 0 for next round
 RET