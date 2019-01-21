#include "esp_log.h"
#include "wifi_ap.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "string.h"

static const char* TAG = "wifi_ap";

wifi_ap::wifi_ap(char* ssid, char* password){
  this->ssid = ssid;
  this->password = password;
}

static void start_dhcp_server(){
    
    	// initialize the tcp stack
	    tcpip_adapter_init();
        // stop DHCP server
        ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
        // assign a static IP to the network interface
        tcpip_adapter_ip_info_t info;
        memset(&info, 0, sizeof(info));
        IP4_ADDR(&info.ip, 192, 168, 1, 1);
        IP4_ADDR(&info.gw, 192, 168, 1, 1);//ESP acts as router, so gw addr will be its own addr
        IP4_ADDR(&info.netmask, 255, 255, 255, 0);
        ESP_ERROR_CHECK(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &info));
        // start the DHCP server   
        ESP_ERROR_CHECK(tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP));
        printf("DHCP server started \n");
}

esp_err_t wifi_ap::event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR " join, AID=%d",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "station:" MACSTR " leave, AID=%d",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
        break;
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "AP Start");
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "AP Stop");
        break;
    default:
        break;
    }
    return ESP_OK;
}


void wifi_ap::init_softap()
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    wifi_ap_config_t ap_config = {};
    memcpy(ap_config.ssid, ssid, strlen(ssid));
    memcpy(ap_config.password, password, strlen(password));
    ap_config.ssid_len = strlen(ssid);
    ap_config.max_connection = 1;
    ap_config.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    ap_config.beacon_interval = 100;

    wifi_config_t wifi_config = {
        .ap = ap_config
    };

    if (strlen(this->password) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    start_dhcp_server();
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "wifi_init_softap finished.");
}

void wifi_ap::init(){
  ESP_LOGI(TAG, "ssid: %s, password: %s", ssid, password);
  init_softap();
}