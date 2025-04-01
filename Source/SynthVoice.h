/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Mar 2025 10:17:24am
    Author:  alex

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void updateADSR(const float attack, const float decay, const float sustain, const float release);


private:
	juce::AudioBuffer<float> synthBuffer;

	juce::ADSR adsr;
	juce::ADSR::Parameters adsrParams;
	
	juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x); } };
	
	juce::dsp::Gain<float> gain;
	
	bool isPrepared{ false };
};