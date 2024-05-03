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
    tempBlock = juce::dsp::AudioBlock<float>(heapBlock, spec.numChannels, spec.maximumBlockSize);
    processorChain.prepare(spec);
}

void MainVoice::noteStarted() {
    auto velocity = getCurrentlyPlayingNote().noteOnVelocity.asUnsignedFloat();
    auto freqHz = (float)getCurrentlyPlayingNote().getFrequencyInHertz();

    processorChain.get<osc1Index>().setFrequency(freqHz, true);
    processorChain.get<osc1Index>().setLevel(velocity);
}

void MainVoice::notePitchbendChanged() {
    auto freqHz = (float)getCurrentlyPlayingNote().getFrequencyInHertz();
    processorChain.get<osc1Index>().setFrequency(freqHz);
}

void MainVoice::noteStopped(bool) {
    clearCurrentNote();
}

void MainVoice::notePressureChanged() {

}

void MainVoice::noteKeyStateChanged() {

}

void MainVoice::noteTimbreChanged() {

}

void MainVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    auto block = tempBlock.getSubBlock(0, (size_t)numSamples);
    block.clear();
    juce::dsp::ProcessContextReplacing<float> context(block);
    processorChain.process(context);

    juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock((size_t)startSample, (size_t)numSamples).add(tempBlock);
}