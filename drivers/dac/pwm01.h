/*
    Driver for 16-bit PWM on Timers 0 and 1 with phase cancellation at 62.5khz
    https://github.com/dlehenbauer/arduino-midi-synth

    Connection to Arduino Uno:
    
                    1M                     10uf*
        pin 5 >----^v^v^----o--------o------|(----> audio out
                            |        |
                   3.9k     |       === 4.7uf**
        pin 6 >----^v^v^----o        |
                            |       gnd
                            |
                            |
                    1M      |
        pin 9 >----^v^v^----o
                            |
                   3.9k     |
       pin 10 >----^v^v^----'

                                                                                                         
       * Note: A/C coupling capacitor typically optional.
      ** Note: RC filtering capacitor can be adjusted to taste.
*/

#ifndef PWM01_H_
#define PWM01_H_

#include "pwm0.h"
#include "pwm1.h"

class Pwm01 final {
  public:
    static void setup() {
      GTCCR = _BV(TSM) | _BV(PSRSYNC);                    // Halt timers 0 and 1
    
      // Setup timers 0 and 1 for PWM
      Pwm0::setup();
      Pwm1::setup();
    
      TCNT0 = 0x80;                                       // Set timer 0 and 1 counters so that they are 180 degrees out
      TCNT1H = TCNT1L = 0;                                // of phase, cancelling the 62.5kHz carrier wave.
      
      GTCCR = 0;                                          // Resume timers
    }

    static void set(uint16_t out) {
      // Note: Setting Pwm0 prior to Pwm1 will save 2 bytes with AVR8/GNU C Compiler v5.4.0.      Pwm0::set(out);
      Pwm1::set(out);
    }
  
    static void sendHiByte() { /* do nothing */ }
    static void sendLoByte() { /* do nothing */ }
};

#endif /* PWM01_H_ */