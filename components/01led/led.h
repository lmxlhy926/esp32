#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 输出：
 *      1. 推挽输出
 *      2. 开漏输出
 * 
 * 输入：
 *      1. 上拉输入：默认高电平
 *      2. 下拉输入：默认低电平
 *      
 */


/* 引脚定义 */
#define LED_GPIO_PIN    GPIO_NUM_1

/* 引脚的输出电平状态 */
enum GPIO_OUTPUT_STATE
{
    PIN_RESET = 0,
    PIN_SET
};

/* LED输出宏定义 */
#define LED_OUT(x)      do { x ?                                        \
                            gpio_set_level(LED_GPIO_PIN, PIN_SET) :     \
                            gpio_set_level(LED_GPIO_PIN, PIN_RESET);    \
                        } while(0)

/* LED取反宏定义 */
#define LED_TOGGLE()    do { \
                            gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN)); \
                        } while(0)   

/* LED初始化 */
void led_init(void);


#ifdef __cplusplus
}
#endif

#endif