
#ifndef LED_H_
#define LED_H_

typedef enum
{
RED_LED,
GREEN_LED,
BLUE_LED,
YELLOW_LED

}led_id_t;

typedef enum
{
LOW=0, //off
HIGH //on
}led_mode_t;

void LED_Init(led_id_t  led_id );//
void LED_setmode(led_id_t led_id,led_mode_t  mode);//high,low*/
void LED_toggle(led_id_t led_id);


#endif /* LED_H_ */