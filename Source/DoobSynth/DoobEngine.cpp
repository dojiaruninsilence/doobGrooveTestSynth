/*
  ==============================================================================

    DoobEngine.cpp
    Created: 2 May 2024 2:53:09pm
    Author:  Zubin

  ==============================================================================
*/

#include "DoobEngine.h"

#include "MainVoice.h"

DoobEngine::DoobEngine() {
    for (auto i = 0; i < maxNumVoices; ++i) {
        addVoice(new MainVoice);
    }

    setVoiceStealingEnabled(true);
}

//DoobEngine::~DoobEngine() {
//
//}

void DoobEngine::prepare(const juce::dsp::ProcessSpec& spec) noexcept {
    setCurrentPlaybackSampleRate(spec.sampleRate);

    for (auto* v : voices) {
        dynamic_cast<MainVoice*>(v)->prepare(spec);
    }
}

void DoobEngine::renderNextSubBlock(juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples) {
    MPESynthesiser::renderNextSubBlock(outputAudio, startSample, numSamples);
}