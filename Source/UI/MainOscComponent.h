/*
  ==============================================================================

    MainOscComponent.h
    Created: 4 May 2024 8:11:02pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../PluginProcessor.h"

#include "CustomLadderFilterComponent.h"

//==============================================================================
/*
*/
class MainOscComponent  : public juce::Component
{
public:
    MainOscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId, juce::String oscLadderModeId, juce::String freqCutoffId, juce::String resonanceId, juce::String driveId);
    ~MainOscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //DoobGrooveTestSynthAudioProcessor& audioProcessor;
    juce::ComboBox oscSelector;
    juce::Slider gainSlider;
    juce::Slider pitchSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchAttachment;
    CustomLadderFilterComponent ladderFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainOscComponent)
};
