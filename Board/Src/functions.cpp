#include "main.h"

GPIO_TypeDef* GpioArray[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOF};
SPI_TypeDef* SpiArray[] = {SPI1,SPI2};
TIM_TypeDef* TimArray[] = {TIM1,TIM3,TIM6,TIM7,TIM14,TIM15,TIM16,TIM17};

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

