
#include "sensors.h"

#define LM35_CHANNEL  CH_0

u16 Temp_Read_lm35(void)
{
	return (ADC_ReadVolt(LM35_CHANNEL));
}