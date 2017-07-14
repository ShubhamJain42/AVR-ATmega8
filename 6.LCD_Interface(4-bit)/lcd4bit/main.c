/*
 * lcd4bit.c
 *
 * Created: 01-06-2017 12:14:35
 * Author : Shubham Jain
 */ 

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#define RS PD0
#define E PD1 
//D4-D7 -> DB4-DB7
//D0->RS,D!->E


void LCD_cmnd(unsigned char cmd){
	//To send higher 4 bits
	PORTD &= 0x0F;
	PORTD |= (cmd & 0xF0);
	PORTC &= (~(1<<RS));	// to give PC = xxxxxxxRS = xxxxxxx0 (RS = 0 is command mode)
	PORTC |= (1<<E);		// to give PC = xxxxxxEx  = xxxxxx1x (E  = 1 is rising edge)
	_delay_ms(10);
	PORTC &= (~(1<<E));		// to give PC = xxxxxxEx  = xxxxxx0x (E  = 0 is falling edge)
	
	//To send lower 4 bits
	PORTD &= 0x0F;
	PORTD |= ((cmd<<4) & 0xF0);
	//PORTC &= (~(1<<RS));	// to give PC = xxxxxxxRS = xxxxxxx0 (RS = 0 is command mode)
	PORTC |= (1<<E);		// to give PC = xxxxxxEx  = xxxxxx1x (E  = 1 is rising edge)
	_delay_ms(10);
	PORTC &= (~(1<<E));		// to give PC = xxxxxxEx  = xxxxxx0x (E  = 0 is falling edge)
	
}

void LCD_data(unsigned char data){
	//To send higher 4 bits
	PORTD &= 0x0F;
	PORTD |= (data & 0xF0);
	PORTC |= (1<<RS);		// to give PC = xxxxxxxRS = xxxxxxx1 (RS = 1 is command mode)
	PORTC |= (1<<E);		// to give PC = xxxxxxEx  = xxxxxx1x (E  = 1 is rising edge)
	_delay_ms(10);
	PORTC &= (~(1<<E));		// to give PC = xxxxxxEx  = xxxxxx0x (E  = 0 is falling edge)

	//To send lower 4 bits
	PORTD &= 0x0F;
	PORTD |= ((data<<4) & 0xF0);
	PORTC |= (1<<RS);		// to give PC = xxxxxxxRS = xxxxxxx1 (RS = 1 is command mode)
	PORTC |= (1<<E);		// to give PC = xxxxxxEx  = xxxxxx1x (E  = 1 is rising edge)
	_delay_ms(10);
	PORTC &= (~(1<<E));		// to give PC = xxxxxxEx  = xxxxxx0x (E  = 0 is falling edge)
}

void LCD_string(unsigned char *str){
	int i;
	for(i=0;i<strlen(str);i++)
		LCD_data(str[i]);
}

void LCD_init(){
	LCD_cmnd(0x02);			//or use 0x32 : hint: lcd by default works in 8-bit mode
	LCD_cmnd(0x28);			//Function Set: 8-bit, 2 Line, 5×7 Dots
	LCD_cmnd(0x06);			//Entry Mode: increment direction
	LCD_cmnd(0x0C);			//Display on Cursor on(not blinking)
	LCD_cmnd(0x01);			//Clear Display (also clear DDRAM content)
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x03;
	LCD_init();
    /* Replace with your application code */
	int i;
    while (1) 
    {
		//Using LCD_string function
		LCD_cmnd(0x80);
		for (i=0;i<100;i++){
			LCD_data(0x30+i/10);
			LCD_data(0x30+i%10);	
			_delay_ms(1000);
			LCD_cmnd(0x01);
		}
		
		_delay_ms(1000);
		/*char str="Shubham Jain";
		LCD_string((str));
		
		LCD_cmnd(0xC0);
		str = "IIT Patna";
		LCD_string(str);
		*/
	//	LCD_data('S');

		// Using LCD_data function
		/*
		LCD_data('S');
		LCD_data('h');
		LCD_data('u');
		LCD_data('b');
		LCD_data('h');
		LCD_data('a');
		LCD_data('m');
		LCD_data(' ');
		LCD_data('J');
		LCD_data('a');
		LCD_data('i');
		LCD_data('n');
		
		LCD_cmnd(0xC0);
		LCD_data('I');
		LCD_data('I');
		LCD_data('T');
		LCD_data(' ');
		LCD_data('P');
		LCD_data('a');
		LCD_data('t');
		LCD_data('n');
		LCD_data('a');
		*/
    }
}


