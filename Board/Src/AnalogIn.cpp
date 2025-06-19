#include "AnalogIn.h"

/*
   AnalogIn pins include
      port A
        pins 0,1,2,3,4,5,6,7
      
      port B
        pins 0,1

      port C
        pins 0,1,2,3,4,5



*/


AnalogIn::AnalogIn(PinName pin)
{
  
/* @brief extracts port and pin number from PinName */
  portNum = (pin >> 4) & 0xF;  // Extracts port number
  pinNum = (pin & 0xF);        // Extracts pin number

  configPin();
  ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;  //set ADC clk to APB clk
  ADC1->CFGR2 |= (1ul << ADC_CFGR2_CKMODE_Pos);
  ADC1->CFGR1 &= ~ADC_CFGR1_RES; //12 bits resolution
  ADC->CCR |= ADC_CCR_VREFEN;
  calibrate();
}

AnalogIn::~AnalogIn()
{
  ADCDisable();
}

void AnalogIn::calibrate()
{
  //ADC should be disable
  if(ADC1->CR & ADC_CR_ADEN)
  {
     ADC1->CR |= ADC_CR_ADDIS;
     while(ADC1->CR & ADC_CR_ADEN); //wait till  adc is fully disable
  }
  //start calibration
  ADC1->CR |= ADC_CR_ADCAL; 
  while (ADC1->CR & ADC_CR_ADCAL);   //till  calibration is done
}

float AnalogIn::read()
{
  float value = 0;
  ADCEnable();
  ADC1->CR |= ADC_CR_ADSTART;
  value = ADC1->DR;
  ADC1->ISR |= ADC_ISR_EOC | ADC_ISR_EOS;
  ADCDisable();
  return (value/4095.0);
}

AnalogIn::operator float()
{
  return read();
}


void AnalogIn::ADCEnable()
{
  //clear ADRDY by set it to 1
  ADC1->ISR |= ADC_ISR_ADRDY; 
  ADC1->CR |= ADC_CR_ADEN; 
  while (!(ADC1->ISR & ADC_ISR_ADRDY));
}
void AnalogIn::ADCDisable()
{
  //stop ongoing conversion
  if(ADC1->CR & ADC_CR_ADSTART)
  {
    ADC1->CR |= ADC_CR_ADSTP;
    while(ADC1->CR & ADC_CR_ADSTART);
  }
  //disable ADC
  ADC1->CR |= ADC_CR_ADDIS;
  while (ADC1->CR & ADC_CR_ADEN);
}

void AnalogIn::configPin()
{
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  if((portNum == PORTA) && pinNum <= PA7) ADC1->CHSELR |= (1ul << pinNum); //PA0 - PA7
  else  if((portNum == PORTB) && pinNum <= PB1) ADC1->CHSELR |= (1ul << (pinNum + 8)); //PB0 - PB1
  else if((portNum == PORTC) && pinNum <= PC5)  ADC1->CHSELR |= (1ul << (pinNum + 10));  //PC0 - PC5
  else 
  {
    RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
    return;
  }
  portClkEn(portNum);
  //mode to analog
  GpioArray[this->portNum]->MODER |= (3ul <<pinNum*2);
}

