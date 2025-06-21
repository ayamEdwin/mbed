#ifndef SPI_H
#define SPI_H

#include "main.h"

class SPI
{
  public:
    SPI(uint8_t,uint8_t,uint8_t);
    ~SPI();
    void format(uint8_t bit_len,uint8_t mode);
    void frequency(uint32_t freq);
    uint8_t write(uint8_t);
  protected:
    uint8_t portNum, mosiPinNum, misoPinNum, clkPinNum;
    void spiConfig();
}; //SPI_H

#endif