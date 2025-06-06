/*
  ==============================================================================

    SynthVoice.cpp
    Created: 31 Mar 2025 10:17:24am
    Author:  alex

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
};

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
	osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
};

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();

	if (!allowTailOff || !adsr.isActive())
		clearCurrentNote();
};

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{

};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	adsr.setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

	osc.prepareToPlay(spec);

    gain.prepare(spec);
    gain.setGainLinear(0.3f);

	isPrepared = true;
};

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) 
{
	adsr.updateADSR(attack, decay, sustain, release);
};

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
{
	jassert(isPrepared);

	if (!isVoiceActive())
		return;

	synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	synthBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
	osc.getNextAudioBlock(audioBlock);
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

	for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
	{
		outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

		if (!adsr.isActive())
			clearCurrentNote();
	}
};

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

};