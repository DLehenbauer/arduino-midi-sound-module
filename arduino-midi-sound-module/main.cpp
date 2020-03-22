/*
    Main loop when compiling with Atmel Studio
    https://github.com/DLehenbauer/arduino-midi-sound-module
*/

/*
    Baseline:
				Program Memory Usage 	:	22218 bytes   67.8 % Full
				Data Memory Usage 		:	1052 bytes   51.4 % Full
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
