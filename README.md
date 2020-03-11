# Arduino MIDI Sound Module
Turn your Arduino Uno into a 16-voice wavetable synthesizer/MIDI sound generator.

[![Image](media/Ardunio-MIDI-Sound-Module-Photo.jpg)](https://raw.githubusercontent.com/DLehenbauer/arduino-midi-sound-module/master/media/Ardunio-MIDI-Sound-Module-Photo.jpg)

# General MIDI Subset
Implements the most commonly used features of the General MIDI 1.0 standard, including:
* 128 standard instruments
* 45 percussion instruments
* 16 note polyphony with key velocity
* Note on/off, program change, pitch bend, channel volume and all notes off.

# Demo

[![Arduino - Imperial March (Video)](media/Thumbnail.jpg)](https://www.youtube.com/watch?v=4pCgZSmhi4E)

# Synth Engine      
* 16 voices sampled & mixed in real-time at ~20kHz
* Wavetable and white noise sources
* Amplitude, frequency, and wavetable offset modulated by envelope generators
* Additional volume control per voice (used for channel volume and key velocity)
* Documented C++ code builds in Arduino IDE or Atmel Studio 6.0

# Hardware
[![Schematic](media/Ardunio-MIDI-Sound-Module-Plans.png)](https://raw.githubusercontent.com/DLehenbauer/arduino-midi-sound-module/master/media/Ardunio-MIDI-Sound-Module-Plans.png)

# Useful Tools
* [Hairless MIDI](https://projectgus.github.io/hairless-midiserial/) - Use default settings and `#define USE_HAIRLESS_MIDI`
* [The Kik Gen Labs - USBMidiKlik](https://github.com/TheKikGen/USBMidiKliK) - Do not `#define USE_HAIRLESS_MIDI`
* [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html)

# Resources
* [Open Music Labs - PWM DAC](http://www.openmusiclabs.com/learning/digital/pwm-dac.1.html)
* [Open Music Labs - Dual PWM Circuits](http://www.openmusiclabs.com/learning/digital/pwm-dac/dual-pwm-circuits/index.html)
