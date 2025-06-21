#include "DigitalIn.h"

/* @brief Constructor implementation for DigitalIn */
DigitalIn::DigitalIn(pin_name pin) 
{
  /* @brief extracts port and pin number from PinName */

  portNum = (pin >> 4) & 0xF;  // Extracts port number
  pinNum = (pin & 0xF);        // Extracts pin number

  //enable port clk
  portClkEn(portNum);

  //Set mode to input
  GPIOPORT->MODER &= ~(3ul << (pinNum * 2));
  // configure mode to default
  mode(PullNone);
    
}

 //Read the pin
bool DigitalIn::read() {
 return ((GPIOPORT->IDR) >> pinNum) & 1U;
}

void DigitalIn::mode(InputConfig pull) 
{
  //confine the range of the mode
  if(pull >= PullNone && pull <= PullDown) pull = pull;
  else pull = PullNone;
  GPIOPORT->PUPDR &= ~(3ul << (pinNum * 2));
  // Set the mode
  GPIOPORT->PUPDR |= (pull << (pinNum * 2));
  
}

DigitalIn::operator bool() {
  return read();
}

