#include "MemMap.h"
#include "STD_types.h"
#include "BitMath.h"

#include "SPI.h"
#include "LCD.h"

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void SPI_Init (SPI_Mode_type mode)
{
	//select mode master or slave
	if(mode == MASTER)
	{
		
		SET_BIT(SPCR,MSTR);
	}
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	
	//clock polarity
	CLR_BIT(SPCR,CPOL); //i selected rising as leadig edge
	
	//pre scaler
	CLR_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	
	
	//spi enable 
	SET_BIT(SPCR,SPE);
	
}

u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}


void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
	while(!GET_BIT(SPSR,SPIF));
	_delay_ms(10);
}

void SPI_SendString (u8* data_send)
{
	u8 i =0;
	do 
	{
		SPI_SendNoBlock(data_send[i]);
	} while (data_send[i++]);
	
}


u8 SPI_ReceivePeriodic(u8 *pdata)
{
	if(GET_BIT(SPSR,SPIF))
	{
		*pdata = SPDR;
		return 1;
	}
	else
	{
		return 0;
	}
}


static u8 counter =0;

u8 SPI_ReceiveString(u8 *data_recieve)
{
	//static u8 flag=0;
	
	
	
	if(SPI_ReceivePeriodic(&data_recieve[counter])==1)
	{
		LCD_goto(3,counter);
		LCD_WriteChar(data_recieve[counter]);
		LCD_goto(3,14);
		LCD_WriteChar((s32)data_recieve[counter]);
		
		if(data_recieve[counter]==0)
		{
			counter=0;
			return 1;
		}
		counter++;
	}

	return 0;
}