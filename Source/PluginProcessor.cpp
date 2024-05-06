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
    ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    for (int i = 0; i < 5; ++i) {
        doobEngine.addVoice(new MainVoice);
    }
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
    //midiMessageCollector.reset(sampleRate);

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
        if (auto voice = dynamic_cast<MainVoice*>(doobEngine.getVoice(i))) {
            // osc controls
            // adsr
            // lfo

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay= *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& osc1Choice = *apvts.getRawParameterValue("OSC1");
            auto& osc2Choice = *apvts.getRawParameterValue("OSC2");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& osc1Pitch = *apvts.getRawParameterValue("OSC1PITCH");
            auto& osc2Pitch = *apvts.getRawParameterValue("OSC2PITCH");

            auto& whiteNoiseGenGain = *apvts.getRawParameterValue("WHITE_NOISE_GAIN");
            auto& whiteNoiseGenMinRandVal = *apvts.getRawParameterValue("WHITE_NOISE_MIN_RAND_VAL");
            auto& whiteNoiseGenMaxRandVal = *apvts.getRawParameterValue("WHITE_NOISE_MAX_RAND_VAL");

            auto& osc1 = voice->getOscillator1();
            auto& osc2 = voice->getOscillator2();
            auto& whiteNoiseGen = voice->getWhiteNoiseGen();
            auto& adsr = voice->getAdsr();

            osc1.setType(osc1Choice);
            osc1.setLevel(osc1Gain);
            osc1.setFrequencyAdjustVal(osc1Pitch);

            osc2.setType(osc2Choice);
            osc2.setLevel(osc2Gain);
            osc2.setFrequencyAdjustVal(osc2Pitch);

            whiteNoiseGen.setLevel(whiteNoiseGenGain);
            whiteNoiseGen.setMinRandVal(whiteNoiseGenMinRandVal);
            whiteNoiseGen.setMaxRandVal(whiteNoiseGenMaxRandVal);

            adsr.update(attack.load(), decay.load(), sustain.load(), release.load());
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

//value tree
juce::AudioProcessorValueTreeState::ParameterLayout DoobGrooveTestSynthAudioProcessor::createParams() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // osc select    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1", "Oscillator 1", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2", "Oscillator 2", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // osc gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float>{ 0.0f, 1.0f, }, 0.1f, "dB"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float>{ 0.0f, 1.0f, }, 0.1f, "dB"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1PITCH", "Oscillator 1 Pitch", 0.0f, 2.0f, 1.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2PITCH", "Oscillator 2 Pitch", 0.0f, 2.0f, 1.0));

    // white noise generator
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WHITE_NOISE_GAIN", "White noise generator gain", 0.0f, 1.0f, 0.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WHITE_NOISE_MIN_RAND_VAL", "White noise generator minRandVal", -1.0f, 1.0f, -1.0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WHITE_NOISE_MAX_RAND_VAL", "White noise generator maxRandVal", -1.0f, 1.0f, -1.0));

    // adsr
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, }, 0.4f));

    return { params.begin(), params.end() };
}
