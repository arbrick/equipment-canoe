#include "esp_log.h"
#include "update_server.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include <string>

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

esp_err_t hello_get_handler(httpd_req_t *req){
    std::string response = "Hello World";
    httpd_resp_send(req, response.c_str(), response.length());
    return ESP_OK;
}

void update_server::register_handlers(){
    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");

    httpd_uri_t hello = {
        .uri       = "/hello",
        .method    = HTTP_GET,
        .handler   = hello_get_handler,
    };
    httpd_register_uri_handler(server, &hello);
}

void update_server::start(){
    start_webserver();
    register_handlers();
}

void update_server::stop(){
    stop_webserver();
}
