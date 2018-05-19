/*
    Driver for Ltc16xx serial DAC
    https://github.com/dlehenbauer/arduino-midi-synth

    DANGER: This driver does not wait for the SPI end-of-transmission flag before selecting the slave
            device or transmitting.  The caller is responsible for ensuring that:
            
              1.  The bus is available before calling sendHiByte()
              2.  Sufficient clock cycles have passed for the prior transmission to complete before
                  calling sendLoByte() and end();
                  
            The sample/mix/output ISR in synth.h ensures this by strategically interleaving calls into
            the DAC to output the previous sample with work to calculate the next sample.
                  
    This driver has been tested with the LTC1655 and LTC1658.
    
        LTC1655 16-bit R2R SPI DAC
        http://www.analog.com/media/en/technical-documentation/data-sheets/16555lf.pdf
    
        LTC1658 14-bit R2R SPI DAC (uses VRef)
        http://www.analog.com/media/en/technical-documentation/data-sheets/1658f.pdf
  
    Connection to Arduino Uno (assuming using pin 10 for CS):
  
                       .------.
         pin 13 >----1-|      |-8----< +5v      3.9k      10uf**
         pin 11 >----2-|  U1  |-7---------------^v^v^--o---|(--------< audio out
         pin 10 >----3-|      |-6----< VRef*           |
                       |      |-5----< gnd            === 3.3nF***
                       '------'                        |
                                                      gnd
                                                                                                         
       * Note: For LTC1658, connect VRef to +5v.  For LTC1655, leave disconnected.
      ** Note: A/C coupling capacitor typically optional.
     *** Note: RC filtering capacitor can be adjusted to taste:
     
                           8kHz      10kHz      30kHz
                2.2nf ~=  -0.7db    -1.1db     -5.6db
                3.3nf ~=  -1.5db    -2.2db     -8.4db
                4.7nf ~=  -2.7db    -3.6db    -11.1db

*/

#ifndef LTC16XX_H_
#define LTC16XX_H_

#include "spi.h"

template<PinId csPin>
class Ltc16xx final {
  private:
    static uint16_t _out;
    static Spi<csPin> _spi;
  
  public:
    static void setup() { _spi.setup(); }
  
    static void sendHiByte() {
      _spi.begin();
      _spi.unsafe_send(_out >> 8);
    }
  
    static void sendLoByte() {
      _spi.unsafe_send(_out & 0xFF);
    }

    static void set(uint16_t value) {
      _out = value;
      _spi.end();
      _spi.unsafe_clearEndOfTransmissionFlag();
    }
};

template<PinId csPin> uint16_t Ltc16xx<csPin>::_out;
template<PinId csPin> Spi<csPin> Ltc16xx<csPin>::_spi;

#endif /* LTC16XX_H_ */