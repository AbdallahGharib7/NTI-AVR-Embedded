#include "STD_types.h"
#include "BitMath.h"
#include "DIO.h"
#include "TIMER.h"
//#include "Timers_Services.h"
#include "LCD.h"

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>


#include "ULTRASONIC.h"

volatile static u16 usec;
volatile static u8  flag;

void func_ICU_callback(void);


void ULTRASONIC_Init(void)
{
	DIO_vSetPinMode(PD6,INPUT_NORMAL);
	//DIO_vSetPinMode(PD6,INPUT_NORMAL);
	
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_SetCallBack(func_ICU_callback);
	GLOBAL_ENABLE();
	Timer1_ICU_InterruptEnable();
	
	
}

u8 ULTRASONIC_GetDistance(ULTRASONIC_type us,u16*pdistance)
{
	u16 del =0;
	flag = 0;
	
	DIO_vSetPinMode(us,OUTPUT_HIGH);
	_delay_us(10);
	DIO_vSetPinMode(us,OUTPUT_LOW);
	
	
	while (flag < 2 && del<23000 )
	{
		_delay_us(1);
		del++;
	}
	
	if(flag == 2)
	{
		*pdistance = (usec) / (58*2-1) ;
		return 1;
	}
	return 0;
	

}

void func_ICU_callback(void)
{
	if(flag == 0)
	{
		TCNT1 = 0;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag == 1)
	{
		usec = ICR1 ;
		Timer1_InputCaptureEdge(RISING);
		flag = 2;
	}
	
}




u16 ULTRASONIC_GetDistance_direct()
{
	flag = 0;
	
	DIO_vSetPinMode(TRIGGER,OUTPUT_HIGH);
	_delay_us(10);
	DIO_vSetPinMode(TRIGGER,OUTPUT_LOW);
	
	
	while (flag < 2);
	
	return (usec) / (58*2-1) ;

	
}