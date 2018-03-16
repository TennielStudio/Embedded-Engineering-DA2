
;
; DA2T2asm.asm
;
; Created: 3/15/2018 1:11:11 PM
; Author : Tenniel Takenaka-Fuller
; ((8MHz / 1024) * 1sec )-1 = 7812 = 1E84
 
 
 
.org 0
;-------------------------------------
;Initialize Values
;-------------------------------------
 
LDI R16, 4
SBI DDRB, 2 ;PB2 is an output
LDI R17, 0 ; use this to XOR to turn LED on
OUT PORTB, R17 ; initial off state
CBI DDRD, 2        ;PD2 is an input
LDI R20, 5
STS TCCR1B, R20


;-------------------------------------
; If button is high 
;------------------------------------
; turn on for one second (call a delay) then turn off


check:
	SBIS PIND, 2		; once pd2 is high, skips next instruction
	RJMP delay			; turn on the light & call a delay
	CBI PORTB, 2		; make portb2 low (off)
	RJMP check			; check again if the status is low
	

delay:
	EOR R17, R16		; ensures light turns on when button pressed
	OUT PORTB, R17		; outputs the press
	LDS R29, TCNT1H		; load the higher counter to r29
	LDS R28, TCNT1L		; load the lower counter to r28
	CPI R28, 0x84		; load the lower portion of timer to r28
	BRSH body			; brsh to the body to check higher bit
	RJMP delay			

body:
	CPI R29, 0x1E		; compare the high reg to the calculated value
	BRSH finish
	RJMP delay

finish:
; clears the counter
	LDI R20, 0x00
	STS TCNT1H, R20
	LDI R20, 0x00
	STS TCNT1L, R20
	RJMP check
