/*
    MidiSynth
    https://github.com/DLehenbauer/arduino-midi-sound-module

    Extends Synth with methods and required state for processing MIDI messages.
*/

#ifndef __MIDISYNTH_H__
#define __MIDISYNTH_H__

#include <stdint.h>#include "synth.h"

class MidiSynth final : public Synth {
  private:
    constexpr static uint8_t numMidiChannels	= 16;					          // MIDI standard has 16 channels.    constexpr static uint8_t maxMidiChannel		= numMidiChannels - 1;	// Maximum channel is 15 when 0-indexed.    constexpr static uint8_t percussionChannel	= 9;					        // Channel 10 is percussion (9 when 0-indexed).
    uint8_t voiceToNote[numVoices];							        // Map synth voice to the current MIDI note (or 0xFF if off).    uint8_t voiceToChannel[numVoices];						      // Map synth voice to the current MIDI channel (or 0xFF if off).    Instrument channelToInstrument[numMidiChannels];		// Map MIDI channel to the current MIDI program (i.e., instrument).

  public:    MidiSynth() : Synth() {      for (int8_t channel = maxMidiChannel; channel >= 0; channel--) {        Instruments::getInstrument(0, channelToInstrument[channel]);      }
      for (int8_t channel = maxMidiChannel; channel >= 0; channel--) {        voiceToNote[channel] = 0xFF;        voiceToChannel[channel] = 0xFF;      }    }
    void midiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {      if (channel == percussionChannel) {						    // If playing the percussion channel        note = Instruments::getPercussiveInstrument(    //   Update the channel instrument for the given note, and          note, channelToInstrument[channel]);          //   replace the note with the correct playback frequency      }                                                 //   for the instrument (expressed as a midi note).
      uint8_t voice = getNextVoice();									  // Find an available voice and play the note.      noteOn(voice, note, velocity, channelToInstrument[channel]);
      voiceToNote[voice] = note;								        // Update our voice -> note/channel maps (used for processing MIDI      voiceToChannel[voice] = channel;						      // pitch bend and note off messages).    }
    void midiNoteOff(uint8_t channel, uint8_t note)  {      for (int8_t voice = maxVoice; voice >= 0; voice--) {						          // For each voice        if (voiceToNote[voice] == note && voiceToChannel[voice] == channel) {   //   that is currently playing the note on this channel          noteOff(voice);														                            //      stop playing the note          voiceToChannel[voice] = 0xFF;										                      //      and remove the voice from our voice -> note/channel          voiceToNote[voice] = 0xFF;											                      //      maps so we ignore it for future node off / pitch bench        }																		                                    //      messages.      }    }
    void midiProgramChange(uint8_t channel, uint8_t program) {      Instruments::getInstrument(program, channelToInstrument[channel]);			  // Load the instrument corresponding to the given MIDI program    }																				                                    // into the MIDI channel -> instrument map.
    void midiPitchBend(uint8_t channel, int16_t value) {      for (int8_t voice = maxVoice; voice >= 0; voice--) {						          // For each voice        if (voiceToChannel[voice] == channel) {									                //   which is currently playing a note on this channel          pitchBend(voice, value);											                        //     update pitch bench with the given value.        }      }    }      void midiControlChange(uint8_t channel, uint8_t controller, uint8_t value) {      switch (controller) {
        case 0x7B: {
          switch (value) {
            // All Notes Off (for current channel):
            case 0: {															                      
              for (int8_t voice = maxVoice; voice >= 0; voice--) {			// For each voice                if (voiceToChannel[voice] == channel) {						      //   currently playing any note on this channel                  noteOff(voice);											                  //	   stop playing the note                  voiceToChannel[voice] = 0xFF;							            //      and remove the voice from our voice -> note/channel                  voiceToNote[voice] = 0xFF;								            //      maps so we ignore it for future node off / pitch bench                }															                          //      messages.              }              break;
            }
          }
          break;
        }
      }
    }}; //MidiSynth

#endif //__MIDISYNTH_H__
