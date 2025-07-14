#include "mbed.h"

InterruptIn button(PTB6);
DigitalOut  led(PTA1);
DigitalOut  ON_BOARD_LED(LED);




void start()
{
  led = !led;
}

void stop()
{
  led = 1;
}



int main(){ 
   
    button.mode(PullUp);
    button.rise(&start);  // attach the address of the flip function to the rising edge
    //button.fall(&stop);

    while(1){
            ON_BOARD_LED = 1; // Turns on board LED on
            wait(1);
            ON_BOARD_LED = 0; // Turns on board LED on
            wait(1);

        }
  }
