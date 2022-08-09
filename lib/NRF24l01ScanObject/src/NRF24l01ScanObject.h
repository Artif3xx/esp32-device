/**
 * @author  Castox
 * @file    NRF24l01ScanObjet.h
 * @brief   
 */

#pragma once 

#include <Arduino.h>

// number of channels that can be recorded
#define NUM_CHANNELS 128
// how often the scan should repeat
#define SCAN_REPEATS 100

/**
 * @brief Class to save the Values while scanning with
 *        the nrf24l01 module.
 */
class NRF24l01ScanObject {
    public:
        /**
         * @brief Set the Value object
         * 
         * @param channel
         * @param value
         */
        void set_Value(uint8_t channel, uint8_t value);

        /**
         * @brief Get the Value object
         * 
         * @param channel   requested channel for the value
         * @return uint8_t  saved value in the channel 
         */
        uint8_t get_Value(uint8_t channel);

        void reset_Values();
        
        const unsigned int scan_repeats = SCAN_REPEATS;

        const unsigned int num_channels = NUM_CHANNELS;
    
    private:
        /**
         * @brief uint8_t array to save the values
         * 
         */
        uint8_t values[NUM_CHANNELS];

        
};