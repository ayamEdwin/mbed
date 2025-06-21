#ifndef SPISLAVE_H
#define SPISLAVE_H

#include "SPI.h"

class SPISlave:public SPI
{
  protected:
    uint8_t SSPinNum;
    uint8_t SSPortNum;
  public:
    SPISlave(pin_name,pin_name,pin_name,pin_name);
    void reply(uint8_t);
    bool receive();
    uint8_t read();
    uint8_t write(uint8_t) = delete;
};  // SPISLAVE_H


#endif
