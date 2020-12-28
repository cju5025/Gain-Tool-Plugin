/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTool04AudioProcessor::GainTool04AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
   addParameter(mGain = new AudioParameterFloat("gain", "Gain", 0.f, 1.f, 1.f));

    
    mGainSmoothed = mGain->get();
}

GainTool04AudioProcessor::~GainTool04AudioProcessor()
{
}

//==============================================================================
const juce::String GainTool04AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainTool04AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainTool04AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainTool04AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainTool04AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainTool04AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainTool04AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainTool04AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainTool04AudioProcessor::getProgramName (int index)
{
    return {};
}

void GainTool04AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainTool04AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainTool04AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainTool04AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void GainTool04AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

        float* channelLeft = buffer.getWritePointer (0);
        float* channelRight = buffer.getWritePointer (1);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            mGainSmoothed = mGainSmoothed - 0.004*(mGainSmoothed-mGain->get());
            
            channelLeft[sample] *= mGainSmoothed;
            channelRight[sample] *= mGainSmoothed;
        }
}

//==============================================================================
bool GainTool04AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GainTool04AudioProcessor::createEditor()
{
    return new GainTool04AudioProcessorEditor (*this);
}

//==============================================================================
void GainTool04AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void GainTool04AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainTool04AudioProcessor();
}
