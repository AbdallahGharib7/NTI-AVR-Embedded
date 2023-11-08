#include "DIO.h"
#include "Led.h"
#include "Button.h"
#include "Keypad.h"
#include "seg.h"
#include "LCD.h"
#include "EX_Interrupt.h"
#include "ADC.h"
#include "sensors.h"
#include "DC_motor.h"
#include "TIMER.h"
#include "servo.h"
#include "ULTRASONIC.h"
#include "UART.h"
#include "UART_Service.h"
#include "SPI.h"
#include "Interfacing_car.h"
#include "UART_SPI_M.h"

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>


typedef enum{
	PRESSED_ONCE,
	PRESSED_TWICE,
	SHORT_HOLD,
	LONG_HOLD
	}LIGHTING_PB_STATES;

#define RIGHT_WARNING '7'
#define LEFT_WARNING  '8'
#define FRONT_LIGHT   '9'
#define BACK_LIGH     '/'

static volatile u32 timer_counter =0;


static volatile LIGHTING_PB_STATES press_state_right = PRESSED_TWICE ;
static volatile LIGHTING_PB_STATES press_state_left  = PRESSED_TWICE ;
static volatile LIGHTING_PB_STATES press_state_front = PRESSED_TWICE ;
static volatile LIGHTING_PB_STATES press_state_back  = PRESSED_TWICE ;


void timer0_func(void);

static u8 password_arr[5]={'1','2','3','4','5'};
u8 password_check(void);





#define RIGHT_LED    YELLOW_LED
#define LEFT_LED     BLUE_LED
#define FRONT_LED    GREEN_LED
#define BACK_LED     RED_LED


