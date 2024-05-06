/*
  ==============================================================================

    AdsrData.h
    Created: 3 May 2024 4:37:27pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template <typename Type>
class AdsrData : public juce::ADSR {
public:
    void update(Type attack, Type decay, Type sustain, Type release) {
        adsrParams.attack = attack;
        adsrParams.decay = decay;
        adsrParams.sustain = sustain;
        adsrParams.release = release;

        setParameters(adsrParams);
    }

    void prepare(const juce::dsp::ProcessSpec& spec) {
        setSampleRate(spec.sampleRate);
    }

    template <typename ProcessContext>
    void process(const ProcessContext& context) {
        using BlockType = typename ProcessContext::AudioBlockType;
        const BlockType& audioBlock = context.getOutputBlock();
        Type numSamples = audioBlock.getNumSamples();
        Type numChannels = audioBlock.getNumChannels();

        for (int sample = 0; sample < numSamples; ++sample) {
            Type envelopeValue = getNextSample();

            for (int channel = 0; channel < numChannels; ++channel) {
                Type currentSample = audioBlock.getSample(channel, sample);
                audioBlock.setSample(channel, sample, currentSample * envelopeValue);
            }
        }

        //applyEnvelopeToBuffer(audioBlock, 0, numSamples);
    }

private:
    juce::ADSR::Parameters adsrParams;
};

template class AdsrData<float>;