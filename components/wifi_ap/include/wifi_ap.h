class wifi_ap {
  public:
    wifi_ap(char* ssid, char* password);
    void start();
    void stop();
  private:
    char* ssid;
    char* password;
};

