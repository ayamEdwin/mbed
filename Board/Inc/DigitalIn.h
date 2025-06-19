#ifndef  DIGITALIN_H
#define DIGITALIN_H


#include "main.h"
  
  // Digital In class
class DigitalIn 
{
  private:
    uint8_t portNum;
    uint8_t pinNum;

  public:
    // constructor for initialising GPIO input pin
    DigitalIn(PinName pin);

    // reads the input represented as zero(0) or one(1)
    bool read();

    // returns the mode settings
    void mode(PinMode pull);

    operator bool();
               
  };

  #endif
