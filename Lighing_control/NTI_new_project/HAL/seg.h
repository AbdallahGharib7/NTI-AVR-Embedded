

#ifndef _SEG_H_
#define _SEG_H_


#include "STD_types.h"
#include "DIO.h"

#define SEG_A PB0
#define SEG_B PB1
#define SEG_C PB2
#define SEG_D PB4


#define SEG_EN1 PA3
#define SEG_EN2 PA2
#define SEG_EN3 PB5
#define SEG_EN4 PB6

#define SEG_DELAY 4

void seg_Init(void);
void seg_write_digit(u8);
void seg_write(u16);




#endif /* 7_SEG_H_ */