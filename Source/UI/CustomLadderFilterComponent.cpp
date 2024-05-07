/*
  ==============================================================================

    CustomLadderFilterComponent.cpp
    Created: 6 May 2024 12:58:38pm
    Author:  Zubin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomLadderFilterComponent.h"

//==============================================================================
CustomLadderFilterComponent::CustomLadderFilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscLadderModeId, juce::String freqCutoffId, juce::String resonanceId, juce::String driveId) {
    juce::StringArray ladderModeChoices{ "Bpf12", "Bpf24", "Hpf12", "Hpf24", "Lpf12", "Lpf24" };
    ladderModeSelector.addItemList(ladderModeChoices, 1);
    ladderModeSelector.setSelectedItemIndex(0);
    addAndMakeVisible(ladderModeSelector);

    freqCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    freqCutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(freqCutoffSlider);

    resonanceSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    resonanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(resonanceSlider);

    driveSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(driveSlider);

    ladderModeSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscLadderModeId, ladderModeSelector);

    freqCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, freqCutoffId, freqCutoffSlider);

    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, resonanceId, resonanceSlider);

    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, driveId, driveSlider);
}

CustomLadderFilterComponent::~CustomLadderFilterComponent() {
}

void CustomLadderFilterComponent::paint (juce::Graphics& g) {
    g.fillAll (juce::Colours::darkkhaki);
}

void CustomLadderFilterComponent::resized() {
    auto bounds = getLocalBounds();
    auto unitWidth = bounds.getWidth() / 3;
    auto unitHeight = bounds.getHeight() / 3;
    ladderModeSelector.setBounds(0, 0, bounds.getWidth(), unitHeight);
    freqCutoffSlider.setBounds(0, ladderModeSelector.getBottom(), unitWidth, unitHeight * 2);
    resonanceSlider.setBounds(freqCutoffSlider.getRight(), ladderModeSelector.getBottom(), unitWidth, unitHeight * 2);
    driveSlider.setBounds(resonanceSlider.getRight(), ladderModeSelector.getBottom(), unitWidth, unitHeight * 2);
}
