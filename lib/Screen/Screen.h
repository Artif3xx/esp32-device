/**
 * @author  Castox
 * @file    oled096.h
 * @brief   functions to display the collected contend
 */ 

#pragma once

// *---------------------------*
//  system includes

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Wire.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

/**
 * @brief Screen class to manage content
 * 
 */
class Screen {
    public:

        /**
         * @brief Construct a new sceen object
         *   
         */
        Screen();

        /**
         * @brief Destroy the screen object
         * 
         */
        ~Screen();

        Adafruit_SSD1306* get_display();
        

        /**
         * @brief Set the title object
         * 
         * @param title
         */
        void set_title(const char title[]);

        void set_title_icon();

        void print_content();

    private:
        /**
         * @brief main object for the display. represents the buffer of the screen
         * 
         */
        Adafruit_SSD1306 *display = new Adafruit_SSD1306 [1];

};
