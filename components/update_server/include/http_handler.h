#include <esp_http_server.h>

class update_handler {
    public:
    static httpd_uri_t get_handler();
};

class hello_handler {
    public:
    static httpd_uri_t get_handler();
};