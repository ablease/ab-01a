/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/SourceMixerComponent.h"

//==============================================================================
/**
*/
class Ab01aAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Ab01aAudioProcessorEditor (Ab01aAudioProcessor&);
    ~Ab01aAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Ab01aAudioProcessor& audioProcessor;
    ADSRComponent adsr;
	OscComponent osc;
    SourceMixerComponent sourceMixer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ab01aAudioProcessorEditor)
};
