/*
  ==============================================================================

    OscComponent.cpp
    Created: 14 May 2025 5:15:07pm
    Author:  alex

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{"Sine", "Saw", "Square"};
	oscWaveSelector.addItemList(choices, 1);
	addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 90, 20);


}
