#include "Led.h"
#include "DIO.h"


void LED_Init(led_id_t  led_id)  //7,4,5,6//by default OUTPUT_LOW
{
	switch(led_id)
	{
		case RED_LED:
		DIO_vSetPinMode(PB7,OUTPUT_LOW);
		break;
		
		case GREEN_LED:
		DIO_vSetPinMode(PA4,OUTPUT_LOW);
		break;
		
		case BLUE_LED:
		DIO_vSetPinMode(PA5,OUTPUT_LOW);
		break;
		
		case YELLOW_LED:
		DIO_vSetPinMode(PA6,OUTPUT_LOW);
		break;
	}
	
	
}//out

void LED_setmode(led_id_t led_id,led_mode_t  mode)
{
	
	if(mode==HIGH)
	{
		switch(led_id)
		{
			case RED_LED:
			DIO_vSetPinMode(PB7,OUTPUT_HIGH);
			break;
			
			case GREEN_LED:
			DIO_vSetPinMode(PA4,OUTPUT_HIGH);
			break;
			
			case BLUE_LED:
			DIO_vSetPinMode(PA5,OUTPUT_HIGH);
			break;
			
			case YELLOW_LED:
			DIO_vSetPinMode(PA6,OUTPUT_HIGH);
			break;
		}
		
	}
	else //LOW
	{
		switch(led_id)
		{
			case RED_LED:
			DIO_vSetPinMode(PB7,OUTPUT_LOW);
			break;
			
			case GREEN_LED:
			DIO_vSetPinMode(PA4,OUTPUT_LOW);
			break;
			
			case BLUE_LED:
			DIO_vSetPinMode(PA5,OUTPUT_LOW);
			break;
			
			case YELLOW_LED:
			DIO_vSetPinMode(PA6,OUTPUT_LOW);
			break;
		}
	}
	
	}//high,low*/


void LED_toggle(led_id_t led_id)
{
	switch(led_id)
	{
		case RED_LED:
		DIO_u8GetPinValue(PB7) ? DIO_vSetPinMode(PB7,OUTPUT_LOW) : DIO_vSetPinMode(PB7,OUTPUT_HIGH);
		break;
		
		case GREEN_LED:
		DIO_u8GetPinValue(PA4) ? DIO_vSetPinMode(PA4,OUTPUT_LOW) : DIO_vSetPinMode(PA4,OUTPUT_HIGH);
		break;
		
		case BLUE_LED:
		DIO_u8GetPinValue(PA5) ? DIO_vSetPinMode(PA5,OUTPUT_LOW) : DIO_vSetPinMode(PA5,OUTPUT_HIGH);
		break;
		
		case YELLOW_LED:
		DIO_u8GetPinValue(PA6) ? DIO_vSetPinMode(PA6,OUTPUT_LOW) : DIO_vSetPinMode(PA6,OUTPUT_HIGH);
		break;
	}
}