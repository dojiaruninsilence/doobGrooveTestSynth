/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "UI/ScopeComponent.h"

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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DoobGrooveTestSynthAudioProcessor& audioProcessor;
    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent{ midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };
    ScopeComponent<float> scopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoobGrooveTestSynthAudioProcessorEditor)
};
