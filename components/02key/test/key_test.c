#include "key_test.h"
#include "key.h"
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


/**
 * 检测到按键按下，则翻转LED状态
 */
void key_test()
{
    led_init();
    key_init();
    while(true){
        int boot_pin_input_value = key_scan(SCAN_CONTINUE);
        switch(boot_pin_input_value){
            case BOOT_PIN_PRESS:
                LED_TOGGLE();
                break;
            case BOOT_PIN_RELEASE:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}