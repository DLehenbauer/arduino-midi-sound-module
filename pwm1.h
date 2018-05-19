/*
    Driver for 16-bit PWM on Timer 1
    https://github.com/DLehenbauer/arduino-midi-sound-module

    Note: Prefer Timer 0 for PWM output, as it requires fewer ops to update it's output.

    Connection to Arduino Uno:
    
                     1M                     10uf*
         pin 9 >----^v^v^----o--------o------|(----> audio out
                             |        |
                    3.9k     |       === 3.3uf**
        pin 10 >----^v^v^----o        |
                                     gnd
                                                                                                         
     * Note: A/C coupling capacitor typically optional.
    ** Note: RC filtering capacitor can be adjusted to taste:
     
                           8kHz      10kHz      30kHz
                2.2nf ~=  -0.7db    -1.1db     -5.6db
                3.3nf ~=  -1.5db    -2.2db     -8.4db
                4.7nf ~=  -2.7db    -3.6db    -11.1db
*/

#ifndef PWM1_H_
#define PWM1_H_

class Pwm1 final {
  public:
    static void setup() {
      TIMSK1 = 0;                                         // Disable any interrupts registered for Timer 1
      
      // Setup Timer1 for PWM
      TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);    // Toggle OC1A/OC1B on Compare Match, Fast PWM (non-inverting)
      TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);       // Fast PWM, Top ICR1H/L, Prescale None
      ICR1H = 0;
      ICR1L = 0xFF;                                       // Top = 255 (8-bit PWM per output), 62.5khz carrier frequency
      DDRB |= _BV(DDB1) | _BV(DDB2);                      // Output PWM to DDB1 / DDB2
    }

    static void set(uint16_t out) {
      OCR1B = out >> 8;      OCR1A = out & 0xFF;
    }
  
    static void sendHiByte() { }
    static void sendLoByte() { }
};

#endif /* PWM1_H_ */