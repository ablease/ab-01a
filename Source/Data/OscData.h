/*
  ==============================================================================

    OscData.h
    Created: 14 May 2025 4:27:07pm
    Author:  alex

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public::juce::dsp::Oscillator<float>
{
public:
    void setWaveType(const int choice);

private:

};