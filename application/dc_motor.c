#include "dc_motor.h"
#include "../driver/TB6612FNG.h"

#define SHORT_MAX 65535

void init_dc_motor(void){
}

void set_speed_dc_motor(DC_MOTOR_CH ch, int32_t speed){
	int32_t speed_int_abs;
	TB6612FNG_CH TB6612FNG_ch;

	if(ch == Right){
		TB6612FNG_ch = A;
	} else {
		TB6612FNG_ch = B;
	}

	if(speed < 0){
		speed_int_abs = -1 * speed;
	} else {
		speed_int_abs = speed;
	}

	if(SHORT_MAX < speed_int_abs){
		speed_int_abs = SHORT_MAX;
	}

	if(0 <= speed){
		if(ch == Right){
			set_control(TB6612FNG_ch,CW);
		} else {
			set_control(TB6612FNG_ch,CCW);
		}
	} else {
		if(ch == Right){
			set_control(TB6612FNG_ch,CCW);
		} else {
			set_control(TB6612FNG_ch,CW);
		}
	}
	set_pwm_value(TB6612FNG_ch,(uint16_t)speed_int_abs);
}

uint16_t get_dc_motor_pwm_resolution(void){
	return get_pwm_resolution();
}
