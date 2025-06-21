#ifndef DIGITALOUT_H
#define DIGITALOUT_H
#include "main.h"



  class DigitalOut {

   public:
       // @brief constructor to initialize gpio output pins
       DigitalOut(PinName pin);

      // @brief writes to specified pin
       void write(int value);

      // @brief return state of output pin
       bool read()const;

       void operator=(int value);

       operator int() const;
       void setSpeed(GPIOSpeed speed);

       private:
           GPIO_TypeDef *gpioPort;
           uint8_t gpioPin;

           void enableClock();

}; // DigitalOut


#endif 
