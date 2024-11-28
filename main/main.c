#include <stdio.h>
#include <stdbool.h>

#include "esp_flash.h"
#include "nvs_flash.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "lwip/err.h"
#include "lwip/sys.h"

static const char* TAG = "ESP32_PANEL";

#define WIFI_CONNECTED_BIT    BIT0
#define WIFI_FAIL_BIT         BIT1

static EventGroupHandle_t s_wifi_event_group;

// wifi配置信息
wifi_config_t conf = {
   .sta = {
      .ssid = "smarthome",
      .password = "changhong1958",
      .threshold.authmode = WIFI_AUTH_WPA2_PSK,
      .pmf_cfg = {
         .capable = true,
         .required = false
      }
   }
};

// 事件触发回调函数
void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data){
   if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
      esp_wifi_connect();

   }else if(event_base == WIFI_EVENT &&  event_id == WIFI_EVENT_STA_DISCONNECTED){
      xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);

   }else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP){
      ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
      ESP_LOGI(TAG, "got ip: " IPSTR, IP2STR(&event->ip_info.ip));
      xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
   }

}


void init(void){
   s_wifi_event_group = xEventGroupCreate();

   esp_err_t ret = nvs_flash_init();

   ESP_ERROR_CHECK(esp_netif_init());
   ESP_ERROR_CHECK(esp_event_loop_create_default());

   esp_netif_create_default_wifi_sta();
   wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
   esp_wifi_init(&wifi_init_config);

   // 注册事件回调函数
   esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, NULL);
   esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, NULL);

   // 设置wifi模式，开始wifi连接
   esp_wifi_set_mode(WIFI_MODE_STA);
   esp_wifi_set_config(WIFI_IF_STA, &conf);
   esp_wifi_start();
   ESP_LOGI(TAG, "wifi_init_sta finished....");

   // 等待执行结果
   EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE,portMAX_DELAY);

   if(bits & WIFI_CONNECTED_BIT){
      ESP_LOGI(TAG, "connected to ap");
   }else if(bits & WIFI_FAIL_BIT){
      ESP_LOGI(TAG, "failed to connect to ap");
   }else {
      ESP_LOGI(TAG, "unexpected event");
   }
}





void app_main(void)
{
   ESP_LOGI(TAG, "program start ....");

   init();

   for(;;){
      vTaskDelay(pdMS_TO_TICKS(10 * 1000));
   }
}