#ifndef MAIN_H
#define MAIN_H
/* Preprocessor Definitions */


/* @brief all c included libraries go here */
#ifdef __cplusplus
extern "C" {
  #endif
  /* usages in main.cpp */ 
  #include "System Configuration.h"
  #include "stdio.h" // for printf
  #include <cstring>
  #include <stdint.h>
  

  /* c libraries for use in APIs */
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
  PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8,
  PA9, PA10, PA11, PA12, PA13, PA14, PA15,

  // PORT B
  PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8,
  PB9, PB10, PB11, PB12, PB13, PB14, PB15,

  // PORT C
  PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8,
  PC9, PC10, PC11, PC12, PC13, PC14, PC15,

  // PORT D
  PD2 = 50,

  // PORT E is Null

  //PORT F
  PF6 = 86,
  PF7 = 87

} PinName;

// mode for input pins
typedef enum{
        PullNone, // No pull-up or pull-down (external resistor)
        PullUp, // pull-up
        PullDown, // pull-down
        //OpenDrain;
} PinMode;


#endif /* MAIN_H */