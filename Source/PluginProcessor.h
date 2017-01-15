/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyLowPassFilter.h"
#include "MyHighPassFilter.h"
#include "MyNotchFilter.h"
#include "MyBandPassFilter1.h"
#include "MyBandPassFilter2.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


	enum paramIndex {kCutoff = 0, kReso, kFilterOrder, kFilterType};
	enum filterTypeIndex { kLowPass = 0, kHighPass, kNotch, kBandPass1, kBandPass2, kNumFilterTypes };

	Array<float> frequencyResponse;
	Array<float> frequencies;

	Array<float> getFrequencyResponse();

	void refreshFilterForDisplay();

private:
	//MyLowPassFilter LowPassFilter[2];
	//MyHighPassFilter HighPassFilter[2];
	//MyNotchFilter NotchFilter[2];
	//MyBandPassFilter1 BandPassFilter1[2];
	//MyBandPassFilter2 BandPassFilter2[2];

	const int maxFilterOrder = 4;

	MyFilter **** Filters;

	AudioParameterFloat* cutoff;
	AudioParameterFloat* reso;

	AudioParameterFloat* filterOrder;

	AudioParameterChoice* filterType;
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessor)

};


#endif  // PLUGINPROCESSOR_H_INCLUDED
