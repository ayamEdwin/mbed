#ifndef DIGITALOUT_H
#define DIGITALOUT_H
 
 
 #include "main.h"
 
 class DigitalOut
 {
    public:
      /* @brief constructor to initialize gpio output pins */
      DigitalOut(PinName pin);

      /* @brief writes to specified pin */
      void write(bool value);

      /* @brief return state of output pin*/
      bool read();

      void mode(uint8_t OType);
      void operator=(bool);
      operator bool();

    private:
      uint8_t portNum;
      uint8_t pinNum;

  }; // DigitalOut


  #endif