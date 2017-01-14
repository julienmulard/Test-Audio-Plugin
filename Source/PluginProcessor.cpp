/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

	addParameter(cutoff = new AudioParameterFloat("cutoff", "Cutoff", NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.2f), 1000.0f));
	addParameter(reso = new AudioParameterFloat("reso", "Resonnance", NormalisableRange<float>(0.5f, 3.0f, 0.0f), 0.5f));
	
	StringArray filterTypeList = { "Low Pass Filter", "High Pass Filter", "Notch Filter", "Band Pass Filter (gain = Q)", "Band Pass Filter (fixed gain)" };

	addParameter(filterType = new AudioParameterChoice("filterType", "FilterType", filterTypeList ,0));

	//LowPassFilter[0] = MyLowPassFilter(*cutoff, *reso, 44100);
	//LowPassFilter[1] = MyLowPassFilter(*cutoff, *reso, 44100);

	//HighPassFilter[0] = MyHighPassFilter(*cutoff, *reso, 44100);
	//HighPassFilter[1] = MyHighPassFilter(*cutoff, *reso, 44100);

	//NotchFilter[0] = MyNotchFilter(*cutoff, *reso, 44100);
	//NotchFilter[1] = MyNotchFilter(*cutoff, *reso, 44100);

	//BandPassFilter1[0] = MyBandPassFilter1(*cutoff, *reso, 44100);
	//BandPassFilter1[1] = MyBandPassFilter1(*cutoff, *reso, 44100);

	//BandPassFilter2[0] = MyBandPassFilter2(*cutoff, *reso, 44100);
	//BandPassFilter2[1] = MyBandPassFilter2(*cutoff, *reso, 44100);

	Filters = new MyFilter*[kNumFilterTypes*2];
	



	Filters[kLowPass*2] = new MyLowPassFilter(*cutoff, *reso, 44100);
	Filters[kLowPass*2+1] =new MyLowPassFilter(*cutoff, *reso, 44100);
	Filters[kHighPass*2] = new MyHighPassFilter(*cutoff, *reso, 44100);
	Filters[kHighPass*2+1] =new MyHighPassFilter(*cutoff, *reso, 44100);
	Filters[kNotch*2] =new MyNotchFilter(*cutoff, *reso, 44100);
	Filters[kNotch*2+1] =new MyNotchFilter(*cutoff, *reso, 44100);
	Filters[kBandPass1*2] = new MyBandPassFilter1(*cutoff, *reso, 44100);
	Filters[kBandPass1*2+1] =new MyBandPassFilter1(*cutoff, *reso, 44100);
	Filters[kBandPass2*2] =new MyBandPassFilter2(*cutoff, *reso, 44100);
	Filters[kBandPass2*2+1] =new MyBandPassFilter2(*cutoff, *reso, 44100);

	frequencyResponse = { 0 };
	
	float log_start = log(20);
	float log_stop = log(22049);
	float step = exp((log_stop - log_start)*0.01);	
	frequencies.add(20);
	for (int i = 1; i < 100; i++) {
		frequencies.add(frequencies[i-1]*step);

	}
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
	for (int i = 0; i < kNumFilterTypes * 2; i++) 
	{
		delete Filters[i];
	}
	delete[] Filters;
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return String();
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	/*LowPassFilter[0].setSampleRate(float(sampleRate));
	LowPassFilter[1].setSampleRate(float(sampleRate));

	HighPassFilter[0].setSampleRate(float(sampleRate));
	HighPassFilter[1].setSampleRate(float(sampleRate));
	
	NotchFilter[0].setSampleRate(float(sampleRate));
	NotchFilter[1].setSampleRate(float(sampleRate));*/

	for (int i = 0; i < kNumFilterTypes; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Filters[i*2+j]->setSampleRate(sampleRate);
		}
	}
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void NewProjectAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
 /*   for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

		for (int inputSample = 0; inputSample < buffer.getNumSamples(); inputSample++)
		{
			LowPassFilter[channel].setFilter(*cutoff, *reso);
			channelData[inputSample] = LowPassFilter[channel].filter(channelData[inputSample]);
		}
    }*/

	for (int inputSample = 0; inputSample < buffer.getNumSamples(); inputSample++)
	{
		for (int channel = 0; channel < totalNumInputChannels; ++channel)
		{

			float* channelData = buffer.getWritePointer(channel);

			Filters[filterType->getIndex()*2+channel]->setFilter(*cutoff, *reso);
			channelData[inputSample] = Filters[filterType->getIndex()*2+channel]->filter(channelData[inputSample]);

			//if (filterType->getIndex() == kLowPass) {
			//	LowPassFilter[channel].setFilter(*cutoff, *reso);
			//	channelData[inputSample] = LowPassFilter[channel].filter(channelData[inputSample]);
			//}
			//else if (filterType->getIndex() == 1) {
			//	HighPassFilter[channel].setFilter(*cutoff, *reso);
			//	channelData[inputSample] = HighPassFilter[channel].filter(channelData[inputSample]);

			//}
			//else if (filterType->getIndex() == 2) {
			//	NotchFilter[channel].setFilter(*cutoff, *reso);
			//	channelData[inputSample] = NotchFilter[channel].filter(channelData[inputSample]);

			//}
			//else if (filterType->getIndex() == 3) {
			//	BandPassFilter1[channel].setFilter(*cutoff, *reso);
			//	channelData[inputSample] = BandPassFilter1[channel].filter(channelData[inputSample]);

			//}
			//else if (filterType->getIndex() == 4) {
			//	BandPassFilter2[channel].setFilter(*cutoff, *reso);
			//	channelData[inputSample] = BandPassFilter2[channel].filter(channelData[inputSample]);

			//}
		}
	}

}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}

Array<float> NewProjectAudioProcessor::getFrequencyResponse()
{
	frequencyResponse.clearQuick();

	for (int i = 0; i < frequencies.size(); i++)
	{
		frequencyResponse.add(Filters[filterType->getIndex()*2]->getFreqencyResponse(frequencies[i]));
	}


	//if (filterType->getIndex() == 0) 
	//{
	//	for (int i =0; i<frequencies.size(); i++)
	//	{
	//		frequencyResponse.add(LowPassFilter[0].getFreqencyResponse(frequencies[i]));
	//	}
	//}
	//else if (filterType->getIndex() == 1)
	//{
	//	for (int i = 0; i<frequencies.size(); i++)
	//	{
	//		frequencyResponse.add(HighPassFilter[0].getFreqencyResponse(frequencies[i]));
	//	}
	//}
	//else if (filterType->getIndex() == 2)
	//{
	//	for (int i = 0; i<frequencies.size(); i++)
	//	{
	//		frequencyResponse.add(NotchFilter[0].getFreqencyResponse(frequencies[i]));
	//	}
	//}
	//else if (filterType->getIndex() == 3)
	//{
	//	for (int i = 0; i<frequencies.size(); i++)
	//	{
	//		frequencyResponse.add(BandPassFilter1[0].getFreqencyResponse(frequencies[i]));
	//	}
	//}
	//else if (filterType->getIndex() == 4)
	//{
	//	for (int i = 0; i<frequencies.size(); i++)
	//	{
	//		frequencyResponse.add(BandPassFilter2[0].getFreqencyResponse(frequencies[i]));
	//	}
	//}
		
	return frequencyResponse;
}