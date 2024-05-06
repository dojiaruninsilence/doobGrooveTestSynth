/*
  ==============================================================================

    MainOscillator.cpp
    Created: 2 May 2024 2:55:12pm
    Author:  Zubin

  ==============================================================================
*/

#include "MainOscillator.h"

template <typename Type>
MainOscillator<Type>::MainOscillator() {
    auto& osc = processorChain.template get<oscIndex>();
    osc.initialise([](Type x) {return std::sin(x);}, 128);
}

//template <typename Type>
//MainOscillator<Type>::~MainOscillator() {
//    
//}

template <typename Type>
void MainOscillator<Type>::setType(const int oscSelection) {
    auto& osc = processorChain.template get<oscIndex>();
    switch (oscSelection) {
        // sine
    case 0:
        osc.initialise([](Type x) {return std::sin(x);}, 128);
        break;
        // saw
    case 1:
        osc.initialise([](Type x) {return x / juce::MathConstants<float>::pi;}, 128);
        break;
        // square
    case 2:
        osc.initialise([](Type x) {return x < 0.0f ? -1.0f : 1.0f;}, 128);
        break;
    default:
        // you shouldnt be here
        jassertfalse;
        break;
    }
}

template <typename Type>
void MainOscillator<Type>::setFrequency(Type newValue, bool force) {
    auto& osc = processorChain.template get<oscIndex>();
    osc.setFrequency((newValue + pitchVal) * frequencyAdjustVal, force);
    lastMidiNote = newValue;
}

template <typename Type>
void MainOscillator<Type>::setLevel(Type newValue) {
    auto& gain = processorChain.template get<gainIndex>();
    gain.setGainLinear(newValue);
}

template <typename Type>
void MainOscillator<Type>::setPitchVal(Type pitch, bool force) {
    auto& osc = processorChain.template get<oscIndex>();
    pitchVal = pitch;
    osc.setFrequency(lastMidiNote + pitchVal);

}

template <typename Type>
void MainOscillator<Type>::setFrequencyAdjustVal(Type newValue) {
    frequencyAdjustVal = newValue;
}

template <typename Type>
void MainOscillator<Type>::reset() noexcept {
    processorChain.reset();
}

template <typename Type>
void MainOscillator<Type>::prepare(const juce::dsp::ProcessSpec& spec) {
    processorChain.prepare(spec);
}