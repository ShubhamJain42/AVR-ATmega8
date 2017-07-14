/*
 * ssd_button.c
 *
 * Created: 30-05-2017 19:51:12
 * Author : Shubham Jain
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	char ssd_val[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
	DDRB = 0x00;
    /* Replace with your application code */
    int i = 0;
	while (1) 
    {	
		if((i & 10) == 10)		// or use i%10
			i=0;
		if((PINB & 0x04)==0x00){	// or use while((PINB & 0x04)==0x00); i.e. infinite loop till button is pressed
		_delay_ms(500);
			if((PINB & 0x04)==0x04)
				i++;
		}
		PORTD = ssd_val[i];
		_delay_ms(10);
    }
}

