/*
    Main loop when compiling with Atmel Studio
    https://github.com/DLehenbauer/arduino-midi-sound-module
*/

/*
    Baseline (w/Pwm0):
    Program Memory Usage 	:	32100 bytes
    Data Memory Usage 		:	1019 bytes

    Ltc16xx:  +18B
    Pwm1:     +32B
    Pwm01:    +72B
*/

//#define DAC Pwm1
//#define DAC Pwm01
//#define DAC Ltc16xx<PinId::D10>

#ifndef ARDUINO
#ifndef __EMSCRIPTEN__

#include "main.h"

// Note: See 'main.h' for definitions of 'setup()' and 'loop()'.
int main() {
  setup();
  
  while(true) {
    loop();
  }
  
  return 0;
}
#endif // !__EMSCRIPTEN__
#endif // !ARDUINO
