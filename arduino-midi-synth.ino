/*
    Arduino Midi Synth v0.1
    https://github.com/DLehenbauer/arduino-midi-sound-module
    
    This sketch turns an Arduino Uno into a 16-voice wavetable synthesizer functioning as a
    MIDI sound module.  Typical usages include generating sound for a MIDI keyboard controller
    or playback of MIDI files.
    
    The MIDI synth implements the most commonly used features of the General MIDI 1.0 standard,
    including:
    
      - 128 standard instruments
      - 45 percussion instruments
      - Key velocity
      - Pitch bend
     
    (See open GitHub issues for caveats: https://github.com/dlehenbauer/arduino-midi-synth/issues)
      
    The synth engine features:
      - 16 voices sampled & mixed in real-time at ~20kHz
      - Wavetable and white noise sources
      - Amplitude, frequency, and wavetable offset modulated by envelope generators
      - Additional volume control per voice (matching MIDI velocity)
    
    The circuit:
    
                        1M*                    10uf**
            pin 5 >----^v^v^----o--------o------|(----> audio out
                                |        |
                       3.9k*    |       === 3.3uf***
            pin 6 >----^v^v^----o        |
                                        gnd
                                        
        * Use 1% resistors, ideally ordering extras and selecting the pair of 1M and 3.9k that
          most closely matches a 1:256 ratio (or adding a trim pot to get the precise ratio):
          http://www.openmusiclabs.com/learning/digital/pwm-dac/dual-pwm-circuits/index.html
          
       ** A/C coupling capacitor can typically be omitted (most audio inputs remove DC bias).
       
      *** Low pass RC filter capacitor can be adjusted to taste:
     
                               8kHz      10kHz      30kHz
                    2.2nf ~=  -0.7db    -1.1db     -5.6db
                    3.3nf ~=  -1.5db    -2.2db     -8.4db
                    4.7nf ~=  -2.7db    -3.6db    -11.1db

    Sending MIDI data to the Arduino:
    
    The easiest/fastest way to send MIDI data from your computer is to use a MIDI <-> Serial Bridge:
    http://projectgus.github.io/hairless-midiserial/

    (To avoid overrunning the small buffer for incoming MIDI data, set the lower the baud rate of
    hairless to 38400.  You will also need to adjust the baud rate of the Midi driver to match.)
    
    If you have an ISP programmer and an Uno R3 w/ATMega82U, you can make your Arduino Uno appear
    as a native USB MIDI device:
    https://github.com/kuwatay/mocolufa
    
    Finally, with a bit more circuitry, you can add an 5-pin DIN serial MIDI input port to the
    Arduino and use a standard serial MIDI interface.
    
                220 
        .------^v^v^----------o-------.                      .----o--------------o----< +5v
        |                     |       |                      |    |              |
        |     .-----.         |  1    |      .--------.      |   === 100nF       /
        |    / 5-DIN \       _|_ N    o----1-|        |-6----'    |              \ 
        |   |  (back) |       ^  9    o----2-| H11L1* |-5---------o--< Gnd       / 280
        |   |o       o|      /_\ 1    |      |        |-4----.                   \
        |    \ o o o /        |  4    |      '--------'      |                   /
        |     /-----\         |       |                      |                   |
        |  4 /       \ 5      |       |                      '-------------------o----> RX
        '---'         '-------o-------'
        
    Notes:
        * H11L1 is a PC900 equivalent
*/

// Defining 'USE_HAIRLESS_MIDI' will set the serial baud rate to 38400.  Comment the #define
// out to use MIDI standard 31250 baud.
#define USE_HAIRLESS_MIDI

#include "main.h"
