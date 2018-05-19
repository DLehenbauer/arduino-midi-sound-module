/*
    Driver for 16-bit PWM on Timer 0
    https://github.com/DLehenbauer/arduino-midi-sound-module

    Connection to Arduino Uno:
    
                    1M                     10uf*
        pin 5 >----^v^v^----o--------o------|(----> audio out
                            |        |
                   3.9k     |       === 3.3uf**
        pin 6 >----^v^v^----o        |
                                    gnd
                                                                                                         
     * Note: A/C coupling capacitor typically optional.
    ** Note: RC filtering capacitor can be adjusted to taste:
     
                           8kHz      10kHz      30kHz
                2.2nf ~=  -0.7db    -1.1db     -5.6db
                3.3nf ~=  -1.5db    -2.2db     -8.4db
                4.7nf ~=  -2.7db    -3.6db    -11.1db
*/

#ifndef PWM0_H_
#define PWM0_H_

class Pwm0 final {
  public:
    static void setup() {
      // Note: The standard Arduino core registers a TIMER0_OVF_vect ISR to keep a count of passing
      //       time for millis and delay.
      //
      //       We need to disable this, or this interrupt will starve our other work once we configure
      //       timer 0 for PWM and set its prescalar to 0.
      TIMSK0 = 0;
      
      // Setup Timer0 for PWM
      TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);   // Fast PWM (non-inverting), Top 0xFF
      TCCR0B = _BV(CS10);												                      // Prescale None
      DDRD |= _BV(DDD5) | _BV(DDD6);									                // Output PWM to DDD5 / DDD6
    }

    static void set(uint16_t out) {
      OCR0A = out >> 8;      OCR0B = out & 0xFF;
    }
  
    static void sendHiByte() { /* Do nothing. */ }
    static void sendLoByte() { /* Do nothing. */ }
};

#endif /* PWM0_H_ */