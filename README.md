# mbed Application Programming Interface (mbed API)
### INSPIRED BY RETIRING [MBED API](https://os.mbed.com/docs/mbed-os/v6.16/apis/index.html)


## Table of Contents
- [Overview](#Overview)
- [Prerequisites](#Prerequisites)
- [Installation](#Installation)
- [Configuration](#Configuration)
- [API Usage Examples](#API-Usage-Examples)
- [License](#License)

  ## Overview
  This repository (mbed API) provides an abstraction layer for the STM32F030x4/x6/x8/xC and STM32F070x6/xB
  advanced Arm®-based 32-bit MCUs,
  simplifying hardware/software interactions for undergraduate students for learning Embedded Systems.
  The API includes modules for DigitalIn, DigitalOut, AnalogIn, AnalogOut, Pwm, Timers,  Serial Communication Protocols, etc. abstracting away
  complex low-level details.
  For the purpose of this documentation, STM32F030x4/x6/x8/xC and STM32F070x6/xB
  microcontrollers are referred to as STM32F0x0.
  The STM32F0x0 is a family of microcontrollers with different memory sizes, packages and
  peripherals.
  For ordering information, mechanical and electrical device characteristics, please refer to
  the corresponding datasheet.

  ## Prerequisites
  If you are taking a course in Embedded Systems at Koforidua Technical University under the Electrical/Electronics
  department, you will most likely be using the following tools:
  
  ### Software Requirements
  - [Embedded Studio](https://www.segger.com/downloads/embedded-studio/) from Segger(Recommended IDE).
  - [J-Link Software](https://www.segger.com/downloads/jlink/) (For ST-Link debugger support).
  - Git (Optional: For this repository)
 
  ### Hardware Requirements
  - STM32FO30RTC6 microcontroller development board.
  - ST-Link/V2 debugger (or compatible J-Link debugger)
  - USB cables for power and debugging.
 
    NB: To use this API, ensure you have the above requirements satisfied installed and succesfully configured.
 

  ## Installation (Method 1 - Mac/Linux/windows)
  1. In your git bash terminal, navigate to:  
      Typical Locations by OS  
      🪟 Windows : Common save locations include:  
           C:\Users\<YourUsername>\Documents\SEGGER Embedded Studio Projects\  
            Or wherever you manually chose when creating the project.  
     
            Check:
            %USERPROFILE%\Documents\SEGGER Embedded Studio Projects\
     
      🍎 macOS : location:  
            /Users/<YourUsername>/SEGGER Embedded Studio Projects/  
            Or any custom path you chose  

          Check
          ~/SEGGER Embedded Studio Projects/

      🐧 Linux : location:  
           /home/<YourUsername>/SEGGER Embedded Studio Projects/  
           SES may use the last-used directory, or wherever you chose  

            Check:
           ~/SEGGER Embedded Studio Projects/
     

  3. Clone this repository to your local machine:  
     ```bash
     git clone https://github.com/ayamEdwin/mbed.git
     ```
  4. Open the project in Sergger Embedded Studio:  
     - Launch Sergger Embedded Studio
     - Select "File" -> "Open Solution"
     - to be continued...

  ## Installation (Method 2 - Mac/Linux/windows)
  1. On this repository navigate to Code and click on the dropdown.
  2. Locate Download Zip and click on it.
  3. Unzip the download mbed repo and copy paste to any appropriate
     directory listed in Method 1.
     or click here to download [mbed](https://github.com/ayamEdwin/mbed/archive/refs/heads/main.zip)
  

  ## Configuration  
  ### J-Link Setup for ST-Link Debugger  
  1. Install the latest [J-Link Software](https://www.segger.com/downloads/jlink/)
  2. Connect your ST-Link debugger to both your computer and the target board
  3. In Segger Embedded Studio:
    - Go to "Tools" -> "Options" -> "Debugger"
    - Select "J-Link" as the debugger
    - Configure the following settings:
      - Interface: SWD
      - Device: STM32F030RC
      - Speed: 1000 kHz (adjust if needed)
      
  ### Embedded Studio Settings
     Blank for now
  ## Pin Out
  
  ![STM32 DEV BOARD PINOUT](https://github.com/ayamEdwin/mbed/blob/main/assets/mbed_pinout.png?raw=true)
  
  ## API-Usage-Examples

  ```   cpp
  
      // This example code illustrates the use of DigitalOut to blink an on board LED
  
      // connected to pin "PTD2"
  
      #include "DigitalOut.h"

      DigitalOut ON_BOARD_LED(PTD2); // Creates a DigitalOut object on PD2
      
      int main(){
        
      while(1){
                  ON_BOARD_LED.write(0); // Turns on board LED off
                  wait_ms(1000); // delays for 1000 ms
                  ON_BOARD_LED.write(1); // Turns on board LED on
                  wait_ms(1000); //  delays for 1000 ms
              }
          }
  ```
 

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/license/mit/)
[MIT LICENSE](https://github.com/ayamEdwin/mbed/blob/main/LICENSE)

 
  
        
  
  
