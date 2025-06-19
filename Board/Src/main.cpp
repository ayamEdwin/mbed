#include "mbed.h"

int main()
{ 

  DigitalOut led(LED);
  DigitalIn i(PA9);
  i.mode(PullDown);
  

  while (1) 
  {
      
      printf("Value is %d \n",i.read());

  }

}