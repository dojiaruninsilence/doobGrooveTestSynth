/*
  ==============================================================================

    CustomLadderFilterComponent.h
    Created: 6 May 2024 12:58:38pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomLadderFilterComponent  : public juce::Component
{
public:
    CustomLadderFilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscLadderModeId, juce::String freqCutoffId, juce::String resonanceId, juce::String driveId);
    ~CustomLadderFilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox ladderModeSelector;
    juce::Slider freqCutoffSlider;
    juce::Slider resonanceSlider;
    juce::Slider driveSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> ladderModeSelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLadderFilterComponent)
};
