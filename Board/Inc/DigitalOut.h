 #include "main.h"
 
 
 class DigitalOut{
                  public:
                          // @brief constructor to initialize gpio output pins
                          DigitalOut(PinName pin);

                          // @brief writes to specified pin 
                          void write(int value);
    
                          // @brief return state of output pin
                          int read();

                   private:
                          uint32_t portNum;
                          uint32_t pinNum;

  }; // DigitalOut