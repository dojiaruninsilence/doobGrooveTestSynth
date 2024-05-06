/*
  ==============================================================================

    WhiteNoiseGeneratorComponent.cpp
    Created: 5 May 2024 3:42:08pm
    Author:  Zubin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WhiteNoiseGeneratorComponent.h"

//==============================================================================
WhiteNoiseGeneratorComponent::WhiteNoiseGeneratorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String gainId, juce::String minRandId, juce::String maxRandId) {
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 25);
    addAndMakeVisible(gainSlider);

    minRandSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    minRandSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 25);
    addAndMakeVisible(minRandSlider);

    maxRandSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    maxRandSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 25);
    addAndMakeVisible(maxRandSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);

    minRandAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, minRandId, minRandSlider);

    maxRandAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, maxRandId, maxRandSlider);
}


WhiteNoiseGeneratorComponent::~WhiteNoiseGeneratorComponent() {
}

void WhiteNoiseGeneratorComponent::paint (juce::Graphics& g) {
    g.fillAll(juce::Colours::darkorchid);
}

void WhiteNoiseGeneratorComponent::resized() {
    auto bounds = getLocalBounds();
    auto unitHeight = bounds.getHeight() / 3;
    gainSlider.setBounds(0, 0, bounds.getWidth(), unitHeight);
    minRandSlider.setBounds(0, gainSlider.getBottom(), bounds.getWidth(), unitHeight);
    maxRandSlider.setBounds(0, minRandSlider.getBottom(), bounds.getWidth(), unitHeight);
}
