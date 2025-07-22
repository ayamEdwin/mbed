#include "Timer.h"
Timer duration;

void wait_us(uint32_t microsec)
{
  duration.start();
  while(duration.read_us() < microsec);
  duration.stop();
}

void wait(float sec) 
{
  duration.start();
  while(duration.read_us() < sec*1000000);
  duration.stop();
}


void wait_ms(uint16_t milisec)
{
  duration.start();
  while(duration.read_ms() < milisec);
  duration.stop();
}