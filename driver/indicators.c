/***********************************************************************************************************************
* ファイル名 : indicators.c
* 説明 : 表示モジュール
*        Raspberry Pi Picoボード上のLEDと機体上4つのLEDを制御する
***********************************************************************************************************************/

/***********************************************************************************************************************
include
***********************************************************************************************************************/
#include "indicators.h"
#include "hardware/gpio.h"

/***********************************************************************************************************************
define and const
***********************************************************************************************************************/
const uint DISP_LED_1_BIT_PIN = 8;
const uint DISP_LED_2_BIT_PIN = 9;
const uint DISP_LED_3_BIT_PIN = 10;
const uint DISP_LED_4_BIT_PIN = 11;

/***********************************************************************************************************************
global
***********************************************************************************************************************/
static uint8_t now_led_disp_value;

/***********************************************************************************************************************
prototype
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: init_indicators
 * Description  : 表示初期化処理
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void init_indicators(void)
{
    now_led_disp_value = 8;
    gpio_init(DISP_LED_1_BIT_PIN);
    gpio_set_dir(DISP_LED_1_BIT_PIN, GPIO_OUT);
    gpio_init(DISP_LED_2_BIT_PIN);
    gpio_set_dir(DISP_LED_2_BIT_PIN, GPIO_OUT);
    gpio_init(DISP_LED_3_BIT_PIN);
    gpio_set_dir(DISP_LED_3_BIT_PIN, GPIO_OUT);
    gpio_init(DISP_LED_4_BIT_PIN);
    gpio_set_dir(DISP_LED_4_BIT_PIN, GPIO_OUT);
}

/***********************************************************************************************************************
 * Function Name: out_indicators
 * Description  : 表示出力処理
 *                機体上4つのLEDに値を2進数で出力する
 * Arguments    : value
 * Return Value : none
 ***********************************************************************************************************************/
void out_indicators(uint8_t value)
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
