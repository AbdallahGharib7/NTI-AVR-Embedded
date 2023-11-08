#include "STD_types.h"
#include "BitMath.h"
#include "DIO.h"
#include "LCD.h"

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

void LCD_Init(void)
{	
// 	DIO_vSetPinMode(D4,OUTPUT_LOW);
// 	DIO_vSetPinMode(D5,OUTPUT_LOW);
// 	DIO_vSetPinMode(D6,OUTPUT_LOW);
// 	DIO_vSetPinMode(D7,OUTPUT_LOW);
// 	DIO_vSetPinMode(RS,OUTPUT_LOW);
	//DIO_vSetPinMode(EN,OUTPUT_HIGH);
	
	_delay_ms(50);
	LCD_WriteIns(0x02);
	LCD_WriteIns(0x28);
	LCD_WriteIns(0x0c);
	LCD_WriteIns(0x01);
	_delay_ms(1);
	LCD_WriteIns(0x06);
}



void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}
void LCD_WriteString(char *str)
{
	u8 i=0;
	while(str[i])
	{
		LCD_WriteChar(str[i++]);
	}
}

void LCD_WriteString_multiLine(u8 *str)
{
	#define MAX_DIGITS_IN_LINE    20
	#define MAX_LINES              4

	u8 line_counter=0;
	u8 in_line_counter=0;
	u8 i=0;
	u8 j=0;
	u8 temp_c=0;
	u8 lenth=0;
	LCD_goto(0,0);
	for(lenth=0;str[lenth];lenth++);
	while(j<lenth && line_counter<MAX_LINES)
	{
		temp_c=0;
		for(i=j;str[i]!=' ' && str[i];i++)
		{
			temp_c++;
		}
		if(!str[i])
		{
			i--;
		}
		
		if(temp_c+in_line_counter<=MAX_DIGITS_IN_LINE)
		{
			while(j<=i)
			{
				LCD_WriteChar(str[j++]);
				in_line_counter++;
			}
			
		}
		else
		{
			while((in_line_counter++)<MAX_DIGITS_IN_LINE)
			{
				LCD_WriteChar(' ');
			}
			line_counter++;
			in_line_counter=0;
			LCD_goto(line_counter,0);
		}
	}
	
}


void LCD_WriteNumber(s32 num)
{
	u8 i =0;
	s32 temp=0;
	
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	
	if(num<0)
	{
		num=-num;
		LCD_WriteChar('-');
	}
	
	
	for(i=0;num;i++)
	{
		temp = temp*10 + num%10;
		num/=10;
	}
	for(;i>0;i--)
	{
		LCD_WriteChar(temp%10 + '0');
		temp/=10;
	}
}


void LCD_goto(u8 line ,u8 cell)
{
	switch(line)
	{
		case 1: cell+=0x40 ;break;
		case 2: cell+=0x14 ;break;
		case 3: cell+=0x54 ;break;
		default: break;
	}
	LCD_WriteIns(0x80 | cell);

}

// void LCD_WriteBinary(s8 num);
// void LCD_WriteHex(s32 num);

// void LCD_WriteNumber_4D(u16 num);
// void LCD_WriteNumber_Digits(s32 num,u8 digit
/*void LCD_ClearCell(u8 line ,u8 cell,u8 num);*/
void LCD_Clear(void)
{
	LCD_WriteIns(0x01);
	_delay_ms(2);
}



void LCD_WriteIns(u8 ins)
{
	DIO_vSetPinMode(RS,OUTPUT_LOW);
	//DIO_vSetPinMode(EN,OUTPUT_LOW);
	
	DIO_vSetPinMode(D7,(GET_BIT(ins,7)));
	DIO_vSetPinMode(D6,(GET_BIT(ins,6)));
	DIO_vSetPinMode(D5,(GET_BIT(ins,5)));
	DIO_vSetPinMode(D4,(GET_BIT(ins,4)));
	
	DIO_vSetPinMode(EN,OUTPUT_HIGH);
	_delay_ms(1);
	DIO_vSetPinMode(EN,OUTPUT_LOW);
	_delay_ms(1);
	
	DIO_vSetPinMode(D7,(GET_BIT(ins,3)));
	DIO_vSetPinMode(D6,(GET_BIT(ins,2)));
	DIO_vSetPinMode(D5,(GET_BIT(ins,1)));
	DIO_vSetPinMode(D4,(GET_BIT(ins,0)));
	
	DIO_vSetPinMode(EN,OUTPUT_HIGH);
	_delay_ms(1);
	DIO_vSetPinMode(EN,OUTPUT_LOW);
	_delay_ms(1);
}
void LCD_WriteData(u8 data)
{
	DIO_vSetPinMode(RS,OUTPUT_HIGH);
	//DIO_vSetPinMode(EN,OUTPUT_LOW);
	
	DIO_vSetPinMode(D7,(GET_BIT(data,7)));
	DIO_vSetPinMode(D6,(GET_BIT(data,6)));
	DIO_vSetPinMode(D5,(GET_BIT(data,5)));
	DIO_vSetPinMode(D4,(GET_BIT(data,4)));
	
	DIO_vSetPinMode(EN,OUTPUT_HIGH);
	_delay_ms(1);
	DIO_vSetPinMode(EN,OUTPUT_LOW);
	_delay_ms(1);
	
	DIO_vSetPinMode(D7,(GET_BIT(data,3)));
	DIO_vSetPinMode(D6,(GET_BIT(data,2)));
	DIO_vSetPinMode(D5,(GET_BIT(data,1)));
	DIO_vSetPinMode(D4,(GET_BIT(data,0)));
	
	DIO_vSetPinMode(EN,OUTPUT_HIGH);
	_delay_ms(1);
	DIO_vSetPinMode(EN,OUTPUT_LOW);
	_delay_ms(1);
}