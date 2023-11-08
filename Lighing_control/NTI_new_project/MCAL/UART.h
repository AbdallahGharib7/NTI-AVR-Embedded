
#ifndef UART_H_
#define UART_H_

#include "STD_types.h"
 
void UART_Init(void);

void UART_Send(u8 data);
u8 UART_Receive(void);


u8 UART_ReceivePeriodic(u8* pdata);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_SendNoBlock(u8 data);
u8 UART_ReceiveNoBlock(void);





/**** mine ****/

typedef enum{
	NO_PARITY,
	ODD_PARITY,
	EVEN_PARITY
}UART_PARITY_types;

u8* UART_FrameMaker(u8 data,u8 data_lenth,UART_PARITY_types parity,u8 stop_bits);


#endif /* UART_H_ */