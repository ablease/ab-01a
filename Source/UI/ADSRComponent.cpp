/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 7 Apr 2025 10:15:26am
    Author:  alex

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
	
    ADSRTitle.setText("ENV", juce::dontSendNotification);
	ADSRTitle.setFont(juce::Font(15.0f, juce::Font::bold));
	ADSRTitle.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(ADSRTitle);

    // adsr sliders
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::darkgrey);
}

void ADSRComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto titleHeight = 20;
    const auto sliderWidth = getWidth() / 4 - padding;
    const auto sliderHeight = getHeight() - titleHeight - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0 + titleHeight + padding;
	

    // title label
	ADSRTitle.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), titleHeight);

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void ADSRComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}