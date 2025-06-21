#include "SPISlave.h"


SPISlave::SPISlave(pin_name mosi, pin_name miso, pin_name clk, pin_name ss):SPI(mosi, miso, clk)
{
  portNum = (ss >> 4) & 0xF;
  portClkEn(portNum);

  SPIPORT->CR1 &= ~SPI_CR1_MSTR;  //salve mode
  SPIPORT->CR2 &= ~SPI_CR2_SSOE;
    
  //configure SS pin as AF
  GPIOPORT->MODER &= ~(3ul << SSPinNum*2);
  GPIOPORT->MODER |= (2ul << SSPinNum*2);
}

/* @brief polls to determine whether data is received
   @return bool

*/

bool SPISlave::receive() 
{
  SPIPORT->CR1 |= SPI_CR1_SPE;
  return (SPIPORT->SR & SPI_SR_RXNE);
}


/* @brief send data to master device
*  @param uint8_t
*/

void SPISlave::reply(uint8_t data)
{
  SPIPORT->CR1 |= SPI_CR1_SPE;
  while(!(SPIPORT->SR & SPI_SR_TXE));
  *(uint8_t*)&(SPIPORT->DR) = data;
  while((SPIPORT->SR & SPI_SR_BSY));
}


/* @brief return data from master device
*  @return uint8_t
*/ 

uint8_t SPISlave::read() 
{
  uint8_t rxdata = 0;
  SPIPORT->CR1 |= SPI_CR1_SPE;
  if((SPIPORT->SR & SPI_SR_RXNE))
  {
    rxdata = *(uint8_t*)&(SPIPORT->DR);
  }
  return rxdata;
}


