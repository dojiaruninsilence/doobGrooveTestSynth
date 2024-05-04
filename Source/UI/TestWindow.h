/*
  ==============================================================================

    TestWindow.h
    Created: 3 May 2024 2:43:40pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../PluginProcessor.h"

#include "ScopeComponent.h"

//==============================================================================
/*
*/
class TestWindow  : public juce::Component
{
public:
    TestWindow(DoobGrooveTestSynthAudioProcessor& p);
    ~TestWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DoobGrooveTestSynthAudioProcessor& audioProcessor;
    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent{ midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };
    ScopeComponent<float> scopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestWindow)
};
