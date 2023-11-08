


#ifndef BUTTON_H_
#define BUTTON_H_

#include "DIO_cfg.h"
#include "DIO_prv.h"

typedef enum
{
	
	PRESSED=0,
	NOTPRESSED=1
	
}pb_state_t;

typedef enum
{
	pd_1,
	pd_2,
	pd_3,
	pd_4,
	
}pb_id_t;

pb_state_t Pushbutton_state(pb_id_t button);//presses/not
void Pushbutton_setup(pb_id_t  button);//Input,

#endif /* BUTTON_H_ */