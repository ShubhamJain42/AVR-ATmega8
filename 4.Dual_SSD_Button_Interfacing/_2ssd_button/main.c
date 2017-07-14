/*
 * _2ssd_button.c
 *
 * Created: 30-05-2017 20:45:50
 * Author : Shubham Jain
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		DDRC = 0x03;
	    DDRD = 0xFF;
	    PORTD = 0x00;
	    char ssd_val[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
	    DDRB = 0x00;
	    /* Replace with your application code */
	    int i = 0,j=0;
	    while (1)
	    {	
		    if((PINB & 0x04)==0x00){
			    while((PINB & 0x04)==0x00);		// infinite loop untill button is released
				i++;
		    }			
			if(i==10){
				j++;
				i=0;
			}
			PORTC = 0x02;
			PORTD = ssd_val[j%10];
			_delay_ms(10);
			
			PORTC = 0x01;
			PORTD = ssd_val[i];
			_delay_ms(5);
			
	    }
    }
}