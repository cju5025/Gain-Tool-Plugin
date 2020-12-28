/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTool04AudioProcessorEditor::GainTool04AudioProcessorEditor (GainTool04AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (150, 200);
    
    
    mGainSlider.setRange(0.f, 1.f, 0.001f);
    mGainSlider.setValue(*gainParameter);
    mGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);
}

GainTool04AudioProcessorEditor::~GainTool04AudioProcessorEditor()
{
}

//==============================================================================
void GainTool04AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(Colours::darkslategrey);
    g.drawText("Gain", ((getWidth() / 2) * 1) - (50), (getHeight() / 2) - 50, 100, 100, Justification::left, false);
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightslategrey);
    getLookAndFeel().setColour (juce::Slider::textBoxTextColourId, juce::Colours::lightslategrey);
}

void GainTool04AudioProcessorEditor::resized()
{
    mGainSlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);
}

void GainTool04AudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    auto& params = processor.getParameters();
    
    if (slider == &mGainSlider)
    {
        AudioParameterFloat* gainParameter = (AudioParameterFloat*)params.getUnchecked(0);
        *gainParameter = mGainSlider.getValue();
    }
}
