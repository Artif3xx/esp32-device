/**
 * @author  Castox
 * @file    WiFiScan.cpp
 * @brief   
 */

#include <string>

class WiFiScanObj {
    public:
        WiFiScanObj();

        ~WiFiScan();

        std::string get_SSID();

        void set_SSID(std::string SSID);

        std::string get_RSSI();

        void set_RSSI(std::string RSSI);

    private:

        std::string SSID;

        int32_t RSSI;

};