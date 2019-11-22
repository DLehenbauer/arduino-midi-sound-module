# Arduino MIDI Sound Module
Turns an Arduino Uno into a 16-voice wavetable synthesizer.  Functions as a MIDI sound module.  Typical usage includes generating sound for a MIDI keyboard controller or playback of MIDI files.

## Demo (Click image to play)
[![Arduino - Star Wars (Video)](https://img.youtube.com/vi/LdMxA-0den4/0.jpg)](https://www.youtube.com/watch?v=LdMxA-0den4)

## General MIDI Subset
The MIDI synth implements the most commonly used features of the General MIDI 1.0 standard, including:
* 128 standard instruments
* 45 percussion instruments
* 16 note polyphony with key velocity
* Note on/off, program change, pitch bend, and all channel notes off.

## Synth Engine      
* 16 voices sampled & mixed in real-time at ~20kHz
* Wavetable and white noise sources
* Amplitude, frequency, and wavetable offset modulated by envelope generators
* Additional volume control per voice (used for MIDI velocity)
