/**
 * @author  Castox
 * @file    WiFiScanObject.h
 * @brief   
 */

#pragma once 


#include <string>

class WiFiScanObject {
    public:
        /**
         * @brief get function for SSID variable
         * 
         * @return std::string contains the SSID as a string
         */
        std::string get_SSID();

        /**
         * @brief set function for SSID variable
         * 
         * @param SSID contains the SSID as a string
         */
        void set_SSID(std::string SSID);

        /**
         * @brief get function for RSSI variable
         * 
         * @return int32_t contains the RSSI value as integer 
         */
        int32_t get_RSSI();

        /**
         * @brief set function for RSSI variable
         * 
         * @param RSSI contains the RSSI value as integer
         */
        void set_RSSI(int32_t RSSI);

    private:

        /**
         * @brief SSID name from the WiFiScanObject
         * 
         */
        std::string SSID;

        /**
         * @brief RSSI strengh from the WiFiScanObject
         * 
         */
        int32_t RSSI;

};