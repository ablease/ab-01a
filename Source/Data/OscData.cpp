/*
  ==============================================================================

    OscData.cpp
    Created: 14 May 2025 4:27:07pm
    Author:  alex

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
	prepare(spec);
}
//>("WAVETYPE", "Osc Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
void OscData::setWaveType(const int choice)
{
	switch (choice)
	{
	case 0: // Sine
		initialise([](float x) { return std::sin(x); });
		break;
	case 1: // Saw
		initialise([](float x) { return x / juce::MathConstants<float>::pi; });
		break;
	case 2: // Square
		initialise([](float x) { return (x < 0.0f) ? -1.0f : 1.0f; });
		break;
	//case 3: // Noise
	//	break;
	default:
		jassertfalse; // Invalid choice for Wave Type
		break;
	}
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
	// Set the frequency of the oscillator
	setFrequency(juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
	process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}