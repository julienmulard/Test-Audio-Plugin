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
	// Creation des paramètres.
	// Pour que tout fonctionne convenablement quand on rajoute un paramètre, il faut:
	// 1 - Déclarer les paramètres float avant les autres types de paramètres.
	// 2 - Ajouter une valeur correspondant à norte paramètre dans l'enum qui va bien (voir .h) EN RESPECTANT LE MÊME ORDRE 
	//entre le constructeur et l'enum (sinon, on ne s'y retrouve pas)
	// 3 - Faire en sorte que le paramètre fasse des trucs (mais, ça t'es grand, je te fais confiance)
	// Note: soit AudioParameterFloat * param, on accède à la valeur directement avec *param 
	
	//Paramètres float
	addParameter(cutoff = new AudioParameterFloat("cutoff", "Cutoff", NormalisableRange<float>(20.0f, 22000.0f, 0.0f, 0.2f), 1000.0f));
	addParameter(reso = new AudioParameterFloat("reso", "Resonnance", NormalisableRange<float>(0.5f, 3.0f, 0.0f), 0.5f));
	addParameter(filterOrder = new AudioParameterFloat("filterOrder", "Filter Order", NormalisableRange<float>(1.0f, 4.0f, 1.0f), 1.0f));
	addParameter(feedbackGain = new AudioParameterFloat("feedbackGain", "Feedback Gain", NormalisableRange<float>(-0.99f, 0.99f, 0.0f), 0.0f));

	//Paramètres à choix multiple
	StringArray filterTypeList = { "Low Pass Filter", "High Pass Filter", "Notch Filter", "Band Pass Filter (gain = Q)", "Band Pass Filter (fixed gain)", "IIR Comb Filter"};
	addParameter(filterType = new AudioParameterChoice("filterType", "FilterType", filterTypeList ,0));

	//Initialisation des filtres
	//Pour accéder à un filtre, il faut donner: 
	// - son type (passe bas, notch, comb, etc...)
	// - son ordre (on se sert de cette dimension pour facilement mettre des filtres en cascade)
	// - son canal audio
	//et on obtient un pointeur vers le filtre qui va bien.
	Filters = new MyFilter***[kNumFilterTypes];
	
	for (int type = 0; type < kNumFilterTypes; type++) {
		Filters[type] = new MyFilter**[maxFilterOrder];

		for (int order = 0; order < maxFilterOrder; order++)
		{
			Filters[type][order] = new MyFilter*[2];
			switch(type)
			{
				case kLowPass:
					Filters[type][order][0] = new MyLowPassFilter(*cutoff, *reso, 44100);
					Filters[type][order][1] = new MyLowPassFilter(*cutoff, *reso, 44100);
					break;

				case kHighPass:
					Filters[type][order][0] = new MyHighPassFilter(*cutoff, *reso, 44100);
					Filters[type][order][1] = new MyHighPassFilter(*cutoff, *reso, 44100);
					break;

				case kNotch:
					Filters[type][order][0] = new MyNotchFilter(*cutoff, *reso, 44100);
					Filters[type][order][1] = new MyNotchFilter(*cutoff, *reso, 44100);
					break;

				case kBandPass1:
					Filters[type][order][0] = new MyBandPassFilter1(*cutoff, *reso, 44100);
					Filters[type][order][1] = new MyBandPassFilter1(*cutoff, *reso, 44100);
					break;

				case kBandPass2:
					Filters[type][order][0] = new MyBandPassFilter2(*cutoff, *reso, 44100);
					Filters[type][order][1] = new MyBandPassFilter2(*cutoff, *reso, 44100);
					break;

				case kComb:
					Filters[type][order][0] = new MyCombFilter(*cutoff, *feedbackGain, 44100);
					Filters[type][order][1] = new MyCombFilter(*cutoff, *feedbackGain, 44100);
					break;
			}
		}

	}

	//On crée le vecteur qui va contenir les fréquences des points de mesures de notre spectre d'amplitude.
	//On utilise un pas exponentiel pour avoir un répartition linéairement espacée sur une échelle log.
	frequencyResponse = { 0 };
	
	int num_point = 1000;

	float log_start = log(20);
	float log_stop = log(22049);
	float step = exp((log_stop - log_start)*1/float(num_point));	
	frequencies.add(20);
	for (int i = 1; i < num_point; i++) {
		frequencies.add(frequencies[i-1]*step);

	}
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
	
	//Destruciton de notre ****Filters :)
	for (int type = 0; type < kNumFilterTypes; type++) 
	{
		for (int order = 0; order < maxFilterOrder; order++)
		{
			for (int channel = 0; channel < 2; channel++)
			{
				delete Filters[type][order][channel];
			}
			delete[] Filters[type][order];
		}
		delete[] Filters[type];
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
	
	//On initialise tous les filtres à la bonne fréquence d'échantillonnage
	for (int type = 0; type < kNumFilterTypes; type++)
	{
		for (int order = 0; order < maxFilterOrder; order++)
		{
			for (int channel = 0; channel < 2; channel++)
			{
				Filters[type][order][channel]->setSampleRate(sampleRate);
			}
		}
	}
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

	//TODO:
	//Il faudrait peut-être rajouter un nettoyage de la mémoire du filtre Comb (et des autres mémoires en fait) 
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

	//C'est ici qu'on filtre
	for (int inputSample = 0; inputSample < buffer.getNumSamples(); inputSample++)
	{
		for (int channel = 0; channel < totalNumInputChannels; ++channel)
		{
			//On récupère le buffer d'entrée dans lequel on va écrire (il entre et on le ressort une fois modifié)
			float* channelData = buffer.getWritePointer(channel);

			for (int order = 0; order < int(*filterOrder); order++)
			{
				//Si on a un filtre qui prend en param fc et Q (les filtres biquadratiques classiques)
				if (filterType->getIndex() != kComb)
				{
					//On update le filtre avec les bons paramètres
					Filters[filterType->getIndex()][order][channel]->setFilter(*cutoff, *reso);
					
					//On filtre les données
					channelData[inputSample] = Filters[filterType->getIndex()][order][channel]->filter(channelData[inputSample]);
				}
				
				//Si on a un filtre qui prend en param fc et un feedback (les filtres en peigne)
				else
				{
					//On update le filtre avec les bons paramètres
					Filters[filterType->getIndex()][order][channel]->setFilter(*cutoff, *feedbackGain);

					//On filtre les données
					channelData[inputSample] = Filters[filterType->getIndex()][order][channel]->filter(channelData[inputSample]);
					
				}			
			}
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
	//Cette fonction calcule le spectre d'amplitude du filtre en cours, pour chaque fréquence contenue dans le vecteur "frequencies"
	frequencyResponse.clearQuick();

	for (int i = 0; i < frequencies.size(); i++)
	{
		frequencyResponse.add(Filters[filterType->getIndex()][0][0]->getFrequencyResponse(frequencies[i],int(*filterOrder)));
	}

	return frequencyResponse;
}

void NewProjectAudioProcessor::refreshFilterForDisplay()
{
	//Cette fonction met à jour le filtre en cours pour pouvoir tracer le bon spectre d'amplitude lors d'un changement de paramètre.
	if (filterType->getIndex() != kComb)
	{
		for (int order = 0; order < int(*filterOrder); order++)
		{
			Filters[filterType->getIndex()][order][0]->setFilter(*cutoff, *reso);
		}
	}
	else
	{
		for (int order = 0; order < int(*filterOrder); order++)
		{
			Filters[filterType->getIndex()][order][0]->setFilter(*cutoff, *feedbackGain);
		}
	}
}