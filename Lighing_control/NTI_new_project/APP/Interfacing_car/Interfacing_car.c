/* lib */
#include "STD_types.h"
#include "BitMath.h"

/* MCAL */
#include "UART.h"
#include "DIO.h"

/* HAL */
#include "DIO.h"
#include "Keypad.h"
#include "ADC.h"
#include "LCD.h"
#include "Led.h"
#include "DC_motor.h"
#include "servo.h"
#include "ULTRASONIC.h"

/* SERVICE */
#include "UART_Service.h"

/* APP */
#include "Interfacing_car.h"




static INTERFACING_CAR_MODES car_mode = CAR_AUTO;
static MANUAL_MODES manual_mode = MANUAL_STOP;
static WIPERS_MODES wipers_mode = WIPERS_STOP;

static u16 distance;
static u8 speed;
static u8 key=NO_KEY;
static s8 car_direction = 1;

 

void interfacing_car_Init(void)
{
	//adc
	ADC_Init();
	
	//lcd
	LCD_Init();
	
	//keypad
	Keypad_Init();
	
	//ultra
	ULTRASONIC_Init();
	
	//uart
	DIO_vSetPinMode(PD0,INPUT_NORMAL);
	DIO_vSetPinMode(PD1,OUTPUT_HIGH);
	UART_Init();
	
	UART_Send(5);
	
	//red led 
	LED_Init(RED_LED);
	//DIO_vSetPinMode(PB7,OUTPUT_LOW);
	
	
}

void interfacing_car_Runnabe(void)
{
	key = keypad_getkey();
	switch(key)
	{
		case '1': car_mode =    CAR_AUTO;                               break;
		case '2': car_mode =    CAR_MANUAL; manual_mode = MANUAL_STOP ; break;
		case '3': manual_mode = MANUAL_P;								break;
		case '4': manual_mode = MANUAL_D;								break;
		case '5': manual_mode = MANUAL_R;								break;
		case '6': manual_mode = MANUAL_STOP ;							break;
		case '7': wipers_mode =  WIPERS_SLOW;							break;
		case '8': wipers_mode = WIPERS_FAST;							break;
		case '9': wipers_mode =  WIPERS_STOP;							break;
		
	}
	
	LCD_goto(0,19);
	LCD_WriteChar(key);
	
	if(car_mode ==  CAR_AUTO)
	{
		car_direction = 1;
		LED_setmode(RED_LED,LOW);
		
		LCD_goto(0,0);
		LCD_WriteString("CAR mode : Auto   ");
		
		 while(ULTRASONIC_GetDistance(PD7,&distance)==0);


		
		if(distance>=150)
		{
			speed=255;
		}
		else if (distance<=30)
		{
			speed=0;
		}
		else
		{
			speed= 2*distance - 60;
		}
		LCD_goto(1,0);
		LCD_WriteString("Speed : ");
		LCD_WriteNumber((s32)speed);//print here in rpm 
		LCD_WriteString(" RPM   ");
		
		LCD_goto(2,0);
		LCD_WriteString("Driving state : D   ");

		motor_speed(MOTOR_ON_CW,speed);
	}
	
	
	
	else if(car_mode == CAR_MANUAL )
	{
		LCD_goto(0,0);
		LCD_WriteString("CAR mode : Manual");
		
		switch(manual_mode)
		{
			case MANUAL_P:
				car_direction=1;
				LED_setmode(RED_LED,LOW);
				LCD_goto(1,0);
				LCD_WriteString("Speed : ");
				LCD_WriteNumber((s32)1);//print here in rpm
				LCD_WriteString(" RPM   ");

				LCD_goto(2,0);
				LCD_WriteString("Driving state : P   ");
				
				motor_speed(MOTOR_ON_CW,1);
				break;
				
				
			case MANUAL_D: 
				car_direction=1;
				LED_setmode(RED_LED,LOW);
				speed=ADC_Read(CH_0)/4;
				
				LCD_goto(1,0);
				LCD_WriteString("Speed : ");
				LCD_WriteNumber((s32)speed);//print here in rpm
				LCD_WriteString(" RPM    ");

				LCD_goto(2,0);
				LCD_WriteString("Driving state : D   ");
			
				motor_speed(MOTOR_ON_CW,speed);
				break;
				
			case MANUAL_R:
				car_direction=-1;
				LED_setmode(RED_LED,LOW);
				speed=ADC_Read(CH_0)/4;
				
				LCD_goto(1,0);
				LCD_WriteString("Speed : ");
				LCD_WriteNumber((s32)speed);//print here in rpm
				LCD_WriteString(" RPM   ");

				LCD_goto(2,0);
				LCD_WriteString("Driving state : R   ");
				
				motor_speed(MOTOR_ON_CCW,speed);
				break;
				
			case MANUAL_STOP :
				
				LED_setmode(RED_LED,HIGH); 
				
				if(speed>10)
				{
					speed-=10;
					if(car_direction==1)
					{
						motor_speed(MOTOR_ON_CW,speed);
					}	
					else if(car_direction == -1 )
					{
						motor_speed(MOTOR_ON_CCW,speed);
					}
				}
				else if (speed <= 10)
				{
					speed = 0;
					motor_speed(MOTOR_OFF,speed);
				}
				
				LCD_goto(1,0);
				LCD_WriteString("Speed : ");
				LCD_WriteNumber((s32)speed);//print here in rpm
				LCD_WriteString(" RPM   ");

				LCD_goto(2,0);
				LCD_WriteString("Driving state : Stop");
				break;
		}
		
		
	}
	
	LCD_goto(3,0);
	
	switch(wipers_mode)//send numbers to  uart
	{
		case WIPERS_FAST : 
			LCD_WriteString("Wipers mode : Fast");
			UART_Send('2');
			break;
			
		case WIPERS_SLOW : 
			LCD_WriteString("Wipers mode : Slow");
			UART_Send('1');
			break;
			
		case WIPERS_STOP : 
			LCD_WriteString("Wipers mode : Stop");
			UART_Send('0');
			break;
	}
}

