int main()//_Lighting_control()
{
	u32 counter=0;
	u8 isPressedBefore_right=0;
	u8 isPressedBefore_left=0;
	u8 isPressedBefore_front=0;
	u8 isPressedBefore_back=0;
	u8 key=NO_KEY;
	

	
	Keypad_Init();
	LCD_Init();
	TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8);
	TIMER0_OVF_InterruptEnable();
	TIMER0_OVF_SetCallBack(timer0_func);
	GLOBAL_ENABLE();
	
	
	LED_Init(BACK_LED);	  //back
	LED_Init(FRONT_LED);  //front
	LED_Init(RIGHT_LED);   //right
	LED_Init(LEFT_LED); //left
	motor_state(MOTOR_OFF);
		
	
	while(password_check()==0);
	LCD_Clear();
	
	LCD_goto(0,0);
	LCD_WriteString("RIGHT : OFF");
	
	LCD_goto(1,0);
	LCD_WriteString("LEFT  : OFF");
	
	LCD_goto(2,0);
	LCD_WriteString("FRONT : OFF");
	
	LCD_goto(3,0);
	LCD_WriteString("BACK  : OFF");
	
	
	
	while(1)
	{
		
		
		counter = 0;
		key=NO_KEY;
		
		while(key==NO_KEY)
		{
			key=keypad_getkey();
			LCD_goto(0,19);
			LCD_WriteChar(key);
			switch(key)
			{
				case RIGHT_WARNING: while (keypad_getkey_No_Wait()==RIGHT_WARNING){counter++;_delay_ms(1);}  break;
				case LEFT_WARNING : while (keypad_getkey_No_Wait()==LEFT_WARNING) {counter++;_delay_ms(1);}  break;
				case FRONT_LIGHT  : while (keypad_getkey_No_Wait()==FRONT_LIGHT)  {counter++;_delay_ms(1);}  break;
				case BACK_LIGH    : while (keypad_getkey_No_Wait()==BACK_LIGH)    {counter++;_delay_ms(1);}  break;
				default: key=NO_KEY; break;
			}
		}
// 		LCD_goto(1,15);
// 		LCD_WriteNumber((s32)counter);
		
		
		if(counter<150)   //normal press   
		{
			switch(key)
			{
				case RIGHT_WARNING: 
					if(isPressedBefore_right==0 )//
					{
						if(press_state_right == LONG_HOLD || press_state_right == SHORT_HOLD )
						{
							isPressedBefore_right++;
						}
						press_state_right = PRESSED_ONCE;
						isPressedBefore_right++;
						
					}
					else
					{
						if(isPressedBefore_right==1 )
							{
								isPressedBefore_right++;
							}
						else
							{
								press_state_right = PRESSED_TWICE;
								isPressedBefore_right=0;
							}
					}
					break;
					
				case LEFT_WARNING:
				if(isPressedBefore_left==0)
				{
					if(press_state_left == LONG_HOLD || press_state_left == SHORT_HOLD )
					{
						isPressedBefore_left++;
					}
					press_state_left = PRESSED_ONCE;
					isPressedBefore_left++;
				}
				else
				{
					if(isPressedBefore_left==1)
					{
						isPressedBefore_left++;
					}
					else
					{
						press_state_left = PRESSED_TWICE;
						isPressedBefore_left=0;
					}
				}
				break;
				
				case FRONT_LIGHT:
				if(isPressedBefore_front==0)
				{
					if(press_state_front == LONG_HOLD || press_state_front == SHORT_HOLD )
					{
						isPressedBefore_front++;
					}
					press_state_front = PRESSED_ONCE;
					isPressedBefore_front++;
				}
				else
				{
					if(isPressedBefore_front==1)
					{
						isPressedBefore_front++;
					}
					else
					{
						press_state_front = PRESSED_TWICE;
						isPressedBefore_front=0;
					}
				}
				break;
				
				case BACK_LIGH:
				if(isPressedBefore_back==0)
				{
					if(press_state_back == LONG_HOLD || press_state_back == SHORT_HOLD )
					{
						isPressedBefore_back++;
					}
					press_state_back = PRESSED_ONCE;
					isPressedBefore_back++;
				}
				else
				{
					if(isPressedBefore_back==1)
					{
						isPressedBefore_back++;
					}
					else
					{
						press_state_back = PRESSED_TWICE;
						isPressedBefore_back=0;
					}
				}
				break;
				
			}
		}
		else if(counter<500)    //short hold   
		{
			switch(key)
			{
				case RIGHT_WARNING: press_state_right = SHORT_HOLD;break;
				case LEFT_WARNING : press_state_left  = SHORT_HOLD;break;
				case FRONT_LIGHT  : press_state_front = SHORT_HOLD;break;
				case BACK_LIGH    : press_state_back  = SHORT_HOLD;break;
			}
			
			isPressedBefore_right=0;
			isPressedBefore_left=0;
			isPressedBefore_front=0;
			isPressedBefore_back=0;

		}
		else   //long hold
		{	
			switch(key)
			{
				case RIGHT_WARNING: press_state_right = LONG_HOLD;break;
				case LEFT_WARNING : press_state_left  = LONG_HOLD;break;
				case FRONT_LIGHT  : press_state_front = LONG_HOLD;break;
				case BACK_LIGH    : press_state_back  = LONG_HOLD;break;
			}
			
			isPressedBefore_right=0;
			isPressedBefore_left=0;
			isPressedBefore_front=0;
			isPressedBefore_back=0;
		}
		
		
		
		switch(press_state_right)
		{
			case PRESSED_ONCE : LCD_goto(0,8);LCD_WriteString("ON   "); break;
			case PRESSED_TWICE: LCD_goto(0,8);LCD_WriteString("OFF  "); break;
			case SHORT_HOLD   : LCD_goto(0,8);LCD_WriteString("SHORT"); break;
			case LONG_HOLD    : LCD_goto(0,8);LCD_WriteString("LONG "); break;
		}
		
		switch(press_state_left)
		{
			case PRESSED_ONCE : LCD_goto(1,8);LCD_WriteString("ON   "); break;
			case PRESSED_TWICE: LCD_goto(1,8);LCD_WriteString("OFF  "); break;
			case SHORT_HOLD   : LCD_goto(1,8);LCD_WriteString("SHORT"); break;
			case LONG_HOLD    : LCD_goto(1,8);LCD_WriteString("LONG "); break;
		}
		
		switch(press_state_front)
		{
			case PRESSED_ONCE : LCD_goto(2,8);LCD_WriteString("ON   "); break;
			case PRESSED_TWICE: LCD_goto(2,8);LCD_WriteString("OFF  "); break;
			case SHORT_HOLD   : LCD_goto(2,8);LCD_WriteString("SHORT"); break;
			case LONG_HOLD    : LCD_goto(2,8);LCD_WriteString("LONG "); break;
		}
		
		switch(press_state_back)
		{
			case PRESSED_ONCE : LCD_goto(3,8);LCD_WriteString("ON   "); break;
			case PRESSED_TWICE: LCD_goto(3,8);LCD_WriteString("OFF  "); break;
			case SHORT_HOLD   : LCD_goto(3,8);LCD_WriteString("SHORT"); break;
			case LONG_HOLD    : LCD_goto(3,8);LCD_WriteString("LONG "); break;
		}
		
	}
	
}







