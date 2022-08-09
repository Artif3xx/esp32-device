#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#include <stdlib.h>
#include <vector>
#include <string>

// *------------------------------------------------------*
//  display includes
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// *------------------------------------------------------*
//  RF24L01 Module includes
#include <nRF24L01.h>
#include <RF24.h>

// *------------------------------------------------------*
//  BLE Module includes
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// *------------------------------------------------------*
//  include own modules
#include <WiFiScanObject.h>
#include <NRF24l01ScanObject.h>

// *------------------------------------------------------*
// defines for this project
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// define the Pins for the rf24l01 module
#define CE_PIN 4 // ce Pin of rf24l01 module
#define CS_PIN 5 // cs Pin of rf24l01 module

// define the led Pins
#define LED_RED 2
#define LED_GREEN 15

// ble server name define
#define bleServerName "ESP32 Device"

// define Service UUID and Characteristic UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// *------------------------------------------------------*
// function declarations
/* display functions */
void initDisplay();
void setTitle(const char* title);
void setContent(const char* content);
void setTitleIcon();
/* wifi functions */
void initWiFi();
std::vector<WiFiScanObject>  scanWiFi();
void displayWiFiScan(std::vector<WiFiScanObject> scan);
/* nrf24l01 functions */
void initNRF24l01();
NRF24l01ScanObject scanNRF24l01();
void displayNRF24l01Scan(NRF24l01ScanObject scan);
/* led (red & green) functions */
void toggle_red(uint8_t duty);
void toggle_green(uint8_t duty);
/* ble functions */
void initBLE();

// *------------------------------------------------------*
// necessary global variables
unsigned long timestamp;
unsigned int main_delay = 500;
unsigned int counter = 0;
char temp[40];
char temp_title[40];

// boolean value if a led is on or off
bool red_state = false;
bool green_state = false;

// boolean value if a device is connected to the ble server
bool deviceConnected = false;

// *------------------------------------------------------*
// create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, 
  &Wire, OLED_RESET);

// *------------------------------------------------------*
//  create a rf24 radio object
RF24 radio(CE_PIN, CS_PIN);

// *------------------------------------------------------*
// Api ble Characteristic and Descriptor
BLECharacteristic apiCharacteristics(
  "ca73b3ba-39f6-4ab3-91ae-186dc9577d99", 
  BLECharacteristic::PROPERTY_NOTIFY
);
BLEDescriptor apiDescriptor(BLEUUID((uint16_t)0x2903));


// *------------------------------------------------------*
//  Class for the ble server Callback functions
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

// *------------------------------------------------------*
// setup loop of the project
void setup() {
  Serial.begin(115200);
  // set pinmode for the leds
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  // set the right parameters for the display
  initDisplay();

  // simple feedback while executing the setup loop 
  display.clearDisplay();
  setTitle("void setup()");
  setContent("init ESP Device");
  display.display();

  // init NRF24l01 module
  initNRF24l01();

  // init Wifi module
  initWiFi();

  // init BLE module
  // initBLE();
  
  toggle_green(100);

  delay(1500);
}

// *------------------------------------------------------*
// main loop of the project
void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  
  // *** set the Title *** //
  
  // clear the temp_title buffer to refill it again!
  temp_title[0] = '\0';
  // save the timestamp as char variable
  utoa(timestamp, temp, 10);
  // create the title
  strcat(temp_title, "main loop(");
  strcat(temp_title, temp);
  strcat(temp_title, ")");

  setTitle(temp_title);

  // *** RF24 SCANNING *** //
  // displayNRF24l01Scan(scanNRF24l01());
  
  scanWiFi();
  // displayWiFiScan(scanWiFi());

  // this play the bufferd conten
  display.display();
  delay(main_delay);
  timestamp = millis();
}

// *------------------------------------------------------*
//  function definiton
// *------------------------------------------------------*

