/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DoobSynth/DoobEngine.h"
#include "DoobSynth/MainVoice.h"

#include "Effects/CustomLadderFilter.h"

#include "Modules/AdsrData.h"

#include "Utils/AudioBufferQueue.h"
#include "Utils/ScopeDataCollector.h"


//==============================================================================
/**
*/
class DoobGrooveTestSynthAudioProcessor  : public juce::AudioProcessor {
public:
    //==============================================================================
    DoobGrooveTestSynthAudioProcessor();
    ~DoobGrooveTestSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::MidiMessageCollector& getMidiMessageCollector() noexcept;
    AudioBufferQueue<float>& getAudioBufferQueue() noexcept;

    juce::AudioProcessorValueTreeState apvts;

private:
    //==============================================================================
    DoobEngine doobEngine;
    MainVoice mainVoice;

    juce::MidiMessageCollector midiMessageCollector;
    AudioBufferQueue<float> audioBufferQueue;
    ScopeDataCollector<float> scopeDataCollector{ audioBufferQueue };
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();

    //juce::MPESynthesiser synth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoobGrooveTestSynthAudioProcessor)
};
