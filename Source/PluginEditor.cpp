/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "UI/TestWindow.h"

//==============================================================================
DoobGrooveTestSynthAudioProcessorEditor::DoobGrooveTestSynthAudioProcessorEditor (DoobGrooveTestSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), testWindow(p), adsr(audioProcessor.apvts) {
    addAndMakeVisible(testWindow);
    addAndMakeVisible(adsr);

    setSize(800, 300);
}

DoobGrooveTestSynthAudioProcessorEditor::~DoobGrooveTestSynthAudioProcessorEditor() {
    
}

//==============================================================================
void DoobGrooveTestSynthAudioProcessorEditor::paint (juce::Graphics& g) {
    // fill black
    g.fillAll(juce::Colours::red);
}

void DoobGrooveTestSynthAudioProcessorEditor::resized() {
    auto area = getLocalBounds();
    testWindow.setBounds(0, 0, area.getWidth() / 2, area.getHeight());
    adsr.setBounds(testWindow.getRight(), 0, area.getWidth() / 2, area.getHeight());
}
