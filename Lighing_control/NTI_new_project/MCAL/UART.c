#include "STD_types.h"
#include "MemMap.h"
#include "BitMath.h"



/* MCAL */
#include "UART.h"


static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;


void UART_Init(void)
{
	//set baud rate
	UBRRL = 103; //9600
	
	//1200
	//UBRRL=158;
	//UBRRH=1;
	
	//normal speed
	CLR_BIT(UCSRA,U2X);
	
	//frame   :  parity - Data length - stop
	/* by default frame no parity 1 stop 8 data*/
	

	//transmitter enable
	SET_BIT(UCSRB,TXEN);
	
	//receiver enable
	SET_BIT(UCSRB,RXEN);
}

void UART_Send(u8 data)
{
	while(GET_BIT(UCSRA,UDRE)==0)
	{
		
	}
	UDR=data;
}

u8 UART_Receive(void)
{
	while(GET_BIT(UCSRA,RXC)==0) //blocking
	{
		
	}
	return UDR;
}

u8 UART_ReceivePeriodic(u8* pdata)
{
	if(GET_BIT(UCSRA,RXC)) //there is data
	{
		*pdata = UDR;
		return 1;
	}
	else
	{
		return 0;
	}
	
}



void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}










u8* UART_FrameMaker(u8 data,u8 data_lenth,UART_PARITY_types parity,u8 stop_bits)
{
	static u8 frame[13]={0};
	u8 i=0,counter=0;
	frame[i]=0;
	
	for(;i<data_lenth;i++)
	{
		frame[i+1]=GET_BIT(data,i);
		if(GET_BIT(data,i)==1)
		{
			counter++;
		}
	}
	
	if(parity == ODD_PARITY)
	{
		if(counter%2)
		{
			frame[i]=1;
		}
		else
		{
			frame[i]=0;
		}
		i++;
	}
	else if(parity == EVEN_PARITY)
	{
		if(counter%2 == 0)
		{
			frame[i]=1;
		}
		else
		{
			frame[i]=0;
		}
		i++;
	}
	else if(parity == NO_PARITY)
	{
		
	}
	frame[i]=1;
	
	return frame;
}

