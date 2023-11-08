
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#define MOTOR_EN   PB3
#define MOTOR_IN1  PB5
#define MOTOR_IN2  PB6




typedef enum{
	MOTOR_ON_CW,
	MOTOR_ON_CCW,
	MOTOR_OFF	
	}MOTOR_MODES;




void motor_state_kit(MOTOR_MODES mode);
void motor_speed_kit(MOTOR_MODES mode,u8 speed);

void motor_state(MOTOR_MODES mode);
void motor_speed(MOTOR_MODES mode,u8 speed);




#endif /* DC_MOTOR_H_ */