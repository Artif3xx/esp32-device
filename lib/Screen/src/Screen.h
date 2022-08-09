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
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
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

        /**
         * @brief init function for the Adafruit Display Class
         * 
         * @return true 
         * @return false 
         */
        bool begin(void);

        /**
         * @brief Set the title object
         * 
         * @param title
         */
        void set_Title(const char title[]);

        /**
         * @brief Set the title icon object
         * 
         */
        void set_Title_Icon();

        /**
         * @brief print Content under the title
         * 
         */
        void print_Content(const char content[]);

        /**
         * @brief clear the buffer of the screen
         * 
         */
        void clear_Screen();

        /**
         * @brief           function to draw a vertical line
         * 
         * @param x         x position where to start
         * @param y         y position where to start
         * @param h         hight, how long the line should be
         * @param color     in which color the line should be printed
         */
        void draw_vertical_Line(int16_t x, int16_t y, int16_t h, uint16_t color);

        /**
         * @brief           function to draw a horizontal line
         * 
         * @param x         x position where to start
         * @param y         y position where to start
         * @param h         hight, how long the line should be
         * @param color     in which color the line should be printed
         */
        void draw_horizontal_Line(int16_t x, int16_t y, int16_t h, uint16_t color);

    private:
        /**
         * @brief main object for the display. represents the buffer of the screen
         * 
         */
        Adafruit_SSD1306 *display;

};
