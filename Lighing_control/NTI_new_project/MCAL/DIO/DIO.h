

#ifndef DIO_H_
#define DIO_H_

#include "STD_types.h"
#include "BitMath.h"
#include "MemMap.h"

#include "DIO_cfg.h"
#include "DIO_prv.h"

typedef enum
{
	PA0,
	PA1,
	PA2,
	PA3,
	PA4,
	PA5,
	PA6,
	PA7,
	
	
	PB0,
	PB1,
	PB2,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,


	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5,
	PC6,
	PC7,

	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7

}dio_channel_t;

typedef enum
{
	OUTPUT_LOW,
	OUTPUT_HIGH,
	INPUT_NORMAL,
	INPUT_PULLUP
}dio_mode;

void DIO_vSetPinMode(dio_channel_t channelID,dio_mode mode);
u8 DIO_u8GetPinValue(dio_channel_t channelID);


#endif /* DIO_H_ */