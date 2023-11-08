#include "STD_types.h"
#include "MemMap.h"
#include "BitMath.h"

#include "TIMER.h"


/*************************************************** timer0 *******************************************************************/

u32 timer0_counter;

/*************************************** timer0 pointer to funtion in ISR ********************************************************/
static void (*Timer0_OVF_Fptr) (void)=NULLPTR;
static void (*Timer0_OC_Fptr)  (void)=NULLPTR;

/*************************************************** timer0 *******************************************************************/
void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler)
{
	switch(mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	
	switch(scaler)
	{
		case TIMER0_STOP:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_1:
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_8:
		CLR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_64:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		 
		case TIMER0_SCALER_256:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_1024:
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
		case T0_EXTERNAL_FALLING:
		CLR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
		case T0_EXTERNAL_RISING:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
	}
	//TIMER0_OVF_InterruptEnable();
	//TIMER0_OC_InterruptEnable();
	
	
	
	
	
}
void TIMER0_OC0Mode(OC0Mode_type mode)
{
	switch(mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
}



void OC0_AnalogWritePresentage(u8 pres)
{
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	
	/*TIMER0_OC0Mode(OC0_NON_INVERTING);
	OCR0=((u32)pres*255)/100;*/
	
	TIMER0_OC0Mode(OC0_INVERTING);
	OCR0=255-(((u32)pres*255)/100);
}

void OC0_AnalogWrite(u8 oc )
{
	static u8 first_time=1;
	if(first_time==1)
	{
		TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	
	/*TIMER0_OC0Mode(OC0_NON_INVERTING);
	OCR0=oc;*/
	
	TIMER0_OC0Mode(OC0_INVERTING);
	first_time=0;
	}
	
	
	
	OCR0=255-oc;
}


void OC0_AnalogWriteVoltage(u16 volt)
{
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	
	/*
	TIMER0_OC0Mode(OC0_NON_INVERTING);      //???????? ?????
	OCR0=(((u32)volt*255)/5000);*/
	
	TIMER0_OC0Mode(OC0_INVERTING);         //???????? ?? 255
	OCR0=(255-((u32)volt*255)/5000);
	
	
}
void OC0_SetPrescaler(Timer0Scaler_type scaler)
{
	switch(scaler)
	{
		case TIMER0_STOP:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_1:
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_8:
		CLR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_64:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_256:
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
		case TIMER0_SCALER_1024:
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
		case T0_EXTERNAL_FALLING:
		CLR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
		case T0_EXTERNAL_RISING:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		
	}
}
//freq range :    F_CPU/2 -> 15 hz
void OC0_SetFrequency_duty50(u32 freq)
{
	TIMER0_Init(TIMER0_CTC_MODE,TIMER0_STOP); 
	TIMER0_OC0Mode(OC0_TOGGLE);
	
	if(freq<=4000000 && freq>400000)
	{
		OC0_SetPrescaler(TIMER0_SCALER_1);
		OCR0=((u32)(F_CPU)/(2*freq*1))-1;
	}
	else if(freq<=400000 && freq>40000)
	{
		OC0_SetPrescaler(TIMER0_SCALER_8);
		OCR0=((u32)(F_CPU)/(2*freq*8))-1;
	}
	else if(freq<=40000 && freq>4000)
	{
		OC0_SetPrescaler(TIMER0_SCALER_64);
		OCR0=((u32)(F_CPU)/(2*freq*64))-1;
	}
	else if(freq<=4000 && freq>400)
	{
		OC0_SetPrescaler(TIMER0_SCALER_256);
		OCR0=((u32)(F_CPU)/(2*freq*256))-1;
	}
	else if(freq<=400 && freq>=15)
	{
		OC0_SetPrescaler(TIMER0_SCALER_1024);
		OCR0=((u32)(F_CPU)/(2*freq*1024))-1;
	}
}



void timer0_delay_ms(u32 delay_ms,void (*ptr)(void))
{
	
}



/****************************************************** timer0 Interrupt functions *************************************************/


void TIMER0_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
	//TIMER0_OVF_SetCallBack(Timer0_OVF_func);
}

void TIMER0_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}

void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
	//TIMER0_OC_SetCallBack(Timer0_OC_func);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

