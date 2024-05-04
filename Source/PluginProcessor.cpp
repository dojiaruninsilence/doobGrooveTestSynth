/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DoobGrooveTestSynthAudioProcessor::DoobGrooveTestSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    doobEngine.addVoice(new MainVoice);
}

DoobGrooveTestSynthAudioProcessor::~DoobGrooveTestSynthAudioProcessor() {
}

//==============================================================================
const juce::String DoobGrooveTestSynthAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool DoobGrooveTestSynthAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DoobGrooveTestSynthAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DoobGrooveTestSynthAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DoobGrooveTestSynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int DoobGrooveTestSynthAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DoobGrooveTestSynthAudioProcessor::getCurrentProgram() {
    return 0;
}

void DoobGrooveTestSynthAudioProcessor::setCurrentProgram (int index){
}

const juce::String DoobGrooveTestSynthAudioProcessor::getProgramName (int index) {
    return {};
}

void DoobGrooveTestSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DoobGrooveTestSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    doobEngine.setCurrentPlaybackSampleRate(sampleRate);
    //doobEngine.prepare({ sampleRate, (juce::uint32)samplesPerBlock, 2 });
    midiMessageCollector.reset(sampleRate);

    for (int i = 0; i < doobEngine.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<MainVoice*>(doobEngine.getVoice(i))) {
            voice->prepare({ sampleRate, (juce::uint32)samplesPerBlock, (juce::uint32)getTotalNumOutputChannels() });
        }
    }
}

void DoobGrooveTestSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DoobGrooveTestSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DoobGrooveTestSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    midiMessageCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // update per user input
    for (int i = 0; i < doobEngine.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<juce::MPESynthesiserVoice*>(doobEngine.getVoice(i))) {
            // osc controls
            // adsr
            // lfo
        }
    }

    doobEngine.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    scopeDataCollector.process(buffer.getReadPointer(0), (size_t)buffer.getNumSamples());
}

//==============================================================================
bool DoobGrooveTestSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DoobGrooveTestSynthAudioProcessor::createEditor()
{
    return new DoobGrooveTestSynthAudioProcessorEditor (*this);
}

//==============================================================================
void DoobGrooveTestSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DoobGrooveTestSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::MidiMessageCollector& DoobGrooveTestSynthAudioProcessor::getMidiMessageCollector() noexcept {
    return midiMessageCollector;
}

AudioBufferQueue<float>& DoobGrooveTestSynthAudioProcessor::getAudioBufferQueue() noexcept {
    return audioBufferQueue;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DoobGrooveTestSynthAudioProcessor();
}
