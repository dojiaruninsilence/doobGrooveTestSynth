/*
  ==============================================================================

    MainVoice.h
    Created: 2 May 2024 2:52:30pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../NoiseGens/MainOscillator.h"
#include "../Modules/AdsrData.h"

class MainVoice : public juce::MPESynthesiserVoice {
public:
    MainVoice();
    //~MainVoice();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void noteStarted() override;
    void notePitchbendChanged() override;
    void noteStopped(bool) override;

    void notePressureChanged() override;
    void noteTimbreChanged() override;
    void noteKeyStateChanged() override;

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack, const float decay, const float sustain, const float release);
private:
    juce::HeapBlock<char> heapBlock;
    juce::dsp::AudioBlock<float> tempBlock;
    AdsrData adsr;


    enum {
        osc1Index,
        masterGainIndex
    };

    juce::dsp::ProcessorChain<MainOscillator<float>, juce::dsp::Gain<float>> processorChain;

    bool isPrepared = false;

    static constexpr size_t lfoUpdateRate = 100;
};
