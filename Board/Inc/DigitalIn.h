#include "main.h"

#ifndef DIGITALIN_H
#define DIGITALIN_H

  
  // Digital In class
class DigitalIn 
{
  private:
    uint8_t portNum;
    uint8_t pinNum;

  public:
    // constructor for initialising GPIO input pin
    DigitalIn(pin_name pin);

    // reads the input represented as zero(0) or one(1)
    bool read();

    // returns the mode settings
    void mode(InputConfig pull);

    operator bool();
               
  };

  #endif
