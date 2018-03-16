/*
 * DA2T4Ccode.c
 *
 * Created: 3/14/2018 2:57:51 PM
 * Author : Tenniel Takenaka-Fuller
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


#define F_CPU 8000000UL
#define LEDDDR DDRB
#define LEDPORT PORTB
#define LED_PIN PORTB2

int main(void)
{
	LEDDDR |= (1 << LED_PIN); // enable led as output
	TCCR0B |= (1 << CS02) | (1 << CS00); // clock divided by 256
	TIMSK0 |= (1 << TOIE0); // enable interrupt on overflow
	sei(); // turns on interrupts
	while (1)
	{
		// do nothing
	}
}
// called after overflow of timer.
// inverts LED state
ISR(TIMER0_OVF_vect)
{
	_delay_ms(1740); // delay to allow LED to blink
	
	if(LEDPORT & (1 << LED_PIN)) // if LED is on
	LEDPORT &= ~(1 << LED_PIN); // turn led off
	else
	LEDPORT |= (1 << LED_PIN); // otherwise turn led on
	
}
