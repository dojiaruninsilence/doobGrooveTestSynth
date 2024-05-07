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
    : AudioProcessorEditor(&p), audioProcessor(p), testWindow(p), whiteNoise(audioProcessor.apvts, "WHITE_NOISE_GAIN", "WHITE_NOISE_MIN_RAND_VAL", "WHITE_NOISE_MAX_RAND_VAL"), osc1(audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH", "OSC1_LAD_FILT_MODE", "OSC1_FREQ_CUTOFF", "OSC1_RESONANCE", "OSC1_DRIVE"), osc2(audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH", "OSC2_LAD_FILT_MODE", "OSC2_FREQ_CUTOFF", "OSC2_RESONANCE", "OSC2_DRIVE"), adsr(audioProcessor.apvts) {
    addAndMakeVisible(testWindow);

    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);

    addAndMakeVisible(whiteNoise);

    addAndMakeVisible(adsr);

    setSize(1000, 350);
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
    auto unitWidth = area.getWidth() / 10;
    auto unitHeight = area.getHeight() / 4;

    testWindow.setBounds(0, 0, unitWidth * 4, area.getHeight());

    osc1.setBounds(testWindow.getRight(), 0, unitWidth * 3, area.getHeight() / 2);
    osc2.setBounds(testWindow.getRight(), osc1.getBottom(), unitWidth * 3, area.getHeight() / 2);

    adsr.setBounds(osc1.getRight(), 0, unitWidth * 3, unitHeight * 3);
    whiteNoise.setBounds(osc1.getRight(), adsr.getBottom(), unitWidth * 3, unitHeight);
}
