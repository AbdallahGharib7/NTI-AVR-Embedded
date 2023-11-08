#include "Keypad.h"
#include "Led.h"
#include "Std_Types.h"

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

u8	arr_row[ROW]={ROW1,ROW2,ROW3,ROW4};
u8	arr_col[COL]={COL1,COL2,COL3,COL4};
extern u8 arr_keypad[ROW][COL];

void Keypad_Init(void)
{
	DIO_vSetPinMode(ROW1,OUTPUT_HIGH);
	DIO_vSetPinMode(ROW2,OUTPUT_HIGH);
	DIO_vSetPinMode(ROW3,OUTPUT_HIGH);
	DIO_vSetPinMode(ROW4,OUTPUT_HIGH);
	DIO_vSetPinMode(COL1,INPUT_PULLUP);
	DIO_vSetPinMode(COL2,INPUT_PULLUP);
	DIO_vSetPinMode(COL3,INPUT_PULLUP);
	DIO_vSetPinMode(COL4,INPUT_PULLUP);
}

u8 keypad_getkey(void)
{
	u8 key=NO_KEY;
	for(int i=0;i<ROW;i++)
	{
		DIO_vSetPinMode(arr_row[i],OUTPUT_LOW);
		for(int j=0;j<COL;j++)
		{
			if(DIO_u8GetPinValue(arr_col[j])==LOW)
			{
				key=arr_keypad[i][j];
// 				_delay_ms(1);
// 				while(DIO_u8GetPinValue(arr_col[j])==LOW);
				_delay_ms(35);
				
			}
			
		}
		DIO_vSetPinMode(arr_row[i],OUTPUT_HIGH);
	}
	return key;
}

u8 keypad_getkey_No_Wait(void)
{
	u8 key=NO_KEY;
	for(int i=0;i<ROW;i++)
	{
		DIO_vSetPinMode(arr_row[i],OUTPUT_LOW);
		for(int j=0;j<COL;j++)
		{
			if(DIO_u8GetPinValue(arr_col[j])==LOW)
			{
				key=arr_keypad[i][j];
			}
			
		}
		DIO_vSetPinMode(arr_row[i],OUTPUT_HIGH);
	}
	return key;
}