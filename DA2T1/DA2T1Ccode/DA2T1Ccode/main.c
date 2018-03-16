/*
 * DA2T1Ccode.c
 *part 2: page 226
 * Created: 3/8/2018 4:29:08 PM
 * Author : Tenniel Takenaka-Fuller
 */ 

#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
	DDRB |= (1 << PORTB2); // port B 2 is an output 
	PORTB &= ~(1 << PORTB2); 
	

    while (1) 
    {
		PORTB |= (1 << PORTB2);		// set port b 2 
		_delay_ms(2000);	
		PORTB &= ~(1 << PORTB2);		// clear port b 2 
		_delay_ms(2000); 
		
	}
	return 0;
}