// *------------------------------------------------------*
//  display functions
/**
 * @brief   init function for the device. should be called in setup() loop
 * 
 */
void initDisplay() {
  Serial.println("Init OLed display");
  // simple funtions to set the right variables for this project
  display.setCursor(0, 0);
  // rotate the display by 180 degree (upside down)
  display.setRotation(2);
  // using white as text color
  display.setTextColor(WHITE);
  // set standard text size
  display.setTextSize(1);
}

/**
 * @brief         Set the Title in the top of the screen and set a underline
 * 
 * @param title   const char* 
 */
void setTitle(const char* title) {
  // display should be cleared fist
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print(title);
  display.drawFastHLine(0, 8, 128, SSD1306_WHITE);
  // use display.display() to write content inside the buffer refresh the dispaly
}

/**
 * @brief           Set the Content under the heading
 * 
 * @param content   const char* 
 */
void setContent(const char* content) {
  // display should be cleared fist.
  // you can set a title fist. This does not collied
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.print(content);
  // use display.display() to write content inside the buffer refresh the dispaly
}

// function to set title icon
void setTitleIcon() {

}

// *------------------------------------------------------*
//  WiFi functions
/**
 * @brief init function for the Wifi module
 * @note  should be called once, inside the setup section
 */
void initWiFi() {
  Serial.println("Init Wifi module");
  // set wifi mode to 'station'
  WiFi.mode(WIFI_STA);
  // disconnect possible devices
  WiFi.disconnect();
  delay(25);
}

/**
 * @brief function to execute a wifi scan. lists all nearby networks and
 *        there encryption type
 * 
 * @return WiFiScanObject*  a list with all scaned itemes, if there is at least one network
 * @return nullptr          if there are no networks available
 */
std::vector<WiFiScanObject> scanWiFi() {
  toggle_green(80);
  timestamp = millis();
  Serial.printf("WiFi-Scan started at tick: %i\n", timestamp);
  Serial.println("+-----------------------------");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();

  if (n == 0) {
    // create a vector with only one item
    std::vector<WiFiScanObject> emptyscan;
    
    // set values as response
    emptyscan[0].set_SSID("nothing found");
    emptyscan[0].set_RSSI(0);

    toggle_red(80);
    // return element
    return emptyscan;
  } else {
    // create a vector for all the wifi networks
    std::vector<WiFiScanObject> wifi_obj(n-1);
    // save the number of network inside a char variable
    char n_buffer[sizeof(n)];
    itoa(n, n_buffer, 10);

    for (uint8_t i = 0; i < n ; ++i) {
      /* create a message for the Serial Monitor */
      Serial.print("(");
      itoa(i+1, n_buffer, 10);
      Serial.print(n_buffer);
      Serial.print(") ");
      Serial.print(WiFi.SSID(i));
      
      Serial.print(" RSSI: ");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dB");

      /* save the data in the wifiscan-object */

      // set SSID and RSSI of the wifi_object      
      //wifi_obj[i].set_SSID(temp.assign(WiFi.SSID(i).c_str()));
      // Serial.println(temp.c_str());
      
      // wifi_obj[i].set_SSID(temp);
      // wifi_obj[i].set_RSSI(WiFi.RSSI(i));
    }

    Serial.printf("(info) this scan took %i ticks\n", millis()-timestamp);
    Serial.println("+-----------------------------");
    toggle_green(80);
    // return the list of scanned items
    return wifi_obj;
  }

}

void displayWiFiScan(std::vector<WiFiScanObject> scan) {
  uint16_t start_line = 10;
  for (auto& i : scan) {
    display.setCursor(0, start_line);
    display.print(i.get_SSID().c_str());
    // Serial.println(i.get_SSID().c_str());
    display.display();
    start_line += 8;
  }
}

// *------------------------------------------------------*
//  nrf24l01 functions
/**
 * @brief init function for the nrf24l01 module
 * @note  should be called once, inside the setup section
 */
