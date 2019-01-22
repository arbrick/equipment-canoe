#include "http_handler.h"
#include <string>

static const char* TAG = "hello_handler";

esp_err_t hello_get_handler(httpd_req_t *req){
    std::string response = "Hello World";
    httpd_resp_send(req, response.c_str(), response.length());
    return ESP_OK;
}

httpd_uri_t hello_handler::get_handler(){
    return {
        .uri       = "/hello",
        .method    = HTTP_GET,
        .handler   = hello_get_handler,
    };
}