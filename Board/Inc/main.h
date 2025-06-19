/*********************************************************************
*                          MBED API PROJECT                          *
*                                                                    *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

Drivers : Low Level Drivers, CMSIS_5, STM32F0XX
Language  : C/C++
Tools    : Embedded studio
Target Device : STM32F030RCT6
Collaborators    : Mr. Richard Mensah, Edwin Setsoafia, Enos Essandoh,
                    Amidu Lukeman, Lawson Chinedu, Paul
              
Comment Style: @brief describes in brief the funtionality
               @param description of parameters
               // For comments that are not lengthy

NB: This is a standard for code clarity and better documentation
Adhere to it!

*/



#ifndef MAIN_H
#define MAIN_H

// Preprocessor Definitions


// @brief all c included libraries go here 
#ifdef __cplusplus
extern "C" {
  #endif
  // usages in main.cpp 
  #include "System Configuration.h"
  #include "stdio.h" // for printf
  #include <cstring>
  #include <stdint.h>
  

  // c libraries for use in APIs 
  #include "stm32f0xx_ll_crs.h"
  #include "stm32f0xx_ll_rcc.h"
  #include "stm32f0xx_ll_bus.h"
  #include "stm32f0xx_ll_system.h"
  #include "stm32f0xx_ll_exti.h"
  #include "stm32f0xx_ll_cortex.h"
  #include "stm32f0xx_ll_utils.h"
  #include "stm32f0xx_ll_pwr.h"
  #include "stm32f0xx_ll_dma.h"
  #include "stm32f0xx_ll_tim.h"
  #include "stm32f0xx_ll_gpio.h"

  #ifdef __cplusplus
}
#endif

typedef enum{
  // PORT A
  PTA0, PTA1, PTA2, PTA3, PTA4, PTA5, PTA6, PTA7, PTA8,
  PTA9, PTA10, PTA11, PTA12, PTA13, PTA14, PTA15,

  // PORT B
  PTB0, PTB1, PTB2, PTB3, PTB4, PTB5, PTB6, PTB7, PTB8,
  PTB9, PTB10, PTB11, PTB12, PTB13, PTB14, PTB15,

  // PORT C
  PTC0, PTC1, PTC2, PTC3, PTC4, PTC5, PTC6, PTC7, PTC8,
  PTC9, PTC10, PTC11, PTC12, PTC13, PTC14, PTC15,

  // PORT D
  PTD2 = 50,

  // PORT E is Null

  //PORT F
  PTF6 = 86,
  PTF7 = 87

} PinName;

/*
// mode for input pins
typedef enum{
        PullNone, // No pull-up or pull-down (external resistor)
        PullUp, // pull-up
        PullDown, // pull-down
        //OpenDrain;
} PinMode;
*/

#endif // MAIN_H