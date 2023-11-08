#include "Button.h"
#include "DIO.h"

pb_state_t Pushbutton_state(pb_id_t   button)//7,6,5,3
{
	pb_state_t  state=NOTPRESSED;
	switch(button)
	{
		case pd_1:
		state=DIO_u8GetPinValue(PD7);
		break;
		
		case pd_2:
		state=DIO_u8GetPinValue(PD6);
		break;
		
		case pd_3:
		state=DIO_u8GetPinValue(PD5);
		break;
		
		case pd_4:
		state=DIO_u8GetPinValue(PD3);
		break;
	}
	return state;
	
}//presses/not

void Pushbutton_setup(pb_id_t   button ) //init //pin-->inpull
{
	switch(button )
	{
		case pd_1:
		DIO_vSetPinMode(PD7,INPUT_PULLUP);
		break;
		
		case pd_2:
		DIO_vSetPinMode(PD6,INPUT_PULLUP);
		break;
		
		case pd_3:
		DIO_vSetPinMode(PD5,INPUT_PULLUP);
		break;
		
		case pd_4:
		DIO_vSetPinMode(PD3,INPUT_PULLUP);
		break;
	}
	
	
}//Input,