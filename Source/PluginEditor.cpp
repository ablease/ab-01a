/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Ab01aAudioProcessorEditor::Ab01aAudioProcessorEditor (Ab01aAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // ADSR
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attackSlider);
	decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
	sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
	releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", releaseSlider);

	// OSC selector
	oscSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        audioProcessor.apvts, "OSC", oscSelector);

	setSliderParams(attackSlider);
	setSliderParams(decaySlider);
	setSliderParams(sustainSlider);
	setSliderParams(releaseSlider);
}

Ab01aAudioProcessorEditor::~Ab01aAudioProcessorEditor()
{
}

//==============================================================================
void Ab01aAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkgrey);
}

void Ab01aAudioProcessorEditor::resized()
{
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
    const auto sliderWidth = getWidth() / 4 - padding;
    const auto sliderHeight = getHeight() / 4 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void Ab01aAudioProcessorEditor::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}