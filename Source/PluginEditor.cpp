#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KlinkerAudioProcessorEditor::KlinkerAudioProcessorEditor (KlinkerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // --- 1. Delay Time Slider ---
    delayTimeSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    delayTimeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible (delayTimeSlider);

    delayTimeLabel.setText ("Delay Time", juce::dontSendNotification);
    delayTimeLabel.setJustificationType (juce::Justification::centred);
    delayTimeLabel.attachToComponent (&delayTimeSlider, false);

    // Connect to APVTS (Using the ID "DELAY_MS" we defined in Processor)
    delayTimeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "DELAY_MS", delayTimeSlider);

    // --- 2. Feedback Slider ---
    feedbackSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible (feedbackSlider);

    feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType (juce::Justification::centred);
    feedbackLabel.attachToComponent (&feedbackSlider, false);

    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "FEEDBACK", feedbackSlider);

    // --- 3. Wet Level Slider ---
    wetLevelSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    wetLevelSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible (wetLevelSlider);

    wetLevelLabel.setText ("Mix", juce::dontSendNotification);
    wetLevelLabel.setJustificationType (juce::Justification::centred);
    wetLevelLabel.attachToComponent (&wetLevelSlider, false);

    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "WET", wetLevelSlider);

    // Set the window size
    setSize (400, 300);
}

KlinkerAudioProcessorEditor::~KlinkerAudioProcessorEditor()
{
}

//==============================================================================
void KlinkerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background Color (Dark Grey)
    g.fillAll (juce::Colours::darkgrey);

    // Title
    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("Klinker", getLocalBounds().removeFromTop(40), juce::Justification::centred, 1);
}

void KlinkerAudioProcessorEditor::resized()
{
    // Simple Layout: 3 Knobs in a row
    auto area = getLocalBounds().reduced(20);
    auto topArea = area.removeFromTop(40); // Skip title

    // Calculate width for each knob
    int knobWidth = area.getWidth() / 3;
    int knobHeight = 200;

    // Define positions
    auto knobArea = area.withHeight(knobHeight).withY(60); // Push down a bit
    
    delayTimeSlider.setBounds (knobArea.removeFromLeft(knobWidth).reduced(10));
    feedbackSlider.setBounds  (knobArea.removeFromLeft(knobWidth).reduced(10));
    wetLevelSlider.setBounds  (knobArea.removeFromLeft(knobWidth).reduced(10));
}
