
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "STD_types.h"
#include "DIO.h"


#define TRIGGER  PD7

typedef enum{
	ULTRASONIC_1=PD7,
	ULTRASONIC_2=PD2,
	ULTRASONIC_3=PD3,
	ULTRASONIC_4=PD4,
}ULTRASONIC_type;


void ULTRASONIC_Init(void);
u8 ULTRASONIC_GetDistance(ULTRASONIC_type us,u16*pdistance);

u16 ULTRASONIC_GetDistance_direct(void);




#endif /* ULTRASONIC_H_ */