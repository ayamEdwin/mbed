#include "main.h"
#include "DigitalOut.h"


/*  @brief constructor implementation for DigitalOut
 *  @param PinName name of gpio pin
 */
DigitalOut::DigitalOut(PinName pin)
       :gpioPort(pin.port), gpioPin(pin.pin){
       
       // enables gpio clock
       enableClock();
       gpioPort->MODER &= ~(0b11 << (2 * gpioPin));
       gpioPort->MODER |= (0b01 << (2 * gpioPin));

       write(0);
       
}


// @brief enables gpio clock for appropriate pin
void DigitalOut::enableClock(){
       
       if (gpioPort == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
       else if (gpioPort == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
       else if (gpioPort == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
       else if (gpioPort == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
       else if (gpioPort == GPIOF) RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
}


/* @brief writes to specified pin 
 * @param value value to write to pin
 */ 
void DigitalOut::write(int value){
      if (value)
        gpioPort->BSRR = (1 << gpioPin);
      else 
         gpioPort->BSRR = (1 << (gpioPin + 16));
}


/*  @brief Return the output setting, represented as 0 or 1 (bool)
 *  a boolean representing the output setting of the pin,
 *    0 for logical 0, 1 for logical 1
 */
bool DigitalOut::read()const{
      return((gpioPort->ODR>>gpioPin) & 1ul)? 1 : 0;

}


/* @brief A shorthand for write() using the assignment
 * operator which copies the state from the DigitalOut argument.
 * \sa DigitalOut::write()
 */
void DigitalOut::operator=(int value){
      write(value);
}

/* @brief A shorthand for read() using the assignment
 * operator which copies the state from the DigitalOut argument.
 * \sa DigitalOut::write()
 */
DigitalOut::operator int() const{
      return read();
}


/* @brief defines speed mode of gpio pins
 * @param speed speed of gpio pin
 * (low, medium, high)
 */
void DigitalOut::setSpeed(GPIOSpeed speed){
    gpioPort->OSPEEDR &= ~(0b11 << (2 *gpioPin));
    gpioPort->OSPEEDR |= ~(speed << (2 *gpioPin));
}
