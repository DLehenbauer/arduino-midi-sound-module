/*
    Templated digital I/O pin driver
    https://github.com/DLehenbauer/arduino-midi-sound-module
*/

#ifndef PINS_H_
#define PINS_H_

#include <avr/io.h>

enum class PinId {
  D0 = 0,
  D1 = 1,
  D2 = 2,
  D3 = 3,
  D4 = 4,
  D5 = 5,
  D6 = 6,
  D7 = 7,
  D8 = 8,
  D9 = 9,
  D10 = 10,
  D11 = 11,
  D12 = 12,
  D13 = 13,
  A0 = 14,
  A1 = 15,
  A2 = 16,
  A3 = 17,
  A4 = 18,
  A5 = 19,
};

template<PinId pin>
class Pin {
  public:
    void output() __attribute__((always_inline)) {
      switch (pin) {
        // DDRD
        case PinId::D0: DDRD |= _BV(DDD0); break;
        case PinId::D1: DDRD |= _BV(DDD1); break;
        case PinId::D2: DDRD |= _BV(DDD2); break;
        case PinId::D3: DDRD |= _BV(DDD3); break;
        case PinId::D4: DDRD |= _BV(DDD4); break;
        case PinId::D5: DDRD |= _BV(DDD5); break;
        case PinId::D6: DDRD |= _BV(DDD6); break;
        case PinId::D7: DDRD |= _BV(DDD7); break;

        // DDRB
        case PinId::D8: DDRB |= _BV(DDB0); break;
        case PinId::D9: DDRB |= _BV(DDB1); break;
        case PinId::D10: DDRB |= _BV(DDB2); break;
        case PinId::D11: DDRB |= _BV(DDB3); break;
        case PinId::D12: DDRB |= _BV(DDB4); break;
        case PinId::D13: DDRB |= _BV(DDB5); break;

        // DDRC
        case PinId::A0: DDRC |= _BV(DDC0); break;
        case PinId::A1: DDRC |= _BV(DDC1); break;
        case PinId::A2: DDRC |= _BV(DDC2); break;
        case PinId::A3: DDRC |= _BV(DDC3); break;
        case PinId::A4: DDRC |= _BV(DDC4); break;
        case PinId::A5: DDRC |= _BV(DDC5); break;
      }
    }

    void high() __attribute__((always_inline)) {
      switch (pin) {
        // PortD
        case PinId::D0: PORTD |= _BV(PORTD0); break;
        case PinId::D1: PORTD |= _BV(PORTD1); break;
        case PinId::D2: PORTD |= _BV(PORTD2); break;
        case PinId::D3: PORTD |= _BV(PORTD3); break;
        case PinId::D4: PORTD |= _BV(PORTD4); break;
        case PinId::D5: PORTD |= _BV(PORTD5); break;
        case PinId::D6: PORTD |= _BV(PORTD6); break;
        case PinId::D7: PORTD |= _BV(PORTD7); break;

        // PortB
        case PinId::D8: PORTB |= _BV(PORTB0); break;
        case PinId::D9: PORTB |= _BV(PORTB1); break;
        case PinId::D10: PORTB |= _BV(PORTB2); break;
        case PinId::D11: PORTB |= _BV(PORTB3); break;
        case PinId::D12: PORTB |= _BV(PORTB4); break;
        case PinId::D13: PORTB |= _BV(PORTB5); break;

        // PortC
        case PinId::A0: PORTC |= _BV(PORTC0); break;
        case PinId::A1: PORTC |= _BV(PORTC1); break;
        case PinId::A2: PORTC |= _BV(PORTC2); break;
        case PinId::A3: PORTC |= _BV(PORTC3); break;
        case PinId::A4: PORTC |= _BV(PORTC4); break;
        case PinId::A5: PORTC |= _BV(PORTC5); break;
      }
    }

    void low() __attribute__((always_inline)) {
      switch (pin) {
        // PortD
        case PinId::D0: PORTD &= ~_BV(PORTD0); break;
        case PinId::D1: PORTD &= ~_BV(PORTD1); break;
        case PinId::D2: PORTD &= ~_BV(PORTD2); break;
        case PinId::D3: PORTD &= ~_BV(PORTD3); break;
        case PinId::D4: PORTD &= ~_BV(PORTD4); break;
        case PinId::D5: PORTD &= ~_BV(PORTD5); break;
        case PinId::D6: PORTD &= ~_BV(PORTD6); break;
        case PinId::D7: PORTD &= ~_BV(PORTD7); break;

        // PortB
        case PinId::D8: PORTB &= ~_BV(PORTB0); break;
        case PinId::D9: PORTB &= ~_BV(PORTB1); break;
        case PinId::D10: PORTB &= ~_BV(PORTB2); break;
        case PinId::D11: PORTB &= ~_BV(PORTB3); break;
        case PinId::D12: PORTB &= ~_BV(PORTB4); break;
        case PinId::D13: PORTB &= ~_BV(PORTB5); break;

        // PortC
        case PinId::A0: PORTC &= ~_BV(PORTC0); break;
        case PinId::A1: PORTC &= ~_BV(PORTC1); break;
        case PinId::A2: PORTC &= ~_BV(PORTC2); break;
        case PinId::A3: PORTC &= ~_BV(PORTC3); break;
        case PinId::A4: PORTC &= ~_BV(PORTC4); break;
        case PinId::A5: PORTC &= ~_BV(PORTC5); break;
      }
    }
};

#endif /* PINS_H_ */
