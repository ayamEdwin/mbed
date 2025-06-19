#include "DigitalOut.h"

/* @brief Constructor implementation for DigitalOut */
DigitalOut::DigitalOut(PinName pin) 
{
  /* @brief extracts port and pin number from PinName */
  portNum = (pin >> 4) & 0xF;  // Extracts port number
  pinNum = (pin & 0xF);        // Extracts pin number

  portClkEn(portNum);
  //Set mode to output
  GpioArray[portNum]->MODER  &= ~(3ul << (pinNum* 2));
  GpioArray[portNum]->MODER |= (1ul << (pinNum* 2));

  // use mode to default
  this->mode(PushPull);
}

bool DigitalOut::read() 
{
 //Read the pin
  return ((GpioArray[portNum]->ODR >>pinNum) & 1ul);
}

void DigitalOut::write(bool state) 
{
  //Write to pin
  if(!state) GpioArray[portNum]->ODR &= ~(1ul << pinNum);
  else GpioArray[portNum]->ODR |= (1ul << pinNum);
}

void DigitalOut::operator=(bool state) 
{
  write(state);
}

DigitalOut::operator bool()
{
  return read();
}

void DigitalOut::mode(uint8_t OType) 
{
  // set the output type
  if(OType == OpenDrain) GpioArray[portNum]->OTYPER |= (1ul << pinNum);
  else GpioArray[portNum]->OTYPER &= ~(1ul << pinNum);  // Push Pull
}
