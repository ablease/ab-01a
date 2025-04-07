/*
  ==============================================================================

    ADSRData.h
    Created: 7 Apr 2025 10:15:51am
    Author:  alex

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRData  : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:

    juce::ADSR::Parameters adsrParams;
};
