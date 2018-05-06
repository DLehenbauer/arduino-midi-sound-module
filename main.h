/*
    Main 'setup()' & 'loop()' definitions, shared with main.cpp and *.ino
    https://github.com/dlehenbauer/arduino-midi-synth
*/

#ifndef MAIN_H_
#define MAIN_H_

#ifdef USE_HAIRLESS_MIDI
  #define MIDI_BAUD 38400
#else
  #define MIDI_BAUD 31250
#endif

#include <stdint.h>
#include "drivers/midi.h"
#include "drivers/ssd1306.h"
#include "midisynth.h"

Ssd1306</* rotate 180: */ true> display;    // SSD1306 driver for 128x64 OLED SPI display
MidiSynth synth;

// The below thunks are invoked during Midi::Dispatch() and forwarded to our MidiSynth.
void noteOn(uint8_t channel, uint8_t note, uint8_t velocity)		    { synth.midiNoteOn(channel, note, velocity); }
void noteOff(uint8_t channel, uint8_t note)							            { synth.midiNoteOff(channel, note); }
void sysex(uint8_t cbData, uint8_t data[])							            { /* do nothing */ }
void controlChange(uint8_t channel, uint8_t control, uint8_t value) { synth.midiControlChange(channel, control, value); }
void programChange(uint8_t channel, uint8_t value)					        { synth.midiProgramChange(channel, value); }
void pitchBend(uint8_t channel, int16_t value)						          { synth.midiPitchBend(channel, value); }

// Invoked once after the device is reset, prior to starting the main 'loop()' below.
void setup() {
  display.begin();                        // Initializing the display prior to start the synth ensures that
  display.reset();                        // the display has exclusive access to SPI during 'setup()'.
  display.setRegion(0, 127, 0, 7, 0);     // (Note: 7 -> pages 0..7, each page being 8px, for 64px total.)
  
  synth.begin();                          // Start synth sample/mixing on Timer2 ISR

  Midi::begin(MIDI_BAUD);                 // Start receiving MIDI messages via USART.
  
  sei();                                  // Begin processing interrupts.
}

// Helper used by main 'loop()' to set each column of an 8x7 block of pixels to the given mask,
// and then dispatch any MIDI messages that were queued while the SPI transfer was in progress.
//
// Note: Because this is the only call to 'display.send7()', AVR8/GNU C Compiler v5.4.0 will
//       inline it (even with -Os), and then jump into Midi::dispatch().
void display_send7(uint8_t mask) {
  synth.suspend();                            // Suspend audio processing ISR so display has exclusive access to SPI.
  display.set7x8(mask);                       // Set first 7 columns of currently selected 8x8 block to given 'mask'.
  synth.resume();                             // Resume audio processing.
  Midi::dispatch();                           // (Drain the pending queue of MIDI messages)
}

// There are four activities happening concurrently, roughly in priority order:
//
//    1. The USART RX ISR started by Midi::begin() is queuing incoming bytes from the serial port
//       in a circular buffer for later dispatch.
//
//    2. The Timer2 ISR started by synth.begin() is sampling/mixing and updating the output
//       waveform (by default, at ~20khz).
//
//    3. The main 'loop()' below interleaves the following two activities:
//        a. Handling the MIDI messages queued by the USART RX ISR by updating the state of the synth.
//        b. Updating the bar graph on the OLED display with the current amplitude of each voice.
//
void loop() {
  static uint8_t voice = 0;                   // Each time through the loop, we update the bar for one voice (in
  voice++;                                    // round-robin order.)
  voice &= 0x0F;

  uint8_t y = synth.getAmp(voice);            // The height of the bar is equal to 1.5x the current amplitude,
  y += y >> 1;                                // with a maximum of 64px (i.e., [0..63])
  y &= 0x3F;
  
  const uint8_t x = voice << 3;               // Calculate the left edge of the bar from the voice index.
  const int8_t page = 7 - (y >> 3);           // Calculate the 8px page that contains 'y'.
  Midi::dispatch();                           // (Drain the pending queue of MIDI messages)
  
  synth.suspend();                            // Suspend audio processing ISR so display has exclusive access to SPI.
  display.select(x, x + 6, 0, 7);             // Select the 7px x 64px area of the display containing the current bar.
  synth.resume();                             // Resume audio processing.
  
  for (int8_t i = page; i > 0; i--) {         // Clear 7x8 blocks above the new bar graph's current level.
    display_send7(0x00);
  }

  {                                           // Set/Clear the pixel of the 7x8 block containing the current bar graph level.
    const uint8_t remainder = 7 - (y & 0x07);
    display_send7(~((1 << remainder) - 1));
  }

  for (int8_t i = 6 - page; i >= 0; i--) {    // Set 7x8 blocks under the new bar graph's current level.
    display_send7(0xFF);
  }
}

#endif /* MAIN_H_ */
