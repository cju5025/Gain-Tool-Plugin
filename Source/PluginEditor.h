/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GainTool04AudioProcessorEditor  : public juce::AudioProcessorEditor,
public Slider::Listener
{
public:
    GainTool04AudioProcessorEditor (GainTool04AudioProcessor&);
    ~GainTool04AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;

private:
    Slider mGainSlider;
    
    GainTool04AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainTool04AudioProcessorEditor)
};
