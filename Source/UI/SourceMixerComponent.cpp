/*
  ==============================================================================

    SourceMixerComponent.cpp
    Created: 27 May 2025 12:21:01pm
    Author:  alex

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SourceMixerComponent.h"

//==============================================================================
SourceMixerComponent::SourceMixerComponent(
    juce::AudioProcessorValueTreeState& apvts,
    juce::String squareId,
    juce::String sawId,
    juce::String subOscId,
    juce::String noiseId)
{
    setSliderWithlabel(squareSlider, squareLabel, apvts, squareId, squareAttachment);;
	setSliderWithlabel(sawSlider, sawLabel, apvts, sawId, sawAttachment);
	setSliderWithlabel(subOscSlider, subOscLabel, apvts, subOscId, subOscAttachment);
	setSliderWithlabel(noiseSlider, noiseLabel, apvts, noiseId, noiseAttachment);
}

SourceMixerComponent::~SourceMixerComponent()
{
}
void SourceMixerComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::darkgrey);
	g.setColour(juce::Colours::white);
    g.setFont(20.0f);
	g.drawText("Source Mixer", labelSpace.withX(5), juce::Justification::centredTop);

	g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);

}
void SourceMixerComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;

	squareSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    squareLabel.setBounds(squareSlider.getX(), labelStart, sliderWidth, labelHeight);

	sawSlider.setBounds(squareSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sawLabel.setBounds(sawSlider.getX(), labelStart, sliderWidth, labelHeight);

	subOscSlider.setBounds(sawSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	subOscLabel.setBounds(subOscSlider.getX(), labelStart, sliderWidth, labelHeight);

	noiseSlider.setBounds(subOscSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	noiseLabel.setBounds(noiseSlider.getX(), labelStart, sliderWidth, labelHeight);
}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void SourceMixerComponent::setSliderWithlabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.05f);
	label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

