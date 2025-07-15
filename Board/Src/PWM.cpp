#include "PWM.h"

/*
Pwm pins include
      port A
        pins 2,3,4,6,7,8,9,10,11
      
      port B
        pins 0,1,4,5,8,9

      port C
        pins 6,7,8,9
*/


PwmOut::PwmOut(pin_name pin)
{

/* @brief extracts port and pin number from PinName */
      portNum = (pin >> 4) & 0xF;  // Extracts port number
      pinNum = (pin & 0xF);        // Extracts pin number
  if(isPwmPin())
  {
    timerClkEn(tim);
    configTIM_CHN();
  }
}

void PwmOut::period(float _period)
{
  TIMER->PSC = ((SystemCoreClock*_period)/0xffff)-1; 
  TIMER->ARR = 0xffff; 
  TIMER->EGR |= TIM_EGR_UG;
}

void PwmOut::write(float duty_c)
{
  if(chn == channel1) 
    TIMER->CCR1 = (duty_c * 0xffff); //dut cycle
  else if(chn == channel2) 
    TIMER->CCR2 = (duty_c * 0xffff); //dut cycle
  else if(chn == channel3) 
    TIMER->CCR3 = (duty_c * 0xffff); //dut cycle
  else if(chn == channel4) 
    TIMER->CCR4 = (duty_c * 0xffff); //dut cycle
}

void PwmOut::operator=(float duty_c)
{
  write(duty_c);
}

void PwmOut::configTIM_CHN()
{
  if(chn <= channel2)
  {
    TIMER->CCMR1 &= ~(0b11 << (8*chn)); // output
                   //pwm mode 1             //enable preload register
    TIMER->CCMR1 |= ( 0b110 << (TIM_CCMR1_OC1M_Pos + 8*chn) | (1U << (TIM_CCMR1_OC1PE_Pos+8*chn)) ); 
    TIMER->CCER |= 1U << (TIM_CCER_CC1E_Pos + 4*chn); 
  }
  else
  {
    TIMER->CCMR2 &= ~(0b11 << (8*(chn-2))); // output
                 //pwm mode 1             //enable preload register
    TIMER->CCMR2 |= ( 0b110 << (TIM_CCMR2_OC3M_Pos + 8*(chn-2)) | (1U << (TIM_CCMR2_OC3PE_Pos+8*(chn-2))) ); 
    TIMER->CCER |= 1U << (TIM_CCER_CC3E_Pos + 4*(chn-2)); 
  }
    
  TIMER->BDTR |= TIM_BDTR_MOE; 
  TIMER->CR1 |= TIM_CR1_CEN; 
}

bool PwmOut::isPwmPin()
{
  portClkEn(portNum);
  GPIOPORT->MODER |= 0b10<<(pinNum*2);

  if(portNum == PORTA)
  {
    switch (pinNum)
    {
      case 2:
        tim = tim15;
        chn = channel1;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        break;
      case 3:
        tim = tim15;
        chn = channel2;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        break;
      case 4:
        tim = tim14;
        chn = channel1;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0100<< pinNum*4);
        break;
      case 6:
        tim = tim3;
        chn = channel1;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0001<< pinNum*4);
        break;
      case 7:
        tim = tim3;
        chn = channel2;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0001<< pinNum*4);
        break;
      case 8:
        tim = tim1;
        chn = channel1;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum-8)*4);
        GPIOPORT->AFR[1] |= (0b0010<< (pinNum-8)*4);
        break;
      case 9:
        tim = tim1;
        chn = channel2;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum-8)*4);
        GPIOPORT->AFR[1] |= (0b0010<< (pinNum-8)*4);
        break;
      case 10:
        tim = tim1;
        chn = channel3;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum-8)*4);
        GPIOPORT->AFR[1] |= (0b0010<< (pinNum-8)*4);
        break;
      case 11:
        tim = tim1;
        chn = channel4;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum-8)*4);
        GPIOPORT->AFR[1] |= (0b0010<< (pinNum-8)*4);
        break;
      default:
        return false;
      }
  }
  else if(portNum == PORTB)
  {
    switch (pinNum) 
    {
      case 0:
        tim = tim3;
        chn = channel3;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0001<< pinNum*4);
        break;
      case 1:
        tim = tim3;
        chn = channel4;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0001<< pinNum*4);
        break;
      case 4:
        tim = tim3;
        chn = channel1;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0001<< pinNum*4);
        break;
      case 5:
        tim = tim3;
        chn = channel2;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        GPIOPORT->AFR[0] |= (0b0001<< pinNum*4);
        break;
      case 8:
        tim = tim16;
        chn = channel1;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum -8)*4);
        GPIOPORT->AFR[1] |= (0b0010<< (pinNum -8)*4);
        break;
      case 9:
        tim = tim17;
        chn = channel1;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum -8)*4);
        GPIOPORT->AFR[1] |= (0b0010<< (pinNum -8)*4);
        break;
      default:
        return false;
    }
  }
  else if(portNum == PORTC)
  { 
    switch (pinNum) 
    {
      case 6:
        tim = tim3;
        chn = channel1;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        break;
     case 7:
        tim = tim3;
        chn = channel2;
        GPIOPORT->AFR[0] &= ~(0b1111<< pinNum*4);
        break;
      case 8:
        tim = tim3;
        chn = channel3;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum-8)*4);
        break;
      case 9:
        tim = tim3;
        chn = channel4;
        GPIOPORT->AFR[1] &= ~(0b1111<< (pinNum-8)*4);
        break;
      default:
        return false;
    }
  }
  else return false;

  return true;
}

