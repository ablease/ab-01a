/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Ab01aAudioProcessor::Ab01aAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
	 ), apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
	synth.addSound(new SynthSound());
	synth.addVoice(new SynthVoice());

}

Ab01aAudioProcessor::~Ab01aAudioProcessor()
{
}

//==============================================================================
const juce::String Ab01aAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Ab01aAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Ab01aAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Ab01aAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Ab01aAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Ab01aAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Ab01aAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Ab01aAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Ab01aAudioProcessor::getProgramName (int index)
{
    return {};
}

void Ab01aAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Ab01aAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
			voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void Ab01aAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Ab01aAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Ab01aAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
		if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
		{
			// oscilator controls, adsr, lfo etc from value tree state
			// ADSR Can we do this so that it only updates when the value changes?
			auto& attack = *apvts.getRawParameterValue("ATTACK");
			auto& decay = *apvts.getRawParameterValue("DECAY");
			auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
			auto& release = *apvts.getRawParameterValue("RELEASE");

			auto& oscWaveChoice = *apvts.getRawParameterValue("WAVETYPE");
			voice->update(attack.load(), decay.load(), sustain.load(), release.load());

			voice->getOscillator().setWaveType(oscWaveChoice);
		}
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Ab01aAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Ab01aAudioProcessor::createEditor()
{
    return new Ab01aAudioProcessorEditor (*this);
}

//==============================================================================
void Ab01aAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Ab01aAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Ab01aAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Ab01aAudioProcessor::createParameterLayout()
{
    // combo box to switch oscilators
    // adsr params

	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // OSC selector
	params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVETYPE", "Osc Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // ADSR
	params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.1f, 1.0f, 0.1f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.1f, 1.0f, 0.1f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.1f, 3.0f, 0.4f));

	
    return { params.begin(), params.end() };
}