void TIMER0_OVF_SetCallBack(void(*local_fptr)(void))
{
	Timer0_OVF_Fptr=local_fptr;
}

void TIMER0_OC_SetCallBack(void(*local_fptr)(void))
{
	Timer0_OC_Fptr=local_fptr;
}



ISR(TIMER0_OVF_vect)
{
	if(Timer0_OVF_Fptr!=NULLPTR)
	{
		Timer0_OVF_Fptr();
	}
}

ISR(TIMER0_OC_vect)
{
	if(Timer0_OC_Fptr!=NULLPTR)
	{
		Timer0_OC_Fptr();
	}
}



/*************************************************** timer1 *******************************************************************/

/*************************************** timer1 pointer to funtion in ISR ********************************************************/

static void (*Timer1_OVF_Fptr)  (void)=NULLPTR;
static void (*Timer1_OCA_Fptr)  (void)=NULLPTR;
static void (*Timer1_OCB_Fptr)  (void)=NULLPTR;
static void (*Timer1_ICU_Fptr)  (void)=NULLPTR;

/*************************************************** timer1 *******************************************************************/

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	switch(edge)
	{
		case RISING:
		SET_BIT(TCCR1B,ICES1);
		break;
		
		case FALLING:
		CLR_BIT(TCCR1B,ICES1);
		break;
	}
}


void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_8_BIT:
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode)
{
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode)
{
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}

void OC1A_AnalogWrite_255(u8 oc )
{
	Timer1_Init(TIMER1_FASTPWM_8_BIT,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_INVERTING);
	OCR1A=255-oc;
}

void OC1B_AnalogWrite_255(u8 oc )
{
	Timer1_Init(TIMER1_FASTPWM_8_BIT,TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_INVERTING);
	OCR1B=255-oc;
}
/*
		Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
		Timer1_OCRB1Mode(OCRB_NON_INVERTING);
		
		ICR1=(u16)19999;
		OCR1B=(u16)(((u32)angle*100)/18)+999;

*/
void OC1A_fast_rgb(u8 oc )
{
	if(oc == 0 )
	{
		CLR_BIT(PORTD,5);
	}
	else if(oc == 255)
	{
		SET_BIT(PORTD,5);
	}
	else
	{
		Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
		Timer1_OCRA1Mode(OCRA_NON_INVERTING);
		ICR1=(u16)19999;
		OCR1A=(u16)(((oc*(u32)19999)/255));
	}
}


void OC1_signal_no_ICR(u32 freq, u8 duty_A, u8 duty_B)
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	
	ICR1=((u32)1000000*2/freq);   //timer freq  / required freq 
	
	OCR1A=(((u32)duty_A*ICR1)/100);
	OCR1B=(((u32)duty_B*ICR1)/100);
}

void OC1B_signal_no_OC1A(u32 freq, u8 duty)
{
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	
	OCR1A=(((u32)1000000*2)/(freq));                           //500 -> 1000 micro
	OCR1B=((((u32)duty*OCR1A))/100); 
}





/****************************************************** timer1 Interrupt functions *************************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
	//Timer1_ICU_SetCallBack(Timer1_ICU_func);
}

void Timer1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}

void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
	//Timer1_OVF_SetCallBack(Timer1_OVF_func);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}

void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
	//Timer1_OCA_SetCallBack(Timer1_OCA_func);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}

void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
	//Timer1_OCB_SetCallBack(Timer1_OCB_func);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!= NULLPTR)
	{
		Timer1_OVF_Fptr();
	}
}


ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!= NULLPTR)
	{
		Timer1_OCA_Fptr();
	}
}

ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!= NULLPTR)
	{
		Timer1_OCB_Fptr();
	}
}

ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!= NULLPTR)
	{
		Timer1_ICU_Fptr();
	}
}






/*************************************************** timer2 *******************************************************************/


/*************************************** timer2 pointer to funtion in ISR ********************************************************/
static void (*Timer2_OVF_Fptr) (void)=NULLPTR;
static void (*Timer2_OC_Fptr)  (void)=NULLPTR;

