#ifndef KEY_H
#define KEY_H

#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


// boot按键对应的引脚
#define BOOT_GPIO_PIN GPIO_NUM_0

#define BOOT_PIN_PRESS 0
#define BOOT_PIN_RELEASE 1

#define BOOT_PIN_STATE() gpio_get_level(BOOT_GPIO_PIN)

typedef enum{
    SCAN_ONE_SHOT,
    SCAN_CONTINUE
}scan_mode_t;


/* 初始化按键 */
void key_init();

/* 读取GPIO引脚的输入值，延时去抖 */
uint8_t key_scan(scan_mode_t mode);


#ifdef __cplusplus
}
#endif

#endif /* KEY_H */