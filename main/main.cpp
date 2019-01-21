#include "esp_log.h"
#include "wifi_ap.h"
#include "update_server.h"
#include "esp_system.h"
#include "nvs_flash.h"

extern "C" {
  void app_main(void);
}

static const char* TAG = "canoe-paddle-main";

void init_nvs() {
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void init(){
  init_nvs();
  wifi_ap* ap = new wifi_ap("canoe_paddle_0", "mypassword");
  ap->init();

  update_server* server = new update_server();
  server->start();
  ESP_LOGI(TAG, "Startup Complete");
}
void app_main(void) {
  // esp_log_level_set("*", ESP_LOG_ERROR); 
  init();
  ESP_LOGI(TAG, "Done!");
}