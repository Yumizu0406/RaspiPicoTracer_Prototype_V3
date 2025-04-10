#include <stdio.h>
#include "pico/stdlib.h"
#include "driver/cycle.h"
#include "driver/sw.h"
#include "driver/lineSensor.h"
#include "driver/adchange.h"
#include "driver/TB6612FNG.h"
#include "application/control.h"

const uint DISP_LED_1_BIT_PIN = 8;
const uint DISP_LED_2_BIT_PIN = 9;
const uint DISP_LED_3_BIT_PIN = 10;
const uint DISP_LED_4_BIT_PIN = 11;

typedef enum{
    selecting_menu = 0,
	exe_menu
}menu_status_t;

void init_driver(void);
void menu_no_0(void);
void menu_no_1(void);
void menu_no_2(void);
void menu_no_3(void);
void menu_no_4(void);
void menu_no_5(void);
void menu_no_6(void);
void menu_no_7(void);
void disp_led_uint8(uint8_t value);
void exe_select_func(uint8_t select_func);

static uint8_t now_led_disp_value;
static uint8_t menu_no;
static menu_status_t menu_status;

void (*ptr_f[8])(void) = {
    menu_no_0,
    menu_no_1,
    menu_no_2,
    menu_no_3,
    menu_no_4,
    menu_no_5,
    menu_no_6,
    menu_no_7
};

int main()
{
    control_parameters_t parameter;

    now_led_disp_value = 8;
    menu_no = 0;
    menu_status = selecting_menu;

    stdio_init_all();
    init_control();

    parameter.speed_at_straight = 1000;
    parameter.p_gain_at_straight = 1.0;
    set_control_parameter(trial_run, parameter);

    init_driver();

    while (true) {
        if(menu_status == selecting_menu){
            if(isSwStatus(SW_NEXT, click)){
                menu_no++;
                if(menu_no >= 8){
                    menu_no = 0;
                }
            }
            disp_led_uint8(menu_no);

            if(isSwStatus(SW_EXE, click)){
                menu_status = exe_menu;
            }

        } else {
            exe_select_func(menu_no);
        }
    }
}

void init_driver(void)
{
    gpio_init(DISP_LED_1_BIT_PIN);
    gpio_set_dir(DISP_LED_1_BIT_PIN, GPIO_OUT);
    gpio_init(DISP_LED_2_BIT_PIN);
    gpio_set_dir(DISP_LED_2_BIT_PIN, GPIO_OUT);
    gpio_init(DISP_LED_3_BIT_PIN);
    gpio_set_dir(DISP_LED_3_BIT_PIN, GPIO_OUT);
    gpio_init(DISP_LED_4_BIT_PIN);
    gpio_set_dir(DISP_LED_4_BIT_PIN, GPIO_OUT);

    init_TB6612FNG();
    init_sw();
    init_adc();
    init_lineSensor();
    init_cycle();
}

void menu_no_0(void)
{
    if(isSwStatus(SW_EXE, click)){
        if(get_control_status() == stop){
            set_control_status(switching_to_run);
        } else {
            set_control_status(stop);
        }
    }
}

void menu_no_1(void)
{
    printf("sensor = %d\n", get_line_center_deff());
    sleep_ms(500);
}

void menu_no_2(void)
{
    printf("sensor = %d\n", get_adc_value(3));
    sleep_ms(500);
}

void menu_no_3(void)
{
    if(isSwStatus(SW_EXE, click)){
    
    }
}

void menu_no_4(void)
{
    if(isSwStatus(SW_EXE, click)){

    }
}

void menu_no_5(void)
{
    if(isSwStatus(SW_EXE, click)){

    }
}

void menu_no_6(void)
{
    if(isSwStatus(SW_EXE, click)){

    }
}

void menu_no_7(void)
{
    if(isSwStatus(SW_EXE, click)){

    }
}

void disp_led_uint8(uint8_t value)
{
    const uint DISP_LED_ARRAY[4] = {DISP_LED_1_BIT_PIN, DISP_LED_2_BIT_PIN, DISP_LED_3_BIT_PIN, DISP_LED_4_BIT_PIN};
    uint8_t tmp_value;
    uint8_t bit_count;
    tmp_value = value & 0x0f;

    if(now_led_disp_value == value){
        return;
    }
    now_led_disp_value = value;

    for(bit_count = 0; bit_count < 4; bit_count++){
        if((tmp_value & 0x01) != 0x00){
            gpio_put(DISP_LED_ARRAY[bit_count], false);
        } else {
            gpio_put(DISP_LED_ARRAY[bit_count], true);
        }
        tmp_value = tmp_value >> 1;
    }
}

void exe_select_func(uint8_t select_func)
{
    (void)(*ptr_f[select_func])();
}
