/*
 * DA2T5Ccode.c
 *
 * Created: 3/14/2018 3:50:50 PM
 * Author : Tenniel Takenaka-Fuller
 */ 
// Implement task 2 using INT0 interrupt mechanism
// 

#define F_CPU 8000000UL // CPU Frequence

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_FAST 100
#define BLINK_DELAY_SLOW 500

#define BUTTON_PIN PORTD2
#define BUTTONPIN PIND
#define BUTTONDDR DDRD
#define BUTTONPORT PORTD

#define LEDDDR DDRB
#define LEDPORT PORTB
#define LED_PIN PORTB2

volatile short goFast = 0;
void Delay();
int main(void)
{
	LEDDDR |= (1 << LED_PIN); // Enable LED as output
	LEDPORT &= ~(1 << LED_PIN);
	
	BUTTONPORT |= (1 << BUTTON_PIN); // Internal pull-up
	
	EICRA |= (1 << ISC01);    // set INT0 to trigger on falling edge
	EIMSK |= (1 << INT0);     // Turns on INT0
	sei();		// enables interrupts
	
	// While loop flashes LED at a variable rate
	while (1)
	{
		LEDPORT &= ~(1 << LED_PIN); // Turn off led
		_delay_ms(250);
		LEDPORT |= (1 << LED_PIN); // Turn on led
		_delay_ms(250);
	}
}

ISR(INT0_vect)
{
	LEDPORT |= (1 << LED_PIN); // Turn on led
	_delay_ms(700); // delay to "debounce"
}