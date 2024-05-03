/*
  ==============================================================================

    ScopeDataCollector.h
    Created: 2 May 2024 2:58:48pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "AudioBufferQueue.h"

template <typename SampleType>
class ScopeDataCollector {
public:
    ScopeDataCollector(AudioBufferQueue<SampleType>& queueToUse);
    ~ScopeDataCollector();

    void process(const SampleType* data, size_t numSamples);
private:
    AudioBufferQueue<SampleType>& audioBufferQueue;
    std::array<SampleType, AudioBufferQueue<SampleType>::bufferSize> buffer;
    size_t numCollected;
    SampleType prevSample = SampleType(100);

    static constexpr auto triggerLevel = SampleType(0.05);

    enum class State { waitingForTrigger, collecting } state { State::waitingForTrigger };
};

template class ScopeDataCollector<float>;