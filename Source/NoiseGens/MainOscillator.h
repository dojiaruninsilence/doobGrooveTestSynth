/*
  ==============================================================================

    MainOscillator.h
    Created: 2 May 2024 2:55:12pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Effects/CustomLadderFilter.h"

template <typename Type>
class MainOscillator {
public:
    MainOscillator();
    //~MainOscillator();

    void setType(const int oscSelection);
    void setFrequency(Type newValue, bool force = false);
    void setLevel(Type newValue);
    void setPitchVal(Type pitch, bool force = false);
    void setFrequencyAdjustVal(Type newValue);
    void reset() noexcept;

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept {
        processorChain.process(context);
    }

    void prepare(const juce::dsp::ProcessSpec& spec);

    CustomLadderFilter<Type>& getLadderFilter() { return processorChain.get<ladderFilterIndex>(); }
private:
    enum {
        oscIndex,
        ladderFilterIndex,
        gainIndex
    };

    Type pitchVal{ 0 };
    Type lastMidiNote{ 0 };

    Type frequencyAdjustVal{ 0 };

    juce::dsp::ProcessorChain<juce::dsp::Oscillator<Type>, CustomLadderFilter<Type>, juce::dsp::Gain<Type>> processorChain;
};

template class MainOscillator<float>;
