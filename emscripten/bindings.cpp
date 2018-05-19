/*    Embind declarations used to expose synth functionality to JavaScript when compiling with Emscripten:    https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/embind.html#embind        (Only used by private testing and tools.)*/#include <emscripten/bind.h>
#define DAC Ltc16xx<PinId::D10>
#include "../envelope.h"#include "../synth.h"#include "../midi.h"#include "../midisynth.h"#include "../instruments.h"using namespace emscripten;
MidiSynth synth;

void noteOn(uint8_t channel, uint8_t note, uint8_t velocity)		    { synth.midiNoteOn(channel, note, velocity); }
void noteOff(uint8_t channel, uint8_t note)							            { synth.midiNoteOff(channel, note); }
void sysex(uint8_t cbData, uint8_t data[])							            { }
void controlChange(uint8_t channel, uint8_t control, uint8_t value) { synth.midiControlChange(channel, control, value); }
void programChange(uint8_t channel, uint8_t value)					        { synth.midiProgramChange(channel, value); }
void pitchBend(uint8_t channel, int16_t value)						          { synth.midiPitchBend(channel, value); }

static MidiSynth* getSynth()  { return &synth; }
static double getSampleRate() { return Synth::sampleRate; }

EMSCRIPTEN_BINDINGS(firmware) {  function("midi_decode_byte", &Midi::decode);  function("getPercussionNotes", &Instruments::getPercussionNotes);
  function("getWavetable", &Instruments::getWavetable);
  function("getEnvelopeStages", &Instruments::getEnvelopeStages);
  function("getEnvelopePrograms", &Instruments::getEnvelopePrograms);
  function("getInstruments", &Instruments::getInstruments);
  function("sample", &Synth::isr);
  
  value_object<HeapRegion<int8_t>>("I8s")
    .field("start", &HeapRegion<int8_t>::start)
    .field("end", &HeapRegion<int8_t>::end)
    .field("itemSize", &HeapRegion<int8_t>::itemSize);

  value_object<HeapRegion<uint8_t>>("U8s")
    .field("start", &HeapRegion<uint8_t>::start)
    .field("end", &HeapRegion<uint8_t>::end)
    .field("itemSize", &HeapRegion<uint8_t>::itemSize);

  value_object<HeapRegion<EnvelopeStage>>("EnvelopeStages")
    .field("start", &HeapRegion<EnvelopeStage>::start)
    .field("end", &HeapRegion<EnvelopeStage>::end)
    .field("itemSize", &HeapRegion<EnvelopeStage>::itemSize);

  value_object<HeapRegion<EnvelopeProgram>>("EnvelopePrograms")
    .field("start", &HeapRegion<EnvelopeProgram>::start)
    .field("end", &HeapRegion<EnvelopeProgram>::end)
    .field("itemSize", &HeapRegion<EnvelopeProgram>::itemSize);

  value_object<HeapRegion<Instrument>>("Instruments")
    .field("start", &HeapRegion<Instrument>::start)
    .field("end", &HeapRegion<Instrument>::end)
    .field("itemSize", &HeapRegion<Instrument>::itemSize);
  
  function("getSampleRate", &getSampleRate);
  function("getSynth", &getSynth, allow_raw_pointer<ret_val>());
  class_<EnvelopeStage>("EnvelopeStage");  class_<EnvelopeProgram>("EnvelopeProgram");  class_<Instrument>("Instrument");  class_<Envelope>("Envelope")    .constructor<>()    .function("sample", &Envelope::sampleEm)    .function("start", &Envelope::startEm)    .function("stop", &Envelope::stopEm)    .function("getStageIndex", &Envelope::getStageIndex);  class_<Synth>("Synth")    .constructor<>()
    .function("noteOn", &Synth::noteOnEm)
    .function("noteOff", &Synth::noteOff);
  class_<MidiSynth, base<Synth>>("MidiSynth")    .constructor<>()    .function("midiNoteOn", &MidiSynth::midiNoteOn)    .function("midiNoteOff", &MidiSynth::midiNoteOff)    .function("midiProgramChange", &MidiSynth::midiProgramChange)    .function("midiPitchBend", &MidiSynth::midiPitchBend);
}