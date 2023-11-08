/*
 * ADC.h
 *
 * Created: 10/24/2023 11:06:28 AM
 *  Author: abdal
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "STD_types.h"
#include "BitMath.h"
#include "MemMap.h"


typedef enum{
	VREF_AREF,
	VREF_VCC,
	VREF_256
}ADC_VoltRef_type;

typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128
}ADC_Prescaler_type;

typedef enum{
	CH_0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;


void ADC_Init(void);

u16 ADC_Read(ADC_Channel_type channel);

u16 ADC_ReadVolt(ADC_Channel_type channel);

#endif /* ADC_H_ */