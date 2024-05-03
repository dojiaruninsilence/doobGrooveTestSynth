/*
  ==============================================================================

    MainOscillator.h
    Created: 2 May 2024 2:55:12pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template <typename Type>
class MainOscillator {
public:
    MainOscillator();
    ~MainOscillator();

    void setFrequency(Type newValue, bool force = false);
    void setLevel(Type newValue);
    void reset() noexcept;

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept {
        processorChain.process(context);
    }

    void prepare(const juce::dsp::ProcessSpec& spec);
private:
    enum {
        oscIndex,
        gainIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Oscillator<Type>, juce::dsp::Gain<Type>> processorChain;
};

template class MainOscillator<float>;