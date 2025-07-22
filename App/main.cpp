#include "mbed.h"

InterruptIn button(PTB6);
DigitalOut  led(PTA1);
DigitalOut  ON_BOARD_LED(LED);


void flip()
{
  led = !led;
}



int main(){ 
   
    button.mode(PullUp);
    button.rise(&flip);  // attach the address of the flip function to the rising edge
    //button.fall(&stop);

    while(1){
            ON_BOARD_LED = ! ON_BOARD_LED; // Turns on board LED on
            wait_ms(500);
           

        }
  }
