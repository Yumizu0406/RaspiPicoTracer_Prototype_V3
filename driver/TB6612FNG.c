/*
 * TB6612FNG.c
 *
 *  Created on: 2023/07/02
 *      Author: yuusuke
 */

#include "TB6612FNG.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define AIN1	13
#define AIN2	12
#define BIN1	20
#define BIN2	21
#define EN		22

#define PWM_A	16
#define PWM_B	17

#define PIN_LOW		0
#define PIN_HIGH	1

#define WRAP_SETTING_VALUE 2399//タイマ周期設定値 30kHz

static TB6612FNG_CONTROL control_state_A;
static TB6612FNG_CONTROL control_state_B;

void init_TB6612FNG(void){
	gpio_set_function(PWM_A, GPIO_FUNC_PWM);
    gpio_set_function(PWM_B, GPIO_FUNC_PWM);

	uint slice_num = pwm_gpio_to_slice_num(2);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, WRAP_SETTING_VALUE);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1000);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1000);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);

	gpio_init(AIN1);
    gpio_set_dir(AIN1, GPIO_OUT);
    gpio_init(AIN2);
    gpio_set_dir(AIN2, GPIO_OUT);
	gpio_init(BIN1);
    gpio_set_dir(BIN1, GPIO_OUT);
    gpio_init(BIN2);
    gpio_set_dir(BIN2, GPIO_OUT);
    gpio_init(EN);
    gpio_set_dir(EN, GPIO_OUT);

	gpio_put(AIN1, 1);
	gpio_put(AIN2, 1);
	gpio_put(BIN1, 1);
	gpio_put(BIN2, 1);
	gpio_put(EN, 1);
}

void set_pwm_duty(TB6612FNG_CH ch, uint16_t duty){

	if(ch == A){
		/*
		if(duty != GPTW9.GTCCRB){
			GPTW9.GTCCRB = duty;//TB6612FNGのA端子がPWMのB端子に接続されている
		}
		*/
	} else {
		/*
		if(duty != GPTW9.GTCCRA){
			GPTW9.GTCCRA = duty;//TB6612FNGのA端子がPWMのB端子に接続されている
		}
		*/
	}
}

void set_control(TB6612FNG_CH ch, TB6612FNG_CONTROL control){
	if(ch == A){
		if(control == control_state_A){
			return;
		}

		if(control == SHORT_BRAKE){
			gpio_put(AIN1, 1);
			gpio_put(AIN2, 1);
		} else if(control == CW){
			gpio_put(AIN1, 1);
			gpio_put(AIN2, 0);
		} else if(control == CCW){
			gpio_put(AIN1, 0);
			gpio_put(AIN2, 1);
		} else {
			gpio_put(AIN1, 0);
			gpio_put(AIN2, 0);
		}
	} else {
		if(control == control_state_B){
			return;
		}

		if(control == SHORT_BRAKE){
			gpio_put(BIN1, 1);
			gpio_put(BIN2, 1);
		} else if(control == CW){
			gpio_put(BIN1, 1);
			gpio_put(BIN2, 0);
		} else if(control == CCW){
			gpio_put(BIN1, 0);
			gpio_put(BIN2, 1);
		} else {
			gpio_put(BIN1, 0);
			gpio_put(BIN2, 0);
		}
	}
}

uint16_t get_pwm_resolution(void){
	return (WRAP_SETTING_VALUE + 1);
}
