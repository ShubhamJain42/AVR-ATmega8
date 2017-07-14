/*
 * ADC_2.c
 *
 * Created: 02-06-2017 11:54:46
 * Author : Shubham Jain
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define RS PC0
#define E PC1

void LCD_cmnd(unsigned char cmnd){
	PORTD &= 0x0F;
	PORTD |= (cmnd & 0xF0);
	PORTC &= (~(1<<RS));
	PORTC |= (1<<E);
	_delay_ms(10);
	PORTC &= (~(1<<E));
	
	PORTD &= 0x0F;
	PORTD |= (cmnd<<4);
	PORTC |= (1<<E);
	_delay_ms(10);
	PORTC &= (~(1<<E));
}

void LCD_data(unsigned char data){
	PORTD &= 0x0F;
	PORTD |= (data & 0xF0);
	PORTC |= (1<<RS);
	PORTC |= (1<<E);
	_delay_ms(10);
	PORTC &= (~(1<<E));
	
	PORTD &= 0x0F;
	PORTD |= (data<<4);
	PORTC |= (1<<E);
	_delay_ms(10);
	PORTC &= (~(1<<E));
}

void LCD_init(){
	LCD_cmnd(0x32);
	LCD_cmnd(0x28);
	LCD_cmnd(0x06);
	LCD_cmnd(0x0C);
	LCD_cmnd(0x01);
}
void LCD_string(unsigned char *str){
	int i=0;
	while(str[i]!='\0'){
		LCD_data(str[i]);
		i++;
	}
}

void LCD_display(int num){
	num=num>>1;
	if (num>137)
		num-=4;
	else if(num>100)
		num-=3;
	else if(num>61)
		num-=2;
	else if(num>24)
		num-=1;
		
	LCD_data(0x30+num/100);
	LCD_data(0x30+((num/10)%10));
	LCD_data(0x30+num%10);
	
	
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0x03;
	LCD_init();
	int a;
	while(1)
	{
		ADMUX = 0x42;
		ADCSRA = 0xA3;
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADIF)) != (1<<ADIF));
		
		LCD_cmnd(0x80);
		ADCSRA |= (1<<ADIF);
		a=ADC;
		
		LCD_string("TEMP1 : ");
		LCD_display(a);
		
		ADMUX = 0x43;
		ADCSRA = 0xA3;
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADIF)) != (1<<ADIF));
		LCD_cmnd(0xC0);
		ADCSRA |= (1<<ADIF);
		a=ADC;
		LCD_string("TEMP2 : ");
		LCD_display(a);
	}
}

