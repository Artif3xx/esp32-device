/**
 * @author  Castox
 * @file    WiFiScan.cpp
 * @brief   
 */

#include "WiFiScanObj.h"

WiFiScanObj::WiFiScanObj() {

}

WiFiScanObj::~WiFiScanObj() {

}

std::string WiFiScanObj::get_SSID() {
    return this->SSID;
}


void WiFiScanObj::set_SSID(std::string SSID) {
    this->SSID = SSID;
}

int32_t WiFiScanObj::get_RSSI() {
    return this->RSSI;
}


void WiFiScanObj::set_RSSI(int32_t RSSI) {
    this->RSSI = RSSI;
}