#include "led_test.h"
#include "led.h"
#include "freertos/FreeRTOS.h"

/**
 * 1. 配置LED对应的GPIO
 * 2. 端口输出高电平，LED熄灭
 * 3. 延时，翻转LED输出状态
 */
void led_test()
{
    led_init();
    LED_OUT(1);
    while(true){
        vTaskDelay(pdMS_TO_TICKS(3 * 1000));
        LED_TOGGLE();
    }

}