#include "Servo.h"

#define MAX_PULSEWIDTH 2640
#define MIN_PULSEWIDTH 355
#define RANGE (MAX_PULSEWIDTH - MIN_PULSEWIDTH)


 Servo::Servo(pin_name pin):PwmOut(pin){
  TIMER->PSC = (SystemCoreClock/1000000)-1; 
  TIMER->ARR = 20000; 
  TIMER->EGR |= TIM_EGR_UG;
}

void Servo::angle(uint16_t degree){
//constrain the angle within the range
  if(degree > 180) degree = 180;

  pulseWidth = MIN_PULSEWIDTH + (degree/180.0)*RANGE;

  if(chn == channel1) 
    TIMER->CCR1 = pulseWidth;
  else if(chn == channel2) 
    TIMER->CCR2 = pulseWidth; 
  else if(chn == channel3) 
    TIMER->CCR3 = pulseWidth; 
  else if(chn == channel4) 
    TIMER->CCR4 = pulseWidth;

}