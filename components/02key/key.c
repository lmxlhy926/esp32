#include "key.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * 开关按键按下时，GPIO引脚被拉到低电平
 * 需要配置上拉电阻，当开关按键没有被按下时，输入端口保持为高电平
 */
void key_init()
{
    gpio_config_t gpio_config_init = {
        .pin_bit_mask = 1ull << BOOT_GPIO_PIN,
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };

    gpio_config(&gpio_config_init);
}


/**
 * 返回GPIO引脚的输入状态
 *      按键没有被按下时，引脚保持高电平状态
 *      按键被按下时，引脚保持低电平状态
 * 
 * 当按键被按下时，翻转LED的状态
 *      按键持续保持按下时，是否需要翻转LED的状态？
 *      按键每次按下，只翻转一次LED的状态？
 * 
 * 通过延时再次判断输入引脚的状态，确定按键是否真的按下
 * 
 */
uint8_t key_scan(scan_mode_t mode)
{
    static bool key_press_state_allow_report = true;
    int boot_pin_scan_value = BOOT_PIN_RELEASE;
    
    if(mode == SCAN_CONTINUE){
        key_press_state_allow_report = true;
    }
    
    if(BOOT_PIN_STATE() == BOOT_PIN_PRESS && key_press_state_allow_report){  // 按键按下且状态未上报
        vTaskDelay(pdMS_TO_TICKS(10));
        if(BOOT_PIN_STATE() == BOOT_PIN_PRESS && key_press_state_allow_report){
            boot_pin_scan_value = BOOT_PIN_PRESS;
            key_press_state_allow_report = false;
        }

    }else if(BOOT_PIN_STATE() == BOOT_PIN_RELEASE){ // 按键松开，
        vTaskDelay(pdMS_TO_TICKS(10));
        if(BOOT_PIN_STATE() == BOOT_PIN_RELEASE){
            key_press_state_allow_report = true;
        }
    }   
    
    return boot_pin_scan_value;
}
