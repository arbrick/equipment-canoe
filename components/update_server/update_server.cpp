#include "esp_log.h"
#include "update_server.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include "http_handler.h"

static const char* TAG = "update_server";

update_server::update_server(){
    config = HTTPD_DEFAULT_CONFIG();
}

void update_server::start_webserver(){
    httpd_handle_t server = {};
    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        this->server = server;
        ESP_LOGI(TAG, "Server started!");    
    } else {
        ESP_LOGI(TAG, "Error starting server!");
    }
}

void update_server::stop_webserver(){
    // Stop the httpd server
    httpd_stop(server);
    this->server = NULL;
}

void register_handlers(httpd_handle_t server){
    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");
    
    httpd_uri_t hello_h = hello_handler::get_handler();
    httpd_register_uri_handler(server, &hello_h);
    httpd_uri_t update_h = update_handler::get_handler();
    httpd_register_uri_handler(server, &update_h);
}

void update_server::start(){
    start_webserver();
    register_handlers(server);
}

void update_server::stop(){
    stop_webserver();
}
