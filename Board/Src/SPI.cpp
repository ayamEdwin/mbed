#include "SPI.h"


SPI::SPI(uint8_t mosi, uint8_t miso, uint8_t clk)
{
  portNum = (mosi >> 4) & 0xF;
  mosiPinNum = (mosi & 0xF);
  misoPinNum = (miso & 0xF);   
  clkPinNum = (clk & 0xF); 
    
  if(mosi == PTA7)
  {
      // Enable clk for SPI1
      RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  }
  else if(mosi == PTB15)
  {
     // Enable clk for SPI2
      RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
  }
  //configure spi
  spiConfig();
  // use default format
  format(8,3);
  // use default frequency
  frequency(1000000);
}

SPI::~SPI(){
  if(portNum == PORTA) RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
  else RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;
}


/*@brief set the bit length and the mode of the device */

void SPI::format(uint8_t bit_len, uint8_t mode)
{
  SPIPORT->CR2  |= (0xf<< SPI_CR2_DS_Pos);
  SPIPORT->CR2  &= ~(0x7<< SPI_CR2_DS_Pos);

  // confine bit length in the range of 4 - 16
  if(bit_len >=4 && bit_len < 9)
  {
     SPIPORT->CR2 |= (bit_len-1)<< SPI_CR2_DS_Pos;
     SPIPORT->CR2 &= ~(0x8 << SPI_CR2_DS_Pos);
  }
  else if( bit_len > 9 && bit_len <= 16)
  {
    SPIPORT->CR2 |= ((bit_len - 1) -8)<< SPI_CR2_DS_Pos;
  }

  SPIPORT->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);
  // confine mode in the range of 0 - 3
  SPIPORT->CR1 |= (mode >= 0 && mode <= 3)? mode:0;

  if(bit_len <= 7) SPIPORT->CR2 |= SPI_CR2_FRXTH;   //8bits should set rxne
  else SPIPORT->CR2 &= ~SPI_CR2_FRXTH;              //16bits should set rxne
}


/* @brief set the frequency of the device
*  @param uint32_t
*/

void SPI::frequency(uint32_t freq) 
{
  uint8_t freq_range;
  if (freq >= 100000 && freq <= 187500) freq_range = 7;
  else if (freq > 187500 && freq <= 375000)freq_range = 6;
  else if (freq > 375000 && freq <= 750000) freq_range = 5;
  else if (freq > 750000 && freq <= 1500000) freq_range = 4;
  else if (freq > 1500000 && freq <= 3000000) freq_range = 3;
  else if (freq > 3000000 && freq <= 6000000) freq_range = 2;
  else if (freq > 6000000 && freq <= 12000000) freq_range = 1;
  else if (freq > 12000000 && freq <= 24000000)freq_range = 0;
  else freq_range = 7;

  // config the baud rate
  SPIPORT->CR1 &= ~SPI_CR1_BR;
  SPIPORT->CR1 |= (freq_range << SPI_CR1_BR_Pos);
}

/*
  @brief write data to slave device
   and return the data received from the slave

   @param uint8_t
   @return uint8_t

*/

uint8_t SPI::write(uint8_t data) 
{
  uint8_t rxdata = 0;
  // enable spi
  SPIPORT->CR1 |= SPI_CR1_SPE;

  //wait untill the tx buffer is empty
  while(!(SPIPORT->SR & SPI_SR_TXE));
  *(uint8_t*)&(SPIPORT->DR) = data;

  while(((SPIPORT->SR) & SPI_SR_BSY));

  if((SPIPORT->SR & SPI_SR_RXNE))
  {
      rxdata = *(uint8_t*)&(SPIPORT->DR);
  }
  SPIPORT->CR1 &= ~SPI_CR1_SPE;

  return rxdata;
}


/* @brief configure the GPIO pins 
*   configure  the specified spi in master mode
*/

void SPI::spiConfig() 
{
    //Enable clk of the port
    portClkEn(portNum);

    // Config mosi, miso and clk as AF
    GPIOPORT->MODER &= ~((3ul << (mosiPinNum*2)) | (3ul << (misoPinNum*2)) | (3ul << (clkPinNum*2)));
    // set them as AF
    GPIOPORT->MODER |= ((2ul << (mosiPinNum*2)) | (2ul << (misoPinNum*2)) | (2ul << (clkPinNum*2)));
    //set the speed to high

    // choosing the right AF for the pins
    if ((this->portNum) == PORTB) GPIOPORT->AFR[1] &= ~(GPIO_AFRH_AFSEL13 | GPIO_AFRH_AFSEL14 | GPIO_AFRH_AFSEL15); //SPI2
    else GPIOPORT->AFR[0] &= ~(GPIO_AFRL_AFRL5 | GPIO_AFRL_AFRL6 | GPIO_AFRL_AFRL7);  //SPI1

    // Clear MSS and SSI to use any Gpio pin           MSBFIRST
    SPIPORT->CR1 &= ~(SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_LSBFIRST);
    SPIPORT->CR1 |= SPI_CR1_MSTR;    //master
    SPIPORT->CR2 |= SPI_CR2_SSOE;
}

