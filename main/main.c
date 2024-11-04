#include <stdio.h>
#include <stdbool.h>
#include "esp_log.h"
#include "test/led_test.h"
#include "test/key_test.h"

void app_main(void)
{
    key_test();
}