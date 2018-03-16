/*
 * DA2T2Ccode.c
 *
 * Created: 3/8/2018 4:48:11 PM
 * Author : Tenniel Takenaka-Fuller
 */


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PORTD2
#define BUTTONPIN PIND
#define BUTTONDDR DDRD 
#define BUTTONPORT PORTD

#define LEDDDR DDRB
#define LEDPORT PORTB
#define LED_PIN PORTB2

short checkButton();
int main(void)
{
	LEDDDR |= (1 << LED_PIN);	// Set LED to output
	LEDPORT &= ~(1 << LED_PIN); // Initial state of OFF
	
	BUTTONPORT |= (1 << BUTTON_PIN); // Internal pull-up
	
	while (1)
	{
		
		short buttonActivated = checkButton();
		if(buttonActivated)
		{
			
			LEDPORT |= (1 << PORTB2); // turn on light
			_delay_us(200); // 250 us
			_delay_us(200); // 250 us
			_delay_us(200); // 250 us
			_delay_us(200); // 250 us
			
		}
		else
			{
			
			LEDPORT &= ~(1 << PORTB2); // turn off light

		}
	}
	
	}



// De bounces button input
short checkButton()
{
	short matchValue = 0; // match counter
	
	while(!(PIND & (1 << BUTTON_PIN)) && // Check if button is still held down
	matchValue < 10) // Count to 10
	{
		matchValue++;
		_delay_ms(5);
		
	}
	// return true if button has been held for 50ms
	return (matchValue == 10);
}

