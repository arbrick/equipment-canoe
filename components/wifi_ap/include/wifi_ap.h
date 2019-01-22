class wifi_ap {
  public:
    /**
     * @brief Construct a new WiFi ap object
     * 
     * @param ssid [in] Name of the created network
     * @param password  [in] Password for the created network, empty string for open auth.
     */
    wifi_ap(char* ssid, char* password);
    /**
     * @brief Start the WiFi access point.
     * @details IP/GW: 192.168.1.1
     * Netmask: 255.255.255.0
     * 
     */
    void start();
    /**
     * @brief Stop the WiFi access point.
     * 
     */
    void stop();
  private:
    char* ssid;
    char* password;
};

