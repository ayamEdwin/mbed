#include "DigitalIn.h"

/* @brief Constructor implementation for DigitalIn */
DigitalIn::DigitalIn(PinName pin) 
{
  /* @brief extracts port and pin number from PinName */

  portNum = (pin >> 4) & 0xF;  // Extracts port number
  pinNum = (pin & 0xF);        // Extracts pin number

  //enable port clk
  portClkEn(portNum);

  //Set mode to input
  GpioArray[this->portNum]->MODER &= ~(3ul << (pinNum * 2));
  // configure mode to default
  mode(PullNone);
    
}

 //Read the pin
bool DigitalIn::read() {
 return ((GpioArray[portNum]->IDR) >> pinNum) & 1U;
}

void DigitalIn::mode(PinMode pull) 
{
  //confine the range of the mode
  if(pull >= PullNone && pull <= PullDown) pull = pull;
  else pull = PullNone;
  GpioArray[portNum]->PUPDR &= ~(3ul << (pinNum * 2));
  // Set the mode
  GpioArray[portNum]->PUPDR |= (pull << (pinNum * 2));
  
}

DigitalIn::operator bool() {
  return read();
}

