/*
  ==============================================================================

    SynthSound.h
    Created: 31 Mar 2025 10:18:14am
    Author:  alex

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}

	bool appliesToChannel(int midiChannel) override
	{
		return true;
	}
};