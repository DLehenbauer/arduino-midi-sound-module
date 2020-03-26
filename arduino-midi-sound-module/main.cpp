/*
    Entry point when compiling with Atmel Studio
    https://github.com/DLehenbauer/arduino-midi-sound-module
*/

/*
    Baseline:
				Program Memory Usage 	:	22218 bytes   67.8 % Full
				Data Memory Usage 		:	1052 bytes   51.4 % Full
*/

#ifndef ARDUINO
#ifndef __EMSCRIPTEN__

// `main()` is defined in "main.h" so that it can be shared between the Atmel Studio entry
// point ("main.cpp") and the Arduino IDE entry point ("arduino-midi-sound-module.ino").
#include "main.h"

#endif // !__EMSCRIPTEN__
#endif // !ARDUINO
