#include "DigitalOut.h"

/* @brief Constructor implementation for DigitalOut */
 DigitalOut::DigitalOut(pin_name pin) 
{
  /* @brief extracts port and pin number from PinName */
  portNum = (pin >> 4) & 0xF;  // Extracts port number
  pinNum = (pin & 0xF);        // Extracts pin number

  portClkEn(portNum);
  //Set mode to output
  GPIOPORT->MODER  &= ~(3ul << (pinNum* 2));
  GPIOPORT->MODER |= (1ul << (pinNum* 2));

  // use mode to default
  this->mode(PushPull);
}



/* @brief writes to specified pin 
 * @param value value to write to pin
 */ 
void DigitalOut::write(bool state) 
{
  //Write to pin
  if(!state) GPIOPORT->ODR &= ~(1ul << pinNum);
  else GPIOPORT->ODR |= (1ul << pinNum);
}

/* @brief sets the mode of the specified pin 
 * @param mode of pin
 */ 
void DigitalOut::mode(OutputConfig OType) 
{
  if(OType == OpenDrain) GPIOPORT->OTYPER |= (1ul << pinNum);
  else GPIOPORT->OTYPER &= ~(1ul << pinNum);  // Push Pull
}


/*  @brief Return the output setting, represented as 0 or 1 (bool)
 *  a boolean representing the output setting of the pin,
 *    0 for logical 0, 1 for logical 1
 */
bool DigitalOut::read() 
{
  return ((GPIOPORT->ODR >>pinNum) & 1ul);
}

/* @brief A shorthand for write() using the assignment
 * operator which copies the state from the DigitalOut argument.
 * \sa DigitalOut::write()
 */
void DigitalOut::operator=(bool state) 
{
  write(state);
}

/* @brief A shorthand for read() using the assignment
 * operator which copies the state from the DigitalOut argument.
 * \sa DigitalOut::write()
 */

 DigitalOut::operator bool()
{
  return read();
}


/* @brief defines speed mode of gpio pins
 * @param speed speed of gpio pin
 * (low, medium, high)
 */
void DigitalOut::setSpeed(GPIOSpeed speed){
    GPIOPORT->OSPEEDR &= ~(0b11 << (2 * pinNum));
    GPIOPORT->OSPEEDR |= ~(speed << (2 * pinNum));
}

