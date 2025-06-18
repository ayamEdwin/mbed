#include "main.h"
#include "DigitalIn.h"


/* @brief Constructor implementation for DigitalIn */
  DigitalIn::DigitalIn(PinName pin) {
                /* @brief extracts port and pin number from PinName */
                  portNum = (pin >> 4) & 0xF;  // Extracts port number
                  pinNum = (pin & 0xF);        // Extracts pin number

                 
    }
