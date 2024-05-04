/*
  ==============================================================================

    MainVoice.cpp
    Created: 2 May 2024 2:52:30pm
    Author:  Zubin

  ==============================================================================
*/

#include "MainVoice.h"

MainVoice::MainVoice() {
    auto& masterGain = processorChain.get<masterGainIndex>();
    masterGain.setGainLinear(0.7f);
}

//MainVoice::~MainVoice() {
//
//}

void MainVoice::prepare(const juce::dsp::ProcessSpec& spec) {
    adsr.setSampleRate(spec.sampleRate);

    tempBlock = juce::dsp::AudioBlock<float>(heapBlock, spec.numChannels, spec.maximumBlockSize);
    processorChain.prepare(spec);

    isPrepared = true;
}

void MainVoice::noteStarted() {
    auto velocity = getCurrentlyPlayingNote().noteOnVelocity.asUnsignedFloat();
    auto freqHz = (float)getCurrentlyPlayingNote().getFrequencyInHertz();

    processorChain.get<osc1Index>().setFrequency(freqHz, true);
    processorChain.get<osc1Index>().setLevel(velocity);

    adsr.noteOn();
}

void MainVoice::notePitchbendChanged() {
    auto freqHz = (float)getCurrentlyPlayingNote().getFrequencyInHertz();
    processorChain.get<osc1Index>().setFrequency(freqHz);
}

void MainVoice::noteStopped(bool allowTailOff) {
    //clearCurrentNote();
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void MainVoice::notePressureChanged() {

}

void MainVoice::noteKeyStateChanged() {

}

void MainVoice::noteTimbreChanged() {

}

void MainVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}

void MainVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);

    if (!isActive()) {
        return;
    }

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    processorChain.process(context);

    /*auto block = tempBlock.getSubBlock(0, (size_t)numSamples);
    block.clear();
    juce::dsp::ProcessContextReplacing<float> context(block);
    processorChain.process(context);

    juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock((size_t)startSample, (size_t)numSamples).add(tempBlock);*/

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive()) {
            clearCurrentNote();
        }
    }
}