

#ifndef UART_SPI_M_H_
#define UART_SPI_M_H_

#include "DIO.h"

#define SS   PB4
#define MOSI PB5
#define MISO PB6
#define CLK  PB7

#define PB_MASTER PD2

#define RX  PD0
#define TX  PD1

void UART_SPI_MASTER_Init (void);
void UART_SPI_MASTER_Runnable (void);

void ex0_func(void);



#endif /* UART_SPI_M_H_ */