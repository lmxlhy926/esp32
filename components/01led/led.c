#include "led.h"

void led_init(void)
{
    /**
     * 指定引脚
     * 配置中断
     * 指定输入输出模式
     * 配置上拉电阻
     * 配置下拉电阻
     * 
     */
    gpio_config_t gpio_init_struct = {
        .pin_bit_mask = 1ull << LED_GPIO_PIN,   
        .intr_type = GPIO_INTR_DISABLE,         
        .mode = GPIO_MODE_INPUT_OUTPUT,          
        .pull_up_en = GPIO_PULLUP_ENABLE,      
        .pull_down_en = GPIO_PULLDOWN_DISABLE    
    };
    
    gpio_config(&gpio_init_struct);
}

