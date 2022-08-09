/**
 * @author  Castox
 * @file    NRF24l01ScanObjet.cpp
 * @brief   
 */

#include <NRF24l01ScanObject.h>

void NRF24l01ScanObject::set_Value(uint8_t channel, uint8_t value) {
    // check if channel is available to write
    if (!(channel > NUM_CHANNELS)) {
        // save value in array
        this->values[channel] = value;
    }

    return;
}

uint8_t NRF24l01ScanObject::get_Value(uint8_t channel) {
    // check if channel is available to write
    if (!(channel > NUM_CHANNELS)) {
        // return the requsted value
        return this->values[channel];
    }

    // return 0 - value is not available
    return 0;
}

void NRF24l01ScanObject::reset_Values() {
    // set all values to zero
    memset(this->values, 0, sizeof(this->values));
}