    // This example code illustrates the use of DigitalOut to blink an on board LED
    // connected to pin "PTD2".
  
    #include "DigitalOut.h"

    DigitalOut ON_BOARD_LED(PTD2); // Creates a DigitalOut object on PTD2

    /* @important FROM PIN MAP
     * PC13, PC14 and PC15 are supplied through the power switch. Since the switch only sinks a limited amount
     * of current (3 mA), the use of GPIOs PC13 to PC15 in output mode is limited:
     * - The speed should not exceed 2 MHz with a maximum load of 30 pF.
     * - These GPIOs must not be used as current sources (e.g. to drive an LED).

     
      PTA13 (SWDIO)
      PTA14 (SWCLK)
      PAT15 Not working

      PTC0 to PTC15 has been reversed on the Dev Board
      PTF6 and PTF7 not tested
    */

    DigitalOut led_pin_test(PTA0); 


    int main(){ 
    //LL_mDelay(1000);
      //set up code
      SystemClock_Config(); // configures system clock
      ON_BOARD_LED.write(1); // Turns on board LED on
  
      while(1){
            // ALL TEST CODES HERE MUST BE COMMENTED EXCEPT LATEST VERSION

            /*// Blinky Test with write()
            ON_BOARD_LED.write(0); // Turns on board LED off
            LL_mDelay(1000); // delays for 1000 ms
            ON_BOARD_LED.write(1); // Turns on board LED on
            LL_mDelay(1000); //  delays for 1000 ms*/

            /*// Blinky test with '=' operator
            ON_BOARD_LED = 1; // Turns on board LED off
            LL_mDelay(100); // delays for 1000 ms
            ON_BOARD_LED = 0; // Turns on board LED on
            LL_mDelay(100); //  delays for 1000 ms*/

            // Pin PTA0 Test
            led_pin_test = 1; // Turns on board LED off
            LL_mDelay(100); // delays for 1000 ms
            led_pin_test = 0; // Turns on board LED on
            LL_mDelay(100); //  delays for 1000 ms

        }
    }
