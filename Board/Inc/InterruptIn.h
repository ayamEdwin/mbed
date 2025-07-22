#ifndef INTERRUPT_IN_H
#define INTERRUPT_IN_H

#include "main.h"


// pointer to callback
typedef void (*callback) (void);


class InterruptIn {
      public:
            /* @brief constructor for overall pin initialization
             * @param pin InterruptIn pin to connect to
             */
            InterruptIn(pin_name pin);
            /* @brief Read the input, represented as 0 or 1 (bool) */
            bool read();
            /* @brief short hand of read */
            operator bool();
            /* @brief attach a function to call when a rising edge
             * occurs on the input Interrupts are enabled for the pin.
             */
            void rise(callback userFunc);
            /* @brief attach a function to call when a falling edge
             * occurs on the input Interrupts are enabled for the pin.
             */
            void fall(callback userFunc);
            /* @brief sets the mode of pin*/
            void mode(InputConfig pull);
            /* @brief enables IRQ*/
            void enable_irq();
             /* @brief disables IRQ*/
            void disable_irq();

            /* @brief interrupt event handler */
            void interruptHandler(void);
            
      private:
            uint8_t portNum;
            uint8_t pinNum;
            callback riseCallback = nullptr;
            callback fallCallback = nullptr;

            // prevents copying to maintain unique EXTI lines
            InterruptIn(const InterruptIn&) = delete;
            InterruptIn& operator=(const InterruptIn&) = delete;

             /* @brief configures AHB, APB buses and initialise pins */
            void GPIOx_Init(pin_name pin);
            void NVIC_Init(void);

      //protected:
            // getter for accessing pinNum
            //static uint8_t getPinNum() const;
        

};

#endif