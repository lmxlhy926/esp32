#include "exit_test.h"
#include "exit.h"
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void exit_test()
{
    led_init();
    exit_init();

    while(true){
        vTaskDelay(pdMS_TO_TICKS(1 * 1000));
    }    
}