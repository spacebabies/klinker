#pragma once
#include <juce_audio_utils/juce_audio_utils.h>

class KlinkerAudioProcessor : public juce::AudioProcessor
{
public:
    KlinkerAudioProcessor();
    ~KlinkerAudioProcessor() override;

    using AudioProcessor::processBlock;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    // ==============================================================================
    // DSP Variables
    // ==============================================================================

    // The "Tape Loop": stores past audio samples
    juce::AudioBuffer<float> delayBuffer;

    // The "Write Head": current position in the buffer
    int writePosition { 0 };

    // Parameters (hardcoded for now, we'll make knobs later)
    float currentDelayTimeInMs { 350.0f }; // 350ms slapback
    float currentFeedback { 0.4f };        // 40% repeats
    float currentWetLevel { 0.5f };        // 50% effect mix

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KlinkerAudioProcessor)
};