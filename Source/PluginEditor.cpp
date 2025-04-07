/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Ab01aAudioProcessorEditor::Ab01aAudioProcessorEditor (Ab01aAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // ADSR
	addAndMakeVisible(adsr);

	// OSC selector
	oscSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        audioProcessor.apvts, "OSC", oscSelector);
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
	// set ADSR component bounds
    adsr.setBounds(getWidth()/2, 0, getWidth()/2, getHeight());
}
