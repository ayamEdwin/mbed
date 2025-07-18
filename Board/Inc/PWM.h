#include "main.h"

#ifndef PWMOUT_H
#define PWMOUT_H


  class PwmOut
  {
    private:
      void configTIM_CHN();
      bool isPwmPin();
    public:
      PwmOut(pin_name pin);
      void write(float);
      void operator=(float);
      void period(float);
    protected:
    uint8_t portNum,pinNum,chn,tim;
  };

#endif // PWM_H