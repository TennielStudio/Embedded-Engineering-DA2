/*
 * DA2T3Ccode.c
 * Created: 3/13/2018 3:15:48 PM
 * Author : Tenniel Takenaka-Fuller
 */ 
// Implement task 1 using TIMER0. Count overflow occurrence if needed. No interrupts.

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL
#define LEDDDR DDRB
#define LEDPORT PORTB
#define LED_PIN PORTB2


int main(void)
{
	LEDDDR |= ( 1 << LED_PIN);
	LEDPORT &= ~( 1 << LED_PIN);
	
while (1) {	
	
	
	// 1. T = 1/8MHz = .125us
	// 2. .25ms delay / .125us = 20 clock cycles
	// 3. 256 - 20 = 236
	
	TCCR0A = 0;							// Chooses normal mode
	TCNT0 = 236;
	TCCR0B = (1 << CS02) | (1 << CS00); 
	// clock divided by 1024

	
	while (( TIFR0 & 0x01) == 0)
			{
			_delay_ms(2000); // creates a delay of 250,000 us 
			TCNT0 = 0;  // clears the counter 
			TIFR0 |= (1 << TOV0); // clears the overflow flag
			LEDPORT ^= (1 << LED_PIN); //toggles the pin
			}


	return 0;
	
}
}


