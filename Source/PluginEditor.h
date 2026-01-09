#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

//==============================================================================
class KlinkerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KlinkerAudioProcessorEditor (KlinkerAudioProcessor&);
    ~KlinkerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Reference to the processor (the DSP engine)
    KlinkerAudioProcessor& audioProcessor;

    // --- UI Components ---
    juce::Slider delayTimeSlider;
    juce::Label  delayTimeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;

    juce::Slider feedbackSlider;
    juce::Label  feedbackLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    juce::Slider wetLevelSlider;
    juce::Label  wetLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KlinkerAudioProcessorEditor)
};
