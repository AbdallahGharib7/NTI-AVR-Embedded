
#include "STD_types.h"
#include "DIO.h"
#include "DC_motor.h"
#include "TIMER.h"

void motor_state_kit(MOTOR_MODES mode)
{
	//pwm 100%
	DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH);
	
	switch(mode)
	{
		case MOTOR_ON_CW : DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH); DIO_vSetPinMode(PB5,OUTPUT_HIGH);break;
		case MOTOR_ON_CCW: DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH); DIO_vSetPinMode(PB5,OUTPUT_LOW) ;break;
		case MOTOR_OFF   : DIO_vSetPinMode(MOTOR_EN,OUTPUT_LOW);  break;
	}
	
}


void motor_speed_kit(MOTOR_MODES mode,u8 speed)  // 0 -> 100%
{
	motor_state(mode); //pb3 pwm   oc0
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	OCR0=(speed*255)/100;
	
	
}

void motor_state(MOTOR_MODES mode)
{
	//pwm 100%
	DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH);
	
	switch(mode)
	{
		case MOTOR_ON_CW : DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH); DIO_vSetPinMode(MOTOR_IN1,OUTPUT_HIGH);DIO_vSetPinMode(MOTOR_IN2,OUTPUT_LOW);break;
		case MOTOR_ON_CCW: DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH); DIO_vSetPinMode(MOTOR_IN2,OUTPUT_HIGH);DIO_vSetPinMode(MOTOR_IN1,OUTPUT_LOW);break;
		case MOTOR_OFF   : DIO_vSetPinMode(MOTOR_EN,OUTPUT_LOW);  break;
	}
}

void motor_speed(MOTOR_MODES mode,u8 speed)
{
	//pwm 0 -> 255
	DIO_vSetPinMode(MOTOR_EN,OUTPUT_HIGH);
	
	switch(mode)
	{
		case MOTOR_ON_CW : DIO_vSetPinMode(MOTOR_IN1,OUTPUT_HIGH);DIO_vSetPinMode(MOTOR_IN2,OUTPUT_LOW);break;
		case MOTOR_ON_CCW: DIO_vSetPinMode(MOTOR_IN2,OUTPUT_HIGH);DIO_vSetPinMode(MOTOR_IN1,OUTPUT_LOW);break;
		case MOTOR_OFF   : DIO_vSetPinMode(MOTOR_EN,OUTPUT_LOW);  break;
	}
	
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	
	
	if(mode == MOTOR_OFF)
	{
		OCR0=0;	
	}
	else
	{
		OCR0=speed;
	}

	
}