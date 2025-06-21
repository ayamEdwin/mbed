#ifndef DIGITALOUT_H
#define DIGITALOUT_H

 #include "main.h"
 
 class DigitalOut
 {
    public:
      /* @brief constructor to initialize gpio output pins */
      DigitalOut(pin_name pin);

      /* @brief writes to specified pin */
      void write(bool value);

   /* @brief sets the speed of pin*/
      void setSpeed(GPIOSpeed speed);

      /* @brief return state of output pin*/
      bool read();

      /* @brief sets the mode of pin*/
      void mode(OutputConfig OType);

       /* @brief short hand of write */
      void operator=(bool);

       /* @brief short hand of read */
      operator bool();

    private:
      uint8_t portNum;
      uint8_t pinNum;

  }; // DigitalOut


#endif 
