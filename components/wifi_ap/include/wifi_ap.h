#include "esp_system.h"
#include "esp_event_loop.h"

class wifi_ap {
  public:
    wifi_ap(char* ssid, char* password);
    void init();
  private:
    static esp_err_t event_handler(void *ctx, system_event_t *event);
    void init_softap();
    char* ssid;
    char* password;
};

