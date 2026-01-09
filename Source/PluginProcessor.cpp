#include "PluginProcessor.h"

KlinkerAudioProcessor::KlinkerAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

KlinkerAudioProcessor::~KlinkerAudioProcessor() {}

const juce::String KlinkerAudioProcessor::getName() const { return "Klinker"; }
bool KlinkerAudioProcessor::acceptsMidi() const { return false; }
bool KlinkerAudioProcessor::producesMidi() const { return false; }
bool KlinkerAudioProcessor::isMidiEffect() const { return false; }
double KlinkerAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int KlinkerAudioProcessor::getNumPrograms() { return 1; }
int KlinkerAudioProcessor::getCurrentProgram() { return 0; }
void KlinkerAudioProcessor::setCurrentProgram (int /*index*/) {}
const juce::String KlinkerAudioProcessor::getProgramName (int /*index*/) { return {}; }
void KlinkerAudioProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/) {}

void KlinkerAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void KlinkerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void KlinkerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any output channels that didn't contain input data,
    // (because these aren't guaranteed to be empty - they may contain garbage).
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // For now: Silence/Passthrough is fine.
}

// No Editor yet
bool KlinkerAudioProcessor::hasEditor() const { return false; }
juce::AudioProcessorEditor* KlinkerAudioProcessor::createEditor() { return nullptr; }

void KlinkerAudioProcessor::getStateInformation (juce::MemoryBlock& /*destData*/) {}
void KlinkerAudioProcessor::setStateInformation (const void* /*data*/, int /*sizeInBytes*/) {}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KlinkerAudioProcessor();
}