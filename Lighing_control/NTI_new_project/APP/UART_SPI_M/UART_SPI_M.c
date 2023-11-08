/* LIB */
#include "STD_types.h"
#include "BitMath.h"

/* MCAL */
#include "DIO.h"
#include "UART.h"
#include "SPI.h"
#include "EX_Interrupt.h"

/* HAL */
#include "LCD.h"
#include "Led.h"

/* SERVICE */
#include "UART_Service.h"

/* APP */
#include "UART_SPI_M.h"

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

volatile static u8 uart_arr[20];
volatile static u8 interrupt_arr[20];
volatile static u8 rx_finished_flag=0;


void uart_rx_func(void)
{
	static u8 counter=0;
	
	uart_arr[counter]=UART_ReceiveNoBlock();
	
	if(uart_arr[counter++] == 0x0d )
	{
		rx_finished_flag=1;
		uart_arr[counter]=0;
		counter=0;
	}
	
}

static u8 temp_arr[20];
static volatile u8 T_flag=0;

void UART_SPI_MASTER_Init (void)
{
	//uart
	DIO_vSetPinMode(RX,INPUT_NORMAL);
	DIO_vSetPinMode(TX,OUTPUT_HIGH);
	UART_Init();
	UART_RX_SetCallBack(uart_rx_func);
	UART_RX_InterruptEnable();
	
	//Button
	DIO_vSetPinMode(PB_MASTER,INPUT_PULLUP);
		
	//ex int 0 
	EXI_Init();
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_SetCallBack(EX_INT0,ex0_func);
	EXI_Enable(EX_INT0);
	
	
	
	//spi
	DIO_vSetPinMode(SS,OUTPUT_LOW);
	DIO_vSetPinMode(MOSI,OUTPUT_LOW);
	DIO_vSetPinMode(MISO,INPUT_NORMAL);
	DIO_vSetPinMode(CLK,OUTPUT_LOW);
	SPI_Init(MASTER);
	
	
	//LCD 
	LCD_Init();
	LCD_goto(0,0);
	LCD_WriteString("MASTER");
	
	
	GLOBAL_ENABLE();
}
u8 c1 =0;
void UART_SPI_MASTER_Runnable (void)
{
	if(rx_finished_flag==1)
	{
		for(u8 i=0;i<20;i++)
		{
			interrupt_arr[i]=uart_arr[i];
		}
		LCD_goto(1,0);
		LCD_WriteString(interrupt_arr);
		
		rx_finished_flag=0;
		SPI_SendString(interrupt_arr);
	}
	
	if(T_flag == 1)
	{
		
		//SPI_SendReceive('T');
		for(u8 i=0;i<20;i++)
		{
			//LCD_WriteChar(SPI_SendReceive('T'));
			temp_arr[i]=SPI_SendReceive('T'); 
			_delay_ms(10);
		}
			//temp_arr[i]=SPI_SendReceive('T'); 
			
		LCD_goto(1,19);
		LCD_WriteString(temp_arr);
		T_flag=0;
		
// 		for(u8 i = 0;i<20;i++)
// 		{
// 			temp_arr[i]=SPI_SendReceive('T');
// 			_delay_ms(10);
// 		}
		
// 		if(SPI_ReceivePeriodic(temp_arr[c1])==1)
// 		{
// 			if(temp_arr[c1++]==0)
// 			{
// 				LCD_goto(3,0);
//				LCD_WriteString(temp_arr);
// 				T_flag=0;
// 				c1=0;
// 			}
// 		}

// 		if(SPI_ReceiveString(temp_arr)==1)
// 		{
//  					LCD_goto(3,0);
//					LCD_WriteString(temp_arr);
//  					T_flag=0;
// 		}
	}
// 	LCD_goto(3,17);
// 	LCD_WriteNumber((s32)T_flag);
	
// 	LCD_goto(1,0);
// 	LCD_WriteString(temp_arr);
	
}



void ex0_func(void)
{
	
	T_flag=1;
}












