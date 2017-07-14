/*
 * LED_DROP_DOWN.c
 *
 * Created: 29-05-2017 18:57:09
 * Author : Shubham Jain
 */ 


// PB0 LED1 -> Turn on the LED

#include <avr/io.h>
#include <util/delay.h>
//_delay_ms(1000);
//_delay_us(1000);


int main(void)
{
	DDRD = 0xFF;
	/* Replace with your application code */
	while (1){
		int i;
		int t1=0b10000000;
		int t2=0b00000001;
		for (i=0;i<7;i++){
			PORTD = t1+t2;
			t1 = t1>>1;
			t2 = t2<<1;
			if(i!=4)
			_delay_ms(500);
		}
		//_delay_ms(1000);
	}
}