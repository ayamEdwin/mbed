#ifndef PWMOUT_H
#define PWMOUT_H

#include "main.h"

class PwmOut
{
  private:
    uint8_t portNum,pinNum,chn,tim;
    void configTIM_CHN();
    bool isPwmPin();
  public:
    PwmOut(pin_name pin);
    void write(float);
    void operator=(float);
    void period(float);
};

#endif // PWM_H