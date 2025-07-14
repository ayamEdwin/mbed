#include "InterruptIn.h"


 // one for each EXTI0 to EXTI15
InterruptIn* extiLineHandlers[16] = {nullptr};


// configures GPIO settings
void InterruptIn::GPIOx_Init(pin_name pin){
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
bool InterruptIn::read() {
 return ((GPIOPORT->IDR) >> pinNum) & 1U;
}

InterruptIn::operator bool() {
  return read();
}


void InterruptIn::mode(InputConfig pull) 
{
  //confine the range of the mode
  if(pull >= PullNone && pull <= PullDown) pull = pull;
  else pull = PullNone;
  GPIOPORT->PUPDR &= ~(3ul << (pinNum * 2));
  // Set the mode
  GPIOPORT->PUPDR |= (pull << (pinNum * 2));
  
}


/* @brief checks the corresponding ISR for pin using IRQ number */
void InterruptIn::NVIC_Init(void){
          if (pinNum == INDEX_0 || pinNum == INDEX_1){
              __disable_irq();
              NVIC_EnableIRQ(EXTI0_1_IRQn); // enables handler function
              __enable_irq();
          }
          else if (pinNum == INDEX_2 || pinNum == INDEX_3){
              __disable_irq();
              NVIC_EnableIRQ(EXTI2_3_IRQn);
              __enable_irq();
          }
          else {
              __disable_irq();
              NVIC_EnableIRQ(EXTI4_15_IRQn);
              __enable_irq();
          }
}


// constructor implementation
InterruptIn::InterruptIn(pin_name pin){
            GPIOx_Init(pin);
            // enables clock in system configuration register(APB Bus)
            EXTIClkEn();
            // routes pin to appropriate EXTI line
            EXTIRouter(portNum, pinNum);
            // enables interrupt line
            EXTI->IMR |= (0x1 << pinNum);
            // stores pointer by EXTI line
            extiLineHandlers[pinNum] = this;
}


// Rising edge trigger
void InterruptIn::rise(callback userFunc) {
    this->riseCallback = userFunc;
    EXTI->RTSR |= (0x1 << pinNum);
    // selects appropriate ISR for pin
    NVIC_Init();  
}


void InterruptIn::fall(callback userFunc) {
    this->fallCallback = userFunc;
    // enables falling edge
    EXTI->FTSR |= (0x1 << pinNum);     
    NVIC_Init();
}



// enable IRQ
void InterruptIn::enable_irq(){
      __enable_irq();
}

// disable IRQ
void InterruptIn::disable_irq(){
      __disable_irq();
}

// Getter
//uint8_t InterruptIn::getPinNum() const {return pinNum;}


// IRQ Handler
void InterruptIn::interruptHandler(void) {
    if (EXTI->PR & (1 << pinNum)) {
        EXTI->PR |= (1 << pinNum); // Clear interrupt flag

        // checks for edge triggered
        if (EXTI->RTSR & (1 << pinNum)) {
            if (riseCallback) riseCallback();
        }
        if (EXTI->FTSR & (1 << pinNum)) {
            if (fallCallback) fallCallback();
        }
    }
}



// Event handler for EXTI0_1
extern "C" void EXTI0_1_IRQHandler() {
    for (int i = 0; i <= 1; i++) {
        if (extiLineHandlers[i]) {
            extiLineHandlers[i]->interruptHandler();
        }
    }
}


// Event handler for EXTI2_3
extern "C" void EXTI2_3_IRQHandler() {
    for (int i = 2; i <= 3; i++) {
        if (extiLineHandlers[i]) {
            extiLineHandlers[i]->interruptHandler();
        }
    }
}


// Event handler for EXTI4_15
extern "C" void EXTI4_15_IRQHandler() {
    for (int i = 4; i <= 15; i++) {
        if (extiLineHandlers[i]) {
            extiLineHandlers[i]->interruptHandler();
        }
    }
}