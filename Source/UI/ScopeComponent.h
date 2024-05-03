/*
  ==============================================================================

    ScopeComponent.h
    Created: 2 May 2024 2:59:32pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Utils/AudioBufferQueue.h"

//==============================================================================
/*
*/
template <typename SampleType>
class ScopeComponent : public juce::Component,
    private juce::Timer {
public:
    using Queue = AudioBufferQueue<SampleType>;

    ScopeComponent(Queue& queueToUse);
    ~ScopeComponent() override;

    void setFramesPerSecond(int framesPerSecond);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Queue& audioBufferQueue;
    std::array<SampleType, Queue::bufferSize> sampleData;

    juce::dsp::FFT fft{ Queue::order };
    using WindowFun = juce::dsp::WindowingFunction<SampleType>;
    WindowFun windowFun{ (size_t)fft.getSize(), WindowFun::hann };
    std::array<SampleType, 2 * Queue::bufferSize> spectrumData;

    void timerCallback() override;
    static void plot(const SampleType* data, size_t numSamples, juce::Graphics& g, juce::Rectangle<SampleType> rect, SampleType scaler = SampleType(1), SampleType offset = SampleType(0));

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopeComponent)
};

template class ScopeComponent<float>;
