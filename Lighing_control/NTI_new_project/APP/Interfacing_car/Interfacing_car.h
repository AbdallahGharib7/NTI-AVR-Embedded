
#ifndef INTERFACING_CAR_H_
#define INTERFACING_CAR_H_

typedef enum{
	CAR_AUTO,
	CAR_MANUAL
	}INTERFACING_CAR_MODES;

	

typedef enum{
	MANUAL_P,
	MANUAL_D,
	MANUAL_R,
	MANUAL_STOP//,
	//MANUAL_WIPERS,
	}MANUAL_MODES;


	
typedef enum{
	WIPERS_SLOW,
	WIPERS_FAST,
	WIPERS_STOP
	}WIPERS_MODES;
	

	


void interfacing_car_Init(void);

void interfacing_car_Runnabe(void);





#endif /* INTERFACING_CAR_H_ */