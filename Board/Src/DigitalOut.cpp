#include "main.h"
#include "DigitalOut.h"


/* @brief Constructor implementation for DigitalOut */
  DigitalOut::DigitalOut(PinName pin) {
                /* @brief extracts port and pin number from PinName */
                  portNum = (pin >> 4) & 0xF;  // Extracts port number
                  pinNum = (pin & 0xF);        // Extracts pin number

                 
    }
