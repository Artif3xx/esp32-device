/**
 * @author  Castox
 * @file    main.cpp
 * @brief   device to scan wifi and some other frequenzes. All collected stuff
 *          will be displaied on the 0,96 zoll oled screen.
 */ 

// *---------------------------*
//  system includes

#include <Arduino.h>

#include <SPI.h>
#include <WiFi.h>

// *---------------------------*
//  private includes

#include "Screen.h"
#include "WiFiScanObj.h"


// *---------------------------*
//  Screen initiation
// *---------------------------*

Screen screen;

// *---------------------------*
//  RF24L01 Module initiation
// *---------------------------*

#include "nRF24L01.h"
#include "RF24.h"

#define CE_PIN 4 // ce Pin of rf24l01 module
#define CS_PIN 5 // cs Pin of rf24l01 module

RF24 radio(CE_PIN, CS_PIN);
const uint8_t num_channels = 128;
uint8_t values[num_channels];


// *---------------------------*
//  Device Led´s
// *---------------------------*

#define LED_RED 2
bool red_state = false;
#define LED_GREEN 15
bool green_state = false;


// *---------------------------*
//  Drehregler initiation
// *---------------------------*

#define CLK_PIN 20
#define DT_PIN 21


// *---------------------------*
//  Function declaration
// *---------------------------* 

void toggle_red(uint8_t duty);
void toggle_green(uint8_t duty);

/**
 * @brief   main setup loop from the esp32-device
 */
void setup() {

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  toggle_red(100); // duty cicly = 100%
  toggle_green(100); // duty cicly = 100%

  Serial.begin(115200);

  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!screen.get_display()->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  screen.set_title("setup loop");
  

  delay(20);
  toggle_green(100);

  /*
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  */

  toggle_green(100);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(25);

  screen.get_display()->setCursor(30, 30);
  screen.get_display()->println("Setup Done!");
  screen.get_display()->display();
  delay(25);

  toggle_green(100);
  radio.begin();
  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  // clear display befor sneding new data to display
  // otherwise the pixels will overlap
  screen.get_display()->clearDisplay();

  toggle_red(100);
  toggle_green(50);
}


const int num_reps = 100;

/**
 * @brief   main loop from the esp32-device
 */
void loop() {
  // create a little underlined title
  screen.get_display()->clearDisplay();

  toggle_green(100);
  screen.set_title("WiFi Scan");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  WiFiScanObj obj[n-1];
  // Serial.println("scan done");
  if (n == 0) {
    screen.get_display()->println("no networks found");
  } else {

    screen.get_display()->print(n);
    screen.get_display()->println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      // display.print(i + 1);
      // display.print(": ");

      obj[i].set_SSID(WiFi.SSID(i).c_str());
      obj[i].set_RSSI(WiFi.RSSI(i));

      
      /*
      display.print(WiFi.SSID(i));
      display.print(" (");
      display.print(WiFi.RSSI(i));
      display.print(") ");
      */
      // display.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      screen.get_display()->println(WiFi.encryptionType(i));
      
      delay(100);  
    }
  }

  screen.get_display()->display();
  delay(1000);
  toggle_green(100);
  
  screen.get_display()->clearDisplay();
  screen.set_title("RF24L01 Scan");

  // *** RF24 SCANNING FUNCTION *** //

  // Clear measurement values
  memset(values, 0, sizeof(values));

  // Scan all channels num_reps times
  int rep_counter = num_reps;
  while (rep_counter--)
  {
    int i = num_channels;
    while (i--) {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(128);
      radio.stopListening();

      // Did we get a carrier?
      if ( radio.testCarrier() )
        ++values[i];
    }
  }

  // Print out channel measurements, clamped to a single hex digit
  for (int i = 0 ; i < num_channels ; i++) {
    Serial.printf("%x",min(0xf,values[i]&0xf));
    
    screen.get_display()->drawFastVLine(i, 40, values[i]/2, SSD1306_WHITE);
    screen.get_display()->drawFastVLine(i, 40-values[i]/2, values[i]/2, SSD1306_WHITE);
  }

  Serial.printf("\n\r"); 
  screen.get_display()->drawFastHLine(0, 40, 128, SSD1306_WHITE);

  screen.get_display()->display();

  delay(1000);
  toggle_red(100);

}


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
