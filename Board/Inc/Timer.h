#ifndef TIMER_H
#define TIMER_H

#include "main.h"

class Timer
{
  private:
    uint16_t overflow;
  public:
    Timer();
    uint32_t read_ms();
    uint64_t read_us();
    uint16_t read();
    void start();
    void reset();
    void stop();
    ~Timer();
};

#endif