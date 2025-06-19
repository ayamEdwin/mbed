#include "main.h"
  
  
  // Digital In class
  class DigitalIn {
                  private:
                          uint32_t portNum;
                          uint32_t pinNum;
                          PinName user_pin;
                    
                  public:
                          // constructor for initialising GPIO input pin
                          DigitalIn(PinName pin);

                          //// Getter for pin number
                          //uint32_t get_pin_num();

                          // reads the input represented as zero(0) or one(1)
                          int read();

                          // returns the mode settings
                          //void mode(PinMode pull);
    };
