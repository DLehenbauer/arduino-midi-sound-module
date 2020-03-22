/*
    A stand-alone wave generator to help debug hardware issues w/the 17-bit PWM DAC.
    https://github.com/DLehenbauer/arduino-midi-sound-module    
*/

// FIXME: You'll need to adjust the below path.
#include "D:\gh\my\x\src\firmware\arduino-midi-sound-module\dac.h"

void setup() {
  Dac::setup();

  GTCCR = _BV(TSM) | _BV(PSRSYNC);  // Halt timers 0 and 1
  
  // Synchronize Timers
  TCNT0 = 0x00;                     // Put the timers back in phase.  Dac::setup() configures them
  TCNT1H = TCNT1L = 0;              // out of phase to cancel carrier wave.  (See comments in dac.h)
  
  GTCCR = 0;                        // Resume timers
}

uint16_t v = 0;

void loop() {
  // Busy wait
  for (uint16_t i = 0; i < 0x3FF; i++) { __asm__("nop\n\t"); }
  
  Dac::set0to7(v);
  Dac::set8toF(v);
  
  v++;
}
