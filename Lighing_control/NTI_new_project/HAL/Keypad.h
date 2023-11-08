
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "STD_types.h"
#include "DIO.h"

#define  ROW   4
#define  COL   4
#define  NO_KEY   'T'

typedef enum
{
	ROW1=PC5,
	ROW2=PC4,
	ROW3=PC3,
	ROW4=PC2,
	
	COL1=PC7,
	COL2=PC6,
	COL3=PD5,
	COL4=PD3
}row_col_t;

void Keypad_Init(void);
u8 keypad_getkey(void);

u8 keypad_getkey_No_Wait(void);





#endif /* KEYPAD_H_ */