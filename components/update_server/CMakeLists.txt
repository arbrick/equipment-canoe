idf_component_register(SRCS "hello_handler.cpp" "sha256.cpp" "update_handler.cpp" "update_server.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES "mbedtls" "esp_http_server" "esp_http_client" "app_update")