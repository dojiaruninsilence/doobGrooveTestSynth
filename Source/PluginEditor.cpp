/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DoobGrooveTestSynthAudioProcessorEditor::DoobGrooveTestSynthAudioProcessorEditor (DoobGrooveTestSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), scopeComponent(audioProcessor.getAudioBufferQueue()) {
    addAndMakeVisible(midiKeyboardComponent);
    addAndMakeVisible(scopeComponent);

    setSize (400, 300);

    auto area = getLocalBounds();
    scopeComponent.setTopLeftPosition(0, 80);
    scopeComponent.setSize(area.getWidth(), area.getHeight() - 100);

    midiKeyboardComponent.setMidiChannel(2);
    midiKeyboardState.addListener(&audioProcessor.getMidiMessageCollector());
}

DoobGrooveTestSynthAudioProcessorEditor::~DoobGrooveTestSynthAudioProcessorEditor() {
    midiKeyboardState.removeListener(&audioProcessor.getMidiMessageCollector());
}

//==============================================================================
void DoobGrooveTestSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void DoobGrooveTestSynthAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    midiKeyboardComponent.setBounds(area.removeFromTop(80).reduced(8));
}
