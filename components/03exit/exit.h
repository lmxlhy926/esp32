#ifndef _EXIT_H
#define _EXIT_H

#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BOOT_INTR_GPIO_PIN GPIO_NUM_0

void exit_init();


#ifdef __cplusplus
}
#endif

#endif

