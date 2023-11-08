
#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

#include "STD_types.h"

void UART_SendString(u8 *str);
void UART_ReceiveString(u8*str);
void UART_ReceiveString2(u8*str);


void UART_SendNumber(u32 num);
u32 UART_ReceiveNumber(void);

typedef enum{
	BIG_ENDIAN,
	LITTLE_ENDIAN
	}ENDIAN_types;

ENDIAN_types endian_check(void);

u32 u32_endian_convert(u32 num);
u16 u16_endian_convert(u16 num);

void UART_SendStringCheckSum(u8* ptr);
u8 UART_ReceiveStringCheckSum(u8* str);

void UART_SendStringAsynch(u8 * str);
void UART_ReceiveStringAsynch(u8 * str);

void UART_ReceiveString_kit(u8*str);

#endif /* UART_SERVICE_H_ */