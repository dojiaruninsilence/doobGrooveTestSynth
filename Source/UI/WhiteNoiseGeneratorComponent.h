/*
  ==============================================================================

    WhiteNoiseGeneratorComponent.h
    Created: 5 May 2024 3:42:08pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WhiteNoiseGeneratorComponent  : public juce::Component
{
public:
    WhiteNoiseGeneratorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String gainId, juce::String minRandId, juce::String maxRandId);
    ~WhiteNoiseGeneratorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider gainSlider;
    juce::Slider maxRandSlider;
    juce::Slider minRandSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> maxRandAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> minRandAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhiteNoiseGeneratorComponent)
};
