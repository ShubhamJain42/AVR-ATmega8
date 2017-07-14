/*
 * LCD_interface.c
 *
 * Created: 31-05-2017 18:55:37
 * Author : Shubham Jain
 */ 

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#define RS PC0
#define E PC1 

void LCD_cmnd(unsigned char cmd){
	PORTD = cmd;
	PORTC &= (~(1<<RS));	// to give PC = xxxxxxxRS = xxxxxxx0 (RS = 0 is command mode)
	PORTC |= (1<<E);		// to give PC = xxxxxxEx  = xxxxxx1x (E  = 1 is rising edge)
	_delay_ms(10);
	PORTC &= (~(1<<E));		// to give PC = xxxxxxEx  = xxxxxx0x (E  = 0 is falling edge)
}

void LCD_data(unsigned char data){
	PORTD = data;
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
	LCD_cmnd(0x38);			//Function Set: 8-bit, 2 Line, 5×7 Dots
	LCD_cmnd(0x06);			//Entry Mode: increment direction
	LCD_cmnd(0x0F);			//Display on Cursor on(not blinking)
	LCD_cmnd(0x01);			//Clear Display (also clear DDRAM content)
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x03;
	LCD_init();
    /* Replace with your application code */
    //while (1) 
    {
		//Using LCD_string function
		LCD_cmnd(0x80);
		char str="Shubham Jain";
		LCD_string((str));
		
		LCD_cmnd(0xC0);
		str = "IIT Patna";
		LCD_string(str);
		
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

