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


class Screen {
    public:

        /**
         * @brief Construct a new sceen object
         * 
         * @param init_display a Adafruit_SSD1306 opbject
         */
        Screen(Adafruit_SSD1306 &init_display);

        /**
         * @brief Destroy the screen object
         * 
         */
        ~Screen();
        

        /**
         * @brief Set the title object
         * 
         * @param title
         */
        void set_title(const char title[]);

        void print_content();

    private:
        /**
         * @brief main object for the display. represents the buffer of the screen
         * 
         */
        Adafruit_SSD1306 *display;

};
