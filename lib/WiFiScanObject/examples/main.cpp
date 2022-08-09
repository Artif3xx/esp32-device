/**
 * @author  Castox
 * @file    main.cpp
 * @brief   example for the 'WiFiScan' -lib for this project
 */ 

#include <WiFiScanObject.h>
#include <WiFi.h>

// function declaration
WiFiScanObject* scanWifi();

void setup() {
    /* setup code section */
}

void loop() {
    /* main loop section */
}

/**
 * @brief function to execute a wifi scan. lists all nearby networks and
 *        there encryption type
 * 
 * @return WiFiScanObject*  a list with all scaned itemes, if there is at least one network
 * @return nullptr          if there are no networks available
 */
WiFiScanObject* scanWifi() {
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();

  if (n == 0) {
    // return if no networks found
    return nullptr;
  } else {
    WiFiScanObject wifi_obj[n-1];

    // save the number of network inside a char variable
    char n_buffer[sizeof(n)];
    itoa(n, n_buffer, 10);

    for (uint8_t i = 0; i < n ; ++i) {
      // set SSID and RSSI of the wifi_object
      wifi_obj[i].set_SSID(WiFi.SSID(i).c_str()); // error here
      wifi_obj[i].set_RSSI(WiFi.RSSI(i));
    }

    // return the list of scanned items
    return wifi_obj;
  }

}
