#ifndef SERVO_H
#define SERVO_H

#include "PWM.h"

class Servo:public PwmOut{
protected:
  uint16_t pulseWidth;
public:
  Servo(pin_name pin);
  void angle(uint16_t);
  void write(float) = delete;
  void operator=(float) = delete;
  void period(float) = delete;
};


#endif