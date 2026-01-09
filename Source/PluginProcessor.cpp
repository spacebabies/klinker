#include "PluginProcessor.h"
#include "PluginEditor.h" // We will create this next

KlinkerAudioProcessor::KlinkerAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
       apvts (*this, nullptr, "Parameters", createParameterLayout())
{
}

KlinkerAudioProcessor::~KlinkerAudioProcessor() {}

// Define the Parameter Layout (The Rules)
juce::AudioProcessorValueTreeState::ParameterLayout KlinkerAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // 1. Delay Time: 200, 250, 300, 350, 400 ms
    // Range: 200 to 400, Interval: 50
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "DELAY_MS",       // Parameter ID
        "Delay Time",     // Name
        juce::NormalisableRange<float>(200.0f, 400.0f, 50.0f), // Range & Step
        200.0f            // Default value
    ));

    // 2. Feedback: 0.3, 0.4, 0.5
    // Range: 0.3 to 0.5, Interval: 0.1
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "FEEDBACK",
        "Feedback",
        juce::NormalisableRange<float>(0.3f, 0.5f, 0.1f),
        0.5f
    ));

    // 3. Wet Level: 0-100% in steps of 10%
    // Range: 0.0 to 1.0, Interval: 0.1
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "WET",
        "Wet Level",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f),
        0.5f
    ));

    return layout;
}

const juce::String KlinkerAudioProcessor::getName() const { return "Klinker"; }
bool KlinkerAudioProcessor::acceptsMidi() const { return false; }
bool KlinkerAudioProcessor::producesMidi() const { return false; }
bool KlinkerAudioProcessor::isMidiEffect() const { return false; }
double KlinkerAudioProcessor::getTailLengthSeconds() const
{
    // Fetch directly from APVTS (safe here)
    return apvts.getRawParameterValue("DELAY_MS")->load() / 1000.0;
}

int KlinkerAudioProcessor::getNumPrograms() { return 1; }
int KlinkerAudioProcessor::getCurrentProgram() { return 0; }
void KlinkerAudioProcessor::setCurrentProgram (int /*index*/) {}
const juce::String KlinkerAudioProcessor::getProgramName (int /*index*/) { return {}; }
void KlinkerAudioProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/) {}

void KlinkerAudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    // 1. Calculate how much buffer size we need for max 2 seconds of delay
    // + safety margin.
    const int numInputChannels = getTotalNumInputChannels();
    // Buffer size = 2 seconds worth of samples (e.g., 96000 samples @ 48kHz)
    // This is the maximum delay window - all delay times must fit within this
    const int delayBufferSize = 2 * (int)sampleRate;

    // 2. Initialize the delay buffer
    delayBuffer.setSize (numInputChannels, delayBufferSize);

    // 3. Clear garbage data
    delayBuffer.clear();

    // 4. Reset write head
    writePosition = 0;
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

    // --- READ PARAMETERS FROM APVTS ---
    // Atomic loads are thread-safe and lock-free
    float currentDelayTimeInMs = apvts.getRawParameterValue("DELAY_MS")->load();
    float currentFeedback      = apvts.getRawParameterValue("FEEDBACK")->load();
    float currentWetLevel      = apvts.getRawParameterValue("WET")->load();

    // Clear unused output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Audio processing usually happens per channel (Left, Right)
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = delayBuffer.getNumSamples();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // Get pointers to the raw data (faster than calling getSample repeatedly)
        // 'channelData' is the main audio stream (Input -> Output)
        // 'delayData' is our internal tape loop
        auto* channelData = buffer.getWritePointer (channel);
        auto* delayData = delayBuffer.getWritePointer (channel);

        // Calculate the read position (The Past)
        // Formula: ReadPos = WritePos - (Time * SampleRate)
        const int delaySamples = (int)(currentDelayTimeInMs / 1000.0f * getSampleRate());

        // Process sample by sample
        for (int sample = 0; sample < bufferLength; ++sample)
        {
            // 1. Calculate where to read from in the circular buffer
            // We add delayBufferLength to handle negative numbers before modulo
            int readPosition = (writePosition + sample - delaySamples + delayBufferLength) % delayBufferLength;

            // 2. Fetch the delayed sample
            float delayedSample = delayData[readPosition];

            // 3. Add the input sample to the delay buffer (for the future)
            // Include feedback so it repeats!
            // WritePos for this specific sample needs to wrap around too
            int currentWritePos = (writePosition + sample) % delayBufferLength;

            // Input + (Delayed * Feedback)
            delayData[currentWritePos] = channelData[sample] + (delayedSample * currentFeedback);

            // 4. Mix the delayed signal into the main output
            // Dry signal is already in channelData[sample], we just add the Wet signal
            channelData[sample] += delayedSample * currentWetLevel;
        }
    }

    // Advance the write position for the NEXT block of audio
    writePosition += bufferLength;
    writePosition %= delayBufferLength; // Wrap around safely
}

// Editor Enabled
bool KlinkerAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* KlinkerAudioProcessor::createEditor()
{
    return new KlinkerAudioProcessorEditor (*this);
}

void KlinkerAudioProcessor::getStateInformation (juce::MemoryBlock& /*destData*/) {}
void KlinkerAudioProcessor::setStateInformation (const void* /*data*/, int /*sizeInBytes*/) {}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KlinkerAudioProcessor();
}