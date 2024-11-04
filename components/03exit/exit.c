#include "exit.h"
#include "led.h"
#include "freertos/FreeRTOS.h"

/**
 * 自定义的中断服务处理函数
 */
static void exit_gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    if(gpio_num == BOOT_INTR_GPIO_PIN){
        LED_TOGGLE();
    }
}


void exit_init()
{
    /**
     * 配置为输入、下降沿出发模式
     * 使能上拉电阻、默认是高电平
     */
    gpio_config_t gpio_config_init = {
        .pin_bit_mask = 1ull << BOOT_INTR_GPIO_PIN,
        .intr_type = GPIO_INTR_NEGEDGE,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };
    gpio_config(&gpio_config_init);

    // 安装中断服务
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    // 配置指定引脚的中断处理函数
    gpio_isr_handler_add(BOOT_INTR_GPIO_PIN, exit_gpio_isr_handler, (void*)BOOT_INTR_GPIO_PIN);

    // 使能指定引脚的中断功能
    gpio_intr_enable(BOOT_INTR_GPIO_PIN);
}