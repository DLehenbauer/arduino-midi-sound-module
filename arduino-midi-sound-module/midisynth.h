/*
    MidiSynth
    https://github.com/DLehenbauer/arduino-midi-sound-module

    Extends Synth with methods and required state for processing MIDI messages.
*/

#ifndef __MIDISYNTH_H__
#define __MIDISYNTH_H__

#include <stdint.h>

class MidiSynth final : public Synth {
  private:
    constexpr static uint8_t numMidiChannels	= 16;					          // MIDI standard has 16 channels.
    static uint8_t voiceToNote[numVoices];							        // Map synth voice to the current MIDI note (or 0xFF if off).
    static uint8_t channelToVolume[numMidiChannels];		        // Map MIDI channel to the current 8-bit instrument volume.
    static uint8_t voiceToVolume[numVoices];		                // Map synth voice to 8-bit volume scalar.
    static uint8_t voiceToVelocity[numVoices];	                // Map synth voice to 7-bit velocity scalar.

  public:
    void midiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
      uint8_t voice = getNextVoice();									  // Find an available voice and play the note.
      voiceToNote[voice] = note;								        // Update our voice -> note/channel maps (used for processing MIDI
    void midiNoteOff(uint8_t channel, uint8_t note)  {
    void midiProgramChange(uint8_t channel, uint8_t program) {
    void midiPitchBend(uint8_t channel, int16_t value) {
      // Map 8-bit channel volume and 7-bit velocity to 7-bit total volume.  We've scaled MIDI
      // channel volume up to 8-bit so that we can perform an inexpensive '>> 8'.
      return (static_cast<uint16_t>(volume) * static_cast<uint16_t>(velocity)) >> 8;
    }
  
        // Set channel volume
        case 0x07: {
          // Scale 7-bit MIDI channel volume up to 8-bit.  This reduces the instructions require to convert
          // from 16-bit to 8-bit later in mixVolume().
          value <<= 1;

          channelToVolume[channel] = value;
          for (int8_t voice = maxVoice; voice >= 0; voice--) {			// For each voice
            }
          break;
        }
        case 0x7B: {
          switch (value) {
            // All Notes Off (for current channel):
            case 0: {															                      
              for (int8_t voice = maxVoice; voice >= 0; voice--) {			// For each voice
            }
          }
          break;
        }
      }
    }

uint8_t     MidiSynth::voiceToNote[numVoices] = { 0 };
uint8_t     MidiSynth::channelToVolume[numMidiChannels] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
uint8_t     MidiSynth::voiceToVolume[numVoices] = { 0 };
uint8_t     MidiSynth::voiceToVelocity[numVoices] = { 0 };

#endif //__MIDISYNTH_H__