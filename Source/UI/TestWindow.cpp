/*
  ==============================================================================

    TestWindow.cpp
    Created: 3 May 2024 2:43:40pm
    Author:  Zubin

  ==============================================================================
*/

#include <JuceHeader.h>

#include "TestWindow.h"

//==============================================================================
TestWindow::TestWindow(DoobGrooveTestSynthAudioProcessor& p)
    : audioProcessor(p), scopeComponent(audioProcessor.getAudioBufferQueue()) {
    addAndMakeVisible(midiKeyboardComponent);
    addAndMakeVisible(scopeComponent);

    midiKeyboardComponent.setMidiChannel(2);
    midiKeyboardState.addListener(&audioProcessor.getMidiMessageCollector());
}

TestWindow::~TestWindow() {
    midiKeyboardState.removeListener(&audioProcessor.getMidiMessageCollector());
}

void TestWindow::paint (juce::Graphics& g) {

    g.fillAll(juce::Colours::darkolivegreen);   // clear the background
}

void TestWindow::resized() {
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto unitWidth = bounds.getWidth();
    const auto unitHeight = bounds.getHeight() / 5;
    const auto startX = padding;
    const auto startY = padding;
    
    midiKeyboardComponent.setBounds(startX, startY, unitWidth, unitHeight);
    scopeComponent.setBounds(startX, midiKeyboardComponent.getBottom() + padding, unitWidth, unitHeight * 4 - padding);
}
