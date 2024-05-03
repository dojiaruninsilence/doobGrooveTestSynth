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

template <typename Type>
MainOscillator<Type>::~MainOscillator() {
    
}

template <typename Type>
void MainOscillator<Type>::setFrequency(Type newValue, bool force) {
    auto& osc = processorChain.template get<oscIndex>();
    osc.setFrequency(newValue, force);
}

template <typename Type>
void MainOscillator<Type>::setLevel(Type newValue) {
    auto& gain = processorChain.template get<gainIndex>();
    gain.setGainLinear(newValue);
}

template <typename Type>
void MainOscillator<Type>::reset() noexcept {
    processorChain.reset();
}

template <typename Type>
void MainOscillator<Type>::prepare(const juce::dsp::ProcessSpec& spec) {
    processorChain.prepare(spec);
}