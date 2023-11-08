#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

#include "DIO.h"
#include "seg.h"



void seg_Init(void)
{
	DIO_vSetPinMode(SEG_A,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_B,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_C,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_D,OUTPUT_HIGH);	
	
	DIO_vSetPinMode(SEG_EN1,OUTPUT_LOW);
	DIO_vSetPinMode(SEG_EN2,OUTPUT_LOW);
	DIO_vSetPinMode(SEG_EN3,OUTPUT_LOW);
	DIO_vSetPinMode(SEG_EN4,OUTPUT_LOW);	
}

void seg_write_digit(u8 digit)
{
	switch(digit)
	{
		case 0: DIO_vSetPinMode(SEG_A,OUTPUT_LOW);  DIO_vSetPinMode(SEG_B,OUTPUT_LOW);  DIO_vSetPinMode(SEG_C,OUTPUT_LOW);  DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 1: DIO_vSetPinMode(SEG_A,OUTPUT_HIGH); DIO_vSetPinMode(SEG_B,OUTPUT_LOW);  DIO_vSetPinMode(SEG_C,OUTPUT_LOW);  DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 2: DIO_vSetPinMode(SEG_A,OUTPUT_LOW);  DIO_vSetPinMode(SEG_B,OUTPUT_HIGH); DIO_vSetPinMode(SEG_C,OUTPUT_LOW);  DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 3: DIO_vSetPinMode(SEG_A,OUTPUT_HIGH); DIO_vSetPinMode(SEG_B,OUTPUT_HIGH); DIO_vSetPinMode(SEG_C,OUTPUT_LOW);  DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 4: DIO_vSetPinMode(SEG_A,OUTPUT_LOW);  DIO_vSetPinMode(SEG_B,OUTPUT_LOW);  DIO_vSetPinMode(SEG_C,OUTPUT_HIGH); DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 5: DIO_vSetPinMode(SEG_A,OUTPUT_HIGH); DIO_vSetPinMode(SEG_B,OUTPUT_LOW);  DIO_vSetPinMode(SEG_C,OUTPUT_HIGH); DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 6: DIO_vSetPinMode(SEG_A,OUTPUT_LOW);  DIO_vSetPinMode(SEG_B,OUTPUT_HIGH); DIO_vSetPinMode(SEG_C,OUTPUT_HIGH); DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 7: DIO_vSetPinMode(SEG_A,OUTPUT_HIGH); DIO_vSetPinMode(SEG_B,OUTPUT_HIGH); DIO_vSetPinMode(SEG_C,OUTPUT_HIGH); DIO_vSetPinMode(SEG_D,OUTPUT_LOW);  break;
		case 8: DIO_vSetPinMode(SEG_A,OUTPUT_LOW);  DIO_vSetPinMode(SEG_B,OUTPUT_LOW);  DIO_vSetPinMode(SEG_C,OUTPUT_LOW);  DIO_vSetPinMode(SEG_D,OUTPUT_HIGH); break;
		case 9: DIO_vSetPinMode(SEG_A,OUTPUT_HIGH); DIO_vSetPinMode(SEG_B,OUTPUT_LOW);  DIO_vSetPinMode(SEG_C,OUTPUT_LOW);  DIO_vSetPinMode(SEG_D,OUTPUT_HIGH); break;
	}
}

//   4    3    2    1

void seg_write(u16  number)
{
	u8 digit1 = number%10;
	number/=10;
	u8 digit2 = number%10;
	number/=10;
	u8 digit3 = number%10;
	number/=10;
	u8 digit4 = number%10;
	
	
	
	DIO_vSetPinMode(SEG_EN1,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN2,OUTPUT_LOW);
	DIO_vSetPinMode(SEG_EN3,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN4,OUTPUT_HIGH);
	seg_write_digit(digit2);
	_delay_ms(SEG_DELAY);
	
	DIO_vSetPinMode(SEG_EN1,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN2,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN3,OUTPUT_LOW);
	DIO_vSetPinMode(SEG_EN4,OUTPUT_HIGH);
	seg_write_digit(digit3);
	_delay_ms(SEG_DELAY);
	
	DIO_vSetPinMode(SEG_EN1,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN2,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN3,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN4,OUTPUT_LOW);
	seg_write_digit(digit4);
	_delay_ms(SEG_DELAY);
	
	
	DIO_vSetPinMode(SEG_EN1,OUTPUT_LOW);
	DIO_vSetPinMode(SEG_EN2,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN3,OUTPUT_HIGH);
	DIO_vSetPinMode(SEG_EN4,OUTPUT_HIGH);
	seg_write_digit(digit1);
	_delay_ms(SEG_DELAY);
	
	
	
	
	
	
	  
	
}






