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
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
};

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	adsr.noteOff();
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

    osc.prepare(spec);

    gain.prepare(spec);
    gain.setGainLinear(0.1f);

	isPrepared = true;
};

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
{
	jassert(isPrepared);

	juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(outputBuffer, startSample, outputBuffer.getNumSamples());
};

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

};