void initNRF24l01() {
  Serial.println("Init NRF24l01 module");
  // init radio
  radio.begin();
  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();
  toggle_green(100);
  delay(25);
}

/**
 * @brief function to scan with the nrf24l01 module
 * 
 */
NRF24l01ScanObject scanNRF24l01() {
  Serial.printf("NRF24l01-Scan started at tick: %i\n", millis());
  Serial.println("+-----------------------------");
  
  toggle_green(80);
  NRF24l01ScanObject scanObj;
  scanObj.reset_Values();

  // Scan all channels num_reps times
  int rep_counter = scanObj.scan_repeats;
  while (--rep_counter) {
    // flush the red led
    // scan each channel except 0
    for (int i = scanObj.num_channels ; i > 0 ; --i) {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(64);
      radio.stopListening();

      // Did we get a carrier?
      if (radio.testCarrier())
        // increment the value -> max value is the number of scan repeats
        scanObj.set_Value(i, scanObj.get_Value(i)+1);
    }
  }

  /* send data to Serial Monitor */
  char n_buffer[sizeof(scanObj.num_channels)];
  for (int i = 0; i <= scanObj.num_channels ; ++i) {
    itoa(i, n_buffer, 10);
    Serial.printf("Channel (%i): \tValue %i\n", i, scanObj.get_Value(i));
  }
  Serial.println("+-----------------------------");

  toggle_green(80);
  return scanObj;
}

/**
 * @brief function to buffer the scanned values to the display as a graph
 * @note  it´s necessary to execute display.display() after that
 */
void displayNRF24l01Scan(NRF24l01ScanObject scan) {
  // Print out channel measurements, clamped to a single hex digit
  for (int i = 0 ; i < scan.num_channels ; i++) {
    // draw vertikal lines with the hight of the collected value in the channel
    display.drawFastVLine(i, 40, scan.get_Value(i)/10, SSD1306_WHITE);
    display.drawFastVLine(i, 40-scan.get_Value(i)/10, scan.get_Value(i)/10, SSD1306_WHITE);
  }

  // draw horizontal line as x axis
  display.drawFastHLine(0, 40, 128, SSD1306_WHITE);
}

// *------------------------------------------------------*
//  led functions
/**
 * @brief   toggls the red led in one Sec with a duty cycle
 * @param   uint8_t duty  value between 1 - 100  
 */
void toggle_red(uint8_t duty) {
  // duty of 1 sec: 100%=1sec 50%=0,5sec
  uint8_t on_time = 10*duty;
  uint8_t off_time = 1000-on_time;

  if (red_state) {
    digitalWrite(LED_RED, LOW);
  }
  digitalWrite(LED_RED, HIGH);
  delay(on_time);
  digitalWrite(LED_RED, LOW);
  delay(off_time);
}

/**
 * @brief   toggls the green led in one Sec with a duty cycle
 * @param   uint8_t duty  value between 1 - 100  
 */
void toggle_green(uint8_t duty) {
  uint8_t on_time = 10*duty;
  uint8_t off_time = 1000-on_time;

  if (green_state) {
    digitalWrite(LED_GREEN, LOW);
  }
  digitalWrite(LED_GREEN, HIGH);
  delay(on_time);
  digitalWrite(LED_GREEN, LOW);
  delay(off_time);
}

// *------------------------------------------------------*
//  ble functions

void initBLE() {
  Serial.println("Init Bluetooth-Low-Energy module");
  // creating the BLE Device
  BLEDevice::init(bleServerName);

  // create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // create the BLE Service
  BLEService *apiService = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristics and Create a BLE Descriptor
  // Humidity
  apiService->addCharacteristic(&apiCharacteristics);
  apiDescriptor.setValue("Init Api Ble Service");
  apiCharacteristics.addDescriptor(new BLE2902());

  // start the service
  apiService->start();

  // start Advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  
  Serial.println("done");
  Serial.println("Waiting a client connection to notify ...");
}