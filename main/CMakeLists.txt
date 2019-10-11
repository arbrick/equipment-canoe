idf_component_register(SRCS "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES "nvs_flash" "bootloader_support" "app_update" "wifi_ap" "update_server")