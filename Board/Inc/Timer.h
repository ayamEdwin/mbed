#include "main.h"

#ifndef TIMER_H
#define TIMER_H


  class Timer
  {
    private:
      uint64_t overflow;
    public:
      Timer();
      uint32_t read_ms();
      uint64_t read_us();
      uint16_t read();
      void start();
      void reset();
      void stop();
      void wait(float);
      void wait_ms(uint16_t);
      void wait_us(uint32_t);
      ~Timer();
  };

#endif