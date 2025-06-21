#ifndef  ANALOGIN_H
#define ANALOGIN_H

#include "main.h"

class AnalogIn
{
  private:
    uint8_t portNum;
    uint8_t pinNum;
    void calibrate();
    void ADCEnable();
    void ADCDisable();
    void configPin();
  public:
    AnalogIn(pin_name pin);
    float read();
    operator float();
    ~AnalogIn();
};

#endif //ANALOGIN