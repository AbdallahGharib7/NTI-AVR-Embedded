
#include "STD_types.h"
#include "UART.h"
#include "UART_Service.h"
#include "LCD.h"

void UART_SendString(u8 *str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}

void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[0]=UART_Receive();
	for(i=0 ; str[i]!=0x0d ;) //enter :ascii = 13= 0x0d
	{
		i++;	
		str[i]=UART_Receive();
	}
	str[i]=0;//null
}



void UART_ReceiveString_kit(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for (i=0;str[i]!=10;)//'#'  10     13
	{
		i++;
		str[i]=UART_Receive();
		
	}
	str[i-1]=0;
	//str[i]=0;
	
}
void UART_ReceiveString2(u8*str)
{
	s8 i=0;
	//str[i]=0x08;//clr
	
	while(str[i]==0x08)
	str[i]=UART_Receive();
	
	while(str[i]!=0x0D)//enter    // /n /r on docklight
	{	
		i++;	 
		str[i]=UART_Receive();
		if(str[i]==0x08)
		{
			if(i>0)
			{
				i-=2;
			}
			else
			{
				i=-1;
			}
// 			LCD_SetCursor(0,0);
// 			LCD_WriteNumber(i);
// 			LCD_WriteString("    ");
		}
		
	}
	str[i]=0;
}


void UART_SendNumber(u32 num)
{
	u8 i;
// 	u8 *pnum=&num;
// 	for(i=0;i<sizeof(num);i++)
// 	{
// 		UART_Send(*(pnum+i));
// 	}
	 
// 	 UART_SendNumber(*(pnum+1));
// 	 UART_SendNumber(*(pnum+2));
// 	 UART_SendNumber(*(pnum+3));
     
	 for(i=0;i<sizeof(num);i++)
	 {
		 UART_Send((u8)(num>>(8*i)));
	 }

}

u32 UART_ReceiveNumber(void)
{
	u32 number=0;
	//u8 *p= ((u8*)(&number));
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	
	number=b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	/*
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	*/
	return number; 
}


ENDIAN_types endian_check(void)
{
	u32 i=1;
	u8* p= (u8*)&i;
	
	if(*p == 1)
	{
		return LITTLE_ENDIAN;
	}
	else
	{
		return BIG_ENDIAN;
	}
}


u32 u32_endian_convert(u32 num)
{
	u8 b0=(u8)num;
	u8 b1=(u8)(num>>8);
	u8 b2=(u8)(num>>16);
	u8 b3=(u8)(num>>24);
	
	num=b3|((u32)b2<<8)|((u32)b1<<16)|((u32)b0<<24);
	/*  //there is a generic function
	u8*p=&num;
	u8 temp;
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	
	temp=p[1];
	p[1]=p[2];  
	p[2]=temp;
	
	*/
	return num;
}

u16 u16_endian_convert(u16 num)
{
	num=num<<8|num>>8;
	return num;
}

void UART_SendStringCheckSum(u8* str)
{
	u8 len;
	u16 sum=0;
	for(len=0;str[len];len++)
	{
		sum+=str[len];
	}
	UART_Send(len);
	UART_SendString(str);
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
	
}

u8 UART_ReceiveStringCheckSum(u8* str)
{
	u8 len =UART_Receive();
	u8 i;
	u8 b0,b1;
	u16 sumCalc=0,sumRec;
	for(i=0;i<len;i++)
	{
		str[i]=UART_Receive();
		sumCalc+=str[i];
	}
	b0=UART_Receive();
	b1=UART_Receive();
	sumRec=b0|((u16)b1<<8);
	if(sumCalc==sumRec)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

static void TX_Func(void);

static u8* TXstr;
//static u8 

void UART_SendStringAsynch(u8 * str)
{
	  UART_SendNoBlock(str[0]);
	  UART_TX_SetCallBack(TX_Func);
	  UART_TX_InterruptEnable();
	  TXstr=str;
}

static void TX_Func(void)
{
	static u8 i=1;
	if(TXstr[i]!=0)
	{
		UART_SendNoBlock(TXstr[i]);
		i++;
	}
	else
	{
		i=1;
		//UART_TX_InterruptDisable();
	}
}

static void RX_Func(void);
static u8  *RXstr;

void UART_ReceiveStringAsynch(u8 * str)
{
	UART_RX_SetCallBack(RX_Func);
	UART_RX_InterruptEnable();
	RXstr=str;
}


static void RX_Func(void)
{
	static u8 i=0;
	RXstr[i]=UART_ReceiveNoBlock();
	i++; 
// 	if(RXstr[i]!=0)
// 	{
// 		i++;
// 	}
// 	else
// 	{
// 		i=0;
// 	}
	
	
}





