/*
  ==============================================================================

    MainOscComponent.cpp
    Created: 4 May 2024 8:11:02pm
    Author:  Zubin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainOscComponent.h"

//==============================================================================
MainOscComponent::MainOscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId, juce::String oscLadderModeId, juce::String freqCutoffId, juce::String resonanceId, juce::String driveId)
    : ladderFilter(apvts, oscLadderModeId, freqCutoffId, resonanceId, driveId) {
    juce::StringArray oscChoices{ "Sine", "Saw", "Square" };
    oscSelector.addItemList(oscChoices, 1);
    oscSelector.setSelectedItemIndex(0);
    addAndMakeVisible(oscSelector);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(gainSlider);

    pitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(pitchSlider);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscSelector);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);

    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, pitchId, pitchSlider);

    addAndMakeVisible(ladderFilter);
}

MainOscComponent::~MainOscComponent() {
}

void MainOscComponent::paint (juce::Graphics& g) {
    // fill
    g.fillAll(juce::Colours::darkgoldenrod);
}

void MainOscComponent::resized() {
    auto bounds = getLocalBounds();
    auto unitHeight = bounds.getHeight() / 3;
    oscSelector.setBounds(0, 0, bounds.getWidth() / 2, unitHeight);
    gainSlider.setBounds(0, oscSelector.getBottom(), bounds.getWidth() / 2, unitHeight);
    pitchSlider.setBounds(0, gainSlider.getBottom(), bounds.getWidth() / 2, unitHeight);
    ladderFilter.setBounds(oscSelector.getRight(), 0, bounds.getWidth() / 2, bounds.getHeight());
}
