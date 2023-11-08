#include "STD_types.h"
#include "BitMath.h"
#include "MemMap.h"

#include "DIO.h"
#include "TIMER.h"




//0-180
void servo_angle(u32 angle)
{
	if(angle>=0 && angle<=180)
	{
		DIO_vSetPinMode(PD4,OUTPUT_HIGH);
		Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
		Timer1_OCRB1Mode(OCRB_NON_INVERTING);
		
		ICR1=(u16)(((u32)19999+1)*2)-1;
		OCR1B=(u16)(((((u32)angle*100)/18)+1000)*2-1);
	}

}