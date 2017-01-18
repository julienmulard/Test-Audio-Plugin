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
#include "MyCombFilter.h"
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

	//==============================================================================
	
	//enum des diff�rents param�tres du filtre, � mettre � jour si on rajoute un param�tre (attention � l'ordre!)
	enum paramIndex {kCutoff = 0, kReso, kFilterOrder, kFeedbackGain, kFilterType};

	//enum des diff�rents types de filtres, � mettre � jour si on rajoute un nouveau filtre (attention � l'ordre!)
	enum filterTypeIndex { kLowPass = 0, kHighPass, kNotch, kBandPass1, kBandPass2, kComb , kNumFilterTypes };

	//Vecteur des fr�quences auxquelles on mesure le spectre d'amplitude
	Array<float> frequencies;

	//Vecteur des amplitudes du spectre d'amplitude (fonctionne de paire avec "frequencies")
	Array<float> frequencyResponse;
	
	//Fonction qui calcule le spectre d'amplitude du filtre.
	Array<float> getFrequencyResponse();

	//Fonction qui met � jour le filtre pour pouvoir tracer le spectre d'amplitude le plus pr�cisement possible.
	void refreshFilterForDisplay();

private:

	const int maxFilterOrder = 4;

	//Un tableau de pointeurs de filtres, rang�s par type, ordre et canal audio;
	MyFilter **** Filters;

	//Les param�tres du plugin, avec en premier lieux les param�tres flotant, puis le reste.
	AudioParameterFloat* cutoff;
	AudioParameterFloat* reso;
	AudioParameterFloat* filterOrder;
	AudioParameterFloat* feedbackGain;

	AudioParameterChoice* filterType;
    //==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessor)

};


#endif  // PLUGINPROCESSOR_H_INCLUDED
