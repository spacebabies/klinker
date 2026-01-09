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

    // The APVTS (Public so the Editor can attach to it)
    juce::AudioProcessorValueTreeState apvts;

private:
    // ==============================================================================
    // DSP Variables
    // ==============================================================================

    // The "Tape Loop": stores past audio samples
    juce::AudioBuffer<float> delayBuffer;

    // The "Write Head": current position in the buffer
    int writePosition { 0 };

private:
    // Helper to define our parameter layout (Ranges, Steps, IDs)
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    // Internal smoothing buffers or variables if needed, but for now we read directly from APVTS
    // or use a smoothed value in processBlock.



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KlinkerAudioProcessor)
};