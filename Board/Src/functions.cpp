#include "main.h"


GPIO_TypeDef* GpioArray[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOF};
SPI_TypeDef* SpiArray[] = {SPI1,SPI2};
TIM_TypeDef* TimArray[] = {TIM1,TIM3,TIM6,TIM7,TIM14,TIM15,TIM16,TIM17};
//EXTI_TypeDef* EXTIArray[] = {EXTI0};


void portClkEn(uint8_t port)
{
  switch (port) 
  {
    case PORTA: RCC->AHBENR |= RCC_AHBENR_GPIOAEN; break;
    case PORTB: RCC->AHBENR |= RCC_AHBENR_GPIOBEN; break;
    case PORTC: RCC->AHBENR |= RCC_AHBENR_GPIOCEN; break;
    case PORTD: RCC->AHBENR |= RCC_AHBENR_GPIODEN; break;
    case PORTF: RCC->AHBENR |= RCC_AHBENR_GPIOFEN; break;
  }
}

void timerClkEn(uint8_t timer) 
{
  switch (timer) 
  {
    case tim1:RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; break;
    case tim3:RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; break;
    case tim6:RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; break;
    case tim7:RCC->APB1ENR |= RCC_APB1ENR_TIM7EN; break;
    case tim14:RCC->APB1ENR |= RCC_APB1ENR_TIM14EN; break;
    case tim15:RCC->APB2ENR |= RCC_APB2ENR_TIM15EN; break;
    case tim16:RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; break;
    case tim17:RCC->APB2ENR |= RCC_APB2ENR_TIM17EN; break;
  }
}


void EXTIClkEn(void){
    RCC->APB2ENR |= (0x1 << 0);
}

// optimized EXTI Router
void EXTIRouter(uint8_t port, uint8_t pin_num){
    // PORTA = 0 PORTB = 1 PORTC = 2 PORTD = 3 PORTF = 4 .
    if (port <= PORTF) {
          // clears corresponding EXTI bits
          SYSCFG->EXTICR[pin_num / 4] &= ~(0xF << ((pin_num % 4) * 4));
              /* @brief connects Port of attached pin to appropriate
               * EXTI Line using port and pin number
               */
              SYSCFG->EXTICR[pin_num / 4] |= ((port & 0xF) << ((pin_num % 4) * 4));
    }
}


// EXTI Router for individual pins
/*
void EXTIRouter(uint8_t port, uint8_t pin_num){
      if (port == PORTA){
                SYSCFG->EXTICR[pin_num / 4] |= (0x0 << ((pin_num % 4) * 4)); // Port A = 0

                switch(pin_num){
                            
                            case 0:SYSCFG->EXTICR[INDEX_0] |= SYSCFG_EXTICR1_EXTI0_PA; break;
                            case 1:SYSCFG->EXTICR[INDEX_0] |= SYSCFG_EXTICR1_EXTI1_PA; break;
                            case 2:SYSCFG->EXTICR[INDEX_0] |= SYSCFG_EXTICR1_EXTI2_PA; break;
                            case 3:SYSCFG->EXTICR[INDEX_0] |= SYSCFG_EXTICR1_EXTI3_PA; break;
                            case 4:SYSCFG->EXTICR[INDEX_1] |= SYSCFG_EXTICR2_EXTI4_PA; break;
                            case 5:SYSCFG->EXTICR[INDEX_1] |= SYSCFG_EXTICR2_EXTI5_PA; break;
                            case 6:SYSCFG->EXTICR[INDEX_1] |= SYSCFG_EXTICR2_EXTI6_PA; break;
                            case 7:SYSCFG->EXTICR[INDEX_1] |= SYSCFG_EXTICR2_EXTI7_PA; break;
                            case 8:SYSCFG->EXTICR[INDEX_2] |= SYSCFG_EXTICR3_EXTI8_PA; break;
                            case 9:SYSCFG->EXTICR[INDEX_2] |= SYSCFG_EXTICR3_EXTI9_PA; break;
                            case 10:SYSCFG->EXTICR[INDEX_2] |= SYSCFG_EXTICR3_EXTI10_PA; break;
                            case 11:SYSCFG->EXTICR[INDEX_2] |= SYSCFG_EXTICR3_EXTI11_PA; break;
                            case 12:SYSCFG->EXTICR[INDEX_3] |= SYSCFG_EXTICR4_EXTI12_PA; break;
                            case 13:SYSCFG->EXTICR[INDEX_3] |= SYSCFG_EXTICR4_EXTI13_PA; break;
                            case 14:SYSCFG->EXTICR[INDEX_3] |= SYSCFG_EXTICR4_EXTI14_PA; break;
                            case 15:SYSCFG->EXTICR[INDEX_3] |= SYSCFG_EXTICR4_EXTI15_PA; break;
                      }
          }
}*/

