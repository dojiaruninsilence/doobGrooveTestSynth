/*
  ==============================================================================

    WhiteNoiseGenerator.h
    Created: 5 May 2024 3:41:11pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template <typename Type>
class WhiteNoiseGenerator {
public:
    WhiteNoiseGenerator() {}
    ~WhiteNoiseGenerator() {}

    void setLevel(Type newValue) {
        gain = newValue;
    }
    void setMaxRandVal(Type newValue) {
        maxRandVal = newValue;
    }
    void setMinRandVal(Type newValue) {
        minRandVal = newValue;
    }

    void prepare(const juce::dsp::ProcessSpec& spec) {}

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept {
        if (gain > 0.01) {
            using BlockType = typename ProcessContext::AudioBlockType;
            const BlockType& audioBlock = context.getOutputBlock();

            for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel) {
                auto* channelData = audioBlock.getChannelPointer(channel);
                for (int sampleIndex = 0; sampleIndex < audioBlock.getNumSamples(); ++sampleIndex) {
                    Type whiteNoiseSample = generateRandomNumber(minRandVal, maxRandVal);
                    whiteNoiseSample = whiteNoiseSample / 2;
                    whiteNoiseSample *= gain;

                    // Log the generated sample for debugging
                    DBG("Generated sample: " << whiteNoiseSample);

                    // Ensure the sample is within the valid range for audio data
                    if (whiteNoiseSample > 1.0f)
                        whiteNoiseSample = 1.0f;
                    else if (whiteNoiseSample < -1.0f)
                        whiteNoiseSample = -1.0f;

                
                        channelData[sampleIndex] += whiteNoiseSample;
                }
            }
        }
    }

private:
    Type maxRandVal{ 0 };
    Type minRandVal{ 0 };
    Type gain{ 0 };

    juce::Random random;

    Type generateRandomNumber(Type minValue, Type maxValue) {
        if (minValue > maxValue) {
            std::swap(minValue, maxValue);
        }

        return static_cast<Type>(random.nextFloat() * (maxValue - minValue) + minValue);
    }
};

template class WhiteNoiseGenerator<float>;