void timer0_func(void)
{
	timer0_counter++;
	TCNT0=6;
	
	static u8 right_short_flag=0;
	static u8 right_long_flag =0;
	 
	static u8 left_short_flag=0;
	static u8 left_long_flag =0;
		    
	static u8 front_short_flag=0;
	static u8 front_long_flag =0;
		   
	static u8 back_short_flag=0;
	static u8 back_long_flag =0;
	
	
	if(timer0_counter % 1000 == 0) //8000 ov = 1 sec      -> 1000 = 0.125 sec
	{
		switch(press_state_right)
		{
			case PRESSED_ONCE : LED_setmode(RIGHT_LED,HIGH); right_short_flag=0; right_long_flag=0 ;break;
			case PRESSED_TWICE: LED_setmode(RIGHT_LED,LOW) ; right_short_flag=0; right_long_flag=0 ;break;
			case SHORT_HOLD   :  right_short_flag=1; right_long_flag=0 ;break;
			case LONG_HOLD    :  right_short_flag=0; right_long_flag=1 ;break;
		}
		
		switch(press_state_left)
		{
			case PRESSED_ONCE : LED_setmode(LEFT_LED,HIGH); left_short_flag=0; left_long_flag=0 ;break;
			case PRESSED_TWICE: LED_setmode(LEFT_LED,LOW) ; left_short_flag=0; left_long_flag=0 ;break;
			case SHORT_HOLD   :  left_short_flag=1; left_long_flag=0 ;break;
			case LONG_HOLD    :  left_short_flag=0; left_long_flag=1 ;break;
		}
		
		switch(press_state_front)
		{
			case PRESSED_ONCE : LED_setmode(FRONT_LED,HIGH); front_short_flag=0; front_long_flag=0 ;break;
			case PRESSED_TWICE: LED_setmode(FRONT_LED,LOW) ; front_short_flag=0; front_long_flag=0 ;break;
			case SHORT_HOLD   :  front_short_flag=1; front_long_flag=0 ;break;
			case LONG_HOLD    :  front_short_flag=0; front_long_flag=1 ;break;
		}
		
		switch(press_state_back)
		{
			case PRESSED_ONCE : LED_setmode(BACK_LED,HIGH); back_short_flag=0; back_long_flag=0 ;break;
			case PRESSED_TWICE: LED_setmode(BACK_LED,LOW) ; back_short_flag=0; back_long_flag=0 ;break;
			case SHORT_HOLD   :  back_short_flag=1; back_long_flag=0 ;break;
			case LONG_HOLD    :  back_short_flag=0; back_long_flag=1 ;break;
		}
		
		
	}
	
	
	
	if(timer0_counter % 2000 == 0)//each 0.25 sec     //long
	{
		if(right_long_flag == 1)
		{
			LED_toggle(RIGHT_LED);
		}
		if(left_long_flag == 1)
		{
			LED_toggle(LEFT_LED);
		}
		if(front_long_flag == 1)
		{
			LED_toggle(FRONT_LED);
		}
		if(back_long_flag == 1)
		{
			LED_toggle(BACK_LED);
		}
	}
	
	
	
	
	if(timer0_counter % 4000 == 0 )//each 0.5 sec     //short
	{
		if(right_short_flag == 1)
		{
			LED_toggle(RIGHT_LED);
		}
		if(left_short_flag == 1)
		{
			LED_toggle(LEFT_LED);
		}
		if(front_short_flag == 1)
		{
			LED_toggle(FRONT_LED);
		}
		if(back_short_flag == 1)
		{
			LED_toggle(BACK_LED);
		}
		
		
		timer0_counter=0;
	}

	
}



u8 password_check(void)
{
	u8 right_pass=1;
	u8 counter=0;
	u8 key=NO_KEY;
	u8 temp_pass[5];
	LCD_Clear();
	
	LCD_goto(0,0);
	LCD_WriteString("Enter Password ");
	
	
	while(counter<5)
	{
		key=keypad_getkey();
		if(key!=NO_KEY)
		{
				temp_pass[counter]=key;
				LCD_goto(1,counter++);
				LCD_WriteChar('*');
		}
	}
	for(u8 i=0;i<5;i++)
	{
		if(temp_pass[i]!=password_arr[i])
		{
			right_pass=0;
		}
	}
	
	LCD_goto(2,0); 
	
	if(right_pass)
	{
		LCD_WriteString("Right Password");
		LCD_goto(3,0);
		LCD_WriteString("Welcome to your car");

	}
	else
	{
		LCD_WriteString("Wrong Password  !!!");
	}
	_delay_ms(500);
	return right_pass;
	
}