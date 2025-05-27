/*
  ==============================================================================

    SourceMixerComponent.h
    Created: 27 May 2025 12:21:01pm
    Author:  alex

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SourceMixerComponent : public juce::Component
{
public:
    SourceMixerComponent(
        juce::AudioProcessorValueTreeState& apvts,
        juce::String square,
        juce::String saw,
        juce::String subOsc,
        juce::String noise);
	~SourceMixerComponent() override;
    void paint(juce::Graphics& g) override;
	void resized() override;

private:
	using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	// Helper function to set up a slider with a label and an attachment
	void setSliderWithlabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    // Create Sliders
    juce::Slider squareSlider, sawSlider, subOscSlider, noiseSlider;

    // Create Labels
    juce::Label squareLabel{ "Square", "sq" };
    juce::Label sawLabel{ "Saw", "sw" };
    juce::Label subOscLabel{ "SubOsc", "sub" };
    juce::Label noiseLabel{ "Noise", "n" };

    // Slider Attachments to apvts
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> squareAttachment;
    std::unique_ptr<SliderAttachment> sawAttachment;
    std::unique_ptr<SliderAttachment> subOscAttachment;
    std::unique_ptr<SliderAttachment> noiseAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SourceMixerComponent)
};