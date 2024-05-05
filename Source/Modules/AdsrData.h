/*
  ==============================================================================

    AdsrData.h
    Created: 3 May 2024 4:37:27pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR {
public:
    void update(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};