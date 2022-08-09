/**
 * @author  Castox
 * @file    WiFiScanObject.cpp
 * @brief   
 */

#include <WiFiScanObject.h>

std::string WiFiScanObject::get_SSID() {
    return this->SSID;
}

void WiFiScanObject::set_SSID(std::string SSID) {
    this->SSID = SSID;
}

int32_t WiFiScanObject::get_RSSI() {
    return this->RSSI;
}

void WiFiScanObject::set_RSSI(int32_t RSSI) {
    this->RSSI = RSSI;
}