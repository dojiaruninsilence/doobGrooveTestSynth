/*
  ==============================================================================

    CustomLadderFilter.h
    Created: 6 May 2024 12:58:04pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

template <typename Type>
class CustomLadderFilter : public juce::dsp::LadderFilter<Type> {
public:
    void update(Type newModeIndex, Type newCutoff, Type newResonance, Type newDrive) {
        auto newMode = getModeType(newModeIndex);
        setMode(newMode);
        setCutoffFrequencyHz(newCutoff);
        setResonance(newResonance);
        setDrive(newDrive);
    }
private:
    juce::dsp::LadderFilterMode getModeType(Type modeIndex) {
        auto choice = static_cast<int>(modeIndex);
        switch (choice) {
            case 0: 
                return juce::dsp::LadderFilterMode::BPF12;
            
            case 1: 
                return juce::dsp::LadderFilterMode::BPF24;
            
            case 2: 
                return juce::dsp::LadderFilterMode::HPF12;
            
            case 3: 
                return juce::dsp::LadderFilterMode::HPF24;
            
            case 4: 
                return juce::dsp::LadderFilterMode::LPF12;
            
            case 5: 
                return juce::dsp::LadderFilterMode::LPF24;
            
            default: 
                return juce::dsp::LadderFilterMode::BPF12;
            
        }
    }
};

template class CustomLadderFilter<float>;