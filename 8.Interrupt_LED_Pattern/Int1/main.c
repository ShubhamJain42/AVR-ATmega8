/*
 * Int1.c
 *
 * Created: 04-06-2017 21:03:59
 * Author : Shubham Jain
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{	DDRD = 1<<PD2;		// Set PD2 as input (Using for interrupt INT0)
	PORTD = 1<<PD2;		// Enable PD2 pull-up resistor
	DDRB = 0xFF;
	MCUCR = 0x03;
	GICR = (1<<INT0);
	GIFR = (1<<INT0);
	sei();
    /* Replace with your application code */
    while (1) 
    {
		
		int i;
		for(i=0;i<8;i++){
			PORTB = 1 << i;
			_delay_ms(500);
		}
    }
}

ISR(INT0_vect){
	int i,tmp;
	tmp=PORTB;
	PORTB = 0x00;
	for(i=0;i<10;i++){
		PORTB ^= 0xFF;
		_delay_ms(500);
		//PORTB = 0x00;
		//_delay_ms(500);
	}
	PORTB = tmp;
}