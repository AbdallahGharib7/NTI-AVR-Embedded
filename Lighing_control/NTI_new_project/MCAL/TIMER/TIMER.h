

#ifndef TIMERS_H_
#define TIMERS_H_

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

#include "STD_types.h"

/*************************** timer 0 *****************************/
extern u32 timer0_counter;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_type;

typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	T0_EXTERNAL_FALLING,
	T0_EXTERNAL_RISING
}Timer0Scaler_type;


typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}OC0Mode_type;

void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler);
void TIMER0_OC0Mode(OC0Mode_type mode);

void TIMER0_OVF_InterruptEnable (void);
void TIMER0_OVF_InterruptDisable(void);

void TIMER0_OC_InterruptEnable (void);
void TIMER0_OC_InterruptDisable(void);

void TIMER0_OVF_SetCallBack(void(*local_fptr)(void));
void TIMER0_OC_SetCallBack (void(*local_fptr)(void));

void OC0_AnalogWriteVoltage(u16 volt);	
void OC0_AnalogWritePresentage(u8 pres);	
void OC0_AnalogWrite(u8 oc );	
void OC0_SetPrescaler(Timer0Scaler_type scaler);

void OC0_SetFrequency_duty50(u32 freq);




void timer0_delay_ms(u32 delay_ms,void (*ptr)(void));



// #define TIMER0_READ()  TCNT0
// #define TIMER0_READ(x) *x=TCNT0

/*************************** timer 1 *****************************/
typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_8_BIT,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_type;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;


void Timer1_InputCaptureEdge(ICU_Edge_type edge);

void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler);
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode);
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode);


void OC1A_AnalogWrite_255(u8 oc );	
void OC1B_AnalogWrite_255(u8 oc );	
void OC1A_fast_rgb(u8 oc );


void OC1_signal_no_ICR(u32 freq, u8 duty_A, u8 duty_B);
void OC1B_signal_no_OC1A(u32 freq, u8 duty);


void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);

void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);

void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);

void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));//
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));



/*************************** timer 2 *****************************/

typedef enum
{
	TIMER2_NORMAL_MODE=0,
	TIMER2_PHASECORRECT_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FASTPWM_MODE

}Timer2Mode_type;

typedef enum{
	TIMER2_STOP=0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_32,
	TIMER2_SCALER_64,
	TIMER2_SCALER_128,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024
}Timer2Scaler_type;


typedef enum
{
	OC2_DISCONNECTED=0,
	OC2_TOGGLE,
	OC2_NON_INVERTING,
	OC2_INVERTING

}OC2Mode_type;

void TIMER2_Init(Timer2Mode_type mode,Timer2Scaler_type scaler);
void TIMER2_OC2Mode(OC2Mode_type mode);

void TIMER2_OVF_InterruptEnable (void);
void TIMER2_OVF_InterruptDisable(void);

void TIMER2_OC_InterruptEnable (void);
void TIMER2_OC_InterruptDisable(void);

void TIMER2_OVF_SetCallBack(void(*local_fptr)(void));
void TIMER2_OC_SetCallBack (void(*local_fptr)(void));

void OC2_AnalogWriteVoltage(u16 volt);
void OC2_AnalogWritePresentage(u8 pres);
void OC2_AnalogWrite(u8 oc );
void OC2_SetPrescaler(Timer2Scaler_type scaler);

void OC2_SetFrequency_duty50(u32 freq);



#endif /* TIMERS_H_ */