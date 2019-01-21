#include <esp_http_server.h>


class update_server {
  public:
    update_server();
    void start();
    void stop();
  private:
    httpd_config_t config;
    httpd_handle_t server;
    void start_webserver ();
    void stop_webserver ();
    void register_handlers();
};