/*************************************************** timer2 *******************************************************************/
void TIMER2_Init(Timer2Mode_type mode,Timer2Scaler_type scaler)
{
	switch(mode)
	{
		case TIMER2_NORMAL_MODE:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		
		case TIMER2_PHASECORRECT_MODE:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
		
		case TIMER2_CTC_MODE:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
		
		case TIMER2_FASTPWM_MODE:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	}
	
	TCCR2&=0XF8;
	TCCR2|=scaler;
	
	TIMER2_OVF_InterruptEnable();
	TIMER2_OC_InterruptEnable();
	
	
	
	
	
}
void TIMER2_OC2Mode(OC2Mode_type mode)
{
	switch(mode)
	{
		case OC2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		
		case OC2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
		
		case OC2_NON_INVERTING:
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
		
		case OC2_INVERTING:
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	}
}

void OC2_AnalogWritePresentage(u8 pres)
{
	TIMER2_Init(TIMER2_FASTPWM_MODE,TIMER2_SCALER_8);
	
	/*TIMER2_OC2Mode(OC2_NON_INVERTING);
	OCR2=((u32)pres*255)/100;*/
	
	TIMER2_OC2Mode(OC2_INVERTING);
	OCR2=255-(((u32)pres*255)/100);
}

void OC2_AnalogWrite(u8 oc )
{
	TIMER2_Init(TIMER2_FASTPWM_MODE,TIMER2_SCALER_8);
	
	/*TIMER2_OC2Mode(OC2_NON_INVERTING);
	OCR2=oc;*/
	
	TIMER2_OC2Mode(OC2_INVERTING);
	OCR2=255-oc;
}

void OC2_AnalogWriteVoltage(u16 volt)
{
	TIMER2_Init(TIMER2_FASTPWM_MODE,TIMER2_SCALER_8);
	
	/*
	TIMER2_OC2Mode(OC2_NON_INVERTING);      //???????? ?????
	OCR2=(((u32)volt*255)/5000);*/
	
	TIMER2_OC2Mode(OC2_INVERTING);         //???????? ?? 255
	OCR2=(255-((u32)volt*255)/5000);
	
	
}
void OC2_SetPrescaler(Timer2Scaler_type scaler)
{
	TCCR2&=0XF8;
	TCCR2|=scaler;
}

//4000000 to 15 hz
void OC2_SetFrequency_duty50(u32 freq)
{
	TIMER2_Init(TIMER2_CTC_MODE,TIMER2_STOP);
	TIMER2_OC2Mode(OC2_TOGGLE);
	
	if(freq<=4000000 && freq>400000)
	{
		OC2_SetPrescaler(TIMER2_SCALER_1);
		OCR2=((u32)(F_CPU)/(2*freq*1))-1;
	}
	else if(freq<=400000 && freq>40000)
	{
		OC2_SetPrescaler(TIMER2_SCALER_8);
		OCR2=((u32)(F_CPU)/(2*freq*8))-1;
	}
	else if(freq<=40000 && freq>4000)
	{
		OC2_SetPrescaler(TIMER2_SCALER_64);
		OCR2=((u32)(F_CPU)/(2*freq*64))-1;
	}
	else if(freq<=4000 && freq>400)
	{
		OC2_SetPrescaler(TIMER2_SCALER_256);
		OCR2=((u32)(F_CPU)/(2*freq*256))-1;
	}
	else if(freq<=400 && freq>=15)
	{
		OC2_SetPrescaler(TIMER2_SCALER_1024);
		OCR2=((u32)(F_CPU)/(2*freq*1024))-1;
	}
}



/****************************************************** timer2 Interrupt functions *************************************************/


void TIMER2_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE2);
	//TIMER2_OVF_SetCallBack(Timer2_OVF_func);
}

void TIMER2_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE2);
}

void TIMER2_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE2);
	//TIMER2_OC_SetCallBack(Timer2_OC_func);
}
void TIMER2_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE2);
}





void TIMER2_OVF_SetCallBack(void(*local_fptr)(void))
{
	Timer2_OVF_Fptr=local_fptr;
}

void TIMER2_OC_SetCallBack(void(*local_fptr)(void))
{
	Timer2_OC_Fptr=local_fptr;
}



ISR(TIMER2_OVF_vect)
{
	if(Timer2_OVF_Fptr!=NULLPTR)
	{
		Timer2_OVF_Fptr();
	}
}

ISR(TIMER2_OC_vect)
{
	if(Timer2_OC_Fptr!=NULLPTR)
	{
		Timer2_OC_Fptr();
	}
}

