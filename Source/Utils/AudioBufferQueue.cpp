/*
  ==============================================================================

    AudioBufferQueue.cpp
    Created: 2 May 2024 2:54:11pm
    Author:  Zubin

  ==============================================================================
*/

#include "AudioBufferQueue.h"

template <typename SampleType>
void AudioBufferQueue<SampleType>::push(const SampleType* dataToPush, size_t numSamples) {
    jassert(numSamples <= bufferSize);

    int start1, size1, start2, size2;
    abstractFifo.prepareToWrite(1, start1, size1, start2, size2);

    jassert(size1 <= 1);
    jassert(size2 == 0);

    if (size1 > 0) {
        juce::FloatVectorOperations::copy(buffers[(size_t)start1].data(), dataToPush, (int)juce::jmin(bufferSize, numSamples));
    }

    abstractFifo.finishedWrite(size1);
}

template <typename SampleType>
void AudioBufferQueue<SampleType>::pop(SampleType* outputBuffer) {
    int start1, size1, start2, size2;
    abstractFifo.prepareToRead(1, start1, size1, start2, start2);

    jassert(size1 <= 1);
    jassert(size2 == 0);

    if (size1 > 0) {
        juce::FloatVectorOperations::copy(outputBuffer, buffers[(size_t)start1].data(), (int)bufferSize);
    }

    abstractFifo.finishedRead(size1);
}