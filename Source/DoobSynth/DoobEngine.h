/*
  ==============================================================================

    DoobEngine.h
    Created: 2 May 2024 2:53:09pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DoobEngine : public juce::MPESynthesiser {
public:
    static constexpr auto maxNumVoices = 4;

    DoobEngine();
    ~DoobEngine();

    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;

private:
    void renderNextSubBlock(juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples) override;
};