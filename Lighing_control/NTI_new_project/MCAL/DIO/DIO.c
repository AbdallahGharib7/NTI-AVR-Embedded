#include "STD_types.h"
#include "BitMath.h"
#include "DIO.h"

volatile u8* port_arr[12]={&PORTA,&PORTB,&PORTC,&PORTD, &DDRA,&DDRB,&DDRC,&DDRD, &PINA,&PINB,&PINC,&PIND};
	
void DIO_vSetPinMode(dio_channel_t channelID,dio_mode mode)
{
	u8 port_idx=channelID/8;
	u8 pin_idx=channelID%8;
	
	(mode == OUTPUT_HIGH)||(mode ==OUTPUT_LOW)     ? SET_BIT(*port_arr[port_idx+4],pin_idx):CLR_BIT(*port_arr[port_idx+4],pin_idx);
	(mode == OUTPUT_HIGH)||(mode ==INPUT_PULLUP) ? SET_BIT(*port_arr[port_idx],pin_idx)  :CLR_BIT(*port_arr[port_idx],pin_idx);
	
}

u8 DIO_u8GetPinValue(dio_channel_t channelID)
{
	u8 port_idx=channelID/8;
	u8 pin_idx=channelID%8;
	return GET_BIT(*port_arr[port_idx+8],pin_idx);
}
