#include "esp_log.h"
#include "wifi_ap.h"

extern "C" {
    void init_softap(char* ssid, char* password);
    void stop_softap();
}

static const char* TAG = "wifi_ap";

wifi_ap::wifi_ap(char* ssid, char* password){
  this->ssid = ssid;
  this->password = password;
}

void wifi_ap::start(){
  ESP_LOGI(TAG, "ssid: %s, password: %s", ssid, password);
  init_softap(ssid, password);
}

void wifi_ap::stop(){
  stop_softap();
}