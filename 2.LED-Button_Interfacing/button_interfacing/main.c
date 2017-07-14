/*
 * button_interfacing.c
 *
 * Created: 30-05-2017 12:26:04
 * Author : Shubham Jain
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{	DDRB = 0x18;
	DDRC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
	    if((PINC & 0x04)==0x04){
			PORTB = 0x00;
			if((PINC & 0x08)==0x08)
			PORTB = 0x00;
			else
			PORTB = 0x10;
		}
	    else
			PORTB = 0x08;
		
		
	 _delay_ms(5);
    }
}

