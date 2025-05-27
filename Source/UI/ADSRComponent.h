/*
  ==============================================================================

    ADSRComponent.h
    Created: 7 Apr 2025 10:15:26am
    Author:  alex

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRComponent  : public juce::Component
{
public:
    ADSRComponent(
        juce::String name,
        juce::AudioProcessorValueTreeState& apvts,
        juce::String attackId, juce::String decayID,
        juce::String sustainId,
        juce::String releaseId);
    ~ADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    // Create Sliders
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    // Create Labels
    juce::Label attackLabel{ "Attack", "A" };
    juce::Label decayLabel{ "Decay", "D" };
    juce::Label sustainLabel{ "Sustain", "S" };
    juce::Label releaseLabel{ "Release", "R" };

    // Slider Attachments to apvts
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    juce::String componentName{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
