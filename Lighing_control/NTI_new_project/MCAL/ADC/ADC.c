
#include "ADC.h"
#include "LCD.h"



static ADC_VoltRef_type vref=VREF_VCC;
static ADC_Prescaler_type scaler=ADC_SCALER_64;



void ADC_Init(void)
{
	//VREF
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
		
		case VREF_VCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		
		case VREF_256:
		SET_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
	}
	
	//CLOCK
	ADCSRA=ADCSRA&0xf8;
	ADCSRA|=(scaler&(0x07));
	
	//ADC enable
	SET_BIT(ADCSRA,ADEN);
}


//mine
u16 ADC_Read(ADC_Channel_type ch)
{	
	//select channel using mux
	ADMUX=ADMUX & 0xe0;
	ADMUX=ADMUX | ch;
	
	//CLR_BIT(ADCSRA,ADIE);
	
	//start conversion       //single conversion(this is that methode) ----- or free running mode
	SET_BIT(ADCSRA,ADSC);
	
	//wait until end
	//_delay_ms(1);
	
// 	LCD_goto(0,0);
// 	LCD_WriteString("1");
	
	//while(GET_BIT(ADCSRA,ADSC));//using start conversion
	while(GET_BIT(ADCSRA,ADIF)==0); //using adc interrupt flag
	
	SET_BIT(ADCSRA,ADIF); //clear interrupt flag
// 	
// 	LCD_goto(1,0);
// 	LCD_WriteString("2");
	
	//get reading from 2 registers
	//return (0x03ff)&(((u16)ADCH<<8)|(u16)ADCL);
		
	return ADC;
}




u16 ADC_ReadVolt(ADC_Channel_type channel)
{
	return ((ADC_Read(channel)*(u32)5000)/1024);
	
}