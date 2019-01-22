#include "esp_log.h"
#include "wifi_ap.h"
#include "update_server.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_flash_partitions.h"
#include "esp_partition.h"
#include "esp_ota_ops.h"

#define SHA_256_HASH_LEN 32

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


static void print_sha256 (const uint8_t *image_hash, const char *label)
{
    char hash_print[SHA_256_HASH_LEN * 2 + 1];
    hash_print[SHA_256_HASH_LEN * 2] = 0;
    for (int i = 0; i < SHA_256_HASH_LEN; ++i) {
        sprintf(&hash_print[i * 2], "%02x", image_hash[i]);
    }
    ESP_LOGI(TAG, "%s: %s", label, hash_print);
}

static void check_current_firmware(){
    uint8_t sha_256[SHA_256_HASH_LEN] = { 0 };
    esp_partition_t partition;

    // get sha256 digest for the partition table
    partition.address   = ESP_PARTITION_TABLE_OFFSET;
    partition.size      = ESP_PARTITION_TABLE_MAX_LEN;
    partition.type      = ESP_PARTITION_TYPE_DATA;
    esp_partition_get_sha256(&partition, sha_256);
    print_sha256(sha_256, "SHA-256 for the partition table: ");

    // get sha256 digest for bootloader
    partition.address   = ESP_BOOTLOADER_OFFSET;
    partition.size      = ESP_PARTITION_TABLE_OFFSET;
    partition.type      = ESP_PARTITION_TYPE_APP;
    esp_partition_get_sha256(&partition, sha_256);
    print_sha256(sha_256, "SHA-256 for bootloader: ");

    // get sha256 digest for running partition
    esp_partition_get_sha256(esp_ota_get_running_partition(), sha_256);
    print_sha256(sha_256, "SHA-256 for current firmware: ");

    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_ota_img_states_t ota_state;
    if (esp_ota_get_state_partition(running, &ota_state) == ESP_OK) {
        if (ota_state == ESP_OTA_IMG_PENDING_VERIFY) {
            // run diagnostic function ...
            bool diagnostic_is_ok = true;
            if (diagnostic_is_ok) {
                ESP_LOGI(TAG, "Diagnostics completed successfully! Continuing execution ...");
                esp_ota_mark_app_valid_cancel_rollback();
            } else {
                ESP_LOGE(TAG, "Diagnostics failed! Start rollback to the previous version ...");
                esp_ota_mark_app_invalid_rollback_and_reboot();
            }
        }
    }
}

void init(){
  init_nvs();
  
  check_current_firmware();

  wifi_ap* ap = new wifi_ap("canoe_paddle_0", "mypassword");
  ap->start();

  update_server* server = new update_server();
  server->start();
  ESP_LOGI(TAG, "Startup Complete");
}

void app_main(void) {
  esp_log_level_set("*", ESP_LOG_DEBUG);
  init();
  ESP_LOGI(TAG, "Startup Complete");
}