#include "Timer.h"

static uint8_t count;
uint16_t update = 0;

Timer::Timer()
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

  TIM6->PSC = ((SystemCoreClock)/1000000) - 1;  //1MHz
  TIM6->ARR = 65535;
  TIM6->DIER |= TIM_DIER_UIE;
  TIM6->EGR |= TIM_EGR_UG;
  TIM6->SR &= ~TIM_SR_UIF;

  NVIC_SetPriority(TIM6_IRQn,1);
  NVIC_EnableIRQ(TIM6_IRQn);
  TIM6->CR1 |= TIM_CR1_CEN;

  count++;
}

void Timer::start()
{
  this->overflow = update;
}

void Timer::stop()
{
  this->overflow = 0;
}

uint64_t Timer::read_us()
{
  if(overflow > update)
  {
      return ((UINT64_MAX - overflow + update)*65535+ TIM6->CNT);
  }
  else
  {
    return ((update - overflow)*65535 + TIM6->CNT);
  }
}


void Timer::reset()
{
  this->overflow = update;
}

uint32_t Timer::read_ms()
{
  return (read_us()/1000);
}


uint16_t Timer::read()
{
  return (read_us()/1000000);
}


Timer::~Timer()
{
  count--;
  if(count == 0)
  {
    TIM6->CR1 &= ~TIM_CR1_CEN;
    update = 0;
  }
}



#ifdef __cplusplus
extern "C"
{
#endif

    void  TIM6_IRQHandler(void)
    {
      update++;
      TIM6->SR &= ~TIM_SR_UIF;
    }

#ifdef __cplusplus
}
#endif




