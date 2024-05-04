/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "UI/TestWindow.h"
#include "UI/AdsrComponent.h"

//==============================================================================
/**
*/
class DoobGrooveTestSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DoobGrooveTestSynthAudioProcessorEditor (DoobGrooveTestSynthAudioProcessor& p);
    ~DoobGrooveTestSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscSelector;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DoobGrooveTestSynthAudioProcessor& audioProcessor;
    TestWindow testWindow;
    AdsrComponent adsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoobGrooveTestSynthAudioProcessorEditor)
};
