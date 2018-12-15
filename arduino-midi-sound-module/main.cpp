/*
    Main loop when compiling with Atmel Studio
    https://github.com/DLehenbauer/arduino-midi-sound-module
*/

/*
    Baseline:
    Program Memory Usage 	:	32150 bytes
    Data Memory Usage 		:	1019 bytes
*